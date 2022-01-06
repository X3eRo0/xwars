#include "XWars.hpp"
#include "../common/bitmap.h"
#include "../xasm/xasm.h"
#include "Common.hpp"
#include "Factory.hpp"
#include "MainWindow.hpp"
#include "MiddlePanel.hpp"
#include <cstdio>
#include <unistd.h>
#include <wx/app.h>
#include <wx/event.h>
#include <wx/time.h>
#include <wx/utils.h>

// Created by X3eRo0 on 6/7/2021.
//
// modified @brightprogrammer on 10/7/2021
//     modification : many changes, do diff with original "xwarss/bot.c"
//                    to see them
//     reason : modifying code for use in arena
//     other files modified : common/sections.h, common/sections.c

// this static instance will be allocated when
// get_xwars_instance is called for the first time
// and must be deleted explicitly because of that
//
// in this cpp file we can use this xwars_instance by it's name
// but in other cpp/hpp files we will need to call get_xwars()
// to get this instance

static xwars* xwars_instance = nullptr;

// writer_e and reader_e
// extern FILE * reader_e, * writer_e;

// will create a new xwars_instance if not created already
// and return the intance
xwars* get_xwars_instance()
{
    if (!xwars_instance) {
        xwars_instance = new xwars;
    }

    return xwars_instance;
}

// deallocate xwars and related stuffs
void shutdown_xwars()
{
    delete xwars_instance;
}

// constructor
xwars::xwars()
{
}

void xwars::display_registers(xbot* bot1, xbot* bot2)
{

    // update registers
    // update order must be same as Register::RegisterNames
    fprintf(bot1->reg_writer_e, "$r0=0x%.8x\n", bot1->cpu->regs.r0);
    fprintf(bot1->reg_writer_e, "$r1=0x%.8x\n", bot1->cpu->regs.r1);
    fprintf(bot1->reg_writer_e, "$r2=0x%.8x\n", bot1->cpu->regs.r2);
    fprintf(bot1->reg_writer_e, "$r3=0x%.8x\n", bot1->cpu->regs.r3);
    fprintf(bot1->reg_writer_e, "$r4=0x%.8x\n", bot1->cpu->regs.r4);
    fprintf(bot1->reg_writer_e, "$r5=0x%.8x\n", bot1->cpu->regs.r5);
    fprintf(bot1->reg_writer_e, "$r6=0x%.8x\n", bot1->cpu->regs.r6);
    fprintf(bot1->reg_writer_e, "$r7=0x%.8x\n", bot1->cpu->regs.r7);
    fprintf(bot1->reg_writer_e, "$r8=0x%.8x\n", bot1->cpu->regs.r8);
    fprintf(bot1->reg_writer_e, "$r9=0x%.8x\n", bot1->cpu->regs.r9);
    fprintf(bot1->reg_writer_e, "$ra=0x%.8x\n", bot1->cpu->regs.ra);
    fprintf(bot1->reg_writer_e, "$rb=0x%.8x\n", bot1->cpu->regs.rb);
    fprintf(bot1->reg_writer_e, "$rc=0x%.8x\n", bot1->cpu->regs.rc);
    fprintf(bot1->reg_writer_e, "$sp=0x%.8x\n", bot1->cpu->regs.sp);
    fprintf(bot1->reg_writer_e, "$bp=0x%.8x\n", bot1->cpu->regs.bp);
    fprintf(bot1->reg_writer_e, "$pc=0x%.8x\n", bot1->cpu->regs.pc);
    // fflush(bot1->reg_writer_e);

    // post event
    // wxCommandEvent e1(REGISTER_DISPLAY_UPDATE_EVENT);
    // e1.SetClientData((void *)bot1);
    // if(!m_botInfos.first) puts("No bot panel set!");
    // wxPostEvent(m_botInfos.first, e1);

    // direct call for update
    FactoryGetLeftBotInfo()->UpdateRegisterDisplay(bot1);

    // update registers
    fprintf(bot2->reg_writer_e, "$r0=0x%.8x\n", bot2->cpu->regs.r0);
    fprintf(bot2->reg_writer_e, "$r1=0x%.8x\n", bot2->cpu->regs.r1);
    fprintf(bot2->reg_writer_e, "$r2=0x%.8x\n", bot2->cpu->regs.r2);
    fprintf(bot2->reg_writer_e, "$r3=0x%.8x\n", bot2->cpu->regs.r3);
    fprintf(bot2->reg_writer_e, "$r4=0x%.8x\n", bot2->cpu->regs.r4);
    fprintf(bot2->reg_writer_e, "$r5=0x%.8x\n", bot2->cpu->regs.r5);
    fprintf(bot2->reg_writer_e, "$r6=0x%.8x\n", bot2->cpu->regs.r6);
    fprintf(bot2->reg_writer_e, "$r7=0x%.8x\n", bot2->cpu->regs.r7);
    fprintf(bot2->reg_writer_e, "$r8=0x%.8x\n", bot2->cpu->regs.r8);
    fprintf(bot2->reg_writer_e, "$r9=0x%.8x\n", bot2->cpu->regs.r9);
    fprintf(bot2->reg_writer_e, "$ra=0x%.8x\n", bot2->cpu->regs.ra);
    fprintf(bot2->reg_writer_e, "$rb=0x%.8x\n", bot2->cpu->regs.rb);
    fprintf(bot2->reg_writer_e, "$rc=0x%.8x\n", bot2->cpu->regs.rc);
    fprintf(bot2->reg_writer_e, "$sp=0x%.8x\n", bot2->cpu->regs.sp);
    fprintf(bot2->reg_writer_e, "$bp=0x%.8x\n", bot2->cpu->regs.bp);
    fprintf(bot2->reg_writer_e, "$pc=0x%.8x\n", bot2->cpu->regs.pc);
    // fflush(bot2->reg_writer_e);

    // post event
    // wxCommandEvent e2(REGISTER_DISPLAY_UPDATE_EVENT);
    // e2.SetClientData((void *)bot2);
    // if(!m_botInfos.second) puts("No bot panel set!");
    // wxPostEvent(m_botInfos.second, e2);

    // direct call for update
    FactoryGetRightBotInfo()->UpdateRegisterDisplay(bot2);

    // wait for all events to complete
    // wxTheApp->Yield();
}

