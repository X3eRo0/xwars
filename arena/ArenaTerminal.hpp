#ifndef XVM_ARENA_ARENA_TERMINAL_HPP
#define XVM_ARENA_ARENA_TERMINAL_HPP

#include "Common.hpp"
#include <wx/event.h>
#include <wx/font.h>
#include <wx/gdicmn.h>
#include <wx/gtk/colour.h>
#include <wx/textctrl.h>

class ArenaTerminal : public wxPanel{
public:
    ArenaTerminal(wxWindow *parent);

    // write normal text in the terminal
    template<typename fmtstringtype, typename... args>
    void Print(fmtstringtype fmt, args... _args){
        wxString str;
        str.Printf(fmt, _args...);
        m_terminal->AppendText(str);
    }

    // write error text into the terminal
    template<typename fmtstringtype, typename... args>
    void PrintError(fmtstringtype fmt, args... _args){
        // set write colour to red
        m_terminal->SetForegroundColour(*wxRED);

        // write message
        Print(fmt, _args...);

        // change back to normal
        m_terminal->SetForegroundColour(m_terminalFGColour);
    }

private:
    void OnLoad(wxCommandEvent& event);

    // main sizer
    wxBoxSizer *m_mainSizer;
    // our awesome terminal will only show output
    wxTextCtrl *m_terminal;
    // cmd terminal will accept terminal commands
    wxTextCtrl *m_cmdTerminal;
    // terminal fg colour decides text color
    wxColour m_terminalFGColour = *wxWHITE;
    // terminal bg color
    wxColour m_terminalBGColour = *wxBLACK;
    // will contain control buttons
    wxPanel *m_buttonsPanel;
    // horizontal sizer for buttons panel
    wxBoxSizer *m_btnsPanelHSizer;
    // our control buttons
    wxButton *m_btnLoad, *m_btnStart, *m_btnPlus, *m_btnMinus, *m_btnPause;
    // terminal font
    wxFont m_terminalFont = wxFont(12, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_MEDIUM);

    DECLARE_EVENT_TABLE();
};

#endif//XVM_ARENA_ARENA_TERMINAL_HPP
