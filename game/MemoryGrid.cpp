#include "MemoryGrid.hpp"
#include "../common/bitmap.h"
#include <wx/stringimpl.h>

MemoryGrid::MemoryGrid(wxWindow* parent)
    : wxPanel(parent)
{
    // create grid sizer for memory grid and set it as sizer for "this" panel
    m_memGridSizer = new wxGridSizer(NUM_ROWS_IN_MEM_GRID, NUM_COLS_IN_MEM_GRID, 2, 2);
    this->SetSizer(m_memGridSizer);

    // create memory grid
    for (auto& row : m_memGrid) {
        for (auto& elem : row) {
            elem = new wxStaticText(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(10, 10), wxBORDER_NONE);
            elem->SetBackgroundColour(m_gridElementColour);
            elem->SetFont(wxFont(8, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_LIGHT));
            m_memGridSizer->Add(elem, 1, wxEXPAND | wxALL, 1);
        }
    }
}

void MemoryGrid::UpdateGrid()
{
    for (size_t i = 0; i < NUM_ROWS_IN_MEM_GRID * NUM_COLS_IN_MEM_GRID; i++) {
        // calculate coordinates in mem grid
        size_t x = i / NUM_COLS_IN_MEM_GRID;
        size_t y = i - x * NUM_COLS_IN_MEM_GRID;

        u8 op = get_oprn_at_idx(i);
        bool pm_read = (op >> oprn::oprn_r) & 1;
        bool pm_write = (op >> oprn::oprn_w) & 1;
        bool pm_exec = (op >> oprn::oprn_x) & 1;
        bool bot_id = (op >> oprn::oprn_b) & 1;

        char pm;
        wxColour colour;
        if (check_oprn_valid(op)) {
            /* printf("bot_id: %d\n", bot_id); */
            if (bot_id) {
                if (pm_read) {
                    colour = bot1ReadColour;
                    pm = 'R';
                } else if (pm_write) {
                    colour = bot1WriteColour;
                    pm = 'W';
                } else {
                    colour = bot1ExecColour;
                    pm = 'X';
                }

            } else {
                if (pm_read) {
                    colour = bot2ReadColour;
                    pm = 'R';
                } else if (pm_write) {
                    colour = bot2WriteColour;
                    pm = 'W';
                } else {
                    colour = bot2ExecColour;
                    pm = 'X';
                }
            }
            // m_memGrid[x][y]->SetForegroundColour(*wxWHITE);
            m_memGrid[x][y]->SetBackgroundColour(colour);
            m_memGrid[x][y]->SetLabelText(pm);
        }
    }
}

void MemoryGrid::ClearGrid()
{
    for (size_t i = 0; i < NUM_ROWS_IN_MEM_GRID * NUM_COLS_IN_MEM_GRID; i++) {
        // calculate coordinates in mem grid
        size_t x = i / NUM_COLS_IN_MEM_GRID;
        size_t y = i - x * NUM_COLS_IN_MEM_GRID;

        m_memGrid[x][y]->SetLabelText(wxEmptyString);
        m_memGrid[x][y]->SetBackgroundColour(m_gridElementColour);
    }

    clear_bitmap();
}
