#ifndef XVM_ARENA_COMMON_HPP
#define XVM_ARENA_COMMON_HPP

#include <wx/cmdline.h>
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif // WX_PRECOMP

#include <chrono>
#include <cstdint>
#include <malloc.h>
#include <stdio.h>
#include <unistd.h>
#include <wx/utils.h>

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;

typedef const char* cstring;

// get reader and writer
FILE* get_reader_end();
FILE* get_writer_end();

// GetBot1 read/write/execute colours
inline wxColour GetBot1ReadColour() { return wxColour(0x00, 0xff, 0xff); } // #00ffff
inline wxColour GetBot1WriteColour() { return wxColour(0xff, 0x66, 0xff); } // #ff66ff
inline wxColour GetBot1ExecColour() { return wxColour(0x00, 0x4d, 0x99); } // #004d99

// GetBot2 read/write/execute colors
inline wxColour GetBot2ReadColour() { return wxColour(0xff, 0xff, 0x00); } // #ffff00
inline wxColour GetBot2WriteColour() { return wxColour(0xac, 0x32, 0x00); } // #ac3200
inline wxColour GetBot2ExecColour() { return wxColour(0xc0, 0x23, 0x23); } // #c02323

#endif // XVM_ARENA_COMMON_HPP
