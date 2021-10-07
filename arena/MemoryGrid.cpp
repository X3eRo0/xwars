#include "MemoryGrid.hpp"
#include <wx/gtk/window.h>

MemoryGrid::MemoryGrid(wxWindow* parent) : wxPanel(parent){
    // create grid sizer for memory grid and set it as sizer for "this" panel
    m_memGridSizer = new wxGridSizer(NUM_ROWS_IN_MEM_GRID, NUM_COLS_IN_MEM_GRID, 2, 2);
    this->SetSizer(m_memGridSizer);
    
    // create memory grid
    for(auto& row : m_memGrid){
        for(auto& elem : row){
            elem = new wxButton(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(10, 10), wxBORDER_NONE);
            elem->SetBackgroundColour(m_gridElementColour);
            m_memGridSizer->Add(elem, 1, wxEXPAND | wxALL, 1);
        }
    }   
}