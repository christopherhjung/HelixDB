//
// Created by Christopher Jung on 19.03.22.
//

#include "ClassCollectionHeader.h"
#include "Allocator.h"

Frame* ClassCollectionHeader::getPageDirectoryFrame(){
    return pool->fetch(getU32(CLASS_PAGE_DIRECTORY_OFFSET));
}

void ClassCollectionHeader::setPageDirectoryPage(u32 pageId){
    set(CLASS_PAGE_DIRECTORY_OFFSET, pageId);

}

u32 ClassCollectionHeader::getClassCount(){
    return get<u32>(CLASS_COUNT_OFFSET);
}

void ClassCollectionHeader::setClassCount(u32 count){
    set(CLASS_COUNT_OFFSET, count);
}

void ClassCollectionHeader::init(Allocator *allocator){
    setClassCount(0);
    setPageDirectoryPage(allocator->allocPageId());
    flush();
}