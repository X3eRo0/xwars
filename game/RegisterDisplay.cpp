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
#include <wx/sizer.h>

RegisterDisplay::RegisterDisplay(wxWindow* parent) : wxPanel(parent){
    // change background colour
    SetBackgroundColour(m_bgColor);
    
    // create main sizer
    m_mainSizer = new wxBoxSizer(wxVERTICAL);
    this->SetSizer(m_mainSizer);

    // create static box to contain register display areas and set it to span whole space
    m_parentBox = new wxStaticBox(this, wxID_ANY, "Registers");
    m_mainSizer->Add(m_parentBox, 1, wxEXPAND | wxALL);
    
    // sizer for our parent box
    m_parentBoxSizer = new wxBoxSizer(wxVERTICAL);
    m_parentBox->SetSizer(m_parentBoxSizer);
}