//////////////////////////////////////////////////////////////////////
// This file was auto-generated by codelite's wxCrafter Plugin
// Do not modify this file by hand!
//////////////////////////////////////////////////////////////////////

#include "editor_options_caret.h"


// Declare the bitmap loading function
extern void wxC933InitBitmapResources();

static bool bBitmapLoaded = false;


EditorSettingsCaretBase::EditorSettingsCaretBase(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style)
    : wxPanel(parent, id, pos, size, style)
{
    if ( !bBitmapLoaded ) {
        // We need to initialise the default bitmap handler
        wxXmlResource::Get()->AddHandler(new wxBitmapXmlHandler);
        wxC933InitBitmapResources();
        bBitmapLoaded = true;
    }
    
    mainSizer = new wxBoxSizer(wxVERTICAL);
    this->SetSizer(mainSizer);
    
    fgSizer1 = new wxFlexGridSizer(  0, 2, 0, 0);
    fgSizer1->SetFlexibleDirection( wxBOTH );
    fgSizer1->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
    fgSizer1->AddGrowableCol(1);
    
    mainSizer->Add(fgSizer1, 0, wxALL|wxEXPAND, 5);
    
    m_staticText1 = new wxStaticText(this, wxID_ANY, _("Caret blink period (milliseconds):"), wxDefaultPosition, wxSize(-1, -1), 0);
    
    fgSizer1->Add(m_staticText1, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
    
    m_spinCtrlBlinkPeriod = new wxTextCtrl(this, wxID_ANY, wxT("500"), wxDefaultPosition, wxSize(-1, -1), 0);
    m_spinCtrlBlinkPeriod->SetToolTip(_("Sets the caret blinking period in millisconds"));
    
    fgSizer1->Add(m_spinCtrlBlinkPeriod, 0, wxALL|wxEXPAND|wxALIGN_LEFT, 5);
    
    m_staticText3 = new wxStaticText(this, wxID_ANY, _("Caret width (pixels):"), wxDefaultPosition, wxSize(-1, -1), 0);
    
    fgSizer1->Add(m_staticText3, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
    
    m_spinCtrlCaretWidth = new wxTextCtrl(this, wxID_ANY, wxT("1"), wxDefaultPosition, wxSize(-1, -1), 0);
    m_spinCtrlCaretWidth->SetToolTip(_("Set the caret width in pixels"));
    
    fgSizer1->Add(m_spinCtrlCaretWidth, 0, wxALL|wxEXPAND|wxALIGN_LEFT, 5);
    
    m_checkBoxScrollBeyondLastLine = new wxCheckBox(this, wxID_ANY, _("Allow caret to scroll beyond end of file"), wxDefaultPosition, wxSize(-1, -1), 0);
    m_checkBoxScrollBeyondLastLine->SetValue(false);
    m_checkBoxScrollBeyondLastLine->SetToolTip(_("When scrolling with the mouse, the scrolling can go beyond the end of file"));
    
    fgSizer1->Add(m_checkBoxScrollBeyondLastLine, 0, wxALL, 5);
    
    m_checkBoxAdjustScrollbarSize = new wxCheckBox(this, wxID_ANY, _("Auto-adjust horizontal scrollbar width"), wxDefaultPosition, wxSize(-1, -1), 0);
    m_checkBoxAdjustScrollbarSize->SetValue(false);
    m_checkBoxAdjustScrollbarSize->SetToolTip(_("Auto adjust the borizontal toolbar to fit to the page content"));
    
    fgSizer1->Add(m_checkBoxAdjustScrollbarSize, 0, wxALL, 5);
    
    m_checkBoxCaretOnVirtualSpace = new wxCheckBox(this, wxID_ANY, _("Allow caret to be placed beyond the end of line"), wxDefaultPosition, wxSize(-1,-1), 0);
    m_checkBoxCaretOnVirtualSpace->SetValue(false);
    m_checkBoxCaretOnVirtualSpace->SetToolTip(_("Allow the user to place the caret using the mouse beyond the end of line"));
    
    fgSizer1->Add(m_checkBoxCaretOnVirtualSpace, 0, wxALL, 5);
    
    m_checkBoxCaretUseCamelCase = new wxCheckBox(this, wxID_ANY, _("Caret jumps between word segments"), wxDefaultPosition, wxSize(-1, -1), 0);
    m_checkBoxCaretUseCamelCase->SetValue(false);
    m_checkBoxCaretUseCamelCase->SetToolTip(_("Caret jumps between word segments marked by capitalisation (CamelCase) or underscores"));
    
    fgSizer1->Add(m_checkBoxCaretUseCamelCase, 0, wxALL, 5);
    
    SetSizeHints(-1,-1);
    if ( GetSizer() ) {
         GetSizer()->Fit(this);
    }
    Centre(wxBOTH);
}

EditorSettingsCaretBase::~EditorSettingsCaretBase()
{
}
