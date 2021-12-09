#include "Factory.hpp"
#include "BotInfo.hpp"
#include "InstructionDisplay.hpp"
#include "MainWindow.hpp"
#include "MiddlePanel.hpp"
#include "RegisterDisplay.hpp"
#include <unordered_map>
#include <wx/gdicmn.h>
#include <wx/stringimpl.h>

struct Factory {
    MainWindow* mainWindow = nullptr;
    MiddlePanel* middlePanel = nullptr;
    BotInfo *lBotInfo, *rBotInfo = nullptr;
    RegisterDisplay *lRegDisplay = nullptr, *rRegDisplay = nullptr;
    InstructionDisplay *lInstrDisplay = nullptr, *rInstrDisplay = nullptr;
};

static Factory factory;

// ------------------------- SETTERS --------------------------

// create main window and return ptr
MainWindow* FactoryCreateMainWindow(wxWindow* parent = nullptr,
    wxWindowID id = wxID_ANY,
    const wxString& title = wxEmptyString)
{
    factory.mainWindow = new MainWindow(parent, id, title);
    return factory.mainWindow;
}

// create middle panel
MiddlePanel* FactoryCreateMiddlePanel(wxWindow* parent)
{
    factory.middlePanel = new MiddlePanel(parent);
    return factory.middlePanel;
}

// create bot info for left and return ptr
BotInfo* FactoryCreateLeftBotInfo(wxWindow* parent, const std::string& botname)
{
    factory.lBotInfo = new BotInfo(parent, botname, true); // true means left
    return factory.lBotInfo;
}

// create bot info for right and return ptr
BotInfo* FactoryCreateRightBotInfo(wxWindow* parent, const std::string& botname)
{
    factory.rBotInfo = new BotInfo(parent, botname, false); // false means right
    return factory.rBotInfo;
}

// create left bot info panel register display
RegisterDisplay* FactoryCreateLeftRegisterDisplay(wxWindow* parent)
{
    factory.lRegDisplay = new RegisterDisplay(parent);
    return factory.lRegDisplay;
}

// create right bot info panel register display
RegisterDisplay* FactoryCreateRightRegisterDisplay(wxWindow* parent)
{
    factory.rRegDisplay = new RegisterDisplay(parent);
    return factory.rRegDisplay;
}

// create left bot info panel instructiondisplay
InstructionDisplay* FactoryCreateLeftInstructionDisplay(wxWindow* parent)
{
    factory.lInstrDisplay = new InstructionDisplay(parent);
    return factory.lInstrDisplay;
}

// create right bot info panel instructiondisplay
InstructionDisplay* FactoryCreateRightInstructionDisplay(wxWindow* parent)
{
    factory.rInstrDisplay = new InstructionDisplay(parent);
    return factory.rInstrDisplay;
}

// ------------------------- GETTERS --------------------------

// get already created main window
MainWindow* FactoryGetMainWindow() { return factory.mainWindow; }

// get already create middle panel
MiddlePanel* FactoryGetMiddlePanel() { return factory.middlePanel; }

// get already created bot infos
BotInfo* FactoryGetLeftBotInfo() { return factory.lBotInfo; }
BotInfo* FactoryGetRightBotInfo() { return factory.rBotInfo; }

// get already created register displays
RegisterDisplay* FactoryGetLeftRegisterDisplay() { return factory.lRegDisplay; }
RegisterDisplay* FactoryGetRightRegisterDisplay()
{
    return factory.rRegDisplay;
}

// get already created instruction displays
InstructionDisplay* FactoryGetLeftInstructionDisplay()
{
    if (!factory.lInstrDisplay)
        wxPuts("Wait!");
    return factory.lInstrDisplay;
}

InstructionDisplay* FactoryGetRightInstructionDisplay()
{
    return factory.rInstrDisplay;
}
