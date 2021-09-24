//
// Created by X3eRo0 on 6/7/2021.
//

#include "xwars.h"
extern FILE * logfifo1;
extern FILE * logfifo2;

xbot *init_xbot(){
    xbot *bot = (xbot *)malloc(sizeof(xbot));
    bot->cpu = init_xvm_cpu();
    bot->bin = init_xvm_bin();
    bot->bot_addr = 0;
    bot->init_addr = 0;
    bot->offset = 0;
    bot->size = 0;
    bot->bot_section = NULL;
    return bot;
}

u32 step(xbot* bot){
    return do_execute(bot->cpu, bot->bin);
}

u32 copy_bots(xbot* bot1, xbot* bot2, section_entry* text){
    // get random offsets

    bot1->bot_section = find_section_entry_by_name(bot1->bin->x_section, ".bot");
    bot1->size = bot1->bot_section->m_ofst;

    bot2->bot_section = find_section_entry_by_name(bot2->bin->x_section, ".bot");
    bot2->size = bot2->bot_section->m_ofst;


    srandom(time(NULL));
    // assign bot1 in first half
    while ( (bot1->offset < 0x20) ||
            (bot1->offset > 0x200 - bot1->size)
    ){
        bot1->offset = random() & 0xfff;
    }

    // assign bot2 in second half
    while ( (bot2->offset < 0x220) ||
            (bot2->offset > 0x400 - bot2->size)
            ){
        bot2->offset = random() & 0xfff;
    }

    bot1->bot_addr = text->v_addr + bot1->offset;
    bot2->bot_addr = text->v_addr + bot2->offset;

    printf("text : 0x%x\n", text->v_addr);
    printf("bot1 offset: 0x%x\n", bot1->offset);
    printf("bot2 offset: 0x%x\n", bot2->offset);

    memcpy(&text->m_buff[bot1->offset], bot1->bot_section->m_buff, bot1->size);
    memcpy(&text->m_buff[bot2->offset], bot2->bot_section->m_buff, bot2->size);

    return 0;
}


u32 xlog(char *message, ...){
    va_list args;
    va_start(args, message);
    vfprintf(logfifo2, message, args);
    va_end(args);
    return E_OK;
}

u32 wait_for_gui(){
    char buffer[5];
    fread(buffer, 1, 4, logfifo1);
    buffer[4] = '\0';
    return strncmp(buffer, "CONT", 4) == 0;
}

u32 dump_reg(xbot* bot1, xbot* bot2){
    fwrite("bot1->register_dump\n", 1, 20, logfifo2);
    fprintf(logfifo2, "$r0 : 0x%.8X\t$r1 : 0x%.8X\t$r2 : 0x%.8X\t$r3 : 0x%.8X\n", bot1->cpu->regs.r0, bot1->cpu->regs.r1, bot1->cpu->regs.r2, bot1->cpu->regs.r3);
    fprintf(logfifo2, "$r4 : 0x%.8X\t$r5 : 0x%.8X\t$r6 : 0x%.8X\t$r7 : 0x%.8X\n", bot1->cpu->regs.r4, bot1->cpu->regs.r5, bot1->cpu->regs.r6, bot1->cpu->regs.r7);
    fprintf(logfifo2, "$r8 : 0x%.8X\t$r9 : 0x%.8X\t$ra : 0x%.8X\t$rb : 0x%.8X\n", bot1->cpu->regs.r8, bot1->cpu->regs.r9, bot1->cpu->regs.ra, bot1->cpu->regs.rb);
    fprintf(logfifo2, "$rc : 0x%.8X\t$pc : 0x%.8X\t$bp : 0x%.8X\t$sp : 0x%.8X\n", bot1->cpu->regs.rc, bot1->cpu->regs.pc, bot1->cpu->regs.bp, bot1->cpu->regs.sp);
    fwrite("bot2->register_dump\n", 1, 20, logfifo2);
    fprintf(logfifo2, "$r0 : 0x%.8X\t$r1 : 0x%.8X\t$r2 : 0x%.8X\t$r3 : 0x%.8X\n", bot2->cpu->regs.r0, bot2->cpu->regs.r1, bot2->cpu->regs.r2, bot2->cpu->regs.r3);
    fprintf(logfifo2, "$r4 : 0x%.8X\t$r5 : 0x%.8X\t$r6 : 0x%.8X\t$r7 : 0x%.8X\n", bot2->cpu->regs.r4, bot2->cpu->regs.r5, bot2->cpu->regs.r6, bot2->cpu->regs.r7);
    fprintf(logfifo2, "$r8 : 0x%.8X\t$r9 : 0x%.8X\t$ra : 0x%.8X\t$rb : 0x%.8X\n", bot2->cpu->regs.r8, bot2->cpu->regs.r9, bot2->cpu->regs.ra, bot2->cpu->regs.rb);
    fprintf(logfifo2, "$rc : 0x%.8X\t$pc : 0x%.8X\t$bp : 0x%.8X\t$sp : 0x%.8X\n", bot2->cpu->regs.rc, bot2->cpu->regs.pc, bot2->cpu->regs.bp, bot2->cpu->regs.sp);
    return E_OK;
}

u32 dump_dis(xbot* bot1, xbot* bot2){

    section_entry * text = find_section_entry_by_name(bot1->bin->x_section, ".text");
    xlog("bot1->disasm\n");
    // xasm_disassemble_bytes(logfifo2, bot1->bin, (char *)get_reference(bot1->bin->x_section, bot1->cpu->regs.pc, PERM_EXEC), text->v_size - (bot1->cpu->regs.pc - text->v_addr), 20, bot1->cpu->regs.pc);
    xasm_disassemble_bytes(logfifo2,
                           bot1->bin,
                           (char *) get_reference(bot1->bin->x_section, bot1->cpu->regs.pc, PERM_EXEC),
                           text->v_size - (bot1->cpu->regs.pc - text->v_addr),
                           bot1->cpu->regs.pc,
                           20);
    xlog("bot2->disasm\n");
    xasm_disassemble_bytes(logfifo2,
                           bot2->bin,
                           (char *) get_reference(bot2->bin->x_section, bot2->cpu->regs.pc, PERM_EXEC),
                           text->v_size - (bot2->cpu->regs.pc - text->v_addr),
                           bot2->cpu->regs.pc,
                           20);

    return E_OK;
}


void fini_xbot(xbot *bot){
    if (!bot){
        return;
    }

    if (bot->cpu){
        fini_xvm_cpu(bot->cpu);
    }



    if (bot->bin){
        fini_xvm_bin(bot->bin);
    }

    free(bot); bot = NULL;
}
