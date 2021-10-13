#include "MainWindow.hpp"
#include "XWars.hpp"
#include "SettingsDialog.hpp"
#include "Factory.hpp"
#include <wx/event.h>
#include <wx/gdicmn.h>
#include <wx/msgdlg.h>
#include <wx/wxcrt.h>

// event handler ids
enum MainWindowEventHandlerIDs{
    MENU_ABOUT_ID = wxID_HIGHEST + 1005,
    MENU_SETTINGS_ID = wxID_HIGHEST + 1006
};

// define event table
BEGIN_EVENT_TABLE(MainWindow, wxFrame)
EVT_MENU(MENU_ABOUT_ID, MainWindow::OnAbout)
EVT_MENU(MENU_SETTINGS_ID, MainWindow::OnSettings)
END_EVENT_TABLE()

// constructor
MainWindow::MainWindow(wxWindow *parent, wxWindowID id, const wxString &title,
                       const wxPoint &pos, const wxSize &size)
: wxFrame(parent, id, title, pos, size){
    // main panel to contain other panels
    // this will span this whole frame
    // as the direct child to main frame spans it while
    wxPanel *m_parentPanel = new wxPanel(this);

    // create sizer for parentPanel panel
    // left and right panel will be added to this sizer for sizing
    wxBoxSizer *m_mainHSizer = new wxBoxSizer(wxHORIZONTAL);
    m_parentPanel->SetSizer(m_mainHSizer);

    // left panel will show information about bots
    // right panel will show memory space
    m_lBotInfo = FactoryCreateLeftBotInfo(m_parentPanel, "Khiladi One");
    m_midPanel = FactoryCreateMiddlePanel(m_parentPanel);
    m_rBotInfo = FactoryCreateRightBotInfo(m_parentPanel, "Khiladi Two");

    // register the two bot infos to xwars
    get_xwars_instance()->register_bot_info(m_lBotInfo, m_rBotInfo);

    // add these panels to main sizer
    m_mainHSizer->Add(m_lBotInfo, 3, wxEXPAND | wxALL, 4);
    m_mainHSizer->Add(m_midPanel, 2, wxEXPAND | wxALL, 4);
    m_mainHSizer->Add(m_rBotInfo, 3, wxEXPAND | wxALL, 4);

    // set colors for panels to tell them apart
    m_lBotInfo->SetBackgroundColour(*wxBLACK);
    m_midPanel->SetBackgroundColour(wxColour(32, 64, 32));
    m_rBotInfo->SetBackgroundColour(*wxBLACK);

    // create menu bar
    m_menuBar = new wxMenuBar;
    SetMenuBar(m_menuBar);

    // create file menu
    wxMenu *fileMenu = new wxMenu;
    m_menuBar->Append(fileMenu, "&File");
    fileMenu->Append(MENU_SETTINGS_ID, "&Settings\tCtrl+X");
    fileMenu->Append(MENU_ABOUT_ID, "&About\tCtrl+A");
    fileMenu->AppendSeparator();
    fileMenu->Append(wxID_EXIT);
}

// handle event
void MainWindow::OnAbout(wxCommandEvent &event) {
    wxMessageBox("XWars is a R2Wars like game but written for XVM", "About XWars", wxOK | wxICON_INFORMATION);
}

// handle event
void MainWindow::OnSettings(wxCommandEvent &event) {
    SettingsDialog *dialog = new SettingsDialog(nullptr);
    dialog->ShowModal();
    dialog->Destroy();
}
