/**
   @date 12/10/2021
   @file SettingsDialog.hpp
   @author Siddharth Mishra
   @brief This is the settings dialog
*/

#ifndef XVM_ARENA_SETTINGS_DIALOG_HPP
#define XVM_ARENA_SETTINGS_DIALOG_HPP

#include "Common.hpp"
#include <wx/event.h>
#include <wx/sizer.h>
#include <wx/types.h>
#include "PropertyDisplay.hpp"

class SettingsDialog : public wxDialog{
public:
    SettingsDialog(wxWindow *parent = nullptr, wxWindowID id= wxID_ANY,
		   const wxString& name = "Settings - XVM - XWars",
		   const wxPoint& pos = wxDefaultPosition,
		   const wxSize& size = wxSize(600, 500));
    
    DECLARE_EVENT_TABLE();
private:
    void UpdateDataFromDisplay();
    
    // event handlers
    void OnImportBtnClicked(wxCommandEvent& e);
    void OnExportBtnClicked(wxCommandEvent& e);
    void OnOkBtnClicked(wxCommandEvent& e);
    void OnApplyBtnClicked(wxCommandEvent& e);
    void OnCancelBtnClicked(wxCommandEvent& e);
    void OnWidgetTypeChanged(wxCommandEvent& e);
    
    wxBoxSizer *m_mainSizer;
    wxComboBox *m_widgetTypeSelector;
    PropertiesDisplay *m_propertiesDisplay;
    PropertyData m_mainWindowData, m_botNameDisplayData,
	m_registerDisplayData, m_instructionDisplayData, m_arenaTerminalData;
    wxPanel *m_bottomPanel;
    wxBoxSizer *m_bottomPanelSizer;
    wxButton *m_exportBtn, *m_importBtn, *m_okBtn, *m_applyBtn, *m_cancelBtn;
    wxColour m_btnBGColor = wxColour(16, 16, 16);
};


#endif//XVM_ARENA_SETTINGS_DIALOG_HPP
