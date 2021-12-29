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

#include "BotNameDisplay.hpp"
#include "Common.hpp"
#include "InstructionDisplay.hpp"
#include "RegisterDisplay.hpp"
#include "XBot.hpp"
#include <wx/font.h>
#include <wx/gdicmn.h>

// new event types are declared in header and defined in source
wxDECLARE_EVENT(INSTRUCTION_DISPLAY_UPDATE_EVENT, wxCommandEvent);
wxDECLARE_EVENT(REGISTER_DISPLAY_UPDATE_EVENT, wxCommandEvent);

class BotInfo : public wxPanel {
public:
    // if left is true then it will be assumed that this is the left panel
    // right panel assumed otherwise
    BotInfo(wxWindow* parent, const wxString& botname, bool left = true);

    // set bot name for this panel
    void SetBotName(const std::string& name);

    // get bot name for this panel
    const wxString& GetBotName(){
        return m_botNameDisplay->GetBotName();
    }

    // event handlers
    void UpdateRegisterDisplay(xbot* bot);
    void UpdateInstructionDisplay(xbot* bot);

    // change name of register
    void ChangeRegisterValue(const std::string& regname);

    // print formatted text to instruction display area
    template <typename fmtype = wxString, typename... argstype>
    void PrintInstruction(fmtype str, argstype... args)
    {
        m_instructionDisplay->Print(str, args...);
    }

    // clear instruction display area
    void ClearInstructionDisplay()
    {
        if (m_instructionDisplay)
        m_instructionDisplay->ClearDisplay();
    }

    // fg color setters
    // void SetBotNameColour(const wxColour& c);
    void SetRegisterDisplayFGColour(const wxColour& c);
    void SetInstructionDisplayFGColour(const wxColour& c);

    // bg color setters
    void SetRegisterDisplayBGColour(const wxColour& c);
    void SetInstructionDisplayBGColour(const wxColour& c);

    // get bot name display
    BotNameDisplay* GetBotNameDisplay();
private:
    // our main sizer
    wxBoxSizer* m_mainSizer;
    // heading panel will contain bot name and some other stuffs
    // heading panel is at the top of bot info panel
    BotNameDisplay* m_botNameDisplay;
    // register display will show current state of registers for this bot
    RegisterDisplay* m_registerDisplay;
    // register display colour
    wxColour m_registerDisplayColour = *wxWHITE;
    // instruction display will show current instruction begin executed
    InstructionDisplay* m_instructionDisplay;
    // register display colour
    wxColour m_instructionDisplayColour = *wxWHITE;
};

#endif // XVM_ARENA_BOT_INFO_HPP
