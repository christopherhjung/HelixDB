#include <iostream>

#include <cassert>
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

typedef unsigned long u64;
typedef unsigned int u32;
typedef unsigned int i32;
typedef char i8;
typedef unsigned char u8;

#define BLOCK_SIZE 4096

u64 filesize(const char* filename)
{
    std::ifstream in(filename, std::ifstream::ate | std::ifstream::binary);
    return in.tellg();
}

i8 zeros[BLOCK_SIZE]{0};

struct DBMain{
    u32 freePages;
    u32 usedPageSize;
    u32 classArray;
};

#define FREE_PAGE_QUEUE_SIZE 10



class DiskManager{
    std::fstream file;
    std::mutex filelatch_;
    u32 pageSize = 10;
    i8 mainPageBuffer[BLOCK_SIZE];

    DBMain *main = (DBMain*)mainPageBuffer;
public:
    DiskManager(const std::string& dbName, bool init = false){
        file.open(dbName, std::ios::in | std::ios::out | std::ios::binary);
        read(0, mainPageBuffer);

        std::scoped_lock fileMutex(filelatch_);
        file.open(dbName, std::ios::binary | std::ios::in | std::ios::out);
        if (!file.is_open()) {
            file.clear();
            file.open(dbName, std::ios::binary | std::ios::trunc | std::ios::out);
            file.close();
            file.open(dbName, std::ios::binary | std::ios::in | std::ios::out);
            if (!file.is_open()) {
                throw Exception("can't open db file");
            }
        }

        if(init){
            main->freePages = 0;
            main->usedPageSize = 1;
            main->classArray = 1;
            flushMain();
        }
    }

    DBMain *getMain(){
        return (DBMain*)mainPageBuffer;
    }

    void flushMain(){
        write(0, mainPageBuffer);
    }

    u32 allocPage(){
        u32 page;
        if(main->freePages != 0){
            page = main->freePages;
            u32 nextPage;
            read(page, reinterpret_cast<i8*>(&nextPage), sizeof(nextPage));
            main->freePages = nextPage;
            flushMain();
        }else{
            page = main->usedPageSize++;
        }

        write(pageSize, zeros);
        return page;
    }

    void freePage(u32 page){
        u32 nextPage = main->freePages;
        write(page, reinterpret_cast<i8*>(&nextPage), sizeof(nextPage));
        main->freePages = page;
        flushMain();
    }

    void write(u32 pageIndex, i8* test, u32 size = BLOCK_SIZE){
        file.clear();
        file.seekg(pageIndex * BLOCK_SIZE);
        file.write(test, size);
        file.flush();
    }

    void read(u32 pageIndex, i8* test, u32 size = BLOCK_SIZE){
        file.clear();
        file.seekg(pageIndex * BLOCK_SIZE);
        file.read(test, size);
    }

    void close(){
        flushMain();
        file.flush();
        file.close();
    }
};

#define BUFFER_SIZE 8

struct Frame{
    u32 frameIndex;
    u32 pageIndex;
    u32 refs;
    bool clean;
    i8 buffer[BLOCK_SIZE];
};

class BufferPool{
    DiskManager *diskManager;
    Frame buffer[BLOCK_SIZE];
    u32 current = 0;

    Frame* allocFrame(u32 pageIndex){
        for( u32 i = 0 ; i < BUFFER_SIZE ; i++ ){
            Frame *frame = getFrame(i);
            if(frame->clean && frame->pageIndex == pageIndex){
                frame->refs++;
                return frame;
            }
        }

        for( u32 i = 0 ; i < BUFFER_SIZE ; i++ ){
            Frame *frame = getFrame(current);
            if(frame->refs == 0){
                frame->refs++;
                frame->clean = true;
                frame->frameIndex = current;
                frame->pageIndex = pageIndex;
                load(frame);
                return frame;
            }

            current = (current + 1) % BLOCK_SIZE;
        }

        assert(false);
    }

    void load(Frame* frame){
        diskManager->read(frame->pageIndex, frame->buffer);
    }
public:
    BufferPool(DiskManager *diskManager) : diskManager(diskManager){
    }

    Frame* getFrame(u32 frameIndex){
        return &buffer[frameIndex];
    }

    u32 allocPage(){
        return diskManager->allocPage();
    }

    void freePage(u32 pageIndex){
        diskManager->freePage(pageIndex);
    }

    u32 fetch(u32 pageIndex){
        Frame *frame = allocFrame(pageIndex);
        return frame->frameIndex;
    }

    void flush(u32 frameIndex){
        Frame *frame = getFrame(frameIndex);
        diskManager->write(frame->pageIndex, frame->buffer);
    }

