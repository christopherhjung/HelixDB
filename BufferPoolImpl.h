//
// Created by Christopher Jung on 19.03.22.
//

#pragma once

#include "DiskManager.h"
#include "Frame.h"
#include "defs.h"

static i8 zeros[PAGE_SIZE]{0};

class BufferPool{
public:
    virtual Frame *fetch(u32 pageIndex, bool pinned = false) = 0;
    virtual void flush(Frame *frame) = 0;
    virtual void refresh(Frame *frame) = 0;
    virtual void close(Frame *frame) = 0;
};

class BufferPoolImpl : public BufferPool{
    DiskManager *diskManager;
    Frame *buffer;
    u32 poolSize;
    u32 current = 0;


    void load(Frame* frame){
        diskManager->read(frame->pageId, frame->buffer);
    }
public:
    BufferPoolImpl(DiskManager *diskManager, u32 poolSize) : diskManager(diskManager), poolSize(poolSize), buffer(new Frame[poolSize]){
        foreach(i, poolSize){
            buffer[i].pool = this;
        }
    }

    ~BufferPoolImpl(){
        delete[] buffer;
    }

    Frame* getFrame(u32 frameIndex){
        return &buffer[frameIndex];
    }

    Frame *fetch(u32 pageIndex, bool pinned = false) override{
        for( u32 i = 0 ; i < PAGE_SIZE ; i++ ){
            Frame *frame = getFrame(i);
            if(frame->clean && frame->pageId == pageIndex){
                frame->refs++;
                return frame;
            }
        }

        for( u32 i = 0 ; i < PAGE_SIZE ; i++ ){
            Frame *frame = getFrame(current);
            if(frame->refs == 0){
                frame->refs++;
                frame->clean = true;
                frame->frameIndex = current;
                frame->pageId = pageIndex;
                load(frame);
                return frame;
            }

            current = (current + 1) % poolSize;
        }

        error("No Frames left");
    }

    void flush(Frame *frame) override{
        diskManager->write(frame->pageId, frame->buffer);
    }

    void refresh(Frame *frame) override{
        load(frame);
    }

    void close(Frame *frame) override{

        if(!(frame->refs > 0)) throw new Exception( "There are no refs!!");
        //assert(frame->refs > 0, "There are no refs!!");
        frame->refs--;
    }
};
