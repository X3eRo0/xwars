#include "Register.hpp"
#include <wx/gtk/stattext.h>
#include <wx/gtk/window.h>
#include <wx/sizer.h>

Register::Register(wxWindow *parent, const std::string& name)
: wxPanel(parent), m_registerName(name){
    m_mainSizer = new wxBoxSizer(wxHORIZONTAL);
    this->SetSizer(m_mainSizer);

    m_registerNameText = new wxStaticText(this, wxID_ANY, m_registerName);
    m_registerValueText = new wxStaticText(this, wxID_ANY, "0x0000");

    m_mainSizer->Add(m_registerNameText, 1, wxEXPAND | wxALL);
    m_mainSizer->Add(m_registerValueText, 1, wxEXPAND | wxALL);
}