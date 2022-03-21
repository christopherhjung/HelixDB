cmake_minimum_required(VERSION 3.21)
project(HelixDB)

set(CMAKE_CXX_STANDARD 20)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)


# required if linking to static library
add_definitions(-DANTLR4CPP_STATIC)

# using /MD flag for antlr4_runtime (for Visual C++ compilers only)
set(ANTLR4_WITH_STATIC_CRT OFF)
# add external build for antlrcpp
include(ExternalAntlr4Cpp)
# add antrl4cpp artifacts to project environment
include_directories(${ANTLR4_INCLUDE_DIRS})

# set variable pointing to the antlr tool that supports C++
# this is not required if the jar file can be found under PATH environment
set(ANTLR_EXECUTABLE ${PROJECT_SOURCE_DIR}/libs/antlr-4.9.3-complete.jar)

# add macros to generate ANTLR Cpp code from grammar
find_package(ANTLR REQUIRED)

# Call macro to add lexer and grammar to your build dependencies.

antlr_target(SampleGrammarLexer ${CMAKE_CURRENT_SOURCE_DIR}/grammar/TLexer.g4 LEXER
        PACKAGE antlrcpptest)
antlr_target(SampleGrammarParser ${CMAKE_CURRENT_SOURCE_DIR}/grammar/TParser.g4 PARSER
        PACKAGE antlrcpptest
        DEPENDS_ANTLR SampleGrammarLexer
        COMPILE_FLAGS -lib ${ANTLR_SampleGrammarLexer_OUTPUT_DIR}
        VISITOR)

# include generated files in project environment
include_directories(${ANTLR_SampleGrammarLexer_OUTPUT_DIR})
include_directories(${ANTLR_SampleGrammarParser_OUTPUT_DIR})

add_executable(HelixDB
        ${ANTLR_SampleGrammarLexer_CXX_OUTPUTS}
        ${ANTLR_SampleGrammarParser_CXX_OUTPUTS}
        main.cpp
        MainFrame.cpp
        PageDirectory.cpp
        ClassCollectionHeader.cpp
        Frame.cpp
        DiskManager.cpp
        BufferPool.cpp
        list.cpp
        )

target_link_libraries(HelixDB antlr4_static)