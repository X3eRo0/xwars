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
#include "PropertyData.hpp"
#include <wx/gdicmn.h>

class BotNameDisplay : public wxPanel {
public:
    // create bot name display
    // @param parent is the parent of this panel
    // @param botname is the name to be displayed in place of team name
    // @param left is to mark this as left or right bot. If left == true then this is left bot.
    BotNameDisplay(wxWindow* parent, const wxString& botname, bool left);

    // set botname
    void SetBotName(const std::string& name);

    // get botname
    const wxString& GetBotName(){
        return m_botname;
    }

    // // set botname colour
    // void SetNameColour(const wxString& c);

    // setters
    void SetReadColour(const wxColour& c);
    void SetWriteColour(const wxColour& c);
    void SetExecuteColour(const wxColour& c);

    // getters
    const wxColour& GetReadColour() const;
    const wxColour& GetWriteColour() const;
    const wxColour& GetExecuteColour() const;

    // properties
    PropertyData properties = PropertyData {
        .widgetType = WidgetType::BotNameDisplay,
        .fontSize = 20,
        .fontFamily = wxFONTFAMILY_MODERN,
        .fontStyle = wxFONTSTYLE_NORMAL,
        .fontWeight = wxFONTWEIGHT_NORMAL,
        .bgColour = *wxBLACK,
        .fgColour = *wxWHITE,
        .size = wxSize(1366, 768)
    };

    // call this after changing properties
    void UpdateSelf();

private:
    // main sizer for this panel
    wxBoxSizer* m_mainSizer;
    // botname
    wxString m_botname;
    // to show botname
    wxStaticText* m_botnameText;
    // buttons to show read, write, execute colours
    wxStaticText *m_rText, *m_wText, *m_xText;
    // read, write and execute colour
    wxColour m_rColour = GetBot1ReadColour(),
        m_wColour = GetBot1ReadColour(),
        m_xColour = GetBot1ReadColour(),
        m_rwxBGColour = *wxBLACK;
    // font for our r,w,x items
    wxFont m_rwxTextFont = wxFont(18, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
};

#endif // XVM_ARENA_BOT_NAME_DISPLAY_HPP
