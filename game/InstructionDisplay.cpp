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
#include <wx/event.h>
#include <wx/gdicmn.h>
#include <wx/stream.h>
#include <wx/stringimpl.h>


InstructionDisplay::InstructionDisplay(wxWindow* parent) : wxPanel(parent){
    // change background colour
    SetBackgroundColour(m_bgColor);
    
    // create main sizer
    m_mainSizer = new wxBoxSizer(wxVERTICAL);
    this->SetSizer(m_mainSizer);

    // create static box to contain register display areas
    // and set it to span whole space
    m_parentBox = new wxStaticBox(this, wxID_ANY, "Instructions");
    m_parentBox->SetForegroundColour(m_parentBoxFGColour);
    m_mainSizer->Add(m_parentBox, 1, wxEXPAND | wxALL, 10);
    
    // sizer for our parent box
    m_parentBoxSizer = new wxBoxSizer(wxVERTICAL);
    m_parentBox->SetSizer(m_parentBoxSizer);

    // create area to display instructions
    m_displayTextCtrl = new wxTextCtrl(m_parentBox, wxID_ANY, wxEmptyString,
				       wxDefaultPosition, wxDefaultSize,
				       wxTE_MULTILINE);
    m_displayTextCtrl->SetBackgroundColour(m_displayBGColour);
    m_displayTextCtrl->SetForegroundColour(m_displayFGColour);
    m_displayTextCtrl->SetFont(m_displayFont);
    m_displayTextCtrl->SetEditable(false); // disable editing
    m_parentBoxSizer->Add(m_displayTextCtrl, 1, wxEXPAND | wxALL);
}

void InstructionDisplay::UpdateSelf(){
    m_displayTextCtrl->SetBackgroundColour(properties.bgColour);
    m_displayTextCtrl->SetForegroundColour(properties.fgColour);
    m_displayTextCtrl->SetFont(properties.GetFont());
}
