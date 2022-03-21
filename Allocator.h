//
// Created by Christopher Jung on 19.03.22.
//

#pragma once

#include <unordered_map>
#include "DiskManager.h"
#include "Frame.h"
#include "MainFrame.h"
#include "defs.h"
#include "BufferPoolImpl.h"


class Allocator : BufferPool{
    BufferPool *bufferPool;
    MainFrame* mainFrame;
    u32 poolSize;
    u32 current = 0;


public:
    //static std::string reason;


    Allocator(BufferPool *bufferPool, MainFrame* mainFrame) : bufferPool(bufferPool), mainFrame(mainFrame){

    }

    Frame *allocPage(){
        u32 next = mainFrame->getNextFreePage();
        u32 page;
        if(next != 0){
            page = next;
            Frame* frame = bufferPool->fetch(next);
            //u32 nextFramePageId = 0;
            //frame->get(0, &nextFramePageId);

            u32* nextPageId = frame->map<u32>();
            mainFrame->setNextFreePage(*nextPageId);
            frame->close();
        }else{
            //std::cout << reason << std::endl;
            page = mainFrame->getPageCount();
            mainFrame->setPageCount(page + 1);
        }

        Frame* newPageFrame = bufferPool->fetch(page);
        newPageFrame->clear();
        newPageFrame->flush();
        mainFrame->flush();
        return newPageFrame;
    }

    u32 allocPageId(){
        Frame *frame = allocPage();
        u32 pageId = frame->getPageId();
        frame->close();
        return pageId;
    }

    Frame *fetch(u32 pageIndex, bool pinned = false) override{
        return bufferPool->fetch(pageIndex, pinned);
    }

    void flush(Frame *frame) override{
        bufferPool->flush(frame);
    }

    void refresh(Frame *frame) override{
        bufferPool->refresh(frame);
    }

    void close(Frame *frame) override{
        bufferPool->close(frame);
    }
};
