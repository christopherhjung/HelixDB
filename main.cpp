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
#include "defs.h"
#include "DiskManager.h"
#include "BufferPoolImpl.h"
#include "MainFrame.h"
#include "Allocator.h"
#include "PageDirectory.h"
#include "SlotDirectory.h"

u64 filesize(const char* filename)
{
    std::ifstream in(filename, std::ifstream::ate | std::ifstream::binary);
    return in.tellg();
}


struct ClassEntry{
    u32 entriesPageId;
    u32 propertiesPageId;
};

struct Instance{
    u32 key;
    u32 value;
};

int main () {

    bool init = true;
    auto *diskManager = new DiskManager("test.db");
    auto *bufferPool = new BufferPoolImpl(diskManager, 8);
    u32 size = diskManager->getSize();
    Frame* frame = bufferPool->fetch(0);
    MainFrame* mainFrame = frame->asMainFrame();

    if(size == 0){
        mainFrame->init();
    }

    auto *allocator = new Allocator(bufferPool, mainFrame);

    if(size == 0){
        Frame *testFrame = allocator->allocPage();
        mainFrame->set(12, testFrame->getPageId());
        testFrame->close();
    }

    u32 pdPage = mainFrame->get<u32>(12);
    Frame *pdFrame = allocator->fetch(pdPage);

    auto *types = new SlotDirectory<ClassEntry>(allocator, pdFrame);

    ClassEntry classEntry{};

    if(size == 0){
        classEntry.entriesPageId = allocator->allocPageId();
        classEntry.propertiesPageId = allocator->allocPageId();
        types->set(0, classEntry);
    }

    types->get(0, classEntry);

    std::cout << classEntry.entriesPageId << std::endl;
    std::cout << classEntry.propertiesPageId << std::endl;

    Frame *entriesFrame = allocator->fetch(classEntry.entriesPageId);
    auto *entriesDirectory = new SlotDirectory<Instance>(allocator, entriesFrame);

    Instance instance;
    instance.key = 22;
    instance.value = 99;
    entriesDirectory->set(0, instance);


    std::cout << mainFrame->getPageCount() << std::endl;
    std::cout << diskManager->getSize() << std::endl;



    return 0;
}
