//
// Created by Christopher Jung on 19.03.22.
//

#include "MainFrame.h"
#include "Frame.h"
#include "BufferPoolImpl.h"


u32 MainFrame::getPageCount(){
    return getU32(PAGE_COUNT_OFFSET);
}

void MainFrame::setPageCount(u32 pageSize)
{
    set(PAGE_COUNT_OFFSET, pageSize);
}

Frame* MainFrame::getClassFrame(){
    return pool->fetch(getU32(CLASS_OFFSET));
}

u32 MainFrame::getNextFreePage(){
    return getU32(NEXT_FREE_PAGE_OFFSET);
}

void MainFrame::setNextFreePage(u32 pageId){
    set(NEXT_FREE_PAGE_OFFSET, pageId);
}

void MainFrame::init(){
    clear();
    set(0, (u32)1);
    setPageCount(1);
    setNextFreePage(0);
    flush();
}