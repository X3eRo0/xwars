#include "ArenaTerminal.hpp"
#include <algorithm>
#include <wx/event.h>
#include <wx/filedlg.h>
#include <wx/gdicmn.h>
#include <wx/sizer.h>
#include <wx/stringimpl.h>
#include <wx/wxcrt.h>

enum xvmArenaButtonIDs{
    ID_LOAD  = wxID_HIGHEST + 1000,
    ID_START = wxID_HIGHEST + 1001,
    ID_PAUSE = wxID_HIGHEST + 1002,
    ID_PLUS  = wxID_HIGHEST + 1003,
    ID_MINUS = wxID_HIGHEST + 1004
};

// event table
BEGIN_EVENT_TABLE(ArenaTerminal, wxPanel)
    EVT_BUTTON(ID_LOAD, ArenaTerminal::OnLoad)
END_EVENT_TABLE()

ArenaTerminal::ArenaTerminal(wxWindow* parent) : wxPanel(parent){
    m_mainSizer = new wxBoxSizer(wxVERTICAL);
    this->SetSizer(m_mainSizer);

    // create terminal view
    m_terminal = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE);
    // set terminal view theme
    m_terminal->SetBackgroundColour(m_terminalBGColour);
    m_terminal->SetForegroundColour(m_terminalFGColour);
    m_terminal->SetFont(m_terminalFont);
    m_terminal->SetEditable(false);

    // add welcome text
    m_terminal->AppendText("[+] Welcome To XWars!");

    // create buttons panel and add to sizer
    m_buttonsPanel = new wxPanel(this);
    
    // create buttons panel sizer
    m_btnsPanelHSizer = new wxBoxSizer(wxHORIZONTAL);
    m_buttonsPanel->SetSizer(m_btnsPanelHSizer);

    // create buttons
    m_btnLoad = new wxButton(this, ID_LOAD, "Load");
    m_btnStart = new wxButton(this, ID_START, "Start");
    m_btnPause = new wxButton(this, ID_PAUSE, "Pause");
    m_btnPlus = new wxButton(this, ID_PLUS, "+");
    m_btnMinus = new wxButton(this, ID_MINUS, "-");

    // add for sizing
    m_btnsPanelHSizer->Add(m_btnLoad, 1);
    m_btnsPanelHSizer->Add(m_btnStart, 1);
    m_btnsPanelHSizer->Add(m_btnPause, 1);
    m_btnsPanelHSizer->Add(m_btnPlus, 1);
    m_btnsPanelHSizer->Add(m_btnMinus, 1);

    // add for sizing
    m_mainSizer->Add(m_buttonsPanel, 1, wxEXPAND | wxALL, 0);
    m_mainSizer->Add(m_terminal, 14, wxEXPAND | wxALL, 0);
}

// gets the actual bot name from reversed path
wxString GetBotNameFromFilePath(wxString filepath){
    wxString botname = "";
    size_t i = filepath.size() - 1;

    // read till '/'
    while((filepath[i] != '/') && i > 0){
        botname += filepath[i];
        i--;
    }

    // reverse botname
    std::reverse(botname.begin(), botname.end());

    return botname;
}

// when load button is clicked
// we will open a file selection dialog and read that file into memory
void ArenaTerminal::OnLoad(wxCommandEvent& WXUNUSED(event)){
    // create a new file dialog
    wxFileDialog *fd = new wxFileDialog(this, "XVM XWars - Arena - Load New Bot(s)", ".", wxEmptyString, "Assembly Files (*.asm)|*.asm", wxFD_MULTIPLE | wxFD_OPEN | wxFD_FILE_MUST_EXIST);
    
    // check if file was selected or not
    if(fd->ShowModal() == wxID_CANCEL){
        return;
    }

    wxArrayString filePaths;
    fd->GetPaths(filePaths);

    if(filePaths.size() == 0){
        wxLogError("No files were selected");
    }else{
        for(auto& filepath : filePaths){
            Print("\nLoaded Bot [ %s ]", GetBotNameFromFilePath(filepath));
        }
    }
}