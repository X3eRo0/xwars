/**
 * @file BotNameDisplay.hpp
 * @author Siddharth Mishra
 * @brief Displays bot name and some other information
 * @version 0.1
 * @date 2021-10-09
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef XVM_ARENA_BOT_NAME_DISPLAY_HPP
#define XVM_ARENA_BOT_NAME_DISPLAY_HPP

#include "Common.hpp"
#include <wx/gdicmn.h>
#include <wx/gtk/colour.h>

class BotNameDisplay : public wxPanel{
public:
    BotNameDisplay(wxWindow* parent, const std::string& botname);

    /**
        @note Read, Write & Execute colours are colours that will be used to 
              read, wrote and executable memory for each bot.

              Default values are : 
                    Read = RED
                    Write = BLUE
                    Execute = GREEN
    */

    // setters
    void SetReadColour(const wxColour& c);
    void SetWriteColour(const wxColour& c);
    void SetExecuteColour(const wxColour& c);
    void SetNameColour(const wxColour& c);

    // getters
    const wxColour& GetReadColour();
    const wxColour& GetWriteColour();
    const wxColour& GetExecuteColour();
    
private:
    // main sizer for this panel
    wxBoxSizer *m_mainSizer;
    // botname
    std::string m_botname;
    // to show botname
    wxStaticText *m_botnameText;
    // text font
    wxFont m_botnameTextFont = wxFont(24, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
    // foreground color of botname
    wxColour m_botnameTextColour;
    // buttons to show read, write, execute colours
    wxStaticText *m_rText, *m_wText, *m_xText;
    // read, write and execute colour
    wxColour m_rColour = *wxRED, m_wColour = *wxBLUE, m_xColour = *wxGREEN, m_rwxFGColour = *wxBLACK;
    // font for our r,w,x items
    wxFont m_rwxTextFont = wxFont(12, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
};

#endif//XVM_ARENA_BOT_NAME_DISPLAY_HPP