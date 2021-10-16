/**
 * @file BotInfo.cpp
 * @author Siddharth Mishra
 * @brief This panel will how information such as current state of registers,
 * current instruction being executed etc... for each bot.
 * @version 0.1
 * @date 2021-10-09
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "BotNameDisplay.hpp"
#include "Common.hpp"
#include "BotInfo.hpp"
#include "Factory.hpp"
#include <chrono>
#include <cstdio>
#include <wx/app.h>
#include <wx/gdicmn.h>
#include <wx/sizer.h>
#include <wx/time.h>
#include <wx/utils.h>

BotInfo::BotInfo(wxWindow* parent, const std::string& botname, bool left) : wxPanel(parent){
    // create main sizer for our window
    m_mainSizer = new wxBoxSizer(wxVERTICAL);
    this->SetSizer(m_mainSizer);

    // create register and instruction dislay
    m_botNameDisplay = new BotNameDisplay(this, botname);

    if(left){
	m_registerDisplay = FactoryCreateLeftRegisterDisplay(this);
	m_instructionDisplay = FactoryCreateLeftInstructionDisplay(this);

    }else{
	m_registerDisplay = FactoryCreateRightRegisterDisplay(this);
	m_instructionDisplay = FactoryCreateRightInstructionDisplay(this);
    }
    
    // add displays for sizing
    m_mainSizer->Add(m_botNameDisplay, 1, wxEXPAND | wxALL);
    m_mainSizer->Add(m_registerDisplay, 5, wxEXPAND | wxALL, 3);
    m_mainSizer->Add(m_instructionDisplay, 10, wxEXPAND | wxALL, 3);   
}

// change register display text color
void BotInfo::SetRegisterDisplayFGColour(const wxColour &c){
    m_registerDisplayColour = c;
    m_registerDisplay->SetForegroundColour(c);
}

// change instruction display text color
void BotInfo::SetInstructionDisplayFGColour(const wxColour &c){
    m_instructionDisplayColour = c;
    m_instructionDisplay->SetForegroundColour(c);
}

// register update event handler
void BotInfo::UpdateRegisterDisplay(xbot *bot){
    char * lineptr = NULL;
    size_t n = 0;
    FILE * reader = bot->reg_reader_e;
    
    if (!reader){
        puts("connection with backend failed [ reader end not visible ]");
        return;
    }
    
    // wxMilliSleep(25);
    for (i32 i = 0; i < 16; i++){
        getline(&lineptr, &n, reader);
	    lineptr+=4;
	    m_registerDisplay->SetRegisterValue(Register::RegisterNames[i], lineptr);
    }
}

// register update event handler
void BotInfo::UpdateInstructionDisplay(xbot *bot){
    ClearInstructionDisplay();
    char *lineptr = NULL;
    size_t n = 0;

    // get reader end from bot and check if visible
    FILE *reader = bot->dis_reader_e;
    if (!reader){
        puts("connection with backend failed [ reader end not visible ]");
        return;
    }
    
    getline(&lineptr, &n, reader);

    std::string disassembly = "\n";
    disassembly += "Actual Instruction: ";
    disassembly += lineptr+16;
    disassembly += "\n";
    disassembly += lineptr;

    for (u32 i = 0; i < 19; i++){
        getline(&lineptr, &n, reader);
        //printf("LineNo: %d\n", ++i);
	    disassembly += lineptr;
    }
    
    PrintInstruction("%s", disassembly);
    wxTheApp->Yield(false);
    free(lineptr);
}

void BotInfo::SetBotName(const std::string &name){
    m_botNameDisplay->SetBotName(name);
}

BotNameDisplay* BotInfo::GetBotNameDisplay(){
    return m_botNameDisplay;
}
