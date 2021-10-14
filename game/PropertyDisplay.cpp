
/**
   @date 13/10/2021
   @file PropertiesDisplay.cpp
   @author Siddharth Mishra
   @brief Panel to display properties of a widget like BotInfo, MemoryGrid etc...
*/

#include "PropertyData.hpp"
#include "PropertyDisplay.hpp"
#include <string>
#include <wx/arrstr.h>
#include <wx/font.h>
#include <wx/gdicmn.h>
#include <wx/log.h>
#include <wx/sizer.h>
#include <wx/utils.h>

PropertiesDisplay::PropertiesDisplay(wxWindow *parent)
    : wxPanel(parent){
    // change background colour
    SetBackgroundColour(*wxBLACK);
    
    // create main sizer
    m_mainSizer = new wxBoxSizer(wxVERTICAL);
    this->SetSizer(m_mainSizer);

    // create font settings box
    wxStaticBox *m_fontBox = new wxStaticBox(this, wxID_ANY, "Font Settings");
    m_fontBox->SetBackgroundColour(m_boxBGColour);
    m_fontBoxSizer = new wxBoxSizer(wxVERTICAL);
    m_fontBox->SetSizer(m_fontBoxSizer);
    m_mainSizer->Add(m_fontBox, 3, wxEXPAND | wxALL, 5);
    
    // setup options
    wxArrayString fontfamily;
    fontfamily.push_back("Default");
    fontfamily.push_back("Decorative");
    fontfamily.push_back("Roman");
    fontfamily.push_back("Script");
    fontfamily.push_back("Swiss");
    fontfamily.push_back("Modern");
    fontfamily.push_back("Teletype");

    wxArrayString fontstyle;
    fontstyle.push_back("Normal");
    fontstyle.push_back("Italic");
    fontstyle.push_back("Slant");

    wxArrayString fontweight;
    fontweight.push_back("Normal");
    fontweight.push_back("Light");
    fontweight.push_back("Bold");

    // create widgets
    m_widgets.fontSize = new TextProperty(m_fontBox, "Size", "0");
    m_widgets.fontFamily = new OptionProperty(m_fontBox, "Family", fontfamily);
    m_widgets.fontStyle = new OptionProperty(m_fontBox, "Style", fontstyle);
    m_widgets.fontWeight = new OptionProperty(m_fontBox, "Weight", fontweight);

    m_fontBoxSizer->Add(m_widgets.fontSize);
    m_fontBoxSizer->Add(m_widgets.fontFamily);
    m_fontBoxSizer->Add(m_widgets.fontStyle);
    m_fontBoxSizer->Add(m_widgets.fontWeight);

    // create colour setting box
    m_colourBox = new wxStaticBox(this, wxID_ANY, "Colour Settings");
    m_colourBox->SetBackgroundColour(m_boxBGColour);
    m_colourBoxSizer = new wxBoxSizer(wxVERTICAL);
    m_colourBox->SetSizer(m_colourBoxSizer);
    m_mainSizer->Add(m_colourBox, 2, wxEXPAND | wxALL, 5);
    
    // create widgets
    m_widgets.bgColour = new ColourProperty(m_colourBox, "Background", *wxBLACK);
    m_widgets.fgColour = new ColourProperty(m_colourBox, "Foreground", *wxGREEN);

    m_colourBoxSizer->Add(m_widgets.bgColour);
    m_colourBoxSizer->Add(m_widgets.fgColour);
    
    // create size settings box
    m_sizeBox = new wxStaticBox(this, wxID_ANY, "Size Settings");
    m_sizeBox->SetBackgroundColour(m_boxBGColour);
    m_sizeBoxSizer = new wxBoxSizer(wxVERTICAL);
    m_sizeBox->SetSizer(m_sizeBoxSizer);
    m_mainSizer->Add(m_sizeBox, 1, wxEXPAND | wxALL, 5);

    wxArrayString sizeoptions;
    sizeoptions.push_back("1366x768");
    sizeoptions.push_back("1600x900");
    sizeoptions.push_back("1920x1080");
    
    // create widgets
    m_widgets.size = new OptionProperty(m_sizeBox, "Window Size",
					sizeoptions, 0);
    
    m_sizeBoxSizer->Add(m_widgets.size);
}

