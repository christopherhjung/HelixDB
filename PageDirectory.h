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
                frame->setDirty();
            }else{
                level2Frame = allocator->fetch(entry->pageId);
            }
            return level2Frame;
        }

        return nullptr;
    }

public:
    PageDirectory(Allocator *allocator, Frame *frame) : allocator(allocator), rootFrame((PageDirectoryFrame*)frame){
        rootFrame->open();
    }

    ~PageDirectory(){
        rootFrame->close();
    }

    Frame *fetchFrame(u32 key, bool create = false){
        u32 level1 = (key >> 10) & 0x3ff;
        check((level1 & ~0x3ff) == 0, "Page number too large")
        auto *level2Frame = (PageDirectoryFrame*)getOrCreate(level1, rootFrame, create);
        check(level2Frame != nullptr, "Nothing found for key: " + std::to_string(key));
        u32 level2 = key & 0x3ff;
        auto *level3Frame = getOrCreate(level2, level2Frame, create);
        level2Frame->close();
        return level3Frame;
    }
};

