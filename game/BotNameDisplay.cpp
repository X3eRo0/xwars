#include "BotNameDisplay.hpp"
#include "Common.hpp"
#include <wx/gdicmn.h>
#include <wx/sizer.h>

BotNameDisplay::BotNameDisplay(wxWindow* parent, const wxString& botname, bool left)
    : wxPanel(parent)
    , m_botname(botname)
{
    // change background colour
    SetBackgroundColour(properties.bgColour);

    // create main sizer for this
    m_mainSizer = new wxBoxSizer(wxHORIZONTAL);
    this->SetSizer(m_mainSizer);

    // create botname static text
    m_botnameText = new wxStaticText(this, wxID_ANY, m_botname,
        wxDefaultPosition, wxDefaultSize,
        wxALIGN_CENTRE);

    m_botnameText->SetFont(wxFont(properties.fontSize, properties.fontFamily,
        properties.fontStyle, properties.fontWeight));
    m_botnameText->SetForegroundColour(properties.fgColour);

    // create buttons
    m_rText = new wxStaticText(this, wxID_ANY, "R", wxDefaultPosition,
        wxDefaultSize, wxALIGN_CENTRE);
    // m_rText->SetBackgroundColour(m_rwxBGColour);
    if (left){
        wxColour colour = GetBot1ReadColour();

        float luma = 0.2126f * float(colour.Red()) +
            0.7152f * float(colour.Green()) +
            0.0722f * float(colour.Blue());
        if (luma > 100.0f) {
            m_rText->SetForegroundColour(*wxBLACK);
        }

        m_rText->SetBackgroundColour(GetBot1ReadColour());
    } else {
        wxColour colour = GetBot2ReadColour();

        float luma = 0.2126f * float(colour.Red()) +
            0.7152f * float(colour.Green()) +
            0.0722f * float(colour.Blue());
        if (luma > 100.0f) {
            m_rText->SetForegroundColour(*wxBLACK);
        }

        m_rText->SetBackgroundColour(GetBot2ReadColour());
    }
    m_rText->SetFont(m_rwxTextFont);

    m_wText = new wxStaticText(this, wxID_ANY, "W", wxDefaultPosition,
        wxDefaultSize, wxALIGN_CENTRE);
    if (left){
        wxColour colour = GetBot1WriteColour();

        float luma = 0.2126f * float(colour.Red()) +
            0.7152f * float(colour.Green()) +
            0.0722f * float(colour.Blue());
        if (luma > 100.0f) {
            m_wText->SetForegroundColour(*wxBLACK);
        }

        m_wText->SetBackgroundColour(GetBot1WriteColour());
    }else{
        wxColour colour = GetBot2WriteColour();

        float luma = 0.2126f * float(colour.Red()) +
            0.7152f * float(colour.Green()) +
            0.0722f * float(colour.Blue());
        if (luma > 100.0f) {
            m_wText->SetForegroundColour(*wxBLACK);
        }

        m_wText->SetBackgroundColour(GetBot2WriteColour());
    }

    m_wText->SetFont(m_rwxTextFont);

    m_xText = new wxStaticText(this, wxID_ANY, "X", wxDefaultPosition,
        wxDefaultSize, wxALIGN_CENTRE);
    // m_xText->SetForegroundColour(m_rwxBGColour);{
    if (left){
        wxColour colour = GetBot1ExecColour();

        float luma = 0.2126f * float(colour.Red()) +
            0.7152f * float(colour.Green()) +
            0.0722f * float(colour.Blue());
        if (luma > 100.0f) {
            m_xText->SetForegroundColour(*wxBLACK);
        }

        m_xText->SetBackgroundColour(GetBot1ExecColour());
    } else {
        wxColour colour = GetBot2ExecColour();

        float luma = 0.2126f * float(colour.Red()) +
            0.7152f * float(colour.Green()) +
            0.0722f * float(colour.Blue());
        if (luma > 100.0f) {
            m_xText->SetForegroundColour(*wxBLACK);
        }

        m_xText->SetBackgroundColour(GetBot2ExecColour());
    }

    m_xText->SetFont(m_rwxTextFont);

    // add items to sizer for sizing
    m_mainSizer->Add(m_botnameText, 5, wxEXPAND | wxALL, 4);
    m_mainSizer->Add(m_rText, 1, wxEXPAND | wxALL, 10);
    m_mainSizer->Add(m_wText, 1, wxEXPAND | wxALL, 10);
    m_mainSizer->Add(m_xText, 1, wxEXPAND | wxALL, 10);
}

// void BotNameDisplay::SetNameColour(const wxString &c){
//     m_botnameText->SetForegroundColour(c);
// }

void BotNameDisplay::SetReadColour(const wxColour& c)
{
    m_rColour = c;
    m_rText->SetBackgroundColour(c);
}

void BotNameDisplay::SetWriteColour(const wxColour& c)
{
    m_wColour = c;
    m_wText->SetBackgroundColour(c);
}

void BotNameDisplay::SetExecuteColour(const wxColour& c)
{
    m_xColour = c;
    m_xText->SetBackgroundColour(c);
}

const wxColour& BotNameDisplay::GetReadColour() const { return m_rColour; }

const wxColour& BotNameDisplay::GetWriteColour() const { return m_wColour; }

const wxColour& BotNameDisplay::GetExecuteColour() const { return m_xColour; }

void BotNameDisplay::SetBotName(const std::string& name)
{
    if (name.length() > 10) {
        m_botnameText->SetLabelText(name.substr(0, 10) + "...");
    } else {
        m_botnameText->SetLabelText(name);
    }
}

void BotNameDisplay::UpdateSelf()
{
    // change font
    m_botnameText->SetFont(wxFont(properties.fontSize, properties.fontFamily,
        properties.fontStyle, properties.fontWeight));

    // change colours
    SetBackgroundColour(properties.bgColour);
    m_botnameText->SetForegroundColour(properties.fgColour);
}
