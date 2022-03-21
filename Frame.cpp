//
// Created by Christopher Jung on 19.03.22.
//

#include "Frame.h"
#include "BufferPoolImpl.h"

void Frame::flush(){
    pool->flush(this);
}

void Frame::close(bool dirty){
    if(refs == 1){
        if(dirty || this->dirty){
            flush();
        }
    }else if(dirty){
        this->dirty = true;
    }

    pool->close(this);
}

void Frame::clear(){
    memset(buffer, 0, PAGE_SIZE);
}

void Frame::open(){
    pool->open(this);
}

