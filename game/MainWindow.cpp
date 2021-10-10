#include "MainWindow.hpp"
#include <wx/gdicmn.h>

MainWindow::MainWindow(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size) 
: wxFrame(parent, id, title, pos, size){
    // main panel to contain other panels
    // this will span this whole frame
    // as the direct child to main frame spans it while
    wxPanel *parentPanel = new wxPanel(this);

    // create sizer for parentPanel panel
    // left and right panel will be added to this sizer for sizing
    wxBoxSizer *mainHSizer = new wxBoxSizer(wxHORIZONTAL);
    parentPanel->SetSizer(mainHSizer);

    // left panel will show information about bots
    // right panel will show memory space
    BotInfo *leftPanel, *rightPanel;
    leftPanel = new BotInfo(parentPanel, "Khiladi One");
    midPanel = new MiddlePanel(parentPanel);
    rightPanel = new BotInfo(parentPanel, "Khiladi Two");

    // add these panels to main sizer
    mainHSizer->Add(leftPanel, 3, wxEXPAND | wxALL, 4);
    mainHSizer->Add(midPanel, 2, wxEXPAND | wxALL, 4);
    mainHSizer->Add(rightPanel, 3, wxEXPAND | wxALL, 4);

    // set colors for panels to tell them apart
    leftPanel->SetBackgroundColour(*wxBLACK);
    midPanel->SetBackgroundColour(wxColour(64, 64, 64));
    rightPanel->SetBackgroundColour(*wxBLACK);
   
}