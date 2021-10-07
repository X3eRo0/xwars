#include "XWar.hpp"
#include "XBot.hpp"
//
// Created by X3eRo0 on 6/7/2021.
//
// modified @brightprogrammer on 10/7/2021
//     modification : many changes, do diff with original "xwars/bot.c" to see them
//     reason : modifying code for use in arena
//     other files modified : common/sections.h, common/sections.c 

extern FILE * logfifo1;
extern FILE * logfifo2;

// constructor
xwar::xwar(cstring bot_path1, cstring bot_path2){
    bot1 = init_xbot();
    bot2 = bot1 = init_xbot();

    text_section = init_section_entry();
    set_section_entry(text_section, ".text", 0x400, 0x1337000, PERM_READ | PERM_WRITE | PERM_EXEC);

    // add 2 different stacks for both bots
    add_section(bot1->bin->x_section, "stack", XVM_STACK_SIZE, XVM_DFLT_SP & 0xfffff000, PERM_READ | PERM_WRITE);
    add_section(bot2->bin->x_section, "stack", XVM_STACK_SIZE, XVM_DFLT_SP & 0xfffff000, PERM_READ | PERM_WRITE);
    bot1->cpu->regs.sp = XVM_DFLT_SP;
    bot2->cpu->regs.sp = XVM_DFLT_SP;

    // load .init and .bot sections
    xvm_bin_load_file(bot1->bin, bot_path1);
    xvm_bin_load_file(bot2->bin, bot_path2);

        remove_section_by_name(bot1->bin->x_section, ".text");
    remove_section_by_name(bot2->bin->x_section, ".text");

    // execute some number of instructions from .init for initialisation purposes
    bot1->init_addr = find_section_entry_by_name(bot1->bin->x_section, ".init")->v_addr;
    bot2->init_addr = find_section_entry_by_name(bot2->bin->x_section, ".init")->v_addr;

    // add the .text in bot1
    temp_section = bot1->bin->x_section->sections;
    while (temp_section->next != NULL){
        temp_section = temp_section->next;
    }
    
    temp_section->next = text_section;
    bot1->bin->x_section->n_sections++;

    // add the .text_section in bot2
    temp_section = bot2->bin->x_section->sections;
    while (temp_section->next != NULL){
        temp_section = temp_section->next;
    }

    temp_section->next = text_section;
    bot2->bin->x_section->n_sections++;

    // copy bot1 and bot2 to text_section
    copy_bots(bot1, bot2, text_section);

    // remove bot sections
    remove_section_by_name(bot1->bin->x_section, ".bot");
    remove_section_by_name(bot2->bin->x_section, ".bot");
    bot1->bot_section = NULL;
    bot2->bot_section = NULL;

}

// destructor
xwar::~xwar(){
    fini_xbot(bot1);
    fini_xbot(bot2);
}