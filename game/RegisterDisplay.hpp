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

private:
    wxColour m_bgColor = *wxBLACK;
    // main sizer
    wxSizer *m_mainSizer;
    // this box will contain all our objects
    wxStaticBox *m_parentBox;
    // sizer for sizing objects in parent box
    wxBoxSizer *m_parentBoxSizer;
    // registers will be shown in a grid inside the parent box
    wxGridSizer *m_regGridSizer;
    // handle to each register display item
    std::unordered_map<std::string, Register*> m_registers;
};

#endif//XVM_ARENA_REGISTER_DISPLAY_HPP