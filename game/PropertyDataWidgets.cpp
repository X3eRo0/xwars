#include "PropertyDataWidgets.hpp"
#include <string>
#include <wx/font.h>

    // u32 GetFontSize();
    // wxFontFamily GetFontFamily();
    // wxFontStyle GetFontStyle();
    // wxFontWeight GetFontWeight();
    // wxColour GetBGColour();
    // wxColour GetFGColour();
    // u32 GetSize();

// get font size
u32 PropertyDataWidgets::GetFontSize(){
    return fontSize->GetValueU32();
}

// get font family
wxFontFamily PropertyDataWidgets::GetFontFamily(){
    switch (fontFamily->GetSelection()){
    case 0 : return wxFONTFAMILY_DEFAULT; 
    default: return wxFONTFAMILY_MODERN;
    };
};
