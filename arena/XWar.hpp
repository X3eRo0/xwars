#ifndef XVM_XWAR_HPP
#define XVM_XWAR_HPP

#include "Common.hpp"
#include "XBot.hpp"
#include "Utils/Singleton.hpp"

struct xwar : public Singleton<xwar>{
    xwar(const std::vector<cstring>& bot_paths);
    ~xwar();

    void allocate_bots(const std::vector<cstring>& bot_paths);

    // our bots
    std::vector<xbot*> bots;
    // this is the actual memory region that will contain our bots
    section_entry *text_section;
    // temporary section
    section_entry *temp_section;
};

#endif//XVM_XWAR_HPP