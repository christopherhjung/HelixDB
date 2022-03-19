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

u64 filesize(const char* filename)
{
    std::ifstream in(filename, std::ifstream::ate | std::ifstream::binary);
    return in.tellg();
}

struct DBMain{
    u32 freePages;
    u32 usedPageSize;
    u32 classArray;
};

#define FREE_PAGE_QUEUE_SIZE 10
#define BUFFER_SIZE 8







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


    PageDirectory *pageDirectory = new PageDirectory(allocator, pdFrame);

    if(size == 0){
        pageDirectory->set(0, 111);
        pageDirectory->set(92838, 222);
    }

    std::cout << pageDirectory->get<u32>(0) << std::endl;
    std::cout << pageDirectory->get<u32>(92838) << std::endl;


    std::cout << mainFrame->getPageCount() << std::endl;
    std::cout << diskManager->getSize() << std::endl;



    //auto mainPage = pool->fetch(0);


/*
    auto *arrayList = new ArrayList(pool, mainPage->classArray);

    if(init){
        arrayList->set(0, 1111);
        arrayList->set(1, 2222);
    }

    u64 value = arrayList->get(0);
    u64 value2 = arrayList->get(1);
    std::cout << test << " " << value << " " << value2;

    diskManager->close();*/
/*
    u32 frameId = pool->fetch(0);

    byte* page = pool->getContent(frameId);


    page[0] = 77;

    pool->flush(0);

    page[0] = 1;

    pool->refresh(0);
    std::cout << (int)page[0];

    pool->free(frameId);*/
/*
    u32 result;
    bool success = pageDirectory->lookup(0, &result);
    std::cout << success << " " << result;
*/
/*    u64 size = filesize(db);


    myfile.write(test, BLOCK_SIZE);
*/

    return 0;
}
