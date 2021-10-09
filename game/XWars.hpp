#ifndef XVM_XWAR_HPP
#define XVM_XWAR_HPP

#include "Common.hpp"
#include "XBot.hpp"
#include "../xasm/xasm.h"
#include <utility>

#define MAX_INSTR_EXECS 2000

struct xwars{
    xwars();
    ~xwars();

    // compile given bots
    void compile_bots(const std::vector<std::string>& bot_paths);

    // this will allocate bots for the first time by loading
    // the assembly file(s) from locations in bot_paths
    void load_bots(const std::vector<std::string>& bot_paths, const std::vector<std::string>& bot_names);
    void display_registers(xbot *bot1, xbot *bot2);
    void display_disassembly(xbot *bot1, xbot *bot2);
    // this will copy bots to text_section
    void copy_bots(xbot *bot1, xbot *bot2);

    u32 battle(xbot *bot1, xbot *bot2);

    // -- README -- 
    // here I will explain working : 
    // 1 - get xwars global instance by calling get_xwars_instance()
    // 2 - call load_bots with filenames to load bots into the "bots" vector
    // 3 - to copy any two bots into memory, call "copy_bots" 

    // our bots
    std::vector<xbot*> bots;
    // paths of all bots
    std::vector<std::string> botpaths;
    // names of all bots
    std::vector<std::string> botnames;
};

// get xwars global instance
xwars* get_xwars_instance();

// close everyting, deallocate everything etc...
void shutdown_xwars();

#endif//XVM_XWAR_HPP
