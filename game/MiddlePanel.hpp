#ifndef XVM_ARENA_MIDDLE_PANEL_HPP
#define XVM_ARENA_MIDDLE_PANEL_HPP

#include "Common.hpp"
#include "Arena.hpp"
#include "MemoryGrid.hpp"
#include <array>


class MiddlePanel : public wxPanel{
public:
    MiddlePanel(wxWindow *parent);

    // print instruction in the arena terminal
    template<typename fmttype, typename... argtypes>
    void PrintToTerminal(fmttype fmtstr, argtypes... args){
		m_arenaTerminal->Print(fmtstr, args...);
    }

    // get arena terminal
    Arena* GetArena() { return m_arenaTerminal; }

    // get memory grid
    MemoryGrid* GetMemoryGrid() { return m_memoryGrid; }
private:
    // main sizer to arrage items in middle panel
    wxBoxSizer *m_mainSizer;

    // top panel will contiain the memory grid
    MemoryGrid *m_memoryGrid;
    // wxBoxSizer *m_topPanelVSizer;
    // std::array<wxBoxSizer*, 64> m_topPanelHSizers;

    // bottom panel will show game terminal
    Arena *m_arenaTerminal;

    // memory grid will display current state of memory and
    // for this we will need a grid sizer to arrange items in grid
    wxGridSizer *m_memGridSizer;

    // a memory button is an element in memory grid
    // this will show it's individual status in the grid
};

#endif//XVM_ARENA_MIDDLE_PANEL_HPP
