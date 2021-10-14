/**
   @date 13/10/2021
   @author Siddharth Mishra
   @brief Contains a group of widgets that needs to be displayed in properties
   display panel. There is a property widget for each property.
*/

#ifndef XVM_ARENA_PROPERTY_DATA_WIDGETS_HPP
#define XVM_ARENA_PROPERTY_DATA_WIDGETS_HPP

#include "Common.hpp"
#include "Property.hpp"

// contains widgets for altering properties corresponding to each field
// in property data struct. This is for ease of use
struct PropertyDataWidgets{
    u32 GetFontSize();
    wxFontFamily GetFontFamily();
    wxFontStyle GetFontStyle();
    wxFontWeight GetFontWeight();
    wxColour GetBGColour();
    wxColour GetFGColour();
    u32 GetSize();
    
    TextProperty *fontSize;
    OptionProperty *fontFamily;
    OptionProperty *fontStyle;
    OptionProperty *fontWeight;
    ColourProperty *bgColour;
    ColourProperty *fgColour;
    OptionProperty *size;
};

#endif//XVM_ARENA_PROPERTY_DATA_WIDGETS_HPP
