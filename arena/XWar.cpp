#include "XWar.hpp"
#include "XBot.hpp"
//
// Created by X3eRo0 on 6/7/2021.
//
// modified @brightprogrammer on 10/7/2021
//     modification : many changes, do diff with original "xwars/bot.c" to see them
//     reason : modifying code for use in arena
//     other files modified : common/sections.h, common/sections.c 

// this static instance will be allocated when
// get_xwar is called for the first time
// and must be deleted explicitly because of that
//
// in this cpp file we can use this xwar_instance by it's name
// but in other cpp/hpp files we will need to call get_xwar()
// to get this instance
static xwar *xwar_instance;

// will create a new xwar_instance if not created already
// and return the intance
xwar* get_xwar(){
    if(!xwar_instance){
        xwar_instance = new xwar;
    }

    return xwar_instance;
}

// deallocate xwar and related stuffs
void shutdown_xwar(){
    delete xwar_instance;
}

// constructor
xwar::xwar(){
    text_section = init_section_entry();
    set_section_entry(text_section, ".text", 0x400, 0x1337000, PERM_READ | PERM_WRITE | PERM_EXEC);
}

void xwar::load_bots(const std::vector<cstring> &bot_paths){
    // allocate memory space for all bots
    bots.resize(bot_paths.size());
    
    // initialize every bot
    for(size_t i = 0; i < bots.size(); i++){
        // shorter names
        xbot* &bot = bots[i];
        cstring bot_path = bot_paths[i];

        // initialize this bot
        bot = new xbot;
    
        // add stacks for each bots
        add_section(bot->bin->x_section, "stack", XVM_STACK_SIZE, XVM_DFLT_SP & 0xfffff000, PERM_READ | PERM_WRITE);
    
        // initialize stack pointer to default value
        bot->cpu->regs.sp = XVM_DFLT_SP;

        // load binary file
        // load init and bot sections
        xvm_bin_load_file(bot->bin, bot_path);

        // remove .text section
        remove_section_by_name(bot->bin->x_section, ".text");
    
        // set init address
        bot->init_addr = find_section_entry_by_name(bot->bin->x_section, ".init")->v_addr;
    
        // add the .text in bot1
        bot->add_section(text_section);
    }
}

// load bots into text section at random placesx
void xwar::copy_bots(xbot *bot1, xbot *bot2){
    bot1->bot_section = find_section_entry_by_name(bot1->bin->x_section, ".bot");
    bot1->size = bot1->bot_section->m_ofst;

    bot2->bot_section = find_section_entry_by_name(bot2->bin->x_section, ".bot");
    bot2->size = bot2->bot_section->m_ofst;

    // random seed
    srandom(time(nullptr));

    // assign bot1 in first half
    while ((bot1->offset < 0x20) || (bot1->offset > 0x200 - bot1->size)){
        bot1->offset = random() & 0xfff;
    }

    // assign bot2 in second half
    while ((bot2->offset < 0x220) || (bot2->offset > 0x400 - bot2->size)){
        bot2->offset = random() & 0xfff;
    }

    bot1->bot_addr = text_section->v_addr + bot1->offset;
    bot2->bot_addr = text_section->v_addr + bot2->offset;

    printf("text : 0x%x\n", text_section->v_addr);
    printf("bot1 offset: 0x%x\n", bot1->offset);
    printf("bot2 offset: 0x%x\n", bot2->offset);

    memcpy(&(text_section->m_buff[bot1->offset]), bot1->bot_section->m_buff, bot1->size);
    memcpy(&(text_section->m_buff[bot2->offset]), bot2->bot_section->m_buff, bot2->size);

    // save these bots in current_bots
    current_bots.first = bot1;
    current_bots.second = bot2;
}

// destructor
xwar::~xwar(){
    fini_section_entry(text_section); text_section = NULL;
    
    // destroy bots
    // bots were alloc'd with new operator so
    // the must be dealloc'd with delete operator
    for(xbot* bot : bots){
        delete bot;
    }
}