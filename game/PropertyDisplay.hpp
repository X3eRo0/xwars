/**
   @date 13/10/2021
   @file PropertiesDisplay.hpp
   @author Siddharth Mishra
   @brief Panel to display properties of a widget like BotInfo, MemoryGrid etc...
*/

#ifndef XVM_ARENA_PROPERTIES_DISPLAY_HPP
#define XVM_ARENA_PROPERTIES_DISPLAY_HPP

#include "Common.hpp"
#include "Property.hpp"
#include "PropertyData.hpp"
#include "PropertyDataWidgets.hpp"
#include <wx/font.h>

// this will show the actual properties on the screen.
class PropertiesDisplay : public wxPanel {
public:
    PropertiesDisplay(wxWindow* parent);

    // update display with given data
    void UpdateDisplay(const PropertyData& data);

    // get property data
    PropertyData GetPropertyData() const;

    // get data
    u32 GetFontSize() const;
    wxFontFamily GetFontFamily() const;
    wxFontStyle GetFontStyle() const;
    wxFontWeight GetFontWeight() const;
    wxColour GetBGColour() const;
    wxColour GetFGColour() const;
    wxSize GetSelectedSize() const;

    wxFont GetFont() const;

    // disable size option
    void EnableSizeSelector();
    void DisableSizeSelector();

private:
    PropertyDataWidgets m_widgets;
    wxBoxSizer *m_mainSizer, *m_fontBoxSizer, *m_colourBoxSizer, *m_sizeBoxSizer;
    wxStaticBox *m_fontBox, *m_colourBox, *m_sizeBox;
    wxColour m_boxBGColour = wxColour(16, 0, 16);
};

#endif // XVM_ARENA_PROPERTIES_DISPLAY_HPP
