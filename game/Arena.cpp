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

#include "MainWindow.hpp"
#include "MemoryGrid.hpp"
#include "MiddlePanel.hpp"
#include "StatsDisplay.hpp"

enum xvmArenaButtonIDs {
    ID_LOAD = wxID_HIGHEST + 1000,
    ID_START = wxID_HIGHEST + 1001,
    ID_PAUSE = wxID_HIGHEST + 1002,
    ID_NEXT = wxID_HIGHEST + 1003,
    ID_PLUS = wxID_HIGHEST + 1004,
    ID_MINUS = wxID_HIGHEST + 1005
};

// event table
BEGIN_EVENT_TABLE(Arena, wxPanel)
EVT_BUTTON(ID_LOAD, Arena::OnLoad)
EVT_BUTTON(ID_START, Arena::OnStart)
EVT_BUTTON(ID_PAUSE, Arena::OnPause)
EVT_BUTTON(ID_NEXT, Arena::OnNext)
EVT_BUTTON(ID_PLUS, Arena::OnIncrement)
EVT_BUTTON(ID_MINUS, Arena::OnDecrement)
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
    m_btnLoad = new wxButton(m_buttonsPanel, ID_LOAD, "Load", wxDefaultPosition, wxDefaultSize, 0);
    m_btnStart = new wxButton(m_buttonsPanel, ID_START, "Start", wxDefaultPosition, wxDefaultSize, 0);
    m_btnPause = new wxButton(m_buttonsPanel, ID_PAUSE, "Pause", wxDefaultPosition, wxDefaultSize, 0);
    m_btnNext = new wxButton(m_buttonsPanel, ID_NEXT, "NextI", wxDefaultPosition, wxDefaultSize, 0);
    m_btnPlus = new wxButton(m_buttonsPanel, ID_PLUS, "+", wxDefaultPosition, wxDefaultSize, 0);
    m_btnMinus = new wxButton(m_buttonsPanel, ID_MINUS, "-", wxDefaultPosition, wxDefaultSize, 0);

    // change background and foreground colors
    m_btnLoad->SetForegroundColour(*wxWHITE);
    m_btnLoad->SetBackgroundColour(*wxBLACK);
    m_btnStart->SetForegroundColour(*wxWHITE);
    m_btnStart->SetBackgroundColour(*wxBLACK);
    m_btnPause->SetForegroundColour(*wxWHITE);
    m_btnPause->SetBackgroundColour(*wxBLACK);
    m_btnNext->SetForegroundColour(*wxWHITE);
    m_btnNext->SetBackgroundColour(*wxBLACK);
    m_btnPlus->SetForegroundColour(*wxWHITE);
    m_btnPlus->SetBackgroundColour(*wxBLACK);
    m_btnMinus->SetForegroundColour(*wxWHITE);
    m_btnMinus->SetBackgroundColour(*wxBLACK);

    // add for sizing
    m_btnsPanelHSizer->Add(m_btnLoad, 1, wxEXPAND | wxUP | wxDOWN);
    m_btnsPanelHSizer->Add(m_btnStart, 1, wxEXPAND | wxUP | wxDOWN);
    m_btnsPanelHSizer->Add(m_btnPause, 1, wxEXPAND | wxUP | wxDOWN);
    m_btnsPanelHSizer->Add(m_btnNext, 1, wxEXPAND | wxUP | wxDOWN);
    m_btnsPanelHSizer->Add(m_btnPlus, 1, wxEXPAND | wxUP | wxDOWN);
    m_btnsPanelHSizer->Add(m_btnMinus, 1, wxEXPAND | wxUP | wxDOWN);

    // add for sizing
    m_mainSizer->Add(m_buttonsPanel, 1, wxEXPAND | wxALL);
    m_mainSizer->Add(m_terminal, 5, wxEXPAND | wxALL);

    // bind our timer to this
    m_iterTimer.Bind(wxEVT_TIMER, &Arena::OnIterationTimer, this);
    // m_intervTimer.Bind(wxEVT_TIMER, &Arena::OnIntervalTimer, this);
    m_statusUpdateTimer.Bind(wxEVT_TIMER, &Arena::OnUpdateStatus, this);
    m_statusUpdateTimer.Start(5);

    // create stats display
    m_statsDisplay = new StatsDisplay;
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
    if (!m_isBattlePaused) {
        // clear scoreboard
        m_statsDisplay->ClearDisplay();

        // shorter name for bots
        const auto& bots = get_xwars_instance()->botpaths;

        // add botnames to scoreboard
        for (const auto& botname : bots) {
            m_statsDisplay->AddBot(botname.substr(botname.find_last_of("/\\") + 1), 0);
        }

        // generate battle indices
        m_battlePairs.clear();
        m_battleIdx = 0;
        for (u32 i = 0; i < bots.size() - 1; i++) {
            for (u32 j = i + 1; j < bots.size(); j++) {
                m_battlePairs.push_back({ i, j });
            }
        }

        // clear memory grid
        FactoryGetMiddlePanel()->GetMemoryGrid()->ClearGrid();

        // do first battle
        const std::pair<int, int>& botpair = m_battlePairs[m_battleIdx++];
        if (get_xwars_instance()->battle_init(bots[botpair.first], bots[botpair.second])) {
            m_iterTimer.Start(m_iterWaitTime);
        }
        set_statustext("Running!");
    } else {
        m_iterTimer.Start(m_iterWaitTime);
        m_isBattlePaused = false;
        set_statustext("Running!");
    }
}

