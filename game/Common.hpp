#ifndef XVM_ARENA_COMMON_HPP
#define XVM_ARENA_COMMON_HPP

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif//WX_PRECOMP

#include <stdio.h>
#include <malloc.h>
#include <cstdint>
#include <wx/utils.h>
#include <unistd.h>

typedef uint8_t  u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef int8_t  i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;

typedef const char* cstring;

// get reader and writer
FILE * get_reader_end();
FILE * get_writer_end();

#endif//XVM_ARENA_COMMON_HPP
