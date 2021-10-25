#include "PropertyData.hpp"
#include <string>
#include <wx/font.h>
#include <wx/xml/xml.h>

wxString GetFamilyString(wxFontFamily family){
    switch (family) {
    case wxFONTFAMILY_DEFAULT : return "wxFONTFAMILY_DEFAULT";
    case wxFONTFAMILY_DECORATIVE : return "wxFONTFAMILY_DECORATIVE";
    case wxFONTFAMILY_MODERN : return "wxFONTFAMILY_MODERN";
    case wxFONTFAMILY_ROMAN : return "wxFONTFAMILY_ROMAN";
    case wxFONTFAMILY_SCRIPT : return "wxFONTFAMILY_SCRIPT";
    case wxFONTFAMILY_TELETYPE : return "wxFONTFAMILY_TELETYPE";
    default: return "wxFONTFAMILY_MODERN";
    }
}

// save xml data to give xml document
void PropertyData::SaveTheme(wxXmlDocument *xmldoc) const{
    wxXmlNode *root = xmldoc->GetRoot();

    // get widget name
    wxString widgetname;
    if (widgetType == WidgetType::MainWindow) widgetname = "MainWindow";
    else if(widgetType == WidgetType::BotNameDisplay) widgetname = "BotNameDisplay";
    else if(widgetType == WidgetType::RegisterDisplay) widgetname = "RegisterDisplay";
    else if(widgetType == WidgetType::InstructionDisplay) widgetname = "InstructionDisplay";
    else widgetname = "ArenaTerminal";

    wxXmlNode *widget = new wxXmlNode(wxXML_ELEMENT_NODE, widgetname);
    root->AddChild(widget);

    // add font settings
    wxXmlNode *font = new wxXmlNode(wxXML_ELEMENT_NODE, "Font");
    widget->AddChild(font);
    
    wxXmlAttribute *fontsize, *fontfamily, *fontstyle, *fontweight;
    fontweight = new wxXmlAttribute("Weight", GetFont().GetWeightString(), nullptr);
    fontstyle = new wxXmlAttribute("Style", GetFont().GetStyleString(), fontweight);
    fontfamily = new wxXmlAttribute("Family", GetFamilyString(fontFamily), fontstyle);
    fontsize = new wxXmlAttribute("Size", std::to_string(GetFont().GetPointSize()), fontfamily);
    font->AddAttribute(fontsize);

    // add color settings
    wxXmlNode *colour = new wxXmlNode(wxXML_ELEMENT_NODE, "Colour");
    widget->AddChild(colour);
    
    wxXmlAttribute *bgcolour, *fgcolour;
    fgcolour = new wxXmlAttribute("ForegroundColour", fgColour.GetAsString(), nullptr);
    bgcolour = new wxXmlAttribute("BackgroundColour", bgColour.GetAsString(), fgcolour);
    colour->AddAttribute(bgcolour);

    // size settings is only for main window
    if(widgetType == WidgetType::MainWindow){
	// add size settings
	wxXmlNode *size = new wxXmlNode(wxXML_ELEMENT_NODE, "Size");
	widget->AddChild(size);
	
	wxXmlAttribute *width, *height;
	height = new wxXmlAttribute("Height", "720", nullptr);
	width = new wxXmlAttribute("Width", "1240", height);
	size->AddAttribute(width);
    }
}

// get font family from string
wxFontFamily GetFontFamily(const wxString& famstr){
    if(famstr == "wxFONTFAMILY_DEFAULT") return wxFONTFAMILY_DEFAULT;
    else if(famstr == "wxFONTFAMILY_MODERN") return wxFONTFAMILY_MODERN;
    else if(famstr == "wxFONTFAMILY_DECORATIVE") return wxFONTFAMILY_DECORATIVE;
    else if(famstr == "wxFONTFAMILY_TELETYPE") return wxFONTFAMILY_TELETYPE;
    else if(famstr == "wxFONTFAMILY_SCRIPT") return wxFONTFAMILY_SCRIPT;
    else if(famstr == "wxFONTFAMILY_ROMAN") return wxFONTFAMILY_ROMAN;
    else if(famstr == "wxFONTFAMILY_SWISS") return wxFONTFAMILY_SWISS;
    return wxFONTFAMILY_MODERN;
}

// get font style from string
wxFontStyle GetFontStyle(const wxString &stylstr) {
    if(stylstr == "wxFONTSTYLE_NORMAL") return wxFONTSTYLE_NORMAL;
    else if(stylstr == "wxFONTSTYLE_ITALIC") return wxFONTSTYLE_ITALIC;
    else if(stylstr == "wxFONTSTYLE_SLANT") return wxFONTSTYLE_SLANT;
    return wxFONTSTYLE_NORMAL;
}

