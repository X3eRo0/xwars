#include "MemoryGrid.hpp"

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

void MemoryGrid::UpdateGrid(size_t offset,  BotID bid, Permission pm){
    // calculate position in memory grid
    size_t y = offset / NUM_ROWS_IN_MEM_GRID;
    size_t x = offset - y * NUM_ROWS_IN_MEM_GRID;

    std::cout << "updating mem grid at position [" << x << " " << y << "]" << std::endl;

    wxColour highlightColour;

    // decide hightlight colour based on given data
    if(bid == BotID::Bot1){
        if(pm == Permission::Read) highlightColour = bot1ReadColour;
        else if(pm == Permission::Write) highlightColour = bot1WriteColour;
        else highlightColour = bot1ExecColour;

        // highlight
        m_memGrid[x][y]->SetForegroundColour(highlightColour);
        m_memGrid[x][y]->SetLabelText("1");
    }else{
        if(pm == Permission::Read) highlightColour = bot2ReadColour;
        else if(pm == Permission::Write) highlightColour = bot2WriteColour;
        else highlightColour = bot2ExecColour;

        // highlight
        m_memGrid[x][y]->SetForegroundColour(highlightColour);
        m_memGrid[x][y]->SetLabelText("2");
    }
}
