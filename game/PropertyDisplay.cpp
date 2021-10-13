
/**
   @date 13/10/2021
   @file PropertiesDisplay.cpp
   @author Siddharth Mishra
   @brief Panel to display properties of a widget like BotInfo, MemoryGrid etc...
*/

#include "PropertyData.hpp"
#include "PropertyDisplay.hpp"
#include <wx/arrstr.h>
#include <wx/gdicmn.h>
#include <wx/gtk/statbox.h>
#include <wx/sizer.h>
#include <wx/utils.h>

PropertiesDisplay::PropertiesDisplay(wxWindow *parent,
                                     const PropertyData &defaultProperties)
    : wxPanel(parent), m_defaultProperties(defaultProperties){
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

    // add to sizer for sizing
    // m_fontBoxSizer->Add(m_widgets.fontSize, 1, wxEXPAND | wxALL);
    // m_fontBoxSizer->Add(m_widgets.fontFamily, 1, wxEXPAND | wxALL);
    // m_fontBoxSizer->Add(m_widgets.fontStyle, 1, wxEXPAND | wxALL);
    // m_fontBoxSizer->Add(m_widgets.fontWeight, 1, wxEXPAND | wxALL);

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

    // add to sizer for sizing
    // m_colourBoxSizer->Add(m_widgets.bgColour, 1, wxEXPAND | wxALL);
    // m_colourBoxSizer->Add(m_widgets.fgColour, 1, wxEXPAND | wxALL);

    m_colourBoxSizer->Add(m_widgets.bgColour);
    m_colourBoxSizer->Add(m_widgets.fgColour);
    
    // create size settings box
    m_sizeBox = new wxStaticBox(this, wxID_ANY, "Size Settings");
    m_sizeBox->SetBackgroundColour(m_boxBGColour);
    m_sizeBoxSizer = new wxBoxSizer(wxVERTICAL);
    m_sizeBox->SetSizer(m_sizeBoxSizer);
    m_mainSizer->Add(m_sizeBox, 3, wxEXPAND | wxALL, 5);

    // create widgets
    m_widgets.minSize = new TextProperty(m_sizeBox, "Minimum", "400");
    m_widgets.size = new TextProperty(m_sizeBox, "Current", "400");
    m_widgets.maxSize = new TextProperty(m_sizeBox, "Maximum", "400");
    m_widgets.spanRatioInParent = new TextProperty(m_sizeBox, "Span Ration In Parent", "1");

    // add to sizer for sizing
    // m_sizeBoxSizer->Add(m_widgets.minSize, 1, wxEXPAND | wxALL);
    // m_sizeBoxSizer->Add(m_widgets.size, 1, wxEXPAND | wxALL);
    // m_sizeBoxSizer->Add(m_widgets.maxSize, 1, wxEXPAND | wxALL);
    // m_sizeBoxSizer->Add(m_widgets.spanRatioInParent, 1, wxEXPAND | wxALL);

    m_sizeBoxSizer->Add(m_widgets.minSize);
    m_sizeBoxSizer->Add(m_widgets.size);
    m_sizeBoxSizer->Add(m_widgets.maxSize);
    m_sizeBoxSizer->Add(m_widgets.spanRatioInParent);
}

