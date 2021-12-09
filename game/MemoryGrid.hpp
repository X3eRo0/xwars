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
    void UpdateGrid();

    // clears the grid whenever called
    void ClearGrid();
private:
    // bot1 read/write/execute colours
    wxColour bot1ReadColour = wxColour(0, 255, 255);  // cyan
    wxColour bot1WriteColour = wxColour(255,192,203); // pink
    wxColour bot1ExecColour = wxColour(0, 0, 255);  // blue

    // bot2 read/write/execute colors
    wxColour bot2ReadColour = wxColour(255, 255, 0);  // yellow
    wxColour bot2WriteColour = wxColour(255, 165, 0); // orange
    wxColour bot2ExecColour = wxColour(255, 0, 0);    // red

    // sizer to arrange our memory grid
    wxGridSizer *m_memGridSizer = nullptr;

    // colour for our item in grid
    wxColour m_gridElementColour = wxColour(128, 128, 128);

    // our memory grid
    std::array<std::array<wxStaticText*, NUM_COLS_IN_MEM_GRID>, NUM_ROWS_IN_MEM_GRID> m_memGrid;
};

#endif//XVM_ARENA_MEMORY_GRID_HPP