// get font weight from string
wxFontWeight GetFontWeight(const wxString &wtstr) {
    if(wtstr == "wxFONTWEIGHT_NORMAL") return wxFONTWEIGHT_NORMAL;
    else if(wtstr == "wxFONTWEIGHT_LIGHT") return wxFONTWEIGHT_LIGHT;
    else if(wtstr == "wxFONTWEIGHT_BOLD") return wxFONTWEIGHT_BOLD;
    return wxFONTWEIGHT_NORMAL;
}

// load theme from xml file
void PropertyData::LoadTheme(wxXmlDocument *xmldoc){
    wxXmlNode *mw = xmldoc->GetRoot()->GetChildren(); // main window
    wxXmlNode *bnd = mw->GetNext(); // bot name display
    wxXmlNode *rd = bnd->GetNext(); // register display
    wxXmlNode *id = rd->GetNext(); // instruction display
    wxXmlNode *at = id->GetNext(); // arena terminal
    
    if(widgetType == WidgetType::MainWindow){
        wxXmlNode* font = mw->GetChildren();
        wxXmlNode* colour = font->GetNext();
        wxXmlNode* sz = colour->GetNext();
        
        fontSize = std::stoul(font->GetAttribute("Size").GetData().AsChar());
        fontFamily = GetFontFamily(font->GetAttribute("Family"));
        fontStyle = GetFontStyle(font->GetAttribute("Style"));
        fontWeight = GetFontWeight(font->GetAttribute("Weight"));
        
        bgColour = wxColour(colour->GetAttribute("BackgroundColour"));
        fgColour = wxColour(colour->GetAttribute("ForegroundColour"));
        
        size = wxSize(std::stoul(sz->GetAttribute("Width").GetData().AsChar()),
                      std::stoul(sz->GetAttribute("Height").GetData().AsChar()));
    }else if(widgetType == WidgetType::BotNameDisplay){
        wxXmlNode* font = bnd->GetChildren();
        wxXmlNode* colour = font->GetNext();

        fontSize = std::stoul(font->GetAttribute("Size").GetData().AsChar());
        fontFamily = GetFontFamily(font->GetAttribute("Family"));
        fontStyle = GetFontStyle(font->GetAttribute("Style"));
        fontWeight = GetFontWeight(font->GetAttribute("Weight"));
        
        bgColour = wxColour(colour->GetAttribute("BackgroundColour"));
        fgColour = wxColour(colour->GetAttribute("ForegroundColour"));
    }else if(widgetType == WidgetType::RegisterDisplay){
        wxXmlNode* font = rd->GetChildren();
        wxXmlNode* colour = font->GetNext();
        
        fontSize = std::stoul(font->GetAttribute("Size").GetData().AsChar());
        fontFamily = GetFontFamily(font->GetAttribute("Family"));
        fontStyle = GetFontStyle(font->GetAttribute("Style"));
        fontWeight = GetFontWeight(font->GetAttribute("Weight"));
        
        bgColour = wxColour(colour->GetAttribute("BackgroundColour"));
        fgColour = wxColour(colour->GetAttribute("ForegroundColour"));
    }else if(widgetType == WidgetType::InstructionDisplay){
        wxXmlNode* font = id->GetChildren();
        wxXmlNode* colour = font->GetNext();
        
        fontSize = std::stoul(font->GetAttribute("Size").GetData().AsChar());
        fontFamily = GetFontFamily(font->GetAttribute("Family"));
        fontStyle = GetFontStyle(font->GetAttribute("Style"));
        fontWeight = GetFontWeight(font->GetAttribute("Weight"));
        
        bgColour = wxColour(colour->GetAttribute("BackgroundColour"));
        fgColour = wxColour(colour->GetAttribute("ForegroundColour"));
    }else{
        wxXmlNode* font = at->GetChildren();
        wxXmlNode* colour = font->GetNext();
        
        fontSize = std::stoul(font->GetAttribute("Size").GetData().AsChar());
        fontFamily = GetFontFamily(font->GetAttribute("Family"));
        fontStyle = GetFontStyle(font->GetAttribute("Style"));
        fontWeight = GetFontWeight(font->GetAttribute("Weight"));
        
        bgColour = wxColour(colour->GetAttribute("BackgroundColour"));
        fgColour = wxColour(colour->GetAttribute("ForegroundColour"));
    }
}