    void refresh(u32 frameIndex){
        load(getFrame(frameIndex));
    }

    i8* getBuffer(u32 frameId){
        return getFrame(frameId)->buffer;
    }

    void free(u32 frameIndex){
        Frame *frame = getFrame(frameIndex);
        frame->refs--;
    }
};

struct PageEntry{
    bool present : 1;
    u32 pageIndex : 20;
};

class PageDirectory{
    BufferPool *bufferPool;
    u32 frameId;
    PageEntry* firstLevel;

    i8* fetchValue(u32 key, u32 pageIndex){
        u32 level3 = key & 0xfff;
        u32 thirdFrame = bufferPool->fetch(pageIndex);
        i8 *thirdLevel = (i8*) bufferPool->getBuffer(thirdFrame);
        return thirdLevel + level3;
    }

public:
    PageDirectory(BufferPool *bufferPool, u32 directoryPage) : bufferPool(bufferPool){
        frameId = bufferPool->fetch(directoryPage);
        firstLevel = (PageEntry*) bufferPool->getBuffer(frameId);
    }


    i8* getPageFrameValue(u32 key, u32 frame){
        u32 level3 = key & 0xfff;
        i8 *thirdLevel = (i8*) bufferPool->getBuffer(frame);
        return thirdLevel + level3;
    }

    i32 fetchPageFrame(u32 key, bool create){
        u32 level1 = key >> 22;
        auto *firstEntry = firstLevel + level1;
        i32 result = -1;
        if(firstEntry->present || create){
            if(!firstEntry->present){
                firstEntry->present = true;
                firstEntry->pageIndex = bufferPool->allocPage();
                bufferPool->flush(frameId);
            }

            u32 level2 = ((u32)key >> 12) & 0x3ff;
            u32 secondFrame = bufferPool->fetch(firstEntry->pageIndex);
            auto *secondLevel = (PageEntry*) bufferPool->getBuffer(secondFrame);
            auto *secondEntry = secondLevel + level2;
            if(secondEntry->present || create){
                if(!secondEntry->present){
                    secondEntry->present = true;
                    secondEntry->pageIndex = bufferPool->allocPage();
                    bufferPool->flush(secondFrame);
                }

                result = secondEntry->pageIndex;
            }
            bufferPool->free(secondFrame);
        }

        return result;
    }

    void set(u32 key, u32 value){
        i32 page = fetchPageFrame(key, true);
        if(page == -1){
            return;
        }
        u32 frame = bufferPool->fetch(page);
        i8 *arr = getPageFrameValue(key, frame);
        arr[0] = value;
        bufferPool->flush(frame);
        bufferPool->free(frame);
    }

    u32 get(u32 key){
        i8* arr = lookup(key);
        return arr[0];
    }

    i8* lookup(u32 key, bool create = false){
        i32 page = fetchPageFrame(key, create);
        if(page == -1){
            return nullptr;
        }
        return fetchValue(key, page);
    }
};

class ArrayList{
    BufferPool *bufferPool;
    PageDirectory *pageDirectory;
public:
    ArrayList(BufferPool *bufferPool, u32 arrayPage) : bufferPool(bufferPool), pageDirectory(new PageDirectory(bufferPool, arrayPage)){
    }

    void set(u32 index, u64 value){
        u32 scaledIndex = index * 8;
        i32 page = pageDirectory->fetchPageFrame(scaledIndex, true);
        if(page == -1){
            return;
        }
        u32 frame = bufferPool->fetch(page);
        u64* arr = (u64*)pageDirectory->getPageFrameValue(scaledIndex, frame);
        *arr = value;
        bufferPool->flush(frame);
        bufferPool->free(frame);
    }

    u64 get(u32 index){
        u32 scaledIndex = index * 8;
        i32 page = pageDirectory->fetchPageFrame(index, true);
        if(page == -1){
            return 0;
        }
        u32 frame = bufferPool->fetch(page);
        u64* arr = (u64*)pageDirectory->getPageFrameValue(scaledIndex, frame);
        u64 result = *arr;
        bufferPool->free(frame);
        return result;
    }
};

int main () {
    bool init = true;
    auto *diskManager = new DiskManager("test.db", init);
    auto mainPage = diskManager->getMain();


    auto *pool = new BufferPool(diskManager);

    if(init){
        pool->allocPage();
    }

    auto *arrayList = new ArrayList(pool, mainPage->classArray);

    u32 test = pool->allocPage();
    pool->freePage(test);

    if(init){
        arrayList->set(0, 1111);
        arrayList->set(1, 2222);
    }

    u64 value = arrayList->get(0);
    u64 value2 = arrayList->get(1);
    std::cout << test << " " << value << " " << value2;

    diskManager->close();
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
