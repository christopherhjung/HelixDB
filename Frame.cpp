//
// Created by Christopher Jung on 19.03.22.
//

#include "Frame.h"
#include "BufferPool.h"

void Frame::flush(){
    pool->flush(this);
}

void Frame::close(bool dirty){
    /*if(refs == 1){
        if(dirty || this->dirty){
            flush();
        }
    }else */
    if(dirty){
        setDirty(true);
    }
    pool->close(this);
}

void Frame::clear(){
    memset(buffer, 0, PAGE_SIZE);
}

void Frame::open(){
    pool->open(this);
}

void Frame::setDirty(bool dirty){
    this->dirty = dirty;
}

