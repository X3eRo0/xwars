/**
 * @file InstructionDisplay.hpp
 * @author Siddharth Mishra
 * @brief This will show current instruction being executed for given bot
 * @version 0.1
 * @date 2021-10-09
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef XVM_ARENA_INSTRUCTION_DISPLAY_HPP
#define XVM_ARENA_INSTRUCTION_DISPLAY_HPP

#include "Common.hpp"
#include <wx/listctrl.h>

class InstructionDisplay : public wxPanel{
public:
    InstructionDisplay(wxWindow *parent);

private:
    wxColour m_bgColor = wxColour(32, 16, 32);
    // main sizer
    wxSizer *m_mainSizer;
    // this box will contain all our objects
    wxStaticBox *m_parentBox;
    // parent box colour 
    wxColour m_parentBoxFGColour = *wxCYAN;
    // sizer for sizing objects in parent box
    wxBoxSizer *m_parentBoxSizer;
    // list to display our instructions
    wxListView *m_instructionList;
};

#endif//XVM_ARENA_INSTRUCTION_DISPLAY_HPP