/**
   @date 12/10/2021
   @file SettingsDialog.cpp
   @author Siddharth Mishra
   @brief This is the settings dialog
*/

#include "SettingsDialog.hpp"
#include "Arena.hpp"
#include "BotNameDisplay.hpp"
#include "Factory.hpp"
#include "InstructionDisplay.hpp"
#include "MainWindow.hpp"
#include "RegisterDisplay.hpp"
#include <wx/event.h>
#include <wx/filedlg.h>
#include <wx/gdicmn.h>
#include <wx/generic/panelg.h>
#include <wx/log.h>
#include <wx/sizer.h>
#include <wx/stringimpl.h>
#include <wx/textctrl.h>
#include <wx/utils.h>
#include <wx/wxcrt.h>
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

SettingsDialog::SettingsDialog(wxWindow* parent, wxWindowID id,
    const wxString& name, const wxPoint& pos,
    const wxSize& size)
    : wxDialog(parent, id, "XVM - XWars - Settings", pos, size)
{
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
    m_mainSizer->Add(m_bottomPanel, 1, wxEXPAND | wxALL);

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

    // store default properties
    m_mainWindowData = FactoryGetMainWindow()->properties;
    m_botNameDisplayData = FactoryGetLeftBotInfo()->GetBotNameDisplay()->properties;
    m_registerDisplayData = FactoryGetLeftRegisterDisplay()->properties;
    m_instructionDisplayData = FactoryGetLeftInstructionDisplay()->properties;
    m_arenaTerminalData = FactoryGetMiddlePanel()->GetArena()->properties;

    // update display
    m_propertiesDisplay->UpdateDisplay(m_mainWindowData);
}

void SettingsDialog::OnImportBtnClicked(wxCommandEvent& e)
{
    wxFileDialog* fd = new wxFileDialog(this, "Import Theme",
        wxEmptyString, wxEmptyString,
        "XML Files (*.xml)|*.xml",
        wxFD_OPEN | wxFD_CHANGE_DIR);

    if (fd->ShowModal() != wxID_CANCEL) {
        wxString filename = fd->GetPath();
        wxPuts("importing theme\"" + filename + "\"");

        wxXmlDocument* xmldoc = new wxXmlDocument;
        xmldoc->Load(filename);

        m_mainWindowData.LoadTheme(xmldoc);
        m_botNameDisplayData.LoadTheme(xmldoc);
        m_registerDisplayData.LoadTheme(xmldoc);
        m_instructionDisplayData.LoadTheme(xmldoc);
        m_arenaTerminalData.LoadTheme(xmldoc);

        if (m_widgetTypeSelector->GetSelection() == 0) {
            m_propertiesDisplay->UpdateDisplay(m_mainWindowData);
        } else if (m_widgetTypeSelector->GetSelection() == 1) {
            m_propertiesDisplay->UpdateDisplay(m_botNameDisplayData);
        } else if (m_widgetTypeSelector->GetSelection() == 2) {
            m_propertiesDisplay->UpdateDisplay(m_registerDisplayData);
        } else if (m_widgetTypeSelector->GetSelection() == 3) {
            m_propertiesDisplay->UpdateDisplay(m_instructionDisplayData);
        } else {
            m_propertiesDisplay->UpdateDisplay(m_arenaTerminalData);
        }

        delete xmldoc;
    }
}

void SettingsDialog::OnExportBtnClicked(wxCommandEvent& WXUNUSED(e))
{
    wxFileDialog* fd = new wxFileDialog(this, "Export Theme",
        wxEmptyString, wxEmptyString,
        "XML Files (*.xml)|*.xml",
        wxFD_SAVE | wxFD_CHANGE_DIR | wxFD_OVERWRITE_PROMPT);
    if (fd->ShowModal() != wxCANCEL) {
        wxString filename = fd->GetPath();
        wxPuts("exporting theme \"" + filename + "\"");

        wxXmlDocument* xmldoc = new wxXmlDocument;
        wxXmlNode* root = new wxXmlNode(wxXML_ELEMENT_NODE, "ThemeRoot");
        xmldoc->SetRoot(root);

        m_mainWindowData.SaveTheme(xmldoc);
        m_botNameDisplayData.SaveTheme(xmldoc);
        m_registerDisplayData.SaveTheme(xmldoc);
        m_instructionDisplayData.SaveTheme(xmldoc);
        m_arenaTerminalData.SaveTheme(xmldoc);

        xmldoc->Save(filename);
    }

    fd->Destroy();
}

// apply button will both save the settings to local buffers
// and apply this changes
void SettingsDialog::OnApplyBtnClicked(wxCommandEvent& e)
{
    UpdateDataFromDisplay();

    // update main window
    MainWindow* mw = FactoryGetMainWindow();
    mw->properties = m_mainWindowData;
    mw->UpdateSelf();

    // update bot name displays
    BotNameDisplay* bnd = FactoryGetLeftBotInfo()->GetBotNameDisplay();
    bnd->properties = m_botNameDisplayData;
    bnd->UpdateSelf();
    bnd = FactoryGetRightBotInfo()->GetBotNameDisplay();
    bnd->properties = m_botNameDisplayData;
    bnd->UpdateSelf();

    // update register display
    RegisterDisplay* rd = FactoryGetLeftRegisterDisplay();
    rd->properties = m_registerDisplayData;
    rd->UpdateSelf();
    rd = FactoryGetRightRegisterDisplay();
    rd->properties = m_registerDisplayData;
    rd->UpdateSelf();

    // update instructiondisplay
    InstructionDisplay* id = FactoryGetLeftInstructionDisplay();
    id->properties = m_instructionDisplayData;
    id->UpdateSelf();
    id = FactoryGetRightInstructionDisplay();
    id->properties = m_instructionDisplayData;
    id->UpdateSelf();

    // update arena terminal
    Arena* a = FactoryGetMiddlePanel()->GetArena();
    a->properties = m_arenaTerminalData;
    a->UpdateSelf();
}

