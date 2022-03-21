#pragma once

#include <iostream>
#include <fstream>
#include <filesystem>
#include <fstream>
#include <bitset>
#include <iostream>
#include <filesystem>
#include <mutex>
#include <string>
#include <sys/stat.h>
#include "defs.h"
#include "Exception.h"


class DiskManager{
    std::fstream file;
    std::mutex fileLatch;
    const std::string dbName;
public:
    DiskManager(const std::string& dbName) : dbName(dbName){
        file.open(dbName, std::ios::in | std::ios::out | std::ios::binary);
        //file.rdbuf()->pubsetbuf(nullptr, 0);

        std::scoped_lock fileMutex(fileLatch);
        file.open(dbName, std::ios::binary | std::ios::in | std::ios::out);
        if (!file.is_open()) {
            file.clear();
            file.open(dbName, std::ios::binary | std::ios::trunc | std::ios::out);
            file.close();
            file.open(dbName, std::ios::binary | std::ios::in | std::ios::out);
            if (!file.is_open()) {
                error("can't open db file");
            }
        }
    }

    u32 getSize() {
        struct stat stat_buf{};
        int rc = stat(dbName.c_str(), &stat_buf);
        return rc == 0 ? static_cast<u32>(stat_buf.st_size) : -1;
    }

    void write(u32 pageIndex, i8* data, u32 size = PAGE_SIZE){
        file.clear();
        file.seekg(pageIndex * PAGE_SIZE);
        file.write(data, size);
        file.flush();
    }

    void read(u32 pageIndex, i8* data, u32 size = PAGE_SIZE){
        file.clear();
        file.seekg(pageIndex * PAGE_SIZE);
        file.read(data, size);
    }

    void close(){
        file.flush();
        file.close();
    }
};
