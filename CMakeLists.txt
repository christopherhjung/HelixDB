cmake_minimum_required(VERSION 3.21)
project(HelixDB)

set(CMAKE_CXX_STANDARD 20)

add_executable(HelixDB
        main.cpp
        MainFrame.cpp
        PageDirectory.cpp
        Frame.cpp
        DiskManager.cpp
        BufferPool.cpp)
