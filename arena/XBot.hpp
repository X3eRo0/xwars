#ifndef XVM_ARENA_XBOT_HPP
#define XVM_ARENA_XBOT_HPP

#include <time.h>

#ifdef __cplusplus
    extern "C" {
#endif

#include "../xvm/cpu.h"
#include "../xasm/xasm.h"

#ifdef __cplusplus
    }
#endif

#include "Common.hpp"

// xbot
struct xbot{
    xbot();     // init_xbot()
    ~xbot();    // fini_xbot()

    // add a new section to this bot
    // this will load them at random memory locations
    void add_section(section_entry *sxn);

    // execute next instruction
    u32 step();

    std::string botname; // unique name of this bot
    xvm_cpu *cpu;
    xvm_bin *bin;
    u32 init_addr;
    u32 bot_addr;
    u32 offset;
    u32 size;
    section_entry* bot_section;
};

// u32   step(xbot* bot);
// u32   copy_bots(xbot* bot1, xbot* bot2, section_entry* text);
// u32   xlog(char * message, ...);
// u32   wait_for_gui();
// u32   dump_reg(xbot* bot1, xbot* bot2);
// u32   dump_dis(xbot* bot1, xbot* bot2);

#endif//XVM_ARENA_XBOT_HPP