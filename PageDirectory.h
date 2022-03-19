//
// Created by Christopher Jung on 19.03.22.
//

#pragma once
#include "Allocator.h"
#include "Frame.h"
#include "defs.h"


struct PageEntry{
    bool present : 1;
    u32 pageId : 20;
};

class PageDirectoryFrame : public Frame{
public:
    PageEntry* getEntry(u32 offset){
        return get<PageEntry>() + offset;
    }
};

class PageDirectory{
    Allocator *allocator;
    PageDirectoryFrame *rootFrame;

    Frame *getOrCreate(u32 key, PageDirectoryFrame* frame, bool create){
        auto *entry = frame->getEntry(key);

        if(entry->present || create){
            Frame *level2Frame;
            if(!entry->present){
                entry->present = true;
                level2Frame = allocator->allocPage();
                entry->pageId = level2Frame->getPageId();
                frame->flush();
            }else{
                level2Frame = allocator->fetch(entry->pageId);
            }
            return level2Frame;
        }

        return nullptr;
    }

public:
    PageDirectory(Allocator *allocator, Frame *frame) : allocator(allocator), rootFrame((PageDirectoryFrame*)frame){

    }

    Frame *fetchFrame(u32 key, bool create){
        u32 level1 = key >> 22;
        auto *level2Frame = (PageDirectoryFrame*)getOrCreate(level1, rootFrame, create);
        return_null_if_null(level2Frame);
        u32 level2 = (key >> 12) & 0x3ff;
        auto *level3Frame = getOrCreate(level2, level2Frame, create);
        level2Frame->close();
        return level3Frame;
    }

    template<class T>
    void set(u32 key, T value){
        auto *frame = fetchFrame(key, true);
        return_if_null(frame);
        u32 level3 = key & 0xfff;

        i8 *addr = frame->getData() + level3;
        *((T*)addr) = value;
        frame->flush();
        frame->close();
    }

    template<class T>
    T get(u32 key){
        auto *frame = fetchFrame(key, true);
        assert(frame, "No frame found with key = " + std::to_string(key));
        u32 level3 = key & 0xfff;

        i8 *addr = frame->getData() + level3;
        T value = *((T*)addr);
        frame->flush();
        frame->close();
        return value;
    }
};

