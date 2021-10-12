/**
 * @file BotInfo.cpp
 * @author Siddharth Mishra
 * @brief This panel will how information such as current state of registers, current instruction
 *        being executed etc... for each bot.
 * @version 0.1
 * @date 2021-10-09
 * 
 * @copyright Copyright (c) 2021
 * 
 */

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

// define custom event type
// wxDEFINE_EVENT(REGISTER_DISPLAY_UPDATE_EVENT, wxCommandEvent);
// wxDEFINE_EVENT(INSTRUCTION_DISPLAY_UPDATE_EVENT, wxCommandEvent);

BotInfo::BotInfo(wxWindow* parent, const std::string& botname) : wxPanel(parent){
    // create main sizer for our window
    m_mainSizer = new wxBoxSizer(wxVERTICAL);
    this->SetSizer(m_mainSizer);

    // create register and instruction dislay
    m_headingPanel = new BotNameDisplay(this, botname);
    m_registerDisplay = FactoryCreateLeftRegisterDisplay(this);
    m_instructionDisplay = FactoryCreateRightInstructionDisplay(this);

    // add displays for sizing
    m_mainSizer->Add(m_headingPanel, 1, wxEXPAND | wxALL);
    m_mainSizer->Add(m_registerDisplay, 5, wxEXPAND | wxALL, 3);
    m_mainSizer->Add(m_instructionDisplay, 10, wxEXPAND | wxALL, 3);
    
    // Connect(REGISTER_DISPLAY_UPDATE_EVENT, wxCommandEventHandler(BotInfo::OnRegisterUpdate));
    // Connect(INSTRUCTION_DISPLAY_UPDATE_EVENT, wxCommandEventHandler(BotInfo::OnInstructionUpdate));
}

// change botname text display text color
void BotInfo::SetBotNameColour(const wxColour &c){
    m_headingPanel->SetNameColour(c);
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
    for (i32 i = 0; i < 16; i++){
        getline(&lineptr, &n, reader);
		//// change register values here
        //printf("register: %s", lineptr);
    }
}

// register update event handler
void BotInfo::UpdateInstructionDisplay(xbot *bot){
    //printf("wrting instructions in display\n");
    char *lineptr = NULL;
    size_t n = 0;

    // get reader end from bot and check if visible
    FILE *reader = bot->dis_reader_e;
    if (!reader){
        puts("connection with backend failed [ reader end not visible ]");
        return;
    }
    
    // add junk at the end of file
    // in order to realize this is really eof
    // since we dont know when the stream really ends
    // we needed some method to check that
    // each line by default will contain atleast one address string
    // address is atleast longer than 5 chars
    // so we exploit that and append something smaller than that
    // since we know that xvm won't return something smaller than that
    // we assume that we've reached the end of file!
    // this is just a hack to get over a really irritating bug
    FILE *writer = bot->dis_writer_e;
    if(!writer){
	puts("connection with backend failed [ writer end not visible ]");
	return;
    }
    std::string junk = "x\n";
    fwrite(junk.c_str(), 1, 2, writer);
    // fflush(writer);
    
    ClearInstructionDisplay();
    wxTheApp->Yield(false);
    std::string disassembly = "";
    u32 i = 0;
    while(getline(&lineptr, &n, reader) > 2){
        // getline(&lineptr, &n, reader);
        printf("LineNo: %d\n", ++i);
	disassembly += lineptr;
    }
    
    PrintInstruction("%s", disassembly);
    wxTheApp->Yield(false);
    free(lineptr);
}
