#ifndef XWARS_STATS_DISPLAY_HPP
#define XWARS_STATS_DISPLAY_HPP

#include "Common.hpp"
#include <unordered_map>
#include <wx/listctrl.h>
#include <wx/position.h>

class StatsDisplay : public wxDialog{
public:
    StatsDisplay(const wxString& winner = "None",
                 wxWindow* parent = nullptr, wxWindowID id = wxID_ANY,
                 const wxString& name = "Battle Statistics",
                 const wxPoint& pos = wxPoint(400, 400),
                 const wxSize& size = wxSize(800, 600));

    void SetWinnerAndLooser(u32 state, std::string bot1, std::string bot2);
    void AddBot(const wxString& name, u32 score);
    void SetBotScore(const wxString& name, double score);
    void IncBotScore(const wxString& name);

    // reset scoreboard
    void ClearDisplay();
private:
    // map from bot names to their index in list
    std::unordered_map<wxString, u32> m_botNameIDMap;
    std::unordered_map<wxString, double> m_botNameScoreMap;

    u32 m_botCount = 0;
    wxBoxSizer *m_topSizer, *m_mainSizer;
    wxPanel *m_parentPanel, *m_topPanel, *m_bottomPanel;
    wxListView *m_scoreboardList;
    wxStaticText *m_winnerText;
};

#endif//XWARS_STATS_DISPLAY_HPP
