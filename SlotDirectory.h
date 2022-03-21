//
// Created by Christopher Jung on 19.03.22.
//

#pragma once
#include "PageDirectory.h"
#include "Allocator.h"
#include "Frame.h"
#include "defs.h"



enum Op{
    Set, Get
};




class SlotController{
    u32 entrySize = 0;
    u32 headerSize = 0;
    u32 entriesPerPage = 0;
public:
    template<class H, class C>
    SlotController( ) : SlotController(sizeof(H), sizeof(C)){
    }
    template<class C>
    SlotController( ) : SlotController(0, sizeof(C)){
    }

    SlotController( u32 headerSize, u32 entrySize) : headerSize(headerSize), entrySize(entrySize){
        entriesPerPage = ( PAGE_SIZE - headerSize ) / entrySize;
    }

    u32 getPageId(u32 index){
        return index / entriesPerPage;
    }

    u32 getPageSlot(u32 index){
        return index % entriesPerPage;
    }

    u32 getPageOffset(u32 index){
        return headerSize + getPageSlot(index) * entrySize;
    }


    Frame *fetchFrame(PageDirectory * pageDirectory, u32 index, bool create = false){
        return pageDirectory->fetchFrame(getPageId(index), create);
    }

    void setHeader(Frame* frame, void* value){
        return_if_null(frame);
        std::memcpy(frame->getData(), value, headerSize );
    }

    bool getHeader(Frame *frame, void* value){
        if(frame == nullptr){
            return false;
        }

        std::memcpy(value, frame->getData(), headerSize );
        return true;
    }

    void set(Frame* frame, u32 index, void* value){
        return_if_null(frame);
        u32 offset = getPageOffset(index);
        std::memcpy(frame->getData() + offset, value, entrySize);
        frame->setDirty();
    }

    void set(PageDirectory *pageDirectory, u32 index, void* value){
        Frame *frame = fetchFrame(pageDirectory, index, true);
        set(frame, index, value);
        frame->close();
    }

    void apply(PageDirectory *pageDirectory, u32 index, void* value, Op operation){
        Frame *frame = fetchFrame(pageDirectory, index, true);

        if(operation == Op::Get){
            get(frame, index, value);
        }else if(operation == Op::Set){
            set(frame, index, value);
        }else{
            error("no set or get");
        }

        frame->close();
    }

    bool get(PageDirectory *pageDirectory, u32 index, void* value){
        Frame *frame = fetchFrame(pageDirectory, index, false);
        bool success = get(frame, index, value);
        frame->close();
        return success;
    }

    bool get(Frame *frame, u32 index, void* value){
        if(frame == nullptr){
            return false;
        }
        u32 offset = getPageOffset(index);
        std::memcpy(value, frame->getData() + offset, entrySize);
        return true;
    }

    template<class T>
    T* map(Frame *frame, u32 index){
        if(frame == nullptr){
            return nullptr;
        }
        u32 offset = getPageOffset(index);
        return (T*)(frame->getData() + offset);
    }
};

