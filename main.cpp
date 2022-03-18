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

typedef unsigned long u64;
typedef unsigned int u32;
typedef char byte;

#define BLOCK_SIZE 4096

u64 filesize(const char* filename)
{
    std::ifstream in(filename, std::ifstream::ate | std::ifstream::binary);
    return in.tellg();
}

class DiskManager{
    std::fstream myfile;
    u32 pageSize = 0;
public:
    DiskManager(const std::string& dbName){
        myfile.open(dbName, std::ios::in | std::ios::out |std::ios::binary);
    }

    void write(u32 pageIndex, byte* test){
        myfile.clear();
        myfile.seekg(pageIndex * BLOCK_SIZE);
        myfile.write(test, BLOCK_SIZE);
        myfile.flush();
    }

    void read(u32 pageIndex, byte* test){
        if(pageSize < pageIndex){
            pageSize = pageIndex;
            memset(test, 0, BLOCK_SIZE);
        }else{
            myfile.clear();
            myfile.seekg(pageIndex * BLOCK_SIZE);
            myfile.read(test, BLOCK_SIZE);
        }
    }
};

#define BUFFER_SIZE 100

typedef struct{
    byte buffer[BLOCK_SIZE];
    u32 frameIndex;
    u32 pageIndex;
    bool used;
}Frame;

class BufferPool{
    DiskManager *diskManager;
    Frame buffer[BLOCK_SIZE];

    Frame* allocFrame(u32 pageIndex){
        for( u32 i = 0 ; i < BUFFER_SIZE ; i++ ){
            Frame *frame = getFrame(i);
            if(!frame->used){
                frame->used = true;
                frame->frameIndex = i;
                frame->pageIndex = pageIndex;
                return frame;
            }
        }

        assert(false);
    }

    Frame* getFrame(u32 frameIndex){
        return &buffer[frameIndex];
    }

    void load(Frame* frame){
        diskManager->read(frame->pageIndex, frame->buffer);
    }
public:
    BufferPool(DiskManager *diskManager) : diskManager(diskManager){
    }

    u32 fetch(u32 pageIndex){
        Frame *frame = allocFrame(pageIndex);
        load(frame);
        return frame->frameIndex;
    }

    void flush(u32 frameIndex){
        Frame *frame = getFrame(frameIndex);
        diskManager->write(frame->pageIndex, frame->buffer);
    }

    void refresh(u32 frameIndex){
        load(getFrame(frameIndex));
    }

    byte* getContent(u32 frameId){
        return getFrame(frameId)->buffer;
    }

    void free(u32 frameIndex){
        Frame *frame = getFrame(frameIndex);
        frame->used = false;
    }
};



class PageDirectory{
    BufferPool *bufferPool;
    int frameId;
    int* firstLevel;

public:
    PageDirectory(BufferPool *bufferPool, u32 directoryPage) : bufferPool(bufferPool){
        frameId = bufferPool->fetch(directoryPage);
        firstLevel = (int*)bufferPool->getContent(frameId);
    }

    u32 lookup(u32 key){
        u32 level1 = key >> 22;
        u32 level2 = ((u32)key >> 12) & 0x3ff;
        u32 level3 = key & 0xfff;

        u32 firstEntry = firstLevel[level1];
        u32 secondFrame = bufferPool->fetch(firstEntry);
        int *secondLevel = (int*)bufferPool->getContent(secondFrame);
        u32 secondEntry = secondLevel[level2];
        u32 thirdFrame = bufferPool->fetch(secondEntry);
        int *thirdLevel = (int*)bufferPool->getContent(thirdFrame);
        bufferPool->free(secondFrame);
        bufferPool->free(thirdFrame);
        return thirdLevel[level3];
    }
};

int main () {
    DiskManager *diskManager = new DiskManager("test.db");
    BufferPool *pool = new BufferPool(diskManager);
    PageDirectory *pageDirectory = new PageDirectory(pool, 1);
/*
    u32 frameId = pool->fetch(0);

    byte* page = pool->getContent(frameId);


    page[0] = 77;

    pool->flush(0);

    page[0] = 1;

    pool->refresh(0);
    std::cout << (int)page[0];

    pool->free(frameId);*/

    u32 result = pageDirectory->lookup(0);

    std::cout << result;


/*    u64 size = filesize(db);


    myfile.write(test, BLOCK_SIZE);
*/
    return 0;
}
