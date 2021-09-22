//
// Created by X3eRo0 on 6/7/2021.
//

#include "xwars.h"

FILE * logfifo1 = NULL;
FILE * logfifo2 = NULL;

void __attribute__ ((constructor)) init_xwars(){

    char read_buffer[5] = {0};

    fprintf(stderr, "[" KYEL "#" KNRM "] Waiting for frontend\n");
    do {
        logfifo1 = fopen("/tmp/xwars_1", "r");
        logfifo2 = fopen("/tmp/xwars_2", "w");
    } while (logfifo1 == NULL || logfifo2 == NULL);

    setbuf(logfifo1, 0);
    setbuf(logfifo2, 0);

    fread(read_buffer, 1, 4, logfifo1);
    fwrite("INIT", 1, 4, logfifo2);
    fprintf(stderr, "[" KGRN "+" KNRM "] Connection Established\n");
    fprintf(stderr, "[" KGRN "+" KNRM "] logfifo created\n");
}

void __attribute__ ((destructor)) fini_xwars(){
    fclose(logfifo1);
    fclose(logfifo2);
}

int main(int argc, char *argv[]){

    if (argc != 3){
        fprintf(stderr, "Usage: xwars <bot1> <bot2>");
        exit(-1);
    }

    xbot* bot1 = init_xbot();
    xbot* bot2 = init_xbot();

    section_entry * temp = NULL;
    section_entry * text = init_section_entry();
    set_section_entry(text, ".text", 0x400, 0x1337000, PERM_READ | PERM_WRITE | PERM_EXEC);


    // add 2 different stacks for both bots
    add_section(bot1->bin->x_section, "stack", XVM_STACK_SIZE, XVM_DFLT_SP & 0xfffff000, PERM_READ | PERM_WRITE);
    add_section(bot2->bin->x_section, "stack", XVM_STACK_SIZE, XVM_DFLT_SP & 0xfffff000, PERM_READ | PERM_WRITE);
    bot1->cpu->regs.sp = XVM_DFLT_SP;
    bot2->cpu->regs.sp = XVM_DFLT_SP;

    // load .init and .bot sections
    xvm_bin_load_file(bot1->bin, argv[1]);
    xvm_bin_load_file(bot2->bin, argv[2]);

    remove_section_by_name(bot1->bin->x_section, ".text");
    remove_section_by_name(bot2->bin->x_section, ".text");

    // execute some number of instructions from .init for initialisation purposes

    bot1->init_addr = find_section_entry_by_name(bot1->bin->x_section, ".init")->v_addr;
    bot2->init_addr = find_section_entry_by_name(bot2->bin->x_section, ".init")->v_addr;

    // add the .text in bot1
    temp = bot1->bin->x_section->sections;
    while (temp->next != NULL){
        temp = temp->next;
    }
    temp->next = text;
    bot1->bin->x_section->n_sections++;

    // add the .text in bot2
    temp = bot2->bin->x_section->sections;
    while (temp->next != NULL){
        temp = temp->next;
    }
    temp->next = text;
    bot2->bin->x_section->n_sections++;

    // copy bot1 and bot2 to text
    copy_bots(bot1, bot2, text);

    // remove bot sections
    remove_section_by_name(bot1->bin->x_section, ".bot");
    remove_section_by_name(bot2->bin->x_section, ".bot");
    bot1->bot_section = NULL;
    bot2->bot_section = NULL;

    // push address of botcode and run init function
    bot1->cpu->regs.sp -= sizeof(u32);
    write_dword(bot1->bin->x_section, bot1->cpu->regs.sp, bot1->bot_addr);
    bot1->cpu->regs.pc = text->v_addr + bot1->offset;

    // push address of botcode and run init function
    bot2->cpu->regs.sp -= sizeof(u32);
    write_dword(bot1->bin->x_section, bot1->cpu->regs.sp, bot2->bot_addr);
    bot2->cpu->regs.pc = text->v_addr + bot2->offset;

    u8 winner = 0;
    u32 counter = 0;
    int init_status = 0;
    
    while (
            (counter < 0x50) &&
            get_RF(bot1->cpu) && 
            get_RF(bot2->cpu)
    ){
        if (!wait_for_gui()){
            continue;
        }
        xlog("SENDING\n");
        // dump registers
        dump_reg(bot1, bot2);
        dump_dis(bot1, bot2);
        
        if (bot1->cpu->regs.pc != text->v_addr + bot1->offset){
            step(bot1);

            if (signal_abort(bot1->cpu->errors, bot1->cpu) == E_ERR){
                init_status = -1;
                break;
            }
            if (signal_abort(bot1->bin->x_section->errors, bot1->cpu) == E_ERR){
                init_status = -1;
                break;
            }
        }
        
        if (bot2->cpu->regs.pc != text->v_addr + bot2->offset){   
            step(bot2);

            if (signal_abort(bot2->cpu->errors, bot2->cpu) == E_ERR){
                init_status = -1;
                break;
            }
            if (signal_abort(bot2->bin->x_section->errors, bot2->cpu) == E_ERR){
                init_status = -1;
                break;
            }
        }
        counter++;
    }

    if (init_status == -1){
        xlog("INIT_FAILED\n");
    }
    if (init_status == 0){
        xlog("INIT_SUCCESS\n");
    }

    // execution loop
    while ((counter < 0x2050) && get_RF(bot1->cpu) && get_RF(bot2->cpu)){

        if (!wait_for_gui()){
            continue;
        }
        xlog("SENDING\n");
        // dump registers
        dump_reg(bot1, bot2);
        dump_dis(bot1, bot2);
        step(bot1);

        if (signal_abort(bot1->cpu->errors, bot1->cpu) == E_ERR){
            winner = 2;
            break;
        }
        if (signal_abort(bot1->bin->x_section->errors, bot1->cpu) == E_ERR){
            winner = 2;
            break;
        }

        step(bot2);

        if (signal_abort(bot2->cpu->errors, bot2->cpu) == E_ERR){
            winner = 1;
            break;
        }
        if (signal_abort(bot2->bin->x_section->errors, bot2->cpu) == E_ERR){
            winner = 1;
            break;
        }
        counter++;
    }

    if (wait_for_gui()){
        xlog("Winner : %d\n", winner);
    }

    wait_for_gui();

    temp = bot1->bin->x_section->sections;
    while (temp->next != text){
        temp = temp->next;
    }
    temp->next = NULL;
    bot1->bin->x_section->n_sections--;

    temp = bot2->bin->x_section->sections;
    while (temp->next != text){
        temp = temp->next;
    }

    temp->next = NULL;
    bot2->bin->x_section->n_sections--;

    fini_section_entry(text); text = NULL;

    fini_xbot(bot1); bot1 = NULL;
    fini_xbot(bot2); bot2 = NULL;

    return E_OK;
}
