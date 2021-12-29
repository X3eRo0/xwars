#include "Arena.hpp"
#include "Factory.hpp"
#include "XWars.hpp"
#include <algorithm>
#include <dirent.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <wx/event.h>
#include <wx/filedlg.h>
#include <wx/gdicmn.h>
#include <wx/sizer.h>
#include <wx/stringimpl.h>
#include <wx/time.h>
#include <wx/timer.h>
#include <wx/wxcrt.h>

#include "MemoryGrid.hpp"
#include "MiddlePanel.hpp"
#include "StatsDisplay.hpp"

enum xvmArenaButtonIDs {
    ID_LOAD = wxID_HIGHEST + 1000,
    ID_START = wxID_HIGHEST + 1001,
    ID_PAUSE = wxID_HIGHEST + 1002,
    ID_PLUS = wxID_HIGHEST + 1003,
    ID_MINUS = wxID_HIGHEST + 1004
};

// event table
BEGIN_EVENT_TABLE(Arena, wxPanel)
EVT_BUTTON(ID_LOAD, Arena::OnLoad)
EVT_BUTTON(ID_START, Arena::OnStart)
END_EVENT_TABLE()

Arena::Arena(wxWindow* parent)
    : wxPanel(parent)
{
    m_mainSizer = new wxBoxSizer(wxVERTICAL);
    this->SetSizer(m_mainSizer);

    // create terminal view
    m_terminal = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE);
    // set terminal view theme
    m_terminal->SetBackgroundColour(m_terminalBGColour);
    m_terminal->SetForegroundColour(m_terminalFGColour);
    m_terminal->SetFont(m_terminalFont);
    m_terminal->SetEditable(false);

    // add welcome text
    // create buttons panel and add to sizer
    m_buttonsPanel = new wxPanel(this);

    // create buttons panel sizer
    m_btnsPanelHSizer = new wxBoxSizer(wxHORIZONTAL);
    m_buttonsPanel->SetSizer(m_btnsPanelHSizer);

    // create buttons
    m_btnLoad = new wxButton(this, ID_LOAD, "Load", wxDefaultPosition, wxDefaultSize, wxBORDER_NONE);
    m_btnStart = new wxButton(this, ID_START, "Start", wxDefaultPosition, wxDefaultSize, wxBORDER_NONE);
    m_btnPause = new wxButton(this, ID_PAUSE, "Pause", wxDefaultPosition, wxDefaultSize, wxBORDER_NONE);
    m_btnPlus = new wxButton(this, ID_PLUS, "+", wxDefaultPosition, wxDefaultSize, wxBORDER_NONE);
    m_btnMinus = new wxButton(this, ID_MINUS, "-", wxDefaultPosition, wxDefaultSize, wxBORDER_NONE);

    // change background and foreground colors
    m_btnLoad->SetForegroundColour(*wxWHITE);
    m_btnLoad->SetBackgroundColour(*wxBLACK);
    m_btnStart->SetForegroundColour(*wxWHITE);
    m_btnStart->SetBackgroundColour(*wxBLACK);
    m_btnPause->SetForegroundColour(*wxWHITE);
    m_btnPause->SetBackgroundColour(*wxBLACK);
    m_btnPlus->SetForegroundColour(*wxWHITE);
    m_btnPlus->SetBackgroundColour(*wxBLACK);
    m_btnMinus->SetForegroundColour(*wxWHITE);
    m_btnMinus->SetBackgroundColour(*wxBLACK);

    // add for sizing
    m_btnsPanelHSizer->Add(m_btnLoad, 1);
    m_btnsPanelHSizer->Add(m_btnStart, 1);
    m_btnsPanelHSizer->Add(m_btnPause, 1);
    m_btnsPanelHSizer->Add(m_btnPlus, 1);
    m_btnsPanelHSizer->Add(m_btnMinus, 1);

    // add for sizing
    m_mainSizer->Add(m_buttonsPanel, 1, wxEXPAND | wxALL, 0);
    m_mainSizer->Add(m_terminal, 5, wxEXPAND | wxALL, 0);

    // bind our timer to this
    m_iterTimer.Bind(wxEVT_TIMER, &Arena::OnIterationTimer, this);
    m_intervTimer.Bind(wxEVT_TIMER, &Arena::OnIntervalTimer, this);
}

