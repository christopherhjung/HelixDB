#include <iostream>

#include <iostream>
#include <fstream>
#include <filesystem>
#include <fstream>
#include <bitset>
#include <iostream>
#include <filesystem>
#include <stdio.h>
#include <random>
#include <iostream>
#include <string.h>
#include <mutex>  // NOLINT
#include <string>
#include <thread>  // NOLINT
#include <chrono>
#include "DiskManager.h"
#include "BufferPoolImpl.h"
#include "MainFrame.h"
#include "Allocator.h"
#include "PageDirectory.h"
#include "SlotDirectory.h"
#include "ClassCollectionHeader.h"
#include "defs.h"

using namespace std::chrono;

struct ClassEntry{
    u32 entriesPageId;
    u32 propertiesPageId;
    u32 propertyCount;
    u32 entryCount;
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
        bufferPool = new BufferPoolImpl(diskManager, 32);
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
        classCollectionHeaderFrame->close(false);
        classRootFrame->close();
    }

    bool isInit(){
        return init;
    }

    void shutdown(){
        nameFrame->close();
        mainFrame->close();
        delete classDirectory;
        bufferPool->shutdown();
        delete allocator;
    }

    void addName(const std::string& name, u32 index){
        keyValues[currentValue++].set(name, index);
    }

    i32 findName( const std::string& name, bool shallExist = true){
        for(int i = 0 ; i < 20 ; i++){
            if(strcmp(keyValues[i].name, name.c_str()) == 0){
                return keyValues[i].index;
            }
        }

        if(shallExist){
            error("Name not found: " + name);
        }else{
            return -1;
        }
    }

    u32 createClass(const std::string& name){
        u32 classIndex = classCount++;
        Frame* frame = classDirectory->fetchFrame(classIndex, true);
        auto *classEntry = frame->map<ClassEntry>() + classIndex;
        classEntry->entriesPageId = allocator->allocPageId();
        classEntry->propertiesPageId = allocator->allocPageId();
        classEntry->propertyCount = 0;
        addName(name, classIndex);
        frame->close();
        return classIndex;
    }

    ClassEntry getClass(const std::string& name){
        return getClass(findName(name));
    }

    bool exists(const std::string& name){
        return findName(name, false) >= 0;
    };

    ClassEntry getClass(u32 classId){
        ClassEntry classEntry{};
        classController.get(classDirectory, classId, &classEntry);
        return classEntry;
    }

    u32 createProperty(const std::string&  className, const std::string& propertyName, u16 byteWidth){
        return addProperty(findName(className), propertyName, byteWidth);
    }

    u32 addProperty(u32 classId, const std::string& propertyName, u16 byteWidth){
        Frame *classFrame = classController.fetchFrame(classDirectory, classId);// classDirectory->fetchFrame(classId);

        ClassEntry *classEntry = classController.map<ClassEntry>(classFrame, classId);

        Frame *propertiesRootFrame = allocator->fetch(classEntry->propertiesPageId);
        PageDirectory propertiesDirectory(allocator, propertiesRootFrame); //props per class
        propertiesRootFrame->close();

        u32 propertyId = classEntry->propertyCount++;

        PropertyEntry propertyFrame{
            .valueRootPage = allocator->allocPageId(),
            .byteWidth = byteWidth
        };

        addName(propertyName, propertyId);
        propertyController.set(&propertiesDirectory, propertyId, &propertyFrame);

        classFrame->close();
        return propertyId;
    }

    Frame *getPropertyFrame(u32 classId, u32 propertyId){
        ClassEntry classEntry = getClass(classId);

        Frame *propertiesRootFrame = allocator->fetch(classEntry.propertiesPageId);
        PageDirectory propertiesDirectory(allocator, propertiesRootFrame); //props per class
        propertiesRootFrame->close();

        return propertyController.fetchFrame(&propertiesDirectory, propertyId);
    }

    PropertyEntry getProperty(const std::string&  className, const std::string& propertyName){
        u32 classId = findName(className);
        ClassEntry classEntry = getClass(classId);

        Frame *propertiesRootFrame = allocator->fetch(classEntry.propertiesPageId);
        PageDirectory propertiesDirectory(allocator, propertiesRootFrame); //props per class
        propertiesRootFrame->close();

        u32 propertyId = findName(className);

        PropertyEntry propertyFrame{};
        Frame* frame = propertiesDirectory.fetchFrame(propertyId);
        propertyController.get(frame, propertyId, &propertyFrame);
        frame->close(false);
        return propertyFrame;
    }


    u64 createInstance(const std::string& name){
        return createInstance(findName(name));
    }

    u64 createInstance(u32 classId){
        Frame *classFrame = classController.fetchFrame(classDirectory, classId);// classDirectory->fetchFrame(classId);

        auto *classEntry = classController.map<ClassEntry>(classFrame, classId);

        Frame *entriesRootFrame = allocator->fetch(classEntry->entriesPageId);
        PageDirectory entriesDirectory(allocator, entriesRootFrame); //instances
        entriesRootFrame->close();

        u32 instanceIndex = classEntry->entryCount;
        auto *instancesFrame = instanceController.fetchFrame(&entriesDirectory, instanceIndex, true);

        InstanceEntry instance{};
        InstanceHeader header{};

        instanceController.getHeader(instancesFrame, &header);


        if(header.count == 0){
            header.classId = classId; //init header
        }

        classEntry->entryCount++;

        instance.propertyOffset = instanceIndex;
        instanceController.set(instancesFrame, instanceIndex, &instance);
        instanceController.setHeader(instancesFrame, &header);
        instancesFrame->close();
        classFrame->close();
        return classify(instanceIndex, classId);
    }

    PropertyEntry getPropertyEntry(u64 instanceId, u32 propertyId){
        u32 classId = instanceId >> 32;
        Frame *propertyFrame = getPropertyFrame(classId, propertyId);

        PropertyEntry propertyEntry;
        propertyController.get(propertyFrame, propertyId, &propertyEntry);
        propertyFrame->close();

        return propertyEntry;
    }

    void applyPropertyValue(u64 instanceId, u32 propertyId, void* value, u8 operation){
        PropertyEntry propertyEntry = getPropertyEntry(instanceId, propertyId);
        Frame *propertyValueRootFrame = allocator->fetch(propertyEntry.valueRootPage, false);
        check(propertyValueRootFrame, "ValueFrame not found");
        PageDirectory pageDirectory(allocator, propertyValueRootFrame); //prop values
        propertyValueRootFrame->close();
        SlotController controller(0, propertyEntry.byteWidth);
        u32 offset = instanceId & 0xffffffff;
        controller.apply(&pageDirectory, offset, value, operation);
    }

    void setPropertyValue(u64 instanceId, const std::string& propertyName, void* value){
        setPropertyValue(instanceId, findName(propertyName), value);
    }

    void setPropertyValue(u64 instanceId, u32 propertyId, void* value){
        applyPropertyValue(instanceId, propertyId, value, SET);
    }

    u64 classify(u32 instanceId, const std::string& className){
        return classify(((u64) findName(className)) << 32, instanceId);
    }

    static u64 classify(u32 instanceId, u32 classId){
        return classId | (instanceId & 0xffffffff);
    }

    void getPropertyValue( u32 instanceId, const std::string& className, const std::string& propertyName, void* value){
        getPropertyValue(classify(instanceId, className), propertyName, value);
    }

    void getPropertyValue( u64 instanceId, const std::string& propertyName, void* value){
        getPropertyValue(instanceId, findName(propertyName), value);
    }

    void getPropertyValue( u64 instanceId, u32 propertyId, void* value){
        applyPropertyValue(instanceId, propertyId, value, GET);
    }

    u32 getSize(){
        return diskManager->getSize();
    }

    u32 getPageCount(){
        return mainFrame->getPageCount();
    }
};

