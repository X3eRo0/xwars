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

    // update element of memory grid
    void UpdateGrid(size_t offset, BotID bid, Permission pm);
private:
    // bot1 read/write/execute colours
    wxColour bot1ReadColour = wxColour(31, 255, 240);
    wxColour bot1WriteColour = wxColour(10, 245, 14);
    wxColour bot1ExecColour = wxColour(238, 255, 0);

    // bot2 read/write/execute colors
    wxColour bot2ReadColour = wxColour(151, 15, 153);
    wxColour bot2WriteColour = wxColour(240, 12, 95);
    wxColour bot2ExecColour = wxColour(26, 44, 237);

    // sizer to arrange our memory grid
    wxGridSizer *m_memGridSizer = nullptr;

    // colour for our item in grid
    wxColour m_gridElementColour = *wxWHITE;

    // our memory grid
    std::array<std::array<wxStaticText*, NUM_COLS_IN_MEM_GRID>, NUM_ROWS_IN_MEM_GRID> m_memGrid;
};

#endif//XVM_ARENA_MEMORY_GRID_HPP
