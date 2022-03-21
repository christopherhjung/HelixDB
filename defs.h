#pragma once

#define PAGE_SIZE 4096

typedef unsigned long u64;
typedef unsigned int u32;
typedef unsigned short u16;
typedef int i32;
typedef char i8;
typedef unsigned char u8;

#define SET 1
#define GET 2

#define foreach(i, size) for(u32 i = 0 ; i < (size) ; i++)

#define round_down(X, STEP) ((X) / (STEP) * (STEP))

#define return_null_if_null(ptr) if((ptr) == nullptr) return nullptr;
#define return_if_null(ptr) if((ptr) == nullptr) return;
#define return_null_if(condition) if(condition) return nullptr;
#define error(message) throw new Exception(message);
#define check(condition, message) if(!(condition)) throw new Exception(message);