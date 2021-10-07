#include <cmath>

#include "MainApp.hpp"
#include "MainWindow.hpp"

bool MainApp::OnInit(){
    // this will be our main window
    MainWindow *mainWindow = new MainWindow(nullptr, wxID_ANY, _("XVM XWars - Arena"),
                            wxDefaultPosition, wxSize(MAIN_WINDOW_WIDTH, MAIN_WINDOW_WIDTH));
    mainWindow->Show();
    mainWindow->SetFocus();

    // fixed size window
    mainWindow->SetMaxSize(wxSize(MAIN_WINDOW_WIDTH, MAIN_WINDOW_HEIGHT));
    mainWindow->SetMinSize(wxSize(MAIN_WINDOW_WIDTH, MAIN_WINDOW_HEIGHT));
    

    // everything's ok dude ;-)
    return true;
}

wxIMPLEMENT_APP(MainApp);