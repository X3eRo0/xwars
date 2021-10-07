#ifndef XVM_ARENA_MAIN_WINDOW_HPP
#define XVM_ARENA_MAIN_WINDOW_HPP

#include "Common.hpp"
#include "MiddlePanel.hpp"
#include <wx/gdicmn.h>
#include <wx/stringimpl.h>

class MainWindow : public wxFrame{
public:
    MainWindow(wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize);

private:
    MiddlePanel *midPanel;
};

#endif//XVM_ARENA_MAIN_WINDOW_HPP