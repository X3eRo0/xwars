#ifndef XVM_ARENA_MEMORY_GRID_HPP
#define XVM_ARENA_MEMORY_GRID_HPP

#include "Common.hpp"
#include <wx/gdicmn.h>

// memory grid size
#define NUM_ROWS_IN_MEM_GRID 32
#define NUM_COLS_IN_MEM_GRID 32

enum class BotID { Bot1, Bot2 };

enum class Permission {Read = 'R', Write = 'W', Execute = 'X'};

class MemoryGrid : public wxPanel{
public:
    MemoryGrid(wxWindow* parent);

    // update (x, y) element of memory grid
    void UpdateGrid(size_t x, size_t y, BotID bid, Permission pm);
private:
    // sizer to arrange our memory grid
    wxGridSizer *m_memGridSizer = nullptr;

    // colour for our item in grid
    wxColour m_gridElementColour = *wxWHITE;

    // our memory grid
    std::array<std::array<wxStaticText*, NUM_COLS_IN_MEM_GRID>, NUM_ROWS_IN_MEM_GRID> m_memGrid;
};

#endif//XVM_ARENA_MEMORY_GRID_HPP
