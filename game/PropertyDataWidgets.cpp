#include "PropertyDataWidgets.hpp"
#include <string>
#include <wx/font.h>

// get font size
u32 PropertyDataWidgets::GetFontSize(){
    return fontSize->GetValueU32();
}

// get font family
wxFontFamily PropertyDataWidgets::GetFontFamily(){
    switch (fontFamily->GetSelectionIndex()){
	
    default: return wxFONTFAMILY_MODERN;
    };
};
