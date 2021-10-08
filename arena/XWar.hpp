#ifndef XVM_XWAR_HPP
#define XVM_XWAR_HPP

#include "Common.hpp"
#include "XBot.hpp"
#include <utility>

struct xwar{
    xwar();
    ~xwar();

    // this will allocate bots for the first time by loading
    // the assembly file(s) from locations in bot_paths
    void load_bots(const std::vector<cstring>& bot_paths, const std::vector<cstring>& bot_names);

    // this will copy bots to text_section
    void copy_bots(xbot *bot1, xbot *bot2);

    // bots that are currently loaded into memory
    // load_bots will store bot1 and bot2 here
    // in the first and second member
    std::pair<xbot*, xbot*> current_bots;

    // -- README -- 
    // here I will explain working : 
    // 1 - get xwar global instance by calling get_xwar()
    // 2 - call load_bots with filenames to load bots into the "bots" vector
    // 3 - to copy any two bots into memory, call "copy_bots" 

    // our bots
    std::vector<xbot*> bots;
    // paths of all bots
    std::vector<cstring> botpaths;
    // names of all bots
    std::vector<cstring> botnames;
    // this is the actual memory region that will contain our bots
    section_entry *text_section;
};

// get xwar global instance
xwar* get_xwar();

// close everyting, deallocate everything etc...
void shutdown_xwar();

#endif//XVM_XWAR_HPP