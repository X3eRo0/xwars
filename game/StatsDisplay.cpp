#include "StatsDisplay.hpp"
#include "BotInfo.hpp"
#include "Common.hpp"
#include "Factory.hpp"
#include <wx/font.h>
#include <wx/listbase.h>
#include <wx/listctrl.h>
#include <wx/sizer.h>

StatsDisplay::StatsDisplay(const wxString& winner,
    wxWindow* parent, wxWindowID id,
    const wxString& name, const wxPoint& pos,
    const wxSize& size)
    : wxDialog(parent, id, name, pos, size)
{
    // create main sizer
    m_parentPanel = new wxPanel(this);
    m_mainSizer = new wxBoxSizer(wxVERTICAL);
    ;
    m_parentPanel->SetSizer(m_mainSizer);
    m_parentPanel->SetBackgroundColour(*wxBLACK);

    // create top panel to display winner
    m_topPanel = new wxPanel(m_parentPanel);
    wxBoxSizer* topPanelSizer = new wxBoxSizer(wxVERTICAL);
    m_topPanel->SetSizer(topPanelSizer);
    m_topPanel->SetBackgroundColour(wxColour(16, 8, 16));

    // show winner text in top panel
    u32 draw = 0;
    if (winner == "DRAW") {
        draw = 1;
        m_winnerText = new wxStaticText(m_topPanel, wxID_ANY, "The Winner is " + winner + "!",
            wxDefaultPosition, wxDefaultSize,
            wxST_NO_AUTORESIZE | wxALIGN_CENTER_HORIZONTAL | wxALIGN_CENTER_VERTICAL);
    } else {
        m_winnerText = new wxStaticText(m_topPanel, wxID_ANY, "The Round was a DRAW!",
            wxDefaultPosition, wxDefaultSize,
            wxST_NO_AUTORESIZE | wxALIGN_CENTER_HORIZONTAL | wxALIGN_CENTER_VERTICAL);
    }
    m_winnerText->SetForegroundColour(*wxRED);
    wxFont winnerBotNameFont(36, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
    m_winnerText->SetFont(winnerBotNameFont);
    topPanelSizer->Add(m_winnerText, 1, wxEXPAND | wxALL);

    // create bottom panel
    m_bottomPanel = new wxPanel(m_parentPanel);
    wxBoxSizer* bottomPanelSizer = new wxBoxSizer(wxVERTICAL);
    m_bottomPanel->SetSizer(bottomPanelSizer);
    m_bottomPanel->SetBackgroundColour(wxColour(16, 8, 16));

    // create list for displaying botnames
    m_scoreboardList = new wxListView(m_bottomPanel);
    wxFont scoreboardListFont = wxFont(12, wxFONTFAMILY_TELETYPE, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
    m_scoreboardList->SetFont(scoreboardListFont);

    // add columns for name and score
    m_scoreboardList->AppendColumn("Name", wxLIST_FORMAT_CENTRE, size.GetWidth() * 5 / 6);
    m_scoreboardList->AppendColumn("Score", wxLIST_FORMAT_CENTER, size.GetWidth() / 6);
    bottomPanelSizer->Add(m_scoreboardList, 1, wxEXPAND | wxALL);

    // add all panels to main sizer
    m_mainSizer->Add(m_topPanel, 1, wxEXPAND | wxALL, 2);
    m_mainSizer->Add(m_bottomPanel, 4, wxEXPAND | wxALL, 2);
}

void StatsDisplay::AddBot(const wxString& name, u32 score)
{
    m_scoreboardList->InsertItem(m_botCount, name);
    m_scoreboardList->SetItem(m_botCount, 1, std::to_string(score));
    m_botNameIDMap[name] = m_botCount++;
    m_botNameScoreMap[name] = 0;
}

void StatsDisplay::SetBotScore(const wxString& name, double score){
    m_scoreboardList->SetItem(m_botNameIDMap[name], 1, std::to_string(score));
}

void StatsDisplay::SetWinnerAndLooser(u32 state, std::string bot1, std::string bot2){
    std::string winner = "";
    if ((state & 1) == ROUND_DRAW) {
        m_winnerText->SetLabel("Round Draw !");
        SetBotScore(bot1, m_botNameScoreMap[bot1] + 0.5);
        SetBotScore(bot2, m_botNameScoreMap[bot2] + 0.5);
        return;
    } else {
        if (state == BOT1_WINNER) {
            winner = bot1;
        } else if (state == BOT2_WINNER) {
            winner = bot2;
        }
    }

    m_winnerText->SetLabel("The Winner is " + winner);
    IncBotScore(winner);
    static int lastWinner = -1;

    if (lastWinner != -1) {
        m_scoreboardList->Select(lastWinner, false);
    }

    m_scoreboardList->Select(m_botNameIDMap[winner], true);
    lastWinner = m_botNameIDMap[winner];
}

void StatsDisplay::IncBotScore(const wxString& name){
    SetBotScore(name, 1.0 + m_botNameScoreMap[name]);
}

void StatsDisplay::ClearDisplay()
{
    m_scoreboardList->DeleteAllItems();
    m_botCount = 0;
}
