#ifndef XVM_ARENA_PROPERTY_HPP
#define XVM_ARENA_PROPERTY_HPP

#include "Common.hpp"
#include <wx/clrpicker.h>
#include <wx/combobox.h>
#include <wx/font.h>

// -------------------------------- PROPERTY -----------------------------------
// -----------------------------------------------------------------------------

// ------------------------------ TEXT PROPERTY --------------------------------
// for properties that need string input
class TextProperty : public wxPanel {
public:
    TextProperty(wxWindow* parent,
        const wxString& label,
        const wxString& defaultValue);

    // reset to default value
    void ResetValue();
    // get value as string
    wxString GetValueStr() const;

    // get default value
    const wxString& GetDefaultValue() const;

    // set default value
    void SetDefaultValue(const wxString& defaultValue);

    // set current value
    void SetValue(const wxString& value);

    // get value as numbers
    u32 GetValueU32() const;
    u64 GetValueU64() const;
    float GetValueFloat() const;
    double GetValueDouble() const;

private:
    wxString m_label;
    wxString m_defaultValue;
    wxBoxSizer* m_mainSizer;
    wxStaticText* m_labelText;
    wxTextCtrl* m_valueEntry;
    wxFont m_font = wxFont(10, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
};
// ------------------------------ TEXT PROPERTY --------------------------------
// -----------------------------------------------------------------------------

// ----------------------------- OPTION PROPERTY -------------------------------
// display a dropdown list for choosing an option
class OptionProperty : public wxPanel {
public:
    OptionProperty(wxWindow* parent, const wxString& label,
        const wxArrayString& options, size_t defaultOption = 0);

    void ResetValue();
    wxString GetValueStr() const;

    void SetDefaultSelection(size_t n);
    size_t GetDefaultSelection() const;

    void SetSelection(size_t n);
    void SetValue(const wxString& v);

    // get index of selected option
    size_t GetSelection() const;
    wxString GetValue() const;

public:
    wxString m_label;
    size_t m_defaultOption;
    wxArrayString m_options;
    wxBoxSizer* m_mainSizer;
    wxStaticText* m_labelText;
    wxComboBox* m_optionList;
    wxFont m_font = wxFont(10, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
};
// ----------------------------- OPTION PROPERTY -------------------------------
// -----------------------------------------------------------------------------

// ----------------------------- COLOUR PROPERTY -------------------------------
// display a color picker to select one and apply
class ColourProperty : public wxPanel {
public:
    ColourProperty(wxWindow* parent, const wxString& label,
        const wxColour& defaultColour);

    void ResetValue();
    wxString GetValueStr() const;

    // get and set default colour
    void SetDefaultColour(const wxColour& defaultColour);
    wxColour GetDefaultColour() const;

    void SetValue(const wxColour& v);
    wxColour GetValue() const;

    // get selected colour
    wxColour GetColour() const;

public:
    wxString m_label;
    wxColour m_defaultColour;
    wxBoxSizer* m_mainSizer;
    wxStaticText* m_labelText;
    wxColourPickerCtrl* m_colorPicker;
    wxFont m_font = wxFont(10, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
};
// ----------------------------- COLOUR PROPERTY -------------------------------
// -----------------------------------------------------------------------------

#endif // XVM_ARENA_PROPERTY_HPP
