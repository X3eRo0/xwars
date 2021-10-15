/**
 * @file RegisterDisplay.hpp
 * @author Siddharth Mishra
 * @brief This panel will show current state of registers for the given bot.
 * @version 0.1
 * @date 2021-10-09
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef XVM_ARENA_REGISTER_DISPLAY_HPP
#define XVM_ARENA_REGISTER_DISPLAY_HPP

#include "Common.hpp"
#include "Register.hpp"
#include <array>

class RegisterDisplay : public wxPanel{
public:
    RegisterDisplay(wxWindow* parent);
    
    void SetRegisterValue(const std::string& regname, const std::string& val);
    
    // properties
    PropertyData properties = PropertyData{
	.widgetType = WidgetType::RegisterDisplay,
	.fontSize = 8,
	.fontFamily = wxFONTFAMILY_MODERN,
	.fontStyle = wxFONTSTYLE_NORMAL,
	.fontWeight = wxFONTWEIGHT_NORMAL,
	.bgColour = wxColour(32, 16, 32),
	.fgColour = *wxWHITE
    };

    void UpdateSelf();
private:
    wxColour m_bgColor = wxColour(32, 16, 32);
    // main sizer
    wxSizer *m_mainSizer;
    // this box will contain all our objects
    wxStaticBox *m_parentBox;
    // sizer for sizing objects in parent box
    wxBoxSizer *m_parentBoxSizer;
    // parent box label colour
    wxColour m_parentBoxFGColour = *wxCYAN;
    // registers will be shown in a grid inside the parent box
    wxGridSizer *m_regGridSizer;
    // handle to each register display item
    std::unordered_map<std::string, Register*> m_registers;
};

#endif//XVM_ARENA_REGISTER_DISPLAY_HPP
