//
// Created by Christopher Jung on 19.03.22.
//

#pragma once

#include <list>

#include "DiskManager.h"
#include "Frame.h"
#include "list.h"
#include "defs.h"

static i8 zeros[PAGE_SIZE]{0};

class BufferPool{
public:
    virtual Frame *fetch(u32 pageIndex, bool pinned = false) = 0;
    virtual void flush(Frame *frame) = 0;
    virtual void refresh(Frame *frame) = 0;
    virtual void close(Frame *frame) = 0;
    virtual void open(Frame *frame) = 0;
    virtual void shutdown() = 0;
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
            auto frame = buffer[i];
            frame.pool = this;
            frame.frameIndex = i;
        }
    }

    ~BufferPoolImpl(){
        delete[] buffer;
    }

    void shutdown(){
        foreach(i, poolSize){
            Frame *frame = getFrame(i);
            if(frame->dirty){
                flush(frame);
            }
        }

        foreach(i, poolSize){
            Frame *frame = getFrame(i);
            check(frame->refs == 0, "Refs are not 0");
        }

        diskManager->close();
    }

    Frame* getFrame(u32 frameIndex){
        return &buffer[frameIndex];
    }

    void prepareFrame(Frame* frame, u32 pageId){
        if(frame->dirty){
            flush(frame);
            frame->dirty = false;
        }
        frame->pageId = pageId;
        frame->active = true;
        frame->refs++;
        load(frame);
    }

    Frame *fetch(u32 pageId, bool pinned = false) override{
        foreach(i, poolSize){
            Frame *frame = getFrame(i);
            if(frame->active && frame->pageId == pageId){
                frame->refs++;
                return frame;
            }
        }

        foreach(i, poolSize * 2){
            Frame *frame = getFrame(current);
            current = (current + 1) % poolSize;
            if(frame->refs == 0){
                if(frame->accessed){
                    frame->accessed = false;
                }else{
                    prepareFrame(frame, pageId );
                    return frame;
                }
            }
        }

        error("No Frames left");
    }

    void flush(Frame *frame) override{
        diskManager->write(frame->pageId, frame->buffer);
    }

    void refresh(Frame *frame) override{
        load(frame);
    }

    void open(Frame *frame) override{
        frame->refs++;
    }

    void close(Frame *frame) override{
        check(frame->refs > 0, "There are no refs!!");
        frame->accessed = true;
        frame->refs--;
    }
};
