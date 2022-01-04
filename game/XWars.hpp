#ifndef XVM_XWAR_HPP
#define XVM_XWAR_HPP

#include "../xasm/xasm.h"
#include "BotInfo.hpp"
#include "Common.hpp"
#include "XBot.hpp"
#include <utility>

#define MAX_INSTR_EXECS 2000
#define MAX_BOT_SIZE 0x180

struct xwars {
    xwars();
    ~xwars();

    // // register bot info panels that must be updated
    // void register_bot_info(BotInfo* first, BotInfo* second);

    // this will allocate bots for the first time by loading
    // the assembly file(s) from locations in bot_paths
    void load_bots(const std::vector<std::string>& bot_paths,
        const std::vector<std::string>& bot_names);

    // display registers in the ui
    void display_registers(xbot* bot1, xbot* bot2);

    // display disassembly in the ui
    void display_disassembly(xbot* bot1, xbot* bot2);

    // this will copy bots to text_section
    void copy_bots(xbot* bot1, xbot* bot2);

    // do battle b/w bots
    // this will return true if battle is initialized successfully
    // also this will already take one step into the battle
    bool battle_init(std::string Bot1Path, std::string Bot2Path);

    // takes a next step into battle and returns whether bots can fight
    // again or not, true means this must be called again, false otherwise
    bool battle_step();

    void set_battle_status(u32 value);
    u32 get_battle_status();

    // -- README --
    // here I will explain working :
    // 1 - get xwars global instance by calling get_xwars_instance()
    // 2 - call load_bots with filenames to load bots into the "bots" vector
    // 3 - to copy any two bots into memory, call "copy_bots"

    // paths of all bots
    std::vector<std::string> botpaths;

    // number of steps executed
    u32 counter = 0;

    // winner of last battle
    wxString winner = "";

private:
    // first - left
    // second - right
    std::pair<BotInfo*, BotInfo*> m_botInfos;

    // current fighting bots
    std::pair<xbot*, xbot*> m_currentBots;

    // is battle running
    u32 battle_status = 0;
};

// get xwars global instance
xwars* get_xwars_instance();

// close everyting, deallocate everything etc...
void shutdown_xwars();

#endif // XVM_XWAR_HPP