void xwars::display_disassembly(xbot* bot1, xbot* bot2)
{
    if (!bot1 || !bot2) {
        return;
    }

    if (!bot1->cpu || !bot1->bin || !bot2->cpu || !bot2->bin) {
        return;
    }
    section_entry* text = find_section_entry_by_name(bot1->bin->x_section,
        ".text");

    if (!text) {
        return;
    }

    // generate disassembly and write to
    // to pipe
    xasm_disassemble_bytes(
        bot1->dis_writer_e,
        bot1->bin,
        (char*)get_reference(bot1->bin->x_section, bot1->cpu->regs.pc, 8 | PERM_READ),
        text->v_size - (bot1->cpu->regs.pc - text->v_addr),
        bot1->cpu->regs.pc,
        20);

    // direct call for update
    FactoryGetLeftBotInfo()->UpdateInstructionDisplay(bot1);

    xasm_disassemble_bytes(
        bot2->dis_writer_e,
        bot2->bin,
        (char*)get_reference(bot2->bin->x_section, bot2->cpu->regs.pc, 8 | PERM_READ),
        text->v_size - (bot2->cpu->regs.pc - text->v_addr),
        bot2->cpu->regs.pc,
        20);

    FactoryGetRightBotInfo()->UpdateInstructionDisplay(bot2);
}

