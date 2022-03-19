//
// Created by Christopher Jung on 19.03.22.
//

#pragma once
#include "defs.h"
#include "Frame.h"

#define CLASS_OFFSET 0
#define PAGE_COUNT_OFFSET 4
#define NEXT_FREE_PAGE_OFFSET 8

class MainFrame : public Frame{
public:
    Frame* getClassFrame();
    u32 getPageCount();
    void setPageCount(u32 pageSize);
    u32 getNextFreePage();
    void setNextFreePage(u32 pageId);
    void init();
};
