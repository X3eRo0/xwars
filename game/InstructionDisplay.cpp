/**
 * @file InstructionDisplay.cpp
 * @author Siddharth Mishra
 * @brief This will show current instruction being executed for given bot
 * @version 0.1
 * @date 2021-10-09
 * 
 * @copyright Copyright (c) 2021
 * 
 */


#include "InstructionDisplay.hpp"
#include <limits>
#include <wx/gdicmn.h>

InstructionDisplay::InstructionDisplay(wxWindow* parent) : wxPanel(parent){
    // change background colour
    SetBackgroundColour(m_bgColor);
    
    // create main sizer
    m_mainSizer = new wxBoxSizer(wxVERTICAL);
    this->SetSizer(m_mainSizer);

    // create static box to contain register display areas and set it to span whole space
    m_parentBox = new wxStaticBox(this, wxID_ANY, "Instructions");
    m_parentBox->SetForegroundColour(m_parentBoxFGColour);
    m_mainSizer->Add(m_parentBox, 1, wxEXPAND | wxALL, 10);
    
    // sizer for our parent box
    m_parentBoxSizer = new wxBoxSizer(wxVERTICAL);
    m_parentBox->SetSizer(m_parentBoxSizer);

    // create instruction list and add required columns
    m_instructionList = new wxListView(m_parentBox, wxID_ANY);
    m_instructionList->AppendColumn("Address");
    m_instructionList->AppendColumn("OpCode");
    m_instructionList->AppendColumn("Instruction");

    m_instructionList->SetColumnWidth(0, 100);
    m_instructionList->SetColumnWidth(1, 100);
    m_instructionList->SetColumnWidth(2, 220);

    // populate instruction list
    for(size_t i = 0; i < 10; i++){
        AddNewInstruction("<address>", "<opcode>", "<instruction>");
    }

    m_parentBoxSizer->Add(m_instructionList, 1, wxEXPAND | wxALL);
}

// add new instruction trio
void InstructionDisplay::AddNewInstruction(const std::string &address, const std::string &opcode, const std::string &instruction){
    m_instructionList->InsertItem(m_numInstructions, address);
    m_instructionList->SetItem(m_numInstructions, 1, opcode);
    m_instructionList->SetItem(m_numInstructions, 2, instruction);

    m_instructions.push_back({address, opcode, instruction});

    m_numInstructions++;
}

void InstructionDisplay::SelectInstructionByIndex(size_t idx){
    m_instructionList->Select(idx);
}

size_t InstructionDisplay::GetInstructionIndexByAddress(const std::string &address){
    for(size_t i = 0; i < m_numInstructions; i++){
        if(m_instructions[i].address == address) return i;
    }

    // if address not found then return max value (-1);
    // return std::numeric_limits<size_t>::max();
    return -1;
}

void InstructionDisplay::SelectInstructionByAddress(const std::string& address){
    m_instructionList->Select(GetInstructionIndexByAddress(address));
}