int setProp = 0;
int createInstance = 0;

void test(DB *db){
    std::default_random_engine dev(0);
    std::uniform_int_distribution<int> dist(1, 99999999);
    std::uniform_int_distribution<int> dist2(1, 32563242);

    debugCounter = &createInstance;
    u64 startInstance = 0;
    int size = 1000000;

    auto start = high_resolution_clock::now();

    u32 classId = db->findName("User");
    u32 propertyId = db->findName("amount");
    u32 hashId = db->findName("hash");
    for(int i = 0 ; i < size ; i++){
        u32 number = dist(dev);

        u64 instance = db->createInstance(classId);

        if(i == 0){
            startInstance = instance;
        }

        debugCounter = &setProp;
        db->setPropertyValue(instance, propertyId, &number);

        u32 number2 = dist2(dev);
        db->setPropertyValue(instance, hashId, &number2);

        debugCounter = &createInstance;
    }

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);

    std::cout << "MILLIS: "<< duration.count() << std::endl;

    std::cout << "setProp:" << setProp << std::endl;
    std::cout << "createInstance:" << createInstance << std::endl;

    dev.seed(0);

    for(int i = 0 ; i < size ; i++){
        u32 number = dist(dev);

        u64 instanceClassified = db->classify(i + startInstance, "User");
        u32 value = 0;
        db->getPropertyValue(instanceClassified, "amount", &value);
        check(value == number, "Test fehler at index:" + std::to_string(i) + " " + std::to_string(value) + " != " +
                               std::to_string(number));

        value = 0;
        db->getPropertyValue(instanceClassified, "hash", &value);

        u32 number2 = dist2(dev);
        check(value == number2, "Test fehler at index:" + std::to_string(i) + " " + std::to_string(value) + " != " +
                                std::to_string(number2));
    }

    PropertyEntry propertyEntry = db->getProperty("User", "amount");
    std::cout << "offset:" << startInstance + size << std::endl;
    std::cout << propertyEntry.byteWidth << std::endl;

    std::cout << "Page count:" << db->getPageCount() << std::endl;
    std::cout << "Size:" << db->getSize() << std::endl;
}

void create(DB *db){
    if(!db->exists("User")){
        db->createClass("User");
        db->createProperty("User", "amount", 4);
        db->createProperty("User", "hash", 4);
    }
}

void fetch(DB *db, u32 index){
    u32 value = 0;
    u64 instance = DB::classify(index, db->findName("User"));
    db->getPropertyValue(instance, "amount", &value);

    std::cout << "Value:" << value << std::endl;
}

int main () {
    auto start = high_resolution_clock::now();
    DB *db = new DB("test.db");

    create(db);
    test(db);

    //fetch(db, 10000000);

    db->shutdown();


    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);

    std::cout << "OVERALL RUNTIME: "<< duration.count() << std::endl;
    return 0;
}
