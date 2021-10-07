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
    wxPanel *leftPanel, *rightPanel;
    leftPanel = new wxPanel(parentPanel);
    midPanel = new MiddlePanel(parentPanel);
    rightPanel = new wxPanel(parentPanel);

    // add these panels to main sizer
    mainHSizer->Add(leftPanel, 1, wxEXPAND | wxALL, 4);
    mainHSizer->Add(midPanel, 2, wxEXPAND | wxALL, 4);
    mainHSizer->Add(rightPanel, 1, wxEXPAND | wxALL, 4);

    // set colors for panels to tell them apart
    leftPanel->SetBackgroundColour(wxColour(64, 32, 0));
    midPanel->SetBackgroundColour(wxColour(64, 64, 64));
    rightPanel->SetBackgroundColour(wxColour(0, 50, 64));
   
}