//
// Created by Christopher Jung on 19.03.22.
//

#include "Frame.h"
#include "BufferPoolImpl.h"

void Frame::flush(){
    pool->flush(this);
}

void Frame::close(bool doFlush){
    if(doFlush){
        flush();
    }
    pool->close(this);
}

void Frame::clear(){
    memset(buffer, 0, PAGE_SIZE);
}

void Frame::open(){
    pool->open(this);
}

