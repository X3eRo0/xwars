/**
 * @file Register.hpp
 * @author Siddharth Mishra
 * @brief This represents the smallest element in the register display grid
 * @version 0.1
 * @date 2021-10-10
 */

#ifndef XVM_ARENA_REGISTER_HPP
#define XVM_ARENA_REGISTER_HPP

#include "Common.hpp"
#include "PropertyData.hpp"
#include <wx/sizer.h>

#define NUMBER_OF_REGISTERS 16

class Register : public wxPanel {
public:
    Register(wxWindow* parent, const std::string& regName);

    // setters
    void SetName(const std::string& n);
    void SetValue(const std::string& v);

    // getters
    const std::string& GetName();
    const std::string& GetValue() const;

    // change the text color of each register
    void SetFGColour(const wxColour& c);
    void ResetFGColour();
    void SetBGColour(const wxColour& c);
    void ResetBGColour();

    // set font
    bool SetFont(const wxFont& font);

    // regiser names
    // one can use this as reference to set register name using the set name
    // like in a for loop
    static inline std::array<std::string, NUMBER_OF_REGISTERS> RegisterNames
        = { "r0", "r1", "r2", "r3",
              "r4", "r5", "r6", "r7",
              "r8", "r9", "ra", "rb",
              "rc", "sp", "bp", "pc" };

private:
    // RegisterDisplay and Register, both must have same background colour
    wxColour m_defaultColour = wxColour(32, 16, 32);
    // main sizer
    wxBoxSizer* m_mainSizer;
    // label name and value
    std::string m_registerName, m_registerValue = "0x00000000",
                                m_delimiterString = ":";
    // panel will be like this [ <reg_name> : <reg_value> ]
    wxStaticText *m_registerNameText, *m_registerValueText, *m_delimiterText;
    // label and value fomt
    wxFont m_font = wxFont(8, wxFONTFAMILY_MODERN,
        wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
    // color values
    wxColour m_registerNameFGColour = *wxGREEN, m_registerValueFGColour = *wxWHITE;
};

#endif // XVM_ARENA_REGISTER_HPP
