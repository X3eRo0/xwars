#ifndef XVM_ARENA_TERMINAL_HPP
#define XVM_ARENA_TERMINAL_HPP

#include "Common.hpp"
#include "PropertyData.hpp"
#include "StatsDisplay.hpp"
#include "XWars.hpp"
#include <vector>
#include <wx/event.h>
#include <wx/font.h>
#include <wx/gdicmn.h>
#include <wx/textctrl.h>
#include <wx/timer.h>

class Arena : public wxPanel {
public:
    // read and write end FILE ptrs;

    Arena(wxWindow* parent);

    // write normal text in the terminal
    template <typename fmtstringtype, typename... args>
    void Print(fmtstringtype fmt, args... _args)
    {
        wxString str;
        str.Printf(fmt, _args...);
        m_terminal->AppendText(str);

        // WARNING : ----------------------------------------
        // this is a hack to give the main thread some time :
        // to write things onto the display area            :
        // --------------------------------------------------
        // wxTheApp->SafeYield(GetMainWindow(), false);
        wxTheApp->Yield();
    }

    // write error text into the terminal
    template <typename fmtstringtype, typename... args>
    void PrintError(fmtstringtype fmt, args... _args)
    {
        // set write colour to red
        m_terminal->SetForegroundColour(*wxRED);

        // write message
        Print(fmt, _args...);

        // change back to normal
        m_terminal->SetForegroundColour(m_terminalFGColour);
    }

    // properties
    PropertyData properties = PropertyData {
        .widgetType = WidgetType::ArenaTerminal,
        .fontSize = 10,
        .fontFamily = wxFONTFAMILY_MODERN,
        .fontStyle = wxFONTSTYLE_NORMAL,
        .fontWeight = wxFONTWEIGHT_NORMAL,
        .bgColour = *wxBLACK,
        .fgColour = *wxWHITE
    };

    // update theme after changing properties
    void UpdateSelf();

    // load bots from path
    void LoadBots(const wxString& botsFolder);

    DECLARE_EVENT_TABLE();

private:
    void OnPause(wxCommandEvent& event);
    void OnDecrement(wxCommandEvent& event);
    void OnIncrement(wxCommandEvent& event);
    void OnLoad(wxCommandEvent& event);
    void OnStart(wxCommandEvent& event);
    void OnIntervalTimer(wxTimerEvent& e);
    void OnIterationTimer(wxTimerEvent& e);

    // stats display
    StatsDisplay *m_statsDisplay;

    // is battle paused
    bool m_isBattlePaused = false;
    // main sizer
    wxBoxSizer* m_mainSizer;
    // our awesome terminal will only show output
    wxTextCtrl* m_terminal;
    // cmd terminal will accept terminal commands
    wxTextCtrl* m_cmdTerminal;
    // terminal fg colour decides text color
    wxColour m_terminalFGColour = *wxWHITE;
    // terminal bg color
    wxColour m_terminalBGColour = *wxBLACK;
    // will contain control buttons
    wxPanel* m_buttonsPanel;
    // horizontal sizer for buttons panel
    wxBoxSizer* m_btnsPanelHSizer;
    // our control buttons
    wxButton *m_btnLoad, *m_btnStart, *m_btnPlus, *m_btnMinus, *m_btnPause;
    // terminal font
    wxFont m_terminalFont = wxFont(10, wxFONTFAMILY_MODERN,
        wxFONTSTYLE_NORMAL, wxFONTWEIGHT_MEDIUM);
    // wait size for battle iteration
    size_t m_iterWaitTime = 60, m_interWaitTime = 5000;
    // timer for timed battles
    wxTimer m_iterTimer, m_intervTimer;
    // battle pairs
    std::vector<std::pair<u32, u32>> m_battlePairs;
    // battle index
    size_t m_battleIdx = 0;
};

#endif // XVM_ARENA_TERMINAL_HPP
