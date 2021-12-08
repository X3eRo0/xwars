#include "MemoryGrid.hpp"
#include "../common/bitmap.h"

MemoryGrid::MemoryGrid(wxWindow* parent) : wxPanel(parent){
    // create grid sizer for memory grid and set it as sizer for "this" panel
    m_memGridSizer = new wxGridSizer(NUM_ROWS_IN_MEM_GRID, NUM_COLS_IN_MEM_GRID, 2, 2);
    this->SetSizer(m_memGridSizer);

    // create memory grid
    for(auto& row : m_memGrid){
        for(auto& elem : row){
            elem = new wxStaticText(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(10, 10), wxBORDER_NONE);
            elem->SetBackgroundColour(m_gridElementColour);
            m_memGridSizer->Add(elem, 1, wxEXPAND | wxALL, 1);
        }
    }
}

void MemoryGrid::UpdateGrid(){
    for(size_t i = 0; i < 1024; i++){
        // calculate coordinates in mem grid
        size_t x = i / NUM_COLS_IN_MEM_GRID;
        size_t y = i - x * NUM_COLS_IN_MEM_GRID;

        u8 op = get_oprn_at_idx(i);
        bool pm_read = op & oprn::oprn_r;
        bool pm_write = op & oprn::oprn_w;
        bool pm_exec = op & oprn::oprn_x;
        bool bot_id = op & oprn::oprn_b;

        if(check_oprn_valid(op)){
            wxColour colour;
            if(bot_id){
                char pm;

                if(pm_read){
                    colour = bot1ReadColour;
                    pm = 'r';
                }else if(pm_write){
                    colour = bot1WriteColour;
                    pm = 'w';
                }else{
                    colour = bot1ExecColour;
                    pm = 'x';
                }

                m_memGrid[x][y]->SetForegroundColour(colour);
                m_memGrid[x][y]->SetLabelText(pm);
            }else{
                char pm;

                if(pm_read){
                    colour = bot2ReadColour;
                    pm = 'r';
                }else if(pm_write){
                    colour = bot2WriteColour;
                    pm = 'w';
                }else{
                    colour = bot2ExecColour;
                    pm = 'x';
                }

                m_memGrid[x][y]->SetForegroundColour(colour);
                m_memGrid[x][y]->SetLabelText(pm);
            }
        }
    }
}
