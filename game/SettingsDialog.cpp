/**
   @date 12/10/2021
   @file SettingsDialog.cpp
   @author Siddharth Mishra
   @brief This is the settings dialog
*/

#include "SettingsDialog.hpp"
#include <wx/event.h>
#include <wx/filedlg.h>
#include <wx/gdicmn.h>
#include <wx/generic/panelg.h>
#include <wx/sizer.h>
#include <wx/stringimpl.h>
#include <wx/textctrl.h>
#include <wx/utils.h>
#include <wx/xml/xml.h>

enum ButtonsPanelIDs {
    WIDGET_SELECTOR_ID = 1,
    IMPORT_BUTTON_ID = 1,
    EXPORT_BUTTON_ID = 3,
    OK_BUTTON_ID = 4,
    APPLY_BUTTON_ID = 5,
    CANCEL_BUTTON_ID = 6
};

// define event table
BEGIN_EVENT_TABLE(SettingsDialog, wxDialog)
EVT_COMBOBOX(WIDGET_SELECTOR_ID, SettingsDialog::OnWidgetTypeChanged)
EVT_BUTTON(IMPORT_BUTTON_ID, SettingsDialog::OnImportBtnClicked)
EVT_BUTTON(EXPORT_BUTTON_ID, SettingsDialog::OnExportBtnClicked)
EVT_BUTTON(OK_BUTTON_ID, SettingsDialog::OnOkBtnClicked)
EVT_BUTTON(APPLY_BUTTON_ID, SettingsDialog::OnApplyBtnClicked)
EVT_BUTTON(CANCEL_BUTTON_ID, SettingsDialog::OnCancelBtnClicked)
END_EVENT_TABLE()

SettingsDialog::SettingsDialog(wxWindow *parent, wxWindowID id,
			       const wxString& name, const wxPoint& pos,
			       const wxSize& size)
    : wxDialog(parent, id, "XVM - XWars - Settings", pos, size){
    // change bg colour
    SetBackgroundColour(*wxBLACK);
    
    // create main sizer
    m_mainSizer = new wxBoxSizer(wxVERTICAL);
    this->SetSizer(m_mainSizer);
    
    // create properties displays
    m_propertiesDisplay = new PropertiesDisplay(this);
    m_mainSizer->Add(m_propertiesDisplay, 15, wxEXPAND | wxALL, 5);
    
    // create buttons panels
    m_bottomPanel = new wxPanel(this);
    m_bottomPanelSizer = new wxBoxSizer(wxHORIZONTAL);
    m_bottomPanel->SetSizer(m_bottomPanelSizer);
    m_mainSizer->Add(m_bottomPanel, 1, wxEXPAND |  wxALL);

    wxArrayString widgettypes;
    widgettypes.push_back("Main Window");
    widgettypes.push_back("Bot Name Display");
    widgettypes.push_back("Register Display");
    widgettypes.push_back("Instruction Display");
    widgettypes.push_back("Arena Terminal");
    
    // create combo box to select widget type
    m_widgetTypeSelector = new wxComboBox(m_bottomPanel, WIDGET_SELECTOR_ID,
					  widgettypes[0], wxDefaultPosition,
					  wxDefaultSize, widgettypes.size(),
					  widgettypes.begin(),
					  wxCB_DROPDOWN | wxCB_READONLY);
    m_widgetTypeSelector->SetBackgroundColour(m_btnBGColor);
    
    // create buttons
    m_importBtn = new wxButton(m_bottomPanel, IMPORT_BUTTON_ID, "Import",
			   wxDefaultPosition, wxDefaultSize, wxBORDER_NONE);
    m_exportBtn = new wxButton(m_bottomPanel, EXPORT_BUTTON_ID, "Export",
			   wxDefaultPosition, wxDefaultSize, wxBORDER_NONE);
    m_okBtn = new wxButton(m_bottomPanel, OK_BUTTON_ID, "Ok",
			   wxDefaultPosition, wxDefaultSize, wxBORDER_NONE);
    m_applyBtn = new wxButton(m_bottomPanel, APPLY_BUTTON_ID, "Apply",
			   wxDefaultPosition, wxDefaultSize, wxBORDER_NONE);
    m_cancelBtn = new wxButton(m_bottomPanel, CANCEL_BUTTON_ID, "Cancel",
			   wxDefaultPosition, wxDefaultSize, wxBORDER_NONE);

    // change bg colour
    m_okBtn->SetBackgroundColour(m_btnBGColor);
    m_applyBtn->SetBackgroundColour(m_btnBGColor);
    m_cancelBtn->SetBackgroundColour(m_btnBGColor);
    
    // add to sizer for sizing
    // m_bottomPanelSizer->AddSpacer(GetSize().GetWidth()/4);
    m_bottomPanelSizer->Add(m_widgetTypeSelector, 1, wxEXPAND | wxALL);
    m_bottomPanelSizer->Add(m_importBtn, 1, wxEXPAND | wxALL);
    m_bottomPanelSizer->Add(m_exportBtn, 1, wxEXPAND | wxALL);
    m_bottomPanelSizer->Add(m_okBtn, 1, wxEXPAND | wxALL);
    m_bottomPanelSizer->Add(m_applyBtn, 1, wxEXPAND | wxALL);
    m_bottomPanelSizer->Add(m_cancelBtn, 1, wxEXPAND | wxALL);
}

void SettingsDialog::OnImportBtnClicked(wxCommandEvent &e) {}

void SettingsDialog::OnExportBtnClicked(wxCommandEvent &WXUNUSED(e)) {
    wxFileDialog *fd = new wxFileDialog(this, "Export Theme",
					wxEmptyString, wxEmptyString,
					"XML Files (*.xml)|*.xml",
					wxFD_SAVE | wxFD_CHANGE_DIR |
					wxFD_OVERWRITE_PROMPT);
    if(fd->ShowModal() != wxCANCEL){
	wxPuts("writing...");
	wxString filename = fd->GetPath();
	wxXmlDocument *xmldoc = new wxXmlDocument;
	wxXmlNode *root = new wxXmlNode(wxXML_ELEMENT_NODE, "ThemeRoot");
	xmldoc->SetRoot(root);
	
	wxXmlNode *widget = new wxXmlNode(wxXML_ELEMENT_NODE, "MainWindow");
	root->AddChild(widget);

	// add size settings
	wxXmlNode *size = new wxXmlNode(wxXML_ELEMENT_NODE, "Size");
	widget->AddChild(size);

	wxXmlAttribute *widthattr, *heightattr;
	heightattr = new wxXmlAttribute("Height", "720", nullptr);
	widthattr = new wxXmlAttribute("Width", "1240", heightattr);
	size->AddAttribute(widthattr);
	
	xmldoc->Save(filename);

    }

    fd->Destroy();
}


void SettingsDialog::OnOkBtnClicked(wxCommandEvent &e) { Close(); }
void SettingsDialog::OnApplyBtnClicked(wxCommandEvent &e) {wxPuts("triggered");}
void SettingsDialog::OnCancelBtnClicked(wxCommandEvent &e) { Close(); }

void SettingsDialog::OnWidgetTypeChanged(wxCommandEvent& e){
    // get selection
    size_t selection = e.GetInt();
}
