/**
 * @file RegisterDisplay.cpp
 * @author Siddharth Mishra
 * @brief This panel will show current state of registers for the given bot.
 * @version 0.1
 * @date 2021-10-09
 */

#include "RegisterDisplay.hpp"
#include "Common.hpp"
#include <wx/sizer.h>
#include <wx/stringimpl.h>

RegisterDisplay::RegisterDisplay(wxWindow* parent)
    : wxPanel(parent)
{
    // change bg color
    SetBackgroundColour(m_bgColor);

    // initialize grid sizer for arranging gprs
    m_regGridSizer = new wxGridSizer(6, 3, 0, 0);

    // initialize gen purpose regs
    for (size_t i = 0; i < NUMBER_OF_REGISTERS; i++) {
        // initialize registers and add to grid sizer
        m_registers[Register::RegisterNames[i]] = new Register(this, Register::RegisterNames[i]);
        m_registers[Register::RegisterNames[i]]->SetBackgroundColour(wxColour(0, 0, 0));
        m_regGridSizer->Add(m_registers[Register::RegisterNames[i]], 1);
    }

    this->SetSizer(m_regGridSizer);
}

// set register value
void RegisterDisplay::SetRegisterValue(const std::string& regname, const std::string& val)
{
    m_registers[regname]->SetValue(val);
}

// update self properties
void RegisterDisplay::UpdateSelf()
{
    // change self background
    this->SetBackgroundColour(properties.bgColour);

    // change each registers background and properties
    for (auto& [regname, reg] : m_registers) {
        reg->SetFont(properties.GetFont());
        reg->SetBGColour(properties.bgColour);
        reg->SetFGColour(properties.fgColour);
    };
}
