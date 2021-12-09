#include "MainApp.hpp"
#include "Factory.hpp"
#include "MainWindow.hpp"
#include <cmath>

bool MainApp::OnInit()
{
    // this will be our main window

    if (!wxApp::OnInit())
        return false;

    MainWindow* mainWindow = FactoryCreateMainWindow(nullptr, wxID_ANY,
        "XVM XWars - Arena");
    mainWindow->Show();
    mainWindow->SetFocus();

    if (ConfigFile != "" && wxFileExists(ConfigFile)) {
        /* Found a config file */
        mainWindow->ApplyTheme(ConfigFile);
    }

    if (BotsFolder != "" && wxDirExists(BotsFolder)) {
        FactoryGetMiddlePanel()->GetArena()->LoadBots(BotsFolder);
    }

    // everything's ok dude ;-)
    return true;
}

void MainApp::OnInitCmdLine(wxCmdLineParser& parser)
{
    parser.SetDesc(g_cmdLineDesc);
    // must refuse '/' as parameter starter or cannot use "/path" style paths
    parser.SetSwitchChars(wxT("-"));
}

bool MainApp::OnCmdLineParsed(wxCmdLineParser& parser)
{
    parser.Found("c", &ConfigFile); /* Config File */
    parser.Found("b", &BotsFolder); /* Bots Folder */

    return true;
}

wxIMPLEMENT_APP(MainApp);