// load bots into text section at random placesx
void xwars::copy_bots(xbot* bot1, xbot* bot2)
{
    section_entry* text = find_section_entry_by_name(bot1->bin->x_section, ".text");

    bot1->bot_section = find_section_entry_by_name(bot1->bin->x_section, ".bot");
    bot2->bot_section = find_section_entry_by_name(bot2->bin->x_section, ".bot");

    if (!bot1->bot_section) {
        fprintf(stderr, "[!] .bot section missing in %s\n", bot1->botname.c_str());
        exit(-1);
    }
    if (!bot2->bot_section) {
        fprintf(stderr, "[!] .bot section missing in %s\n", bot2->botname.c_str());
        exit(-1);
    }

    bot1->size = bot1->bot_section->m_ofst;
    bot2->size = bot2->bot_section->m_ofst;

    if (bot1->size > MAX_BOT_SIZE) {
        bot1->size = MAX_BOT_SIZE;
    }
    if (bot2->size > MAX_BOT_SIZE) {
        bot2->size = MAX_BOT_SIZE;
    }
    // random seed
    srandom(time(nullptr));

    xbot* firstbot = bot1;
    xbot* secondbot = bot2;

    if (random() & 1) {
        firstbot = bot2;
        secondbot = bot1;
    }

    // assign bot1 in first half
    do {
        firstbot->offset = random() & 0xfff;
    } while (firstbot->offset > (XWARS_MEM_SIZE) - firstbot->size);

    // assign bot2 in second half
    /* while ((secondbot->offset < (XWARS_MEM_SIZE / 2)) || (secondbot->offset > (XWARS_MEM_SIZE)-secondbot->size)) { */
    /*     secondbot->offset = random() & 0xfff; */
    /* } */

    u32 second_offset = firstbot->offset + firstbot->size + random() & 0xfff;

    if (second_offset > XWARS_MEM_SIZE - secondbot->size){
        second_offset -= secondbot->size;
    }

    if (second_offset >= XWARS_MEM_SIZE){
        second_offset %= XWARS_MEM_SIZE;
    }

    if (second_offset >= firstbot->offset){
        second_offset %= firstbot->offset;
    }

    secondbot->offset = second_offset;

    firstbot = NULL;
    secondbot = NULL;

    bot1->bot_addr = text->v_addr + bot1->offset;
    bot2->bot_addr = text->v_addr + bot2->offset;

    memcpy(&(text->m_buff[bot1->offset]), bot1->bot_section->m_buff, bot1->size);
    memcpy(&(text->m_buff[bot2->offset]), bot2->bot_section->m_buff, bot2->size);
}