// when widget type changes, we need to update the display with new properties
void SettingsDialog::OnWidgetTypeChanged(wxCommandEvent& e)
{
    // get selection
    size_t selection = e.GetInt();

    // if main window is not selected then we don't want size selector
    // but if main window then size slector is necessary
    if (selection) {
        m_propertiesDisplay->DisableSizeSelector();
    } else {
        m_propertiesDisplay->EnableSizeSelector();
    }

    // settings for main window
    if (selection == 0) {
        m_propertiesDisplay->UpdateDisplay(m_mainWindowData);
    }

    // settings for bot name display
    else if (selection == 1) {
        m_propertiesDisplay->UpdateDisplay(m_botNameDisplayData);
    }

    // settings for register display
    else if (selection == 2) {
        m_propertiesDisplay->UpdateDisplay(m_registerDisplayData);
    }

    // settings for instruction display
    else if (selection == 3) {
        m_propertiesDisplay->UpdateDisplay(m_instructionDisplayData);
    }

    // settings for arena terminal
    else {
        m_propertiesDisplay->UpdateDisplay(m_arenaTerminalData);
    }
}

// cancel button won't save anything and will just close the dialog
void SettingsDialog::OnCancelBtnClicked(wxCommandEvent& e) { Close(); }

// ok btn wont apply changes, it'll just save those buffers locally
// to apply changes click apply
void SettingsDialog::OnOkBtnClicked(wxCommandEvent& e)
{
    UpdateDataFromDisplay();

    // close this
    Close();
}

void SettingsDialog::UpdateDataFromDisplay()
{
    // get selection
    size_t selection = m_widgetTypeSelector->GetSelection();

    // settings for main window
    if (selection == 0) {
        m_mainWindowData.size = m_propertiesDisplay->GetSelectedSize();
        m_mainWindowData.fontSize = m_propertiesDisplay->GetFontSize();
        m_mainWindowData.fontFamily = m_propertiesDisplay->GetFontFamily();
        m_mainWindowData.fontStyle = m_propertiesDisplay->GetFontStyle();
        m_mainWindowData.fontWeight = m_propertiesDisplay->GetFontWeight();
        m_mainWindowData.bgColour = m_propertiesDisplay->GetBGColour();
        m_mainWindowData.fgColour = m_propertiesDisplay->GetFGColour();
    }

    // settings for bot name display
    else if (selection == 1) {
        m_botNameDisplayData.size = m_propertiesDisplay->GetSelectedSize();
        m_botNameDisplayData.fontSize = m_propertiesDisplay->GetFontSize();
        m_botNameDisplayData.fontFamily = m_propertiesDisplay->GetFontFamily();
        m_botNameDisplayData.fontStyle = m_propertiesDisplay->GetFontStyle();
        m_botNameDisplayData.fontWeight = m_propertiesDisplay->GetFontWeight();
        m_botNameDisplayData.bgColour = m_propertiesDisplay->GetBGColour();
        m_botNameDisplayData.fgColour = m_propertiesDisplay->GetFGColour();
    }

    // settings for register display
    else if (selection == 2) {
        m_registerDisplayData.size = m_propertiesDisplay->GetSelectedSize();
        m_registerDisplayData.fontSize = m_propertiesDisplay->GetFontSize();
        m_registerDisplayData.fontFamily = m_propertiesDisplay->GetFontFamily();
        m_registerDisplayData.fontStyle = m_propertiesDisplay->GetFontStyle();
        m_registerDisplayData.fontWeight = m_propertiesDisplay->GetFontWeight();
        m_registerDisplayData.bgColour = m_propertiesDisplay->GetBGColour();
        m_registerDisplayData.fgColour = m_propertiesDisplay->GetFGColour();
    }

    // settings for instruction display
    else if (selection == 3) {
        m_instructionDisplayData.size = m_propertiesDisplay->GetSelectedSize();
        m_instructionDisplayData.fontSize = m_propertiesDisplay->GetFontSize();
        m_instructionDisplayData.fontFamily = m_propertiesDisplay->GetFontFamily();
        m_instructionDisplayData.fontStyle = m_propertiesDisplay->GetFontStyle();
        m_instructionDisplayData.fontWeight = m_propertiesDisplay->GetFontWeight();
        m_instructionDisplayData.bgColour = m_propertiesDisplay->GetBGColour();
        m_instructionDisplayData.fgColour = m_propertiesDisplay->GetFGColour();
    }

    // settings for arena terminal
    else {
        m_arenaTerminalData.size = m_propertiesDisplay->GetSelectedSize();
        m_arenaTerminalData.fontSize = m_propertiesDisplay->GetFontSize();
        m_arenaTerminalData.fontFamily = m_propertiesDisplay->GetFontFamily();
        m_arenaTerminalData.fontStyle = m_propertiesDisplay->GetFontStyle();
        m_arenaTerminalData.fontWeight = m_propertiesDisplay->GetFontWeight();
        m_arenaTerminalData.bgColour = m_propertiesDisplay->GetBGColour();
        m_arenaTerminalData.fgColour = m_propertiesDisplay->GetFGColour();
    }
}
