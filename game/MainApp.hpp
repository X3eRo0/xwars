#ifndef XVM_ARENA_MAIN_APP_HPP
#define XVM_ARENA_MAIN_APP_HPP

#include "Common.hpp"

// #define MAIN_WINDOW_WIDTH 1600 
// #define MAIN_WINDOW_HEIGHT 900

#define MAIN_WINDOW_WIDTH 1240 
#define MAIN_WINDOW_HEIGHT 720

class MainApp : public wxApp{
public:
    // on init is our "main"
    virtual bool OnInit();
};

wxDECLARE_APP(MainApp);

#endif//XVM_ARENA_MAIN_APP_HPP
