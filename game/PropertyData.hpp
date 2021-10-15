/**
   @date 13/10/2021
   @author Siddharth Mishra
   @brief Propertydata defines common properties required for settings for each
   widget. This class can handle conversion of property data to XML and back.
*/

#ifndef XVM_ARENA_PROPERTY_DATA_HPP
#define XVM_ARENA_PROPERTY_DATA_HPP

#include "Common.hpp"
#include <wx/font.h>
#include <wx/xml/xml.h>

// defines the type of widget
// we wan't to use the property data for
enum class WidgetType {
    // 2nd top left and right panels where register names are displayed
    RegisterDisplay,
    // black terminal like thing in the middle where output will be shown
    ArenaTerminal,
    // bottom left and right where instructions are displayed
    InstructionDisplay, 
    // the main window that contains all widgets
    MainWindow,
    // top left and right panel which displays bot name
    BotNameDisplay
};

// provides common property types/fields for each widget
// listed in widget type enum
struct PropertyData{
    // create font from explicit data
    wxFont GetFont() const{
	return wxFont(fontSize, fontFamily, fontStyle, fontWeight);
    }

    // save properties for given widget in given xmldoc
    void SaveXml(wxXmlDocument *xmldoc);

    WidgetType widgetType; // type of widget (for xml info)
    u32 fontSize; // size of font in +ve integers
    wxFontFamily fontFamily; // modern, normal etc...
    wxFontStyle fontStyle; // italic, normal etc...
    wxFontWeight fontWeight; // bold, normal, thin etc...
    wxColour bgColour; // changes background colour
    wxColour fgColour; // changes properties like text color
    wxSize size; // current size of panel/window;
};

#endif//XVM_ARENA_PROPERTY_DATA_HPP
