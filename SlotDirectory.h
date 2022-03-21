//
// Created by Christopher Jung on 19.03.22.
//

#pragma once
#include "PageDirectory.h"
#include "Allocator.h"
#include "Frame.h"
#include "defs.h"

class FrameFragment{

};

class SlotDirectory{
    PageDirectory pageDirectory;
    u32 entrySize = 0;
    u32 headerSize = 0;
    u32 entriesPerPage = 0;

    u32 getPageId(u32 index){
        return index / entriesPerPage;
    }

    u32 getPageSlot(u32 index){
        return index % entriesPerPage;
    }

    u32 getPageOffset(u32 index){
        return headerSize + getPageSlot(index) * entrySize;
    }
public:
    SlotDirectory(Allocator *allocator, Frame *frame, u32 headerSize, u32 entrySize) :
        pageDirectory(allocator, frame), headerSize(headerSize), entrySize(entrySize){
        entriesPerPage = round_down(PAGE_SIZE - headerSize, entrySize);
    }

    Frame *fetchFrame(u32 index){
        return pageDirectory.fetchFrame(getPageId(index), true);
    }

    template<class H>
    void setHeader(Frame* frame, H& value){
        return_if_null(frame);
        *((H*)frame->getData()) = value;
        frame->flush();
        frame->close();
    }

    template<class H>
    bool getHeader(Frame *frame, H& value){
        if(frame == nullptr){
            return false;
        }
        value = *((H*)frame->getData());
        frame->close();
        return true;
    }

    template<class T>
    void set(Frame* frame, u32 index, T& value){
        return_if_null(frame);
        u32 offset = getPageOffset(index);
        *((T*)(frame->getData() + offset)) = value;
        frame->flush();
        frame->close();
    }

    template<class T>
    void set(u32 index, T& value){
        set(pageDirectory.fetchFrame(getPageId(index), true), index, value);
    }

    template<class T>
    bool get(u32 index, T& value){
        return get(pageDirectory.fetchFrame(getPageId(index), false), index, value);
    }

    template<class T>
    bool get(Frame *frame, u32 index, T& value){
        if(frame == nullptr){
            return false;
        }
        u32 offset = getPageOffset(index);
        value = *((T*)(frame->getData() + offset));
        frame->close();
        return true;
    }
};

#define PAGE_BYTE_SIZE (PAGE_SIZE >> 3)

class SlotController{
    u32 entrySize = 0;
    u32 headerSize = 0;
    u32 entriesPerPage = 0;
public:
    template<class H, class C>
    SlotController( ) : SlotController(sizeof(H), sizeof(C)){
        entriesPerPage = round_down(PAGE_BYTE_SIZE - headerSize, entrySize);
    }
    template<class C>
    SlotController( ) : SlotController(0, sizeof(C)){
        entriesPerPage = round_down(PAGE_BYTE_SIZE - headerSize, entrySize);
    }

    SlotController( u32 headerSize, u32 entrySize) : headerSize(headerSize), entrySize(entrySize){
        entriesPerPage = round_down(PAGE_BYTE_SIZE - headerSize, entrySize);
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
        frame->flush();
    }

    void set(PageDirectory *pageDirectory, u32 index, void* value){
        Frame *frame = fetchFrame(pageDirectory, index, true);
        set(frame, index, value);
        frame->close();
    }

    void apply(PageDirectory *pageDirectory, u32 index, void* value, u8 operation){
        Frame *frame = fetchFrame(pageDirectory, index, true);

        if(operation == GET){
            get(frame, index, value);
        }else if(operation == SET){
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


/*
template<class T>
class SlotController {
    GenericSlotController controller;

    SlotController(u32 header) : controller(header, sizeof(T)) {

    }
public:

    SlotController() : controller(0, sizeof(T)) {

    }

    Frame *fetchFrame(PageDirectory *directory, u32 index){
        return directory->fetchFrame(controller.getPageId(index), true);
    }

    void set(Frame *frame, u32 index, T &value) {
        return_if_null(frame);
        u32 slot = controller.getPageSlot(index);
        ((T *) frame->getData())[slot] = value;
        frame->flush();
        frame->close();
    }

    bool get(Frame *frame, u32 index, T &value) {
        if (frame == nullptr) {
            return false;
        }
        u32 slot = controller.getPageOffset(index);
        value = ((T *) frame->getData())[slot];
        frame->close();
        return true;
    };
};

template<class H, class T>
class HeaderSlotController : public SlotController<T>{

    HeaderSlotController() : HeaderSlotController(sizeof(H)){

    }

    void setHeader(Frame *frame, H &value) {
        return_if_null(frame);
        *((H *) frame->getData()) = value;
        frame->flush();
        frame->close();
    }

    bool getHeader(Frame *frame, H &value) {
        if (frame == nullptr) {
            return false;
        }
        value = *((H *) frame->getData());
        frame->close();
        return true;
    }
};*/