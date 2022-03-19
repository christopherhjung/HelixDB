//
// Created by Christopher Jung on 19.03.22.
//

#pragma once
#include "defs.h"
#include "Frame.h"

#define PAGE_COUNT_OFFSET 0
#define NEXT_FREE_PAGE_OFFSET 4
#define CLASS_PAGE_OFFSET 8
#define NAME_PAGE_OFFSET 12

class MainFrame : public Frame{
public:
    Frame* getNameFrame();
    void setNamePage(u32 pageId);
    Frame* getClassRootFrame();
    void setClassPage(u32 pageId);
    u32 getPageCount();
    void setPageCount(u32 pageSize);
    u32 getNextFreePage();
    void setNextFreePage(u32 pageId);
    void init();
};
