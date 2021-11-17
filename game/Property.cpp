#include "Property.hpp"
#include <wx/arrstr.h>
#include <wx/clrpicker.h>
#include <wx/font.h>
#include <wx/gdicmn.h>
#include <wx/log.h>
#include <wx/sizer.h>
#include <wx/string.h>
#include <wx/stringimpl.h>

// ------------------------------ TEXT PROPERTY --------------------------------
TextProperty::TextProperty(wxWindow *parent, const wxString &label,
                               const wxString &defaultValue)
    : wxPanel(parent), m_label(label), m_defaultValue(defaultValue){
    // create main sizer
    m_mainSizer = new wxBoxSizer(wxHORIZONTAL);
    this->SetSizer(m_mainSizer);

    // create label text
    m_labelText = new wxStaticText(this, wxID_ANY, m_label);
    m_labelText->SetFont(m_font);
    // we don't want this to expand and span the remaining space
    m_mainSizer->Add(m_labelText, 2, wxEXPAND | wxALL);

    // create text edit (entry)
    m_valueEntry = new wxTextCtrl(this, wxID_ANY, m_defaultValue,
				  wxDefaultPosition, wxSize(160, 40),
				  wxALIGN_RIGHT);
    m_valueEntry->SetFont(m_font);
    m_mainSizer->AddSpacer(90);
    m_mainSizer->Add(m_valueEntry, 1, wxEXPAND | wxALL);
}

// set to default value
void TextProperty::ResetValue(){
    m_valueEntry->SetValue(m_defaultValue);
}

// get value as string
wxString TextProperty::GetValueStr() const{
    return m_valueEntry->GetValue();
}

// get default value
const wxString& TextProperty::GetDefaultValue() const{
    return m_defaultValue;
}

// set default value
void TextProperty::SetDefaultValue(const wxString& v){
    m_defaultValue = v;
}

// set value in text entry
void TextProperty::SetValue(const wxString &value){
    m_valueEntry->SetValue(value);
}

// get value as u32
u32 TextProperty::GetValueU32() const{
    return std::stoul(GetValueStr().GetData().AsChar());
}

// get value as u64
u64 TextProperty::GetValueU64() const{
    return std::stoull(GetValueStr().GetData().AsChar());
}

// get value as float
float TextProperty::GetValueFloat() const{
    return std::stof(GetValueStr().GetData().AsChar());
}

// get value as double
double TextProperty::GetValueDouble() const{
    return std::stod(GetValueStr().GetData().AsChar());
}
// ------------------------------ TEXT PROPERTY --------------------------------
// -----------------------------------------------------------------------------

// ----------------------------- OPTION PROPERTY -------------------------------
OptionProperty::OptionProperty(wxWindow *parent, const wxString &label,
                               const wxArrayString &options,
			       size_t defaultOption)
    : wxPanel(parent), m_label(label), m_options(options),
      m_defaultOption(defaultOption){
    // create main sizer
    m_mainSizer = new wxBoxSizer(wxHORIZONTAL);
    this->SetSizer(m_mainSizer);

    // create label text
    m_labelText = new wxStaticText(this, wxID_ANY, m_label);
    m_labelText->SetFont(m_font);
    // we don't want this to expand and span the remaining space
    m_mainSizer->Add(m_labelText, 2, wxEXPAND | wxALL);

    // create option list
    m_optionList = new wxComboBox(this, wxID_ANY, m_options[m_defaultOption],
				  wxDefaultPosition, wxSize(160, 40),
				  m_options.size(), m_options.begin(),
				  wxCB_DROPDOWN | wxCB_READONLY);
    m_optionList->SetFont(m_font);
    m_mainSizer->AddSpacer(90);
    m_mainSizer->Add(m_optionList, 1, wxEXPAND | wxALL);
}

// reset to default option
void OptionProperty::ResetValue() { m_optionList->Select(m_defaultOption); }

// get selected value as string
wxString OptionProperty::GetValueStr() const{
    return m_optionList->GetStringSelection();
}

// set default selection index
void OptionProperty::SetDefaultSelection(size_t n){
    m_defaultOption = n;
}

// get default selection
size_t OptionProperty::GetDefaultSelection() const{
    return m_defaultOption;
}

void OptionProperty::SetSelection(size_t n){
    m_optionList->SetSelection(n);
}

void OptionProperty::SetValue(const wxString& v){
    m_optionList->ChangeValue(v);
}

// get index of current selection
size_t OptionProperty::GetSelection() const{
    return m_optionList->GetCurrentSelection();
}

wxString OptionProperty::GetValue() const{
    return m_optionList->GetValue();
}
// ----------------------------- OPTION PROPERTY -------------------------------
// -----------------------------------------------------------------------------


// ----------------------------- COLOUR PROPERTY -------------------------------

ColourProperty::ColourProperty(wxWindow *parent, const wxString &label,
                               const wxColour &defaultColour)
    : wxPanel(parent), m_label(label), m_defaultColour(defaultColour){
    // create main sizer
    m_mainSizer = new wxBoxSizer(wxHORIZONTAL);
    this->SetSizer(m_mainSizer);

    // create label text
    m_labelText = new wxStaticText(this, wxID_ANY, m_label);
    m_labelText->SetFont(m_font);
    // we don't want this to expand and span the remaining space
    m_mainSizer->Add(m_labelText, 2, wxEXPAND | wxALL);

    // create color picker
    m_colorPicker = new wxColourPickerCtrl(this, wxID_ANY, m_defaultColour,
					   wxDefaultPosition, wxSize(160, 40),
					   wxCLRP_SHOW_LABEL | wxCLRP_USE_TEXTCTRL);
    m_colorPicker->SetFont(m_font);
    m_mainSizer->AddSpacer(90);
    m_mainSizer->Add(m_colorPicker, 1, wxEXPAND | wxALL);
}

// reset to default colour
void ColourProperty::ResetValue() { m_colorPicker->SetColour(m_defaultColour); }

// get colour value as string
wxString ColourProperty::GetValueStr() const{
    return m_colorPicker->GetColour().GetAsString();
}

// set a new default colour value
void ColourProperty::SetDefaultColour(const wxColour& c){
    m_defaultColour = c;
}

// get default colour value
wxColour ColourProperty::GetDefaultColour() const { return m_defaultColour; }

// get selected colour
wxColour ColourProperty::GetColour() const{
    return m_colorPicker->GetColour();
}

// set colour
void ColourProperty::SetValue(const wxColour &v){
    m_colorPicker->SetColour(v);
}

// get selected colour
wxColour ColourProperty::GetValue() const{
    return m_colorPicker->GetColour();
}


// ----------------------------- COLOUR PROPERTY -------------------------------
// -----------------------------------------------------------------------------
