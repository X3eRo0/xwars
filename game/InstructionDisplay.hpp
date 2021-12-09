/**
 * @file InstructionDisplay.hpp
 * @author Siddharth Mishra
 * @brief This will show current instruction being executed for given bot
 * @version 0.1
 * @date 2021-10-09
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef XVM_ARENA_INSTRUCTION_DISPLAY_HPP
#define XVM_ARENA_INSTRUCTION_DISPLAY_HPP

#include "Common.hpp"
#include "PropertyData.hpp"
#include <ostream>
#include <streambuf>
#include <wx/font.h>
#include <wx/gdicmn.h>
#include <wx/listctrl.h>
#include <wx/stream.h>
#include <wx/stringimpl.h>

class InstructionDisplay : public wxPanel{
public:
    InstructionDisplay(wxWindow *parent);

    template<typename fmtype = wxString, typename... argstype>
    void Print(fmtype str, argstype... args){
        wxString writestr;
        writestr.Printf(str, args...);
        m_displayTextCtrl->WriteText(writestr);

        // WARNING : ----------------------------------------
        // this is a hack to give the main thread some time :
        // to write things onto the display area            :
        // --------------------------------------------------
        // wxTheApp->SafeYield(GetMainWindow(), false);
        // wxTheApp->Yield();
    }

    // properties
    PropertyData properties = PropertyData{
        .widgetType = WidgetType::InstructionDisplay,
        .fontSize = 8,
        .fontFamily = wxFONTFAMILY_MODERN,
        .fontStyle = wxFONTSTYLE_NORMAL,
        .fontWeight = wxFONTWEIGHT_NORMAL,
        .bgColour = *wxBLACK,
        .fgColour = *wxGREEN
    };

    // update theme after changing properties to take effect
    void UpdateSelf();

    // clear the instruction display text ctrl
    void ClearDisplay(){
        if(m_displayTextCtrl) m_displayTextCtrl->Clear();
    }
private:
    wxColour m_bgColor = wxColour(32, 16, 32);
    // main sizer
    wxSizer *m_mainSizer;
    // this box will contain all our objects
    wxStaticBox *m_parentBox;
    // parent box colour
    wxColour m_parentBoxFGColour = *wxCYAN;
    // sizer for sizing objects in parent box
    wxBoxSizer *m_parentBoxSizer;
    // this is where our instructions will be displayed
    wxTextCtrl *m_displayTextCtrl;
    // display area bg color
    wxColour m_displayBGColour = *wxBLACK, m_displayFGColour = *wxGREEN;
    // instruction display font
    wxFont m_displayFont = wxFont(9, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_MEDIUM);
};

#endif//XVM_ARENA_INSTRUCTION_DISPLAY_HPP
