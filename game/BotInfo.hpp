/**
 * @file BotInfo.hpp
 * @author Siddharth Mishra
 * @brief This panel will how information such as current state of registers, current instruction
 *        being executed etc... for each bot.
 * @version 0.1
 * @date 2021-10-09
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef XVM_ARENA_BOT_INFO_HPP
#define XVM_ARENA_BOT_INFO_HPP

#include "Common.hpp"
#include "RegisterDisplay.hpp"
#include "InstructionDisplay.hpp"
#include "BotNameDisplay.hpp"
#include <wx/font.h>
#include <wx/gdicmn.h>

class BotInfo : public wxPanel{
public:
    BotInfo(wxWindow *parent, cstring botname);
    
    // fg color setters
    void SetBotNameColour(const wxColour& c);
    void SetRegisterDisplayFGColour(const wxColour& c);
    void SetInstructionDisplayFGColour(const wxColour& c);

    // bg color setters
    void SetRegisterDisplayBGColour(const wxColour& c);
    void SetInstructionDisplayBGColour(const wxColour& c);
private:
    // our main sizer
    wxBoxSizer *m_mainSizer;
    // heading panel will contain bot name and some other stuffs
    // heading panel is at the top of bot info panel
    BotNameDisplay* m_headingPanel;
    // register display will show current state of registers for this bot
    RegisterDisplay *m_registerDisplay;
    // register display colour
    wxColour m_registerDisplayColour = *wxWHITE;
    // instruction display will show current instruction begin executed
    InstructionDisplay *m_instructionDisplay;
    // register display colour
    wxColour m_instructionDisplayColour = *wxWHITE;
};

#endif//XVM_ARENA_BOT_INFO_HPP