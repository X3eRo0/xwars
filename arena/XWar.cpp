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
// xwar::xwar(const std::vector<cstring>& bot_paths){
//     allocate_bots(bot_paths);

//     text_section = init_section_entry();
//     set_section_entry(text_section, ".text", 0x400, 0x1337000, PERM_READ | PERM_WRITE | PERM_EXEC);

//     // load .init and .bot sections
//     xvm_bin_load_file(bot1->bin, bot_path1);
//     xvm_bin_load_file(bot2->bin, bot_path2);

//         remove_section_by_name(bot1->bin->x_section, ".text");
//     remove_section_by_name(bot2->bin->x_section, ".text");

//     // execute some number of instructions from .init for initialisation purposes
//     bot1->init_addr = find_section_entry_by_name(bot1->bin->x_section, ".init")->v_addr;
//     bot2->init_addr = find_section_entry_by_name(bot2->bin->x_section, ".init")->v_addr;

//     // add the .text in bot1
//     temp_section = bot1->bin->x_section->sections;
//     while (temp_section->next != NULL){
//         temp_section = temp_section->next;
//     }
    
//     temp_section->next = text_section;
//     bot1->bin->x_section->n_sections++;

//     // add the .text_section in bot2
//     temp_section = bot2->bin->x_section->sections;
//     while (temp_section->next != NULL){
//         temp_section = temp_section->next;
//     }

//     temp_section->next = text_section;
//     bot2->bin->x_section->n_sections++;

//     // copy bot1 and bot2 to text_section
//     copy_bots(bot1, bot2, text_section);

//     // remove bot sections
//     remove_section_by_name(bot1->bin->x_section, ".bot");
//     remove_section_by_name(bot2->bin->x_section, ".bot");
//     bot1->bot_section = NULL;
//     bot2->bot_section = NULL;

//     // push address of botcode and run init function
//     bot1->cpu->regs.sp -= sizeof(u32);
//     write_dword(bot1->bin->x_section, bot1->cpu->regs.sp, bot1->bot_addr);
//     bot1->cpu->regs.pc = bot1->init_addr;

//     // push address of botcode and run init function
//     bot2->cpu->regs.sp -= sizeof(u32);
//     write_dword(bot2->bin->x_section, bot2->cpu->regs.sp, bot2->bot_addr);
//     bot2->cpu->regs.pc = bot2->init_addr;

//     u8 winner = 0;
//     u32 counter = 0;
//     int init_status = 0;
    
//     while (
//             (counter < 0x50) &&
//             get_RF(bot1->cpu) && 
//             get_RF(bot2->cpu)
//     ){
//         if (!wait_for_gui()){
//             continue;
//         }

//         xlog("SENDING\n");
//         // dump registers
//         dump_reg(bot1, bot2);
//         dump_dis(bot1, bot2);
        
//         if (bot1->cpu->regs.pc != text_section->v_addr + bot1->offset){
//             step(bot1);

//             if (signal_abort(bot1->cpu->errors, bot1->cpu) == E_ERR){
//                 init_status = -1;
//                 break;
//             }
//             if (signal_abort(bot1->bin->x_section->errors, bot1->cpu) == E_ERR){
//                 init_status = -1;
//                 break;
//             }
//         }
        
//         if (bot2->cpu->regs.pc != text_section->v_addr + bot2->offset){   
//             step(bot2);

//             if (signal_abort(bot2->cpu->errors, bot2->cpu) == E_ERR){
//                 init_status = -1;
//                 break;
//             }
//             if (signal_abort(bot2->bin->x_section->errors, bot2->cpu) == E_ERR){
//                 init_status = -1;
//                 break;
//             }
//         }
//         counter++;
//     }

//     if (init_status == -1){
//         xlog("INIT_FAILED\n");
//     }
//     if (init_status == 0){
//         xlog("INIT_SUCCESS\n");
//     }

//     // execution loop
//     while ((counter < 0x2050) && get_RF(bot1->cpu) && get_RF(bot2->cpu)){

//         if (!wait_for_gui()){
//             continue;
//         }
//         xlog("SENDING\n");
//         // dump registers
//         dump_reg(bot1, bot2);
//         dump_dis(bot1, bot2);
//         step(bot1);

//         if (signal_abort(bot1->cpu->errors, bot1->cpu) == E_ERR){
//             winner = 2;
//             break;
//         }
//         if (signal_abort(bot1->bin->x_section->errors, bot1->cpu) == E_ERR){
//             winner = 2;
//             break;
//         }

//         step(bot2);

//         if (signal_abort(bot2->cpu->errors, bot2->cpu) == E_ERR){
//             winner = 1;
//             break;
//         }
//         if (signal_abort(bot2->bin->x_section->errors, bot2->cpu) == E_ERR){
//             winner = 1;
//             break;
//         }
//         counter++;
//     }

//     if (wait_for_gui()){
//         xlog("Winner : %d\n", winner);
//     }

//     wait_for_gui();

//     temp_section = bot1->bin->x_section->sections;
//     while (temp_section->next != text_section){
//         temp_section = temp_section->next;
//     }
//     temp_section->next = NULL;
//     bot1->bin->x_section->n_sections--;

//     temp_section = bot2->bin->x_section->sections;
//     while (temp_section->next != text_section){
//         temp_section = temp_section->next;
//     }

//     temp_section->next = NULL;
//     bot2->bin->x_section->n_sections--;
// }

void xwar::allocate_bots(const std::vector<cstring> &bot_paths){
    // allocate memory space for all bots
    bots.resize(bot_paths.size());
    
    // initialize every bot
    for(size_t i = 0; i < bots.size(); i++){
        // shorter names
        xbot* &bot = bots[i];
        cstring bot_path = bot_paths[i];

        // initialize this bot
        bot = init_xbot();
    
        // add stacks for each bots
        add_section(bot->bin->x_section, "stack", XVM_STACK_SIZE, XVM_DFLT_SP & 0xfffff000, PERM_READ | PERM_WRITE);
    
        // initialize stack pointer to default value
        bot->cpu->regs.sp = XVM_DFLT_SP;

        // load binary file
        xvm_bin_load_file(bot->bin, bot_path);
    }

}

// destructor
xwar::~xwar(){
    fini_section_entry(text_section); text_section = NULL;
    // destroy bots
}