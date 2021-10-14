#include <cmath>

#include "MainApp.hpp"
#include "MainWindow.hpp"
#include "Factory.hpp"

bool MainApp::OnInit(){
    // this will be our main window
    MainWindow *mainWindow = FactoryCreateMainWindow(nullptr, wxID_ANY,
						     "XVM XWars - Arena");
    mainWindow->Show();
    mainWindow->SetFocus();

    // fixed size window
    mainWindow->SetMaxSize(wxSize(MAIN_WINDOW_WIDTH, MAIN_WINDOW_HEIGHT));
    mainWindow->SetMinSize(wxSize(MAIN_WINDOW_WIDTH, MAIN_WINDOW_HEIGHT));
    

    // everything's ok dude ;-)
    return true;
}


wxIMPLEMENT_APP(MainApp);