// when load button is clicked
// we will open a file selection dialog and read that file into memory
void Arena::OnLoad(wxCommandEvent& WXUNUSED(event))
{
    // create a new file dialog
    wxDirDialog* fd = new wxDirDialog(this, "XVM XWars - Arena - Choose Bots Folder", wxEmptyString, wxDD_DEFAULT_STYLE | wxDD_DIR_MUST_EXIST);

    // check if file was selected or not
    if (fd->ShowModal() == wxID_CANCEL) {
        return;
    }

    // get the selected directory path
    wxString botFolder = fd->GetPath();
    LoadBots(botFolder);
}

void Arena::OnStart(wxCommandEvent& WXUNUSED(event))
{
    // shorter name for bots
    const auto& bots = get_xwars_instance()->botpaths;

    // generate battle indices
    m_battlePairs.clear();
    m_battleIdx = 0;
    for (u32 i = 0; i < bots.size() - 1; i++) {
        for (u32 j = i + 1; j < bots.size(); j++) {
            m_battlePairs.push_back({ i, j });
        }
    }
    // wxPuts("Generated BattlePairs");

    // clear memory grid
    FactoryGetMiddlePanel()->GetMemoryGrid()->ClearGrid();

    // do first battle
    const std::pair<int, int>& botpair = m_battlePairs[m_battleIdx++];
    if (get_xwars_instance()->battle_init(bots[botpair.first],
            bots[botpair.second])) {
        m_iterTimer.Start(m_iterWaitTime);
    }
}

void Arena::OnIntervalTimer(wxTimerEvent& e){
    // show stats
    StatsDisplay *stats = new StatsDisplay(get_xwars_instance()->winner);
    stats->ShowModal();

    if (m_battleIdx == m_battlePairs.size()) {
        m_intervTimer.Stop();
        return;
    }

    // do battle
    const auto& bots = get_xwars_instance()->botpaths;
    const std::pair<int, int>& botpair = m_battlePairs[m_battleIdx++];

    // clear memory grid
    FactoryGetMiddlePanel()->GetMemoryGrid()->ClearGrid();

    // init battle and start iteration timer
    if (get_xwars_instance()->battle_init(bots[botpair.first], bots[botpair.second])) {
        m_iterTimer.Start(m_iterWaitTime);
    }
}

void Arena::OnIterationTimer(wxTimerEvent& e)
{
    // wxPuts("Reached Iteration Timer");

    if (!get_xwars_instance()->battle_step()) {
        Print("[+] Winner %s in %d instructions\n", get_xwars_instance()->winner.c_str(), get_xwars_instance()->counter);
        m_iterTimer.Stop();
        m_intervTimer.Start(m_interWaitTime);
    }
}

void Arena::UpdateSelf()
{
    m_terminal->SetBackgroundColour(properties.bgColour);
    m_terminal->SetForegroundColour(properties.fgColour);
    m_terminal->SetFont(properties.GetFont());
}

// load bots abstraction
void Arena::LoadBots(const wxString& BotsFolder)
{
    DIR* botdir = opendir(BotsFolder.GetData().AsChar());

    // get file names in the selected folder
    std::vector<std::string> botpaths;
    struct dirent* dp = NULL;
    while (botdir) {
        if ((dp = readdir(botdir)) != NULL) {
            if (!strncmp(strchr(dp->d_name, '.'), ".bot", 4)) {
                // assemble all bots
                // bot paths must contain assembled bot paths
                botpaths.emplace_back((BotsFolder + "/" + dp->d_name).ToStdString());
            }
        } else {
            closedir(botdir);
            break;
        }
    }

    // create and load bots
    // get_xwars_instance()->load_bots(botpaths, botnames);
    get_xwars_instance()->botpaths = botpaths;
    // check and print status
    for (size_t i = 0; i < botpaths.size(); i++) {
        Print("[+] Loaded Bot [ %s ]\n", botpaths[i].substr(botpaths[i].find_last_of("/\\") + 1));
    }
}

// OnStart - start iter timer
// OnIterTimer - check if more step and start inter timer and stop iter timer
// OnInterTimer - start iter timer
