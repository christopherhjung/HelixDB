//
// Created by Christopher Jung on 19.03.22.
//

#pragma once
#include "defs.h"
#include "Frame.h"

class Allocator;

#define CLASS_COUNT_OFFSET 0
#define CLASS_PAGE_DIRECTORY_OFFSET 4

class ClassCollectionHeader : public Frame{
public:
    Frame* getPageDirectoryFrame();
    void setPageDirectoryPage(u32 pageId);
    u32 getClassCount();
    void setClassCount(u32 count);
    void init(Allocator *allocator);
};


