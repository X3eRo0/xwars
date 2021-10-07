#ifndef XVM_ARENA_MEMORY_GRID_HPP
#define XVM_ARENA_MEMORY_GRID_HPP

#include "Common.hpp"
#include <wx/gdicmn.h>

// memory grid size
#define NUM_ROWS_IN_MEM_GRID 32
#define NUM_COLS_IN_MEM_GRID 32

class MemoryGrid : public wxPanel{
public:
    MemoryGrid(wxWindow* parent);

private:
    // sizer to arrange our memory grid
    wxGridSizer *m_memGridSizer = nullptr;

    // colour for our item in grid
    wxColour m_gridElementColour = *wxWHITE;

    // our memory grid
    std::array<std::array<wxButton*, NUM_COLS_IN_MEM_GRID>, NUM_ROWS_IN_MEM_GRID> m_memGrid;
};

#endif//XVM_ARENA_MEMORY_GRID_HPP