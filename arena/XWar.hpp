#ifndef XVM_XWAR_HPP
#define XVM_XWAR_HPP

#include "Common.hpp"
#include "XBot.hpp"


struct xwar{
    xwar(cstring bot_path1, cstring bot_path2);
    ~xwar();

    // our bots
    xbot *bot1, *bot2;
    // this is the actual memory region that will contain our bots
    section_entry *text_section;
    // temporary section
    section_entry *temp_section;
};

#endif//XVM_XWAR_HPP