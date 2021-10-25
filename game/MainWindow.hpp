#ifndef XVM_ARENA_MAIN_WINDOW_HPP
#define XVM_ARENA_MAIN_WINDOW_HPP

#include "Common.hpp"
#include "MiddlePanel.hpp"
#include "PropertyData.hpp"
#include "BotInfo.hpp"
#include <wx/event.h>
#include <wx/font.h>
#include <wx/gdicmn.h>
#include <wx/sizer.h>
#include <wx/stringimpl.h>

class MainWindow : public wxFrame{
public:
    MainWindow(wxWindow* parent, wxWindowID id = wxID_ANY,
	       const wxString& title = wxEmptyString);

    // on about button clicked event handler
    void OnAbout(wxCommandEvent& event);

    // on settings button clicked event handler
    void OnSettings(wxCommandEvent& event);

    // properties
    PropertyData properties;

    // call this after changing properties
    void UpdateSelf();
    
    DECLARE_EVENT_TABLE()
private:
    // main panel that spans whole window
    wxPanel *m_parentPanel;
    // main sizer for sizing children
    wxBoxSizer *m_mainHSizer;
    // our menu bar at top of window
    wxMenuBar *m_menuBar;
    // bot info panels at left and right
    BotInfo *m_lBotInfo, *m_rBotInfo;
    // middle panel that contains terminal and memory grid
    MiddlePanel *m_midPanel;
};

#endif//XVM_ARENA_MAIN_WINDOW_HPP
