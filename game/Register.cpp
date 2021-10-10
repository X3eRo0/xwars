/**
 * @file Register.cpp
 * @author Siddharth Mishra
 * @brief This represents the smallest element in the register display grid
 * @version 0.1
 * @date 2021-10-10
 * 
 * @copyright Copyright (c) 2021
 * 
 */


#include "Register.hpp"
#include <wx/gdicmn.h>
#include <wx/gtk/stattext.h>
#include <wx/gtk/window.h>
#include <wx/sizer.h>

Register::Register(wxWindow *parent, const std::string& name)
: wxPanel(parent), m_registerName(name){
    // create main sizer
    m_mainSizer = new wxBoxSizer(wxHORIZONTAL);
    this->SetSizer(m_mainSizer);

    // create label and value static texts
    m_registerNameText = new wxStaticText(this, wxID_ANY, "$"+m_registerName, wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER);
    m_delimiterText = new wxStaticText(this, wxID_ANY, m_delimiterString, wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER);
    m_registerValueText = new wxStaticText(this, wxID_ANY, "0x00000000", wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER);

    // set font
    m_registerNameText->SetFont(m_registerNameFont);
    m_delimiterText->SetFont(wxFont(9, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));
    m_registerValueText->SetFont(m_registerValueFont);
    
    // set Colour
    m_registerNameText->SetForegroundColour(m_registerNameFGColour);
    m_registerValueText->SetForegroundColour(m_registerValueFGColour);
    
    // add for sizing
    m_mainSizer->Add(m_registerNameText, 3, wxEXPAND | wxALL);
    m_mainSizer->Add(m_delimiterText, 1, wxEXPAND | wxALL);
    m_mainSizer->Add(m_registerValueText, 10, wxEXPAND | wxALL);
}

void Register::SetName(const std::string& n){
    m_registerName = n;
    m_registerNameText->SetLabel("$"+n);
}

void Register::SetValue(const std::string& v){
    m_registerValue = v;
    m_registerValueText->SetLabel(v);
}

const std::string& Register::GetName(){
    return m_registerName;
}

const std::string& Register::GetValue(){
    return m_registerValue;
}
