#include "MiddlePanel.hpp"
#include "Arena.hpp"
#include "MemoryGrid.hpp"
#include <wx/gdicmn.h>
#include <wx/sizer.h>

MiddlePanel::MiddlePanel(wxWindow* parent)
    : wxPanel(parent)
{
    // create main sizer to arrage items within
    // this middle panel
    m_mainSizer = new wxBoxSizer(wxVERTICAL);
    this->SetSizer(m_mainSizer);

    // create panels within middle panel
    m_memoryGrid = new MemoryGrid(this);
    m_arenaTerminal = new Arena(this);

    // add items to main sizer
    m_mainSizer->Add(m_memoryGrid, 12, wxEXPAND | wxALL);
    m_mainSizer->Add(m_arenaTerminal, 5, wxEXPAND | wxALL);

    // bottom panel will be black
    m_memoryGrid->SetBackgroundColour(wxColour(10, 10, 10));
    m_arenaTerminal->SetBackgroundColour(wxColour(32, 32, 32));
}