void PropertiesDisplay::UpdateDisplay(const PropertyData &data){
    // set font size
    m_widgets.fontSize->SetValue(std::to_string(data.fontSize));

    // set font family
    wxString v;
    switch (data.fontFamily) {
    case wxFONTFAMILY_MODERN : v = "Modern";
    case wxFONTFAMILY_DEFAULT : v = "Default";
    case wxFONTFAMILY_ROMAN : v = "Roman";
    case wxFONTFAMILY_SWISS : v = "Swiss";
    case wxFONTFAMILY_SCRIPT : v = "Script";
    case wxFONTFAMILY_TELETYPE : v = "Teletype";
    case wxFONTFAMILY_DECORATIVE : v = "Decorative";
    default : wxLogMessage("Unknown Font Family!");
    }
    m_widgets.fontFamily->SetValue(v);

    // change font style
    switch (data.fontStyle) {
    case wxFONTSTYLE_ITALIC : v = "Italic";
    case wxFONTSTYLE_NORMAL : v = "Normal";
    case wxFONTSTYLE_SLANT : v = "Slant";
    default : wxLogMessage("Unknown Font Style");
    }
    m_widgets.fontFamily->SetValue(v);

    // change font weight
    switch (data.fontWeight) {
    case wxFONTWEIGHT_BOLD : v = "Bold";
    case wxFONTWEIGHT_NORMAL : v = "Normal";
    case wxFONTWEIGHT_LIGHT : v = "Light";
    default: wxLogMessage("Unknown Font Weight");
    }
    m_widgets.fontWeight->SetValue(v);

    // change bg & fg colour
    m_widgets.bgColour->SetValue(data.bgColour);
    m_widgets.fgColour->SetValue(data.fgColour);

    // change size
    wxString size = std::to_string(data.size.GetWidth()) + "x" + std::to_string(data.size.GetHeight());
    m_widgets.size->SetValue(size);
}

u32 PropertiesDisplay::GetFontSize() const{
    return m_widgets.fontSize->GetValueU32();
}

wxFontFamily PropertiesDisplay::GetFontFamily() const{
    wxString v = m_widgets.fontFamily->GetValue();

    if(v == "Modern") { return wxFONTFAMILY_MODERN; }
    else if(v == "Default") { return wxFONTFAMILY_DEFAULT; }
    else if(v == "Decorative") { return wxFONTFAMILY_DECORATIVE; }
    else if(v == "Roman") { return wxFONTFAMILY_ROMAN; }
    else if(v == "Swiss") { return wxFONTFAMILY_SWISS; }
    else if(v == "Script") { return wxFONTFAMILY_SCRIPT; }
    else { return wxFONTFAMILY_TELETYPE; }
}

wxFontStyle PropertiesDisplay::GetFontStyle() const{
    wxString v = m_widgets.fontStyle->GetValue();

    if(v == "Normal") { return wxFONTSTYLE_NORMAL; }
    else if(v == "Italic") { return wxFONTSTYLE_ITALIC; }
    else { return wxFONTSTYLE_SLANT; }
}

wxFontWeight PropertiesDisplay::GetFontWeight() const{
    wxString v = m_widgets.fontWeight->GetValue();

    if(v == "Bold") { return wxFONTWEIGHT_BOLD; }
    else if(v == "Normal") { return wxFONTWEIGHT_NORMAL; }
    else { return wxFONTWEIGHT_LIGHT; }
}

wxColour PropertiesDisplay::GetBGColour() const{
    return m_widgets.bgColour->GetColour();
}

wxColour PropertiesDisplay::GetFGColour() const{
    return m_widgets.fgColour->GetColour();
}

wxSize PropertiesDisplay::GetSize() const{
    wxString v = m_widgets.size->GetValue();
    
    u32 w = std::stoul(v.BeforeFirst('x').GetData().AsChar());
    u32 h = std::stoul(v.AfterFirst('x').GetData().AsChar());

    return wxSize(w, h);
}

PropertyData PropertiesDisplay::GetPropertyData() const{
    return PropertyData{
	.fontSize = GetFontSize(),
	.fontFamily = GetFontFamily(),
	.fontStyle = GetFontStyle(),
	.fontWeight = GetFontWeight(),
	.bgColour = GetBGColour(),
	.fgColour = GetFGColour(),
	.size = GetSize()
    };
}
