#include "MiddlePanel.hpp"
#include <wx/gdicmn.h>
#include <wx/sizer.h>
#include "MemoryGrid.hpp"
#include "Arena.hpp"

MiddlePanel::MiddlePanel(wxWindow* parent) : wxPanel(parent){
    // create main sizer to arrage items within
    // this middle panel
    m_mainSizer = new wxBoxSizer(wxVERTICAL);
    this->SetSizer(m_mainSizer);

    // create panels within middle panel
    MemoryGrid *m_topPanel = new MemoryGrid(this);
    Arena *m_bottomPanel = new Arena(this);

    // add items to main sizer
    m_mainSizer->Add(m_topPanel, 2, wxEXPAND | wxALL);
    m_mainSizer->Add(m_bottomPanel, 1, wxEXPAND | wxALL);

    // bottom panel will be black
    m_bottomPanel->SetBackgroundColour(wxColour(10, 10, 10));
    m_topPanel->SetBackgroundColour(wxColour(32, 32, 32));
}
