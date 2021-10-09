#include "XBot.hpp"

// initialize xbot
xbot::xbot(){
    cpu = init_xvm_cpu();
    bin = init_xvm_bin();
    bot_addr = 0;
    offset = 0;
    size = 0;
    bot_section = NULL;
}

// bot destructor
xbot::~xbot(){
    if (cpu != nullptr) fini_xvm_cpu(cpu);
    if (bin) fini_xvm_bin(bin);
}

// add a new section to this bot
void xbot::add_section(section_entry* sxn){
    section_entry *tmp_sxn = bin->x_section->sections;
    while (tmp_sxn->next != NULL){
        tmp_sxn = tmp_sxn->next;
    }
        
    tmp_sxn->next = sxn;
    bin->x_section->n_sections++;
}

u32 xbot::step(){
    return do_execute(cpu, bin);
}


// // xlog is writing to logfifo2
// // logfifo2 is writable only
// // logfifo1 is readable only
// u32 xlog(const char *message, ...){
//     va_list args;
//     va_start(args, message);
//     vfprintf(logfifo2, message, args);
//     va_end(args);
//     return E_OK;
// }

// // if the last line of gui contains "CONT"
// // then it will move forward
// u32 wait_for_gui(){
//     char buffer[5];
//     fread(buffer, 1, 4, logfifo1);
//     buffer[4] = '\0';
//     return strncmp(buffer, "CONT", 4) == 0;
// }

// // copies register values into the logfifo2
// u32 dump_reg(xbot* bot1, xbot* bot2){
//     fwrite("bot1->register_dump\n", 1, 20, logfifo2);
//     fprintf(logfifo2, "$r0 : 0x%.8X\t$r1 : 0x%.8X\t$r2 : 0x%.8X\t$r3 : 0x%.8X\n", bot1->cpu->regs.r0, bot1->cpu->regs.r1, bot1->cpu->regs.r2, bot1->cpu->regs.r3);
//     fprintf(logfifo2, "$r4 : 0x%.8X\t$r5 : 0x%.8X\t$r6 : 0x%.8X\t$r7 : 0x%.8X\n", bot1->cpu->regs.r4, bot1->cpu->regs.r5, bot1->cpu->regs.r6, bot1->cpu->regs.r7);
//     fprintf(logfifo2, "$r8 : 0x%.8X\t$r9 : 0x%.8X\t$ra : 0x%.8X\t$rb : 0x%.8X\n", bot1->cpu->regs.r8, bot1->cpu->regs.r9, bot1->cpu->regs.ra, bot1->cpu->regs.rb);
//     fprintf(logfifo2, "$rc : 0x%.8X\t$pc : 0x%.8X\t$bp : 0x%.8X\t$sp : 0x%.8X\n", bot1->cpu->regs.rc, bot1->cpu->regs.pc, bot1->cpu->regs.bp, bot1->cpu->regs.sp);
//     fwrite("bot2->register_dump\n", 1, 20, logfifo2);
//     fprintf(logfifo2, "$r0 : 0x%.8X\t$r1 : 0x%.8X\t$r2 : 0x%.8X\t$r3 : 0x%.8X\n", bot2->cpu->regs.r0, bot2->cpu->regs.r1, bot2->cpu->regs.r2, bot2->cpu->regs.r3);
//     fprintf(logfifo2, "$r4 : 0x%.8X\t$r5 : 0x%.8X\t$r6 : 0x%.8X\t$r7 : 0x%.8X\n", bot2->cpu->regs.r4, bot2->cpu->regs.r5, bot2->cpu->regs.r6, bot2->cpu->regs.r7);
//     fprintf(logfifo2, "$r8 : 0x%.8X\t$r9 : 0x%.8X\t$ra : 0x%.8X\t$rb : 0x%.8X\n", bot2->cpu->regs.r8, bot2->cpu->regs.r9, bot2->cpu->regs.ra, bot2->cpu->regs.rb);
//     fprintf(logfifo2, "$rc : 0x%.8X\t$pc : 0x%.8X\t$bp : 0x%.8X\t$sp : 0x%.8X\n", bot2->cpu->regs.rc, bot2->cpu->regs.pc, bot2->cpu->regs.bp, bot2->cpu->regs.sp);
//     return E_OK;
// }

// // copies disassembled code of both the bots into logfifo2
// u32 dump_dis(xbot* bot1, xbot* bot2){
//     section_entry * text = find_section_entry_by_name(bot1->bin->x_section, ".text");
//     xlog("bot1->disasm\n");
//     // xasm_disassemble_bytes(logfifo2, bot1->bin, (char *)get_reference(bot1->bin->x_section, bot1->cpu->regs.pc, PERM_EXEC), text->v_size - (bot1->cpu->regs.pc - text->v_addr), 20, bot1->cpu->regs.pc);
//     xasm_disassemble_bytes(logfifo2,
//                            bot1->bin,
//                            (char *) get_reference(bot1->bin->x_section, bot1->cpu->regs.pc, PERM_EXEC),
//                            text->v_size - (bot1->cpu->regs.pc - text->v_addr),
//                            bot1->cpu->regs.pc,
//                            20);
//     xlog("bot2->disasm\n");
//     xasm_disassemble_bytes(logfifo2,
//                            bot2->bin,
//                            (char *) get_reference(bot2->bin->x_section, bot2->cpu->regs.pc, PERM_EXEC),
//                            text->v_size - (bot2->cpu->regs.pc - text->v_addr),
//                            bot2->cpu->regs.pc,
//                            20);

//     return E_OK;
// }

