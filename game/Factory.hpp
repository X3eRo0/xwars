#ifndef XVM_ARENA_FACTORY_HPP
#define XVM_ARENA_FACTORY_HPP

#include "Common.hpp"

class MainWindow;
class BotInfo;
class MiddlePanel;
class RegisterDisplay;
class InstructionDisplay;

// create a new object by calling create functions
// @warning : each object of same type must have different names!
// get already created object by name used during creation

// ------------------------- SETTERS --------------------------

// create main window
// this returns the main window pointer
MainWindow* FactoryCreateMainWindow(wxWindow* parent,
    wxWindowID id, const wxString& title);

// create bot info panel (left and right panel in main window)
// this returns the bot info panel pointer
BotInfo* FactoryCreateLeftBotInfo(wxWindow* parent, const std::string& botname);
BotInfo* FactoryCreateRightBotInfo(wxWindow* parent, const std::string& botname);

// create middle panel (contains memory grid and terminal in main window)
// returns the created middle panel's pointer
MiddlePanel* FactoryCreateMiddlePanel(wxWindow* parent);

// create register display panel
// present at the top of each bot info panel
// newly created register display panel is returned
RegisterDisplay* FactoryCreateLeftRegisterDisplay(wxWindow* parent);
RegisterDisplay* FactoryCreateRightRegisterDisplay(wxWindow* parent);

// create instruction display panel
// present at the bottom of each bot info panel
// newly created instructiondisplay is returned
InstructionDisplay* FactoryCreateLeftInstructionDisplay(wxWindow* parent);
InstructionDisplay* FactoryCreateRightInstructionDisplay(wxWindow* parent);

// create

// ------------------------- SETTERS --------------------------

// get main window pointer
// returns nullptr on fail
MainWindow* FactoryGetMainWindow();

// get bot info panel pointer
// returns nullptr on fail
BotInfo* FactoryGetLeftBotInfo();
BotInfo* FactoryGetRightBotInfo();

// get middle panel pointer
// returns nullptr on fail
MiddlePanel* FactoryGetMiddlePanel();

// get registerdisplay panel
// return nullptr on fail
RegisterDisplay* FactoryGetLeftRegisterDisplay();
RegisterDisplay* FactoryGetRightRegisterDisplay();

// get instructiondisplay panel by name
// return nullptr on fail
InstructionDisplay* FactoryGetLeftInstructionDisplay();
InstructionDisplay* FactoryGetRightInstructionDisplay();

#endif // XVM_ARENA_FACTORY_HPP
