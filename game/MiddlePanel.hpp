#ifndef XVM_ARENA_MIDDLE_PANEL_HPP
#define XVM_ARENA_MIDDLE_PANEL_HPP

#include "Common.hpp"
#include <array>


class MiddlePanel : public wxPanel{
public:
    MiddlePanel(wxWindow *parent);

private:
    // main sizer to arrage items in middle panel
    wxBoxSizer *m_mainSizer;
    
    // top panel will contiain the memory grid
    wxPanel *m_topPanel;
    // wxBoxSizer *m_topPanelVSizer;
    // std::array<wxBoxSizer*, 64> m_topPanelHSizers;

    // bottom panel will show game terminal
    wxPanel *m_bottomPanel;

    // memory grid will display current state of memory and
    // for this we will need a grid sizer to arrange items in grid
    wxGridSizer *m_memGridSizer;
    
    // a memory button is an element in memory grid
    // this will show it's individual status in the grid
    
};

#endif//XVM_ARENA_MIDDLE_PANEL_HPP