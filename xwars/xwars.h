//
// Created by X3eRo0 on 6/7/2021.
//

#ifndef XWARS_H
#define XWARS_H

#include <time.h>
#include "../xvm/cpu.h"
#include "../xasm/xasm.h"

typedef struct xwars_bot_t {
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

#endif //XWARS_H
