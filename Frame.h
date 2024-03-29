//
// Created by Christopher Jung on 19.03.22.
//

#pragma once
#include "list.h"
#include "defs.h"
class BufferPoolImpl;
class MainFrame;
class ClassCollectionHeader;

class Frame{
    friend BufferPoolImpl;

    u32 refs;
    bool active;
    u32 frameIndex;
    u32 pageId;
    bool dirty;
    bool accessed;

    //list_elem elem;

    //Frame* next;
protected:
    i8 buffer[PAGE_SIZE];
    BufferPoolImpl *pool;
public:
    i8* getData(){
        return buffer;
    }

    void flush();
    void close(bool dirty = true);
    void open();
    void clear();
    void setDirty(bool dirty = true);

    MainFrame* asMainFrame(){
        return (MainFrame*)(this);
    }

    ClassCollectionHeader* asClassCollectionHeader(){
        return (ClassCollectionHeader*)(this);
    }

    u32 getPageId(){
        return pageId;
    }

    template<class V>
    void set(u32 index, V value){
        *((V*)(buffer + index)) = value;
    };

    template<class V>
    void get(u32 index, V* value){
        *value = get<V>(index);
    };

    template<class V>
    V* map(){
        return ((V*)(buffer));
    };

    template<class V>
    V* mapIndexed(u32 index){
        return ((V*)(buffer)) + index;
    };

    template<class V>
    V get(u32 index){
        return *((V*)(buffer + index));
    };

    template<class V>
    V* get(){
        return ((V*)(buffer));
    };

    u32 getU32(u32 index){
        return *((u32*)(buffer + index));
    }
};

