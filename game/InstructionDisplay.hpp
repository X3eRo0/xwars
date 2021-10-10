/**
 * @file InstructionDisplay.hpp
 * @author Siddharth Mishra
 * @brief This will show current instruction being executed for given bot
 * @version 0.1
 * @date 2021-10-09
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef XVM_ARENA_INSTRUCTION_DISPLAY_HPP
#define XVM_ARENA_INSTRUCTION_DISPLAY_HPP

#include "Common.hpp"
#include <wx/listctrl.h>

struct InstructionData{
    std::string address;
    std::string opcode;
    std::string instruction;
};

class InstructionDisplay : public wxPanel{
public:
    InstructionDisplay(wxWindow *parent);

    // add a new address, opcode, instruction trio
    void AddNewInstruction(const std::string& address, const std::string& opcode, const std::string& instruction);

    // select a particular instruction by index
    void SelectInstructionByIndex(size_t idx);

    // get index of instruction by address
    // returns -1 if fails to find address in list
    size_t GetInstructionIndexByAddress(const std::string& address);

    // select instruction by address
    void SelectInstructionByAddress(const std::string& address);

private:
    wxColour m_bgColor = wxColour(32, 16, 32);
    // main sizer
    wxSizer *m_mainSizer;
    // this box will contain all our objects
    wxStaticBox *m_parentBox;
    // parent box colour 
    wxColour m_parentBoxFGColour = *wxCYAN;
    // sizer for sizing objects in parent box
    wxBoxSizer *m_parentBoxSizer;
    // list to display our instructions
    wxListView *m_instructionList;
    // keep instruction data
    std::vector<InstructionData> m_instructions;
    // keep track of number of instructions in list
    size_t m_numInstructions = 0;
};

#endif//XVM_ARENA_INSTRUCTION_DISPLAY_HPP
