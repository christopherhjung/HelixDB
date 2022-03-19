#include <iostream>

#include <iostream>
#include <fstream>
#include <filesystem>
#include <fstream>
#include <bitset>
#include <iostream>
#include <filesystem>
#include <stdio.h>
#include <string.h>
#include <mutex>  // NOLINT
#include <string>
#include <thread>  // NOLINT
#include "DiskManager.h"
#include "BufferPoolImpl.h"
#include "MainFrame.h"
#include "Allocator.h"
#include "PageDirectory.h"
#include "SlotDirectory.h"
#include "ClassCollectionHeader.h"
#include "defs.h"

struct ClassEntry{
    u32 entriesPageId;
    u32 propertiesPageId;
    u32 propertyCount;
};

struct InstanceHeader{
    u32 classId;
    u32 super;
    u32 count;
};

struct InstanceEntry{
    u32 propertyOffset;
};

struct PropertyEntry{
    u32 valueRootPage;
    u16 byteWidth;
};

struct KeyValue{
    i8 name[28];
    u32 index;

    void set(const std::string& name, u32 index){
        memcpy(this->name, name.c_str(), name.length() + 1);
        this->index = index;
    }
};



class DB{
    bool init;
    DiskManager* diskManager;
    BufferPool *bufferPool;
    Allocator *allocator;

    MainFrame* mainFrame;
    Frame *nameFrame;

    u32 classCount;
    PageDirectory *classDirectory;

    SlotController propertyController{0, sizeof(PropertyEntry)};
    SlotController classController{0, sizeof(ClassEntry)};
    SlotController instanceController{sizeof(InstanceHeader), sizeof(InstanceEntry)};

    KeyValue *keyValues = nullptr;
    u32 currentValue = 0;
public:
    DB(const std::string& fileName){
        diskManager = new DiskManager(fileName);
        bufferPool = new BufferPoolImpl(diskManager, 16);
        u32 size = diskManager->getSize();
        init = size == 0;
        Frame* frame = bufferPool->fetch(0);
        mainFrame = frame->asMainFrame();

        if(init){
            mainFrame->init();
        }

        allocator = new Allocator(bufferPool, mainFrame);

        if(init){
            mainFrame->setClassPage(allocator->allocPageId());
            mainFrame->setNamePage(allocator->allocPageId());
        }

        nameFrame = mainFrame->getNameFrame();
        keyValues = (KeyValue*)nameFrame->getData();

        ClassCollectionHeader *classCollectionHeaderFrame = mainFrame->getClassRootFrame()->asClassCollectionHeader();

        if(init){
            classCollectionHeaderFrame->init(allocator);
        }

        classCount = classCollectionHeaderFrame->getClassCount();
        Frame *classRootFrame = classCollectionHeaderFrame->getPageDirectoryFrame();
        classDirectory = new PageDirectory(allocator, classRootFrame); //classes
    }

    bool isInit(){
        return init;
    }

    void shutdown(){
        nameFrame->flush();
        mainFrame->flush();
    }

    void addName(const std::string& name, u32 index){
        keyValues[currentValue++].set(name, index);
    }

    u32 findName( const std::string& name){
        for(int i = 0 ; i < 20 ; i++){
            if(strcmp(keyValues[i].name, name.c_str()) == 0){
                return keyValues[i].index;
            }
        }

        error("Name not found: " + name);
    }

    u32 addClass(const std::string& name){
        ClassEntry classEntry{};
        u32 classIndex = classCount++;
        classEntry.entriesPageId = allocator->allocPageId();
        classEntry.propertiesPageId = allocator->allocPageId();
        classEntry.propertyCount = 0;
        addName(name, classIndex);
        classDirectory->set(classIndex, classEntry);
        return classIndex;
    }

    ClassEntry getClass(const std::string& name){
        return getClass(findName(name));
    }

    ClassEntry getClass(u32 classId){
        ClassEntry classEntry{};
        classController.get(classDirectory, classId, classEntry);
        return classEntry;
    }

    u32 addProperty(const std::string&  className, const std::string& propertyName, u16 byteWidth){
        u32 classId = findName(className);
        Frame *classFrame = classDirectory->fetchFrame(classId);
        ClassEntry classEntry{};
        classFrame->get(classId, &classEntry);

        Frame *propertiesRootFrame = allocator->fetch(classEntry.propertiesPageId);
        PageDirectory propertiesDirectory(allocator, propertiesRootFrame); //props per class

        u32 propertyId = classEntry.propertyCount++;

        PropertyEntry propertyFrame{};
        propertyFrame.valueRootPage = allocator->allocPageId();
        propertyFrame.byteWidth = byteWidth;

        addName(propertyName, propertyId);
        propertiesDirectory.set(propertyId, propertyFrame);

        classFrame->flush();
        classFrame->close();
        return propertyId;
    }

