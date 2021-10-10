/**
 * @file RegisterDisplay.cpp
 * @author Siddharth Mishra
 * @brief This panel will show current state of registers for the given bot.
 * @version 0.1
 * @date 2021-10-09
 * 
 * @copyright Copyright (c) 2021
 * 
 */


#include "RegisterDisplay.hpp"
#include <wx/gtk/colour.h>
#include <wx/sizer.h>

RegisterDisplay::RegisterDisplay(wxWindow* parent) : wxPanel(parent){
    // change background colour
    SetBackgroundColour(m_bgColor);
    
    // create main sizer
    m_mainSizer = new wxBoxSizer(wxVERTICAL);
    this->SetSizer(m_mainSizer);

    // create static box to contain register display areas and set it to span whole space
    m_parentBox = new wxStaticBox(this, wxID_ANY, "Registers");
    m_parentBox->SetForegroundColour(m_parentBoxFGColour);
    m_mainSizer->Add(m_parentBox, 1, wxEXPAND | wxALL, 10);
    
    // initialize grid sizer for arranging gprs
    m_regGridSizer = new wxGridSizer(4, 4, 1, 1);
    m_parentBox->SetSizer(m_regGridSizer);

    // initialize gen purpose regs
    for(size_t i = 0; i < NUMBER_OF_REGISTERS; i++){
        // initialize registers and add to grid sizer
        m_registers[Register::RegisterNames[i]] = new Register(m_parentBox, Register::RegisterNames[i]);
        m_registers[Register::RegisterNames[i]]->SetBackgroundColour(wxColour(32, 0, 32));
        m_regGridSizer->Add(m_registers[Register::RegisterNames[i]]);
    }
}