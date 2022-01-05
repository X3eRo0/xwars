#include "MemoryGrid.hpp"
#include "../common/bitmap.h"
#include "Common.hpp"
#include <wx/gdicmn.h>
#include <wx/gtk/colour.h>
#include <wx/stattext.h>
#include <wx/stringimpl.h>

MemoryGrid::MemoryGrid(wxWindow* parent)
    : wxPanel(parent)
{
    // create grid sizer for memory grid and set it as sizer for "this" panel
    m_memGridSizer = new wxGridSizer(NUM_ROWS_IN_MEM_GRID, NUM_COLS_IN_MEM_GRID, 1, 1);
    m_memGridSizer->SetCols(NUM_COLS_IN_MEM_GRID);
    m_memGridSizer->SetRows(NUM_ROWS_IN_MEM_GRID);
    this->SetSizer(m_memGridSizer);

    // create memory grid
    for (auto& row : m_memGrid) {
        for (auto& elem : row) {
            elem = new wxStaticText(this, wxID_ANY, wxEmptyString, wxDefaultPosition,
                wxDefaultSize, wxBORDER_NONE | wxST_NO_AUTORESIZE | wxALIGN_CENTRE_HORIZONTAL);
            elem->Wrap(9);
            elem->SetBackgroundColour(m_gridElementColour);
            elem->SetOwnBackgroundColour(m_gridElementColour);
            elem->SetFont(wxFont(9, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
            m_memGridSizer->Add(elem, 1, wxEXPAND | wxALL, 1);
        }
    }
}

void MemoryGrid::UpdateGrid()
{
    /* ClearExecs(); */
    for (size_t i = 0; i < NUM_ROWS_IN_MEM_GRID * NUM_COLS_IN_MEM_GRID; i++) {
        // calculate coordinates in mem grid
        size_t x = i / NUM_COLS_IN_MEM_GRID;
        size_t y = i - x * NUM_COLS_IN_MEM_GRID;

        u8 op = get_oprn_at_idx(i);
        bool pm_read = (op >> oprn::oprn_r) & 1;
        bool pm_write = (op >> oprn::oprn_w) & 1;
        bool pm_exec = (op >> oprn::oprn_x) & 1;
        bool bot_id = (op >> oprn::oprn_b) & 1;
        wxString pm = wxEmptyString;
        wxColour colour = *wxBLACK;
        if (check_oprn_valid(op)) {
            /* printf("bot_id: %d\n", bot_id); */
            if (bot_id == 1) {
                if (pm_read && pm_write && pm_exec) {
                    colour = GetBot1ExecColour();
                    pm = "X";
                    set_oprn_at_idx(i, make_oprn(1, oprn_x));
                } else if (pm_read) {
                    colour = GetBot1ReadColour();
                    pm = "R";
                } else if (pm_write) {
                    colour = GetBot1WriteColour();
                    pm = "W";
                } else {
                    colour = GetBot1ExecColour();
                    pm = wxEmptyString;
                }

            } else {
                if (pm_read && pm_write && pm_exec) {
                    colour = GetBot2ExecColour();
                    pm = "X";
                    set_oprn_at_idx(i, make_oprn(0, oprn_x));
                } else if (pm_read) {
                    colour = GetBot2ReadColour();
                    pm = "R";
                } else if (pm_write) {
                    colour = GetBot2WriteColour();
                    pm = "W";
                } else {
                    colour = GetBot2ExecColour();
                    pm = wxEmptyString;
                }
            }

            // wxColour fgColour = wxColour(255 - colour.Red(), 255 - colour.Green(), 255 - colour.Blue());
            wxColour fgColour = *wxWHITE;

            // if bg color is bright then fg must be dark
            uint8_t numBrightComponents = 0;
            uint8_t threshold = 40;
            float luma = 0.2126f * float(colour.Red()) + 0.7152f * float(colour.Green()) + 0.0722f * float(colour.Blue());

            if (luma > 100.0f) {
                fgColour = *wxBLACK;
            }

            m_memGrid[x][y]->SetForegroundColour(fgColour);
            m_memGrid[x][y]->SetOwnBackgroundColour(colour);
            m_memGrid[x][y]->SetLabelText(pm);
        }
    }
}

void MemoryGrid::ClearExecs()
{
    for (size_t i = 0; i < NUM_ROWS_IN_MEM_GRID * NUM_COLS_IN_MEM_GRID; i++) {
        // calculate coordinates in mem grid
        size_t x = i / NUM_COLS_IN_MEM_GRID;
        size_t y = i - x * NUM_COLS_IN_MEM_GRID;

        if (m_memGrid[x][y]->GetLabelText() == "X") {
            m_memGrid[x][y]->SetLabelText(" ");
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
        m_memGrid[x][y]->SetOwnBackgroundColour(m_gridElementColour);
    }

    clear_bitmap();
}
