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
#include <wx/font.h>
#include <wx/gdicmn.h>
#include <wx/sizer.h>

Register::Register(wxWindow* parent, const std::string& name)
    : wxPanel(parent)
    , m_registerName(name)
{
    // create main sizer
    m_mainSizer = new wxBoxSizer(wxHORIZONTAL);
    this->SetSizer(m_mainSizer);

    // create label and value static texts
    m_registerNameText = new wxStaticText(this, wxID_ANY, "$" + m_registerName,
        wxDefaultPosition, wxDefaultSize,
        wxALIGN_CENTER | wxST_NO_AUTORESIZE);

    m_delimiterText = new wxStaticText(this, wxID_ANY, m_delimiterString,
        wxDefaultPosition, wxDefaultSize,
        wxALIGN_CENTER | wxST_NO_AUTORESIZE);

    m_registerValueText = new wxStaticText(this, wxID_ANY, "0x00000000",
        wxDefaultPosition, wxDefaultSize,
        wxALIGN_CENTER | wxST_NO_AUTORESIZE);

    // set font
    m_registerNameText->SetFont(m_font);
    m_delimiterText->SetFont(m_font);
    m_registerValueText->SetFont(m_font);

    // set Colour
    m_registerNameText->SetForegroundColour(m_registerNameFGColour);
    m_registerValueText->SetForegroundColour(m_registerValueFGColour);

    // add for sizing
    m_mainSizer->Add(m_registerNameText, 3, wxEXPAND | wxUP | wxDOWN, 1);
    m_mainSizer->Add(m_delimiterText, 1, wxEXPAND | wxUP | wxDOWN, 1);
    m_mainSizer->Add(m_registerValueText, 10, wxEXPAND | wxUP | wxDOWN, 1);
}

void Register::SetName(const std::string& n)
{
    m_registerName = n;
    m_registerNameText->SetLabel("$" + n);
}

void Register::SetValue(const std::string& v)
{
    m_registerValue = v;
    m_registerValueText->SetLabelText(v);
}

const std::string& Register::GetName()
{
    return m_registerName;
}

const std::string& Register::GetValue() const
{
    return m_registerValue;
}

void Register::SetFGColour(const wxColour& c)
{
    m_registerValueText->SetForegroundColour(c);
}

void Register::ResetFGColour()
{
    m_registerValueText->SetForegroundColour(*wxWHITE);
}

void Register::SetBGColour(const wxColour& c)
{
    m_registerNameText->SetBackgroundColour(c);
    m_delimiterText->SetBackgroundColour(c);
    m_registerValueText->SetBackgroundColour(c);
}

void Register::ResetBGColour()
{
    SetBackgroundColour(m_defaultColour);
    m_registerNameText->SetBackgroundColour(m_defaultColour);
    m_delimiterText->SetBackgroundColour(m_defaultColour);
    m_registerValueText->SetBackgroundColour(m_defaultColour);
}

bool Register::SetFont(const wxFont& font)
{
    m_registerValueText->SetFont(font);
    m_registerNameText->SetFont(font);
    m_delimiterText->SetFont(font);

    return true;
}