void Arena::OnIterationTimer(wxTimerEvent& e)
{
    xwars* xwars_instance = get_xwars_instance();

    if (xwars_instance->get_battle_status() && !xwars_instance->battle_step()) {
        Print("%s", xwars_instance->get_battle_results());
        xwars_instance->set_battle_status(0);
        // m_iterTimer.Stop();
        // m_intervTimer.Start(m_interWaitTime);

        // display stats
        m_statsDisplay->SetWinnerAndLooser(xwars_instance->battle_result.state, xwars_instance->battle_result.bot1->botname, xwars_instance->battle_result.bot2->botname);
        m_statsDisplay->ShowModal();

        // this is the last battle
        if (m_battleIdx == m_battlePairs.size()) {
            m_iterTimer.Stop();
            set_statustext("Idle");
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
            if ((dp->d_type == DT_REG) && !strncmp(strchr(dp->d_name, '.'), ".bot", 4)) {
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
        Print("[+] %s Loaded\n", botpaths[i].substr(botpaths[i].find_last_of("/\\") + 1));
    }
}

void Arena::OnNext(wxCommandEvent& event)
{
    if (m_battlePairs.empty()) {
        return;
    }
    if (m_isBattlePaused) {
        get_xwars_instance()->battle_step();
    } else {
        Print("[-] Cannot execute next instruction while battle is not paused\n");
    }
}

void Arena::OnPause(wxCommandEvent& event)
{
    if (m_battlePairs.empty()) {
        return;
    }
    m_iterTimer.Stop();
    m_isBattlePaused = true;
    set_statustext("Paused!");
}

void Arena::OnUpdateStatus(wxTimerEvent& e)
{
    wxString instructionNo;
    wxString delay;
    wxString loadedbots;
    wxString currentbattle;
    wxString animationstring = get_statustext();
    static wxString output = "Status: ";
    u32 max_anim_length = 50;
    static u32 anim_counter = 0;
    static u32 timer_counter = 0;
    anim_counter %= max_anim_length;
    if (timer_counter % 10 == 0) {
        output = "Status: ";
        if (anim_counter < max_anim_length) {
            for (u32 i = 0; i < anim_counter; i++) {
                output += " ";
            }
            u32 len = animationstring.length();
            if (max_anim_length - anim_counter < animationstring.length()) {
                len = max_anim_length - anim_counter;
            }
            output += animationstring.substr(0, len);
            if (len == animationstring.length()) {
                for (u32 i = 0; i < max_anim_length - len - anim_counter; i++) {
                    output += " ";
                }
            }
        }
        anim_counter++;
    }
    timer_counter++;
    instructionNo.Printf("# of Instructions: %.4d", get_xwars_instance()->counter);
    delay.Printf("Delay: %.3ldms", m_iterWaitTime);
    loadedbots.Printf("Loaded Bots: %.3ld", get_xwars_instance()->botpaths.size());
    currentbattle.Printf("Current Battle: %.4ld", m_battleIdx);
    FactoryGetMainWindow()->SetStatusText(instructionNo, 0);
    FactoryGetMainWindow()->SetStatusText(delay, 1);
    FactoryGetMainWindow()->SetStatusText(loadedbots, 2);
    FactoryGetMainWindow()->SetStatusText(currentbattle, 3);
    FactoryGetMainWindow()->SetStatusText(output, 4);
    FactoryGetMainWindow()->SetStatusText("XWars Version 1.0 Alpha", 5);
}

void Arena::OnIncrement(wxCommandEvent& event)
{
    if (m_iterWaitTime >= 20 && m_iterWaitTime <= 990) {
        m_iterWaitTime += 10;
    }
    if (!m_isBattlePaused) {
        m_iterTimer.Stop();
        m_iterTimer.Start(m_iterWaitTime);
    }
}

void Arena::OnDecrement(wxCommandEvent& event)
{
    if (m_iterWaitTime >= 20 && m_iterWaitTime <= 1000) {
        m_iterWaitTime -= 10;
    }
    if (!m_isBattlePaused) {
        m_iterTimer.Stop();
        m_iterTimer.Start(m_iterWaitTime);
    }
}
// OnStart - start iter timer
// OnIterTimer - check if more step and start inter timer and stop iter timer
// OnInterTimer - start iter timer
