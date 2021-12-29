#ifndef XWARS_STATS_DISPLAY_HPP
#define XWARS_STATS_DISPLAY_HPP

#include "Common.hpp"
#include <wx/listctrl.h>

class StatsDisplay : public wxDialog{
public:
    StatsDisplay(const wxString& winner,
                 wxWindow* parent = nullptr, wxWindowID id = wxID_ANY,
                 const wxString& name = "Battle Statistics",
                 const wxPoint& pos = wxDefaultPosition,
                 const wxSize& size = wxSize(800, 600));
private:
    wxBoxSizer *m_topSizer, *m_mainSizer;
    wxPanel *m_parentPanel, *m_topPanel, *m_bottomPanel;
    wxListView *m_scoreboardList;
};

#endif//XWARS_STATS_DISPLAY_HPP