bool xwars::battle_init(std::string Bot1Path, std::string Bot2Path)
{
    // reset counter
    counter = 0;

    // delete old bots
    if (m_currentBots.first && m_currentBots.second) {
        section_entry* text = find_section_entry_by_name(m_currentBots.first->bin->x_section, ".text");
        section_entry* temp = m_currentBots.first->bin->x_section->sections;

        while (temp->next != text) {
            temp = temp->next;
        }
        temp->next = NULL;
        m_currentBots.first->bin->x_section->n_sections--;

        temp = m_currentBots.second->bin->x_section->sections;
        while (temp->next != text) {
            temp = temp->next;
        }

        temp->next = NULL;
        m_currentBots.second->bin->x_section->n_sections--;

        delete m_currentBots.first;
        delete m_currentBots.second;
        m_currentBots.first = NULL;
        m_currentBots.second = NULL;
    }

    // create new bots
    xbot* bot1 = new xbot;
    xbot* bot2 = new xbot;

    // store bots temporarily
    m_currentBots.first = bot1;
    m_currentBots.second = bot2;

    // get bot namaes
    bot1->botname = Bot1Path.substr(Bot1Path.find_last_of("/\\") + 1);
    bot2->botname = Bot2Path.substr(Bot2Path.find_last_of("/\\") + 1);

    // set bot names
    FactoryGetLeftBotInfo()->SetBotName(bot1->botname);
    FactoryGetRightBotInfo()->SetBotName(bot2->botname);

    // allocate stack region for both bots
    add_section(bot1->bin->x_section, "stack", XVM_STACK_SIZE, XVM_DFLT_SP & 0xfffff000, PERM_READ | PERM_WRITE | PERM_EXEC);
    add_section(bot2->bin->x_section, "stack", XVM_STACK_SIZE, XVM_DFLT_SP & 0xfffff000, PERM_READ | PERM_WRITE | PERM_EXEC);

    // set correct stack pointer
    bot1->cpu->regs.sp = XVM_DFLT_SP;
    bot2->cpu->regs.sp = XVM_DFLT_SP;

    // load .bot sections
    xvm_bin_load_file(bot1->bin, Bot1Path.c_str());
    xvm_bin_load_file(bot2->bin, Bot2Path.c_str());

    // remove the default .text section and allocate a new one.
    remove_section_by_name(bot1->bin->x_section, ".text");
    remove_section_by_name(bot2->bin->x_section, ".text");

    // allocate a common text region
    section_entry* temp = NULL;
    section_entry* text = init_section_entry();
    set_section_entry(text, ".text", XWARS_MEM_SIZE, 0x1337000, PERM_READ | PERM_WRITE | PERM_EXEC);

    // add the .text in bot1
    temp = bot1->bin->x_section->sections;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = text;
    bot1->bin->x_section->n_sections++;

    // add the .text in bot2
    temp = bot2->bin->x_section->sections;
    while (temp->next != NULL) {
        temp = temp->next;
    }

    temp->next = text;
    bot2->bin->x_section->n_sections++;

    copy_bots(bot1, bot2);

    remove_section_by_name(bot1->bin->x_section, ".bot");
    remove_section_by_name(bot2->bin->x_section, ".bot");

    bot1->bot_section = NULL;
    bot2->bot_section = NULL;

    bot1->cpu->regs.pc = bot1->bot_addr;
    bot2->cpu->regs.pc = bot2->bot_addr;

    // take first step in battle
    set_battle_status(1);
    return battle_step();
}

// destructor
xwars::~xwars() { }

void xwars::set_battle_status(u32 value)
{
    battle_status = value;
}

u32 xwars::get_battle_status()
{
    return battle_status;
}

bool xwars::battle_step()
{
    xbot* bot1 = m_currentBots.first;
    xbot* bot2 = m_currentBots.second;

    if (
        (counter < MAX_INSTR_EXECS) && get_RF(bot1->cpu) && get_RF(bot2->cpu)) {
        display_registers(bot1, bot2);
        display_disassembly(bot1, bot2);

        // tell backend this is bot 1
        set_current_bitmap_bot(1);

        // next step
        bot1->step();

        // upadte memory grid for bot 1
        /* FactoryGetMiddlePanel()->GetMemoryGrid()->UpdateGrid(); */

        if (signal_abort(bot1->cpu->errors, bot1->cpu) == E_ERR) {
            winner = bot2->botname;
            return false;
        }
        if (signal_abort(bot1->bin->x_section->errors, bot1->cpu) == E_ERR) {
            winner = bot2->botname;
            return false;
        }

        // tell backend this is bot 2
        set_current_bitmap_bot(0);

        // next step
        bot2->step();

        // update memory grid for bot 2
        FactoryGetMiddlePanel()->GetMemoryGrid()->UpdateGrid();

        // check which won
        if (signal_abort(bot2->cpu->errors, bot2->cpu) == E_ERR) {
            winner = bot1->botname;
            return false;
        }

        if (signal_abort(bot2->bin->x_section->errors, bot2->cpu) == E_ERR) {
            winner = bot1->botname;
            return false;
        }
        counter++;
        return true;
    } else {
        winner = "DRAW";
        printf("[!] counter: %d, cpu1: %d, cpu2: %d\n", counter, get_RF(bot1->cpu), get_RF(bot2->cpu));
        return false;
    }
}
