#ifndef XVM_ARENA_MAIN_APP_HPP
#define XVM_ARENA_MAIN_APP_HPP

#include "Common.hpp"

#define MAIN_WINDOW_WIDTH 1366 
#define MAIN_WINDOW_HEIGHT 768

class MainApp : public wxApp{
public:
    // on init is our "main"
    virtual bool OnInit();
};

wxDECLARE_APP(MainApp);

#endif//XVM_ARENA_MAIN_APP_HPP
