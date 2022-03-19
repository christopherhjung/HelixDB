//
// Created by Christopher Jung on 19.03.22.
//

#pragma once
#include "PageDirectory.h"
#include "Allocator.h"
#include "Frame.h"
#include "defs.h"


template<class H, class T>
class SlotDirectory{
    PageDirectory pageDirectory;
    i32 lastPageId = -1;
    Frame *lastFrame = nullptr;

    int getPageId(int index){
        return index / round_down(PAGE_SIZE, sizeof(T));
    }

    int getPageSlot(int index){
        return (index % round_down(PAGE_SIZE, sizeof(T)));
    }

    int getPageOffset(int index){
        return getPageSlot(index) * sizeof(T);
    }
public:
    SlotDirectory(Allocator *allocator, Frame *frame) : pageDirectory(allocator, frame){

    }

    Frame *fetchFrame(u32 index){
        return pageDirectory.fetchFrame(getPageId(index)  , true);
    }

    void setHeader(Frame* frame, H& value){
        return_if_null(frame);
        u32 slot = getPageSlot(index);
        *((H*)frame->getData()) = value;
        frame->flush();
        frame->close();
    }

    bool getHeader(Frame *frame, H& value){
        if(frame == nullptr){
            return false;
        }
        value = *((H*)frame->getData());
        frame->close();
        return true;
    }

    void set(Frame* frame, u32 index, T& value){
        return_if_null(frame);
        u32 slot = getPageSlot(index);
        ((T*)frame->getData())[slot] = value;
        frame->flush();
        frame->close();
    }

    void set(u32 index, T& value){
        set(pageDirectory.fetchFrame(getPageId(index), true), index, value);
    }

    bool get(u32 index, T& value){
        return get(pageDirectory.fetchFrame(getPageId(index), false), index, value);
    }

    bool get(Frame *frame, u32 index, T& value){
        if(frame == nullptr){
            return false;
        }
        u32 slot = getPageOffset(index);
        value = ((T*)frame->getData())[slot];
        frame->close();
        return true;
    }
};

