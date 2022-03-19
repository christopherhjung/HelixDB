cmake_minimum_required(VERSION 3.21)
project(HelixDB)

set(CMAKE_CXX_STANDARD 17)

add_executable(HelixDB main.cpp bitmap.cpp hash.cpp list.cpp)
