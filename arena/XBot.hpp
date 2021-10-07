#ifndef XVM_ARENA_XBOT_HPP
#define XVM_ARENA_XBOT_HPP

#include <time.h>
#include "../xvm/cpu.h"
#include "../xasm/xasm.h"
#include "Common.hpp"

// xbot
typedef struct xwars_bot_t {
    cstring botname; // unique name of this bot
    xvm_cpu *cpu;
    xvm_bin *bin;
    u32 init_addr;
    u32 bot_addr;
    u32 offset;
    u32 size;
    section_entry* bot_section;
} xbot;

xbot *init_xbot();
void  fini_xbot(xbot* bot);
u32   step(xbot* bot);
u32   copy_bots(xbot* bot1, xbot* bot2, section_entry* text);
u32   xlog(char * message, ...);
u32   wait_for_gui();
u32   dump_reg(xbot* bot1, xbot* bot2);
u32   dump_dis(xbot* bot1, xbot* bot2);

#endif//XVM_ARENA_XBOT_HPP