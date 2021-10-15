#include "PropertyData.hpp"
#include <string>
#include <wx/xml/xml.h>

void PropertyData::SaveXml(wxXmlDocument *xmldoc){
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
    fontfamily = new wxXmlAttribute("Family", GetFont().GetFamilyString(), fontstyle);
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
