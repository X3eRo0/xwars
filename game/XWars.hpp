#ifndef XVM_XWAR_HPP
#define XVM_XWAR_HPP

#include "Common.hpp"
#include "XBot.hpp"
#include "../xasm/xasm.h"
#include <utility>
#include "BotInfo.hpp"

#define MAX_INSTR_EXECS 2000

struct xwars{
    xwars();
    ~xwars();

    // register bot info panels that must be updated
    void register_bot_info(BotInfo* first, BotInfo* second);

    // compile given bots
    void compile_bots(const std::vector<std::string>& bot_paths);

    // this will allocate bots for the first time by loading
    // the assembly file(s) from locations in bot_paths
    void load_bots(const std::vector<std::string>& bot_paths, const std::vector<std::string>& bot_names);
    
    // display registers in the ui
    void display_registers(xbot *bot1, xbot *bot2);
    
    // display disassembly in the ui
    void display_disassembly(xbot *bot1, xbot *bot2);
    
    // this will copy bots to text_section
    void copy_bots(xbot *bot1, xbot *bot2);

    // do battle b/w bots
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
private:
    // first - left
    // second - right
    std::pair<BotInfo*, BotInfo*> m_botInfos;
};

// get xwars global instance
xwars* get_xwars_instance();

// close everyting, deallocate everything etc...
void shutdown_xwars();

#endif//XVM_XWAR_HPP
