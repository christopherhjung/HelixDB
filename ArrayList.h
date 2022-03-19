//
// Created by Christopher Jung on 19.03.22.
//

#pragma once

#include "defs.h"
#include "BufferPoolImpl.h"
#include "PageDirectory.h"


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
        bufferPool->close(frame);
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
        bufferPool->close(frame);
        return result;
    }
};

