#ifndef XVM_ARENA_MAIN_APP_HPP
#define XVM_ARENA_MAIN_APP_HPP

#include "Common.hpp"
#include <wx/cmdline.h>

// #define MAIN_WINDOW_WIDTH 1600 
// #define MAIN_WINDOW_HEIGHT 900

#define MAIN_WINDOW_WIDTH 1240 
#define MAIN_WINDOW_HEIGHT 740

class MainApp : public wxApp{
public:
    // on init is our "main"
    virtual bool OnInit();
    virtual void OnInitCmdLine(wxCmdLineParser& parser);
    virtual bool OnCmdLineParsed(wxCmdLineParser& parser);
private:
    wxString ConfigFile = ""; /* path to config file */
    wxString BotsFolder = ""; /* path to bots */
};


static const wxCmdLineEntryDesc g_cmdLineDesc [] =
{
     { wxCMD_LINE_SWITCH, "h", "help", "displays help on the command line parameters",
          wxCMD_LINE_VAL_NONE, wxCMD_LINE_OPTION_HELP },
     { wxCMD_LINE_OPTION, "c", "config", "theme config to load",
          wxCMD_LINE_VAL_STRING, wxCMD_LINE_PARAM_OPTIONAL},
     { wxCMD_LINE_OPTION, "b", "bots", "bots directory to load",
          wxCMD_LINE_VAL_STRING, wxCMD_LINE_PARAM_OPTIONAL},
     { wxCMD_LINE_NONE }
};

wxDECLARE_APP(MainApp);

#endif//XVM_ARENA_MAIN_APP_HPP
