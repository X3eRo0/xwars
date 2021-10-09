/**
 * @file BotNameDisplay.hpp
 * @author Siddharth Mishra
 * @brief Displays bot name and some other information
 * @version 0.1
 * @date 2021-10-09
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef XVM_ARENA_BOT_NAME_DISPLAY_HPP
#define XVM_ARENA_BOT_NAME_DISPLAY_HPP

#include "Common.hpp"

class BotNameDisplay : public wxPanel{
public:
    BotNameDisplay(wxWindow* parent, const std::string& botname);
    
private:
    std::string m_botname;
    wxStaticText *m_botnameText;
};

#endif//XVM_ARENA_BOT_NAME_DISPLAY_HPP