    Frame *getPropertyFrame(u32 classId, u32 propertyId){
        ClassEntry classEntry = getClass(classId);

        Frame *propertiesRootFrame = allocator->fetch(classEntry.propertiesPageId);
        PageDirectory propertiesDirectory(allocator, propertiesRootFrame); //props per class

        return propertyController.fetchFrame(&propertiesDirectory, propertyId);
    }

    PropertyEntry getProperty(const std::string&  className, const std::string& propertyName){
        u32 classId = findName(className);
        ClassEntry classEntry = getClass(classId);

        Frame *propertiesRootFrame = allocator->fetch(classEntry.propertiesPageId);
        auto *propertiesDirectory = new PageDirectory(allocator, propertiesRootFrame); //props per class

        u32 propertyId = findName(className);

        PropertyEntry propertyFrame{};
        Frame* frame = propertiesDirectory->fetchFrame(propertyId);
        propertyController.get(frame, propertyId, propertyFrame);
        return propertyFrame;
    }

    u64 createInstance(const std::string& name){
        u32 classId = findName(name);
        ClassEntry classEntry = getClass(classId);

        Frame *entriesRootFrame = allocator->fetch(classEntry.entriesPageId);
        PageDirectory entriesDirectory(allocator, entriesRootFrame); //instances

        auto *instancesFrame = entriesDirectory.fetchFrame(0, true);

        InstanceEntry instance{};
        InstanceHeader header{};

        instanceController.getHeader(instancesFrame, header);

        u32 instanceIndex = header.count;

        if(header.count == 0){
            header.classId = classId; //init header
            header.count = 1;
        }else{
            header.count++;
        }

        instance.propertyOffset = instanceIndex;
        entriesDirectory.set(instanceIndex, instance);
        instanceController.setHeader(instancesFrame, header);
        return ((u64)classId << 32) | instanceIndex;
    }

    PropertyEntry getPropertyEntry(u64 instanceId, u32 propertyId){
        u32 classId = instanceId >> 32;
        Frame *propertyFrame = getPropertyFrame(classId, propertyId);

        PropertyEntry propertyEntry;
        propertyController.get(propertyFrame, propertyId, propertyEntry);
        propertyFrame->flush();

        return propertyEntry;
    }

    void applyPropertyValue(u64 instanceId, const std::string& propertyName, u64& value, u8 operation){
        u32 propertyId = findName(propertyName);
        PropertyEntry propertyEntry = getPropertyEntry(instanceId, propertyId);
        u32 offset = instanceId & 0xffffffff;
        Frame *propertyValueRootFrame = allocator->fetch(propertyEntry.valueRootPage);
        PageDirectory pageDirectory(allocator, propertyValueRootFrame); //prop values
        SlotController controller(0, propertyEntry.byteWidth * 8);

        controller.apply(&pageDirectory, offset, value, operation);

        propertyValueRootFrame->close();
    }

    void setPropertyValue(u64 instanceId, const std::string& propertyName, u64 value){
        applyPropertyValue(instanceId, propertyName, value, SET);
    }

    u64 classify(u32 instanceId, const std::string& className){
        return (((u64) findName(className)) << 32) | (instanceId & 0xffffffff);
    }

    u64 getPropertyValue( u32 instanceId, const std::string& className, const std::string& propertyName){
        return getPropertyValue(classify(instanceId, className), propertyName);
    }

    u64 getPropertyValue( u64 instanceId, const std::string& propertyName){
        u64 value;
        applyPropertyValue(instanceId, propertyName, value, GET);
        return value;
    }

    u32 getSize(){
        return diskManager->getSize();
    }

    u32 getPageCount(){
        return mainFrame->getPageCount();
    }
};

int main () {

    DB *db = new DB("test.db");

    if(db->isInit()){
        u64 classIndex = db->addClass("User");
        std::cout << classIndex << std::endl;
    }

    ClassEntry classEntry = db->getClass("User");

    if(db->isInit()){
        db->addProperty("User", "amount", 32);
    }

    PropertyEntry propertyEntry = db->getProperty("User", "amount");

    u64 instance = db->createInstance("User");

    db->setPropertyValue(instance, "amount", 955);

    u64 instanceClassified = db->classify(instance, "User");
    u64 value = db->getPropertyValue(instanceClassified, "amount");

    std::cout << "offset:" << instance << std::endl;
    std::cout << "value:" << value << std::endl;
    std::cout << propertyEntry.byteWidth << std::endl;
    std::cout << classEntry.entriesPageId << std::endl;
    std::cout << classEntry.propertiesPageId << std::endl;
    db->shutdown();

    std::cout << "Page count:" << db->getPageCount() << std::endl;
    std::cout << "Size:" << db->getSize() << std::endl;
    return 0;
}
