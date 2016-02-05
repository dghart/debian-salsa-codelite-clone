//////////////////////////////////////////////////////////////////////
// This file was auto-generated by codelite's wxCrafter Plugin
// wxCrafter project file: NewToolBase.wxcp
// Do not modify this file by hand!
//////////////////////////////////////////////////////////////////////

#include "NewToolBase.h"


// Declare the bitmap loading function
extern void wxC3E45InitBitmapResources();

static bool bBitmapLoaded = false;


NewToolBase::NewToolBase(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style)
    : wxDialog(parent, id, title, pos, size, style)
{
    if ( !bBitmapLoaded ) {
        // We need to initialise the default bitmap handler
        wxXmlResource::Get()->AddHandler(new wxBitmapXmlHandler);
        wxC3E45InitBitmapResources();
        bBitmapLoaded = true;
    }
    
    wxBoxSizer* bSizer1 = new wxBoxSizer(wxVERTICAL);
    this->SetSizer(bSizer1);
    
    wxFlexGridSizer* fgSizer1 = new wxFlexGridSizer(5, 3, 0, 0);
    fgSizer1->SetFlexibleDirection( wxBOTH );
    fgSizer1->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
    fgSizer1->AddGrowableCol(1);
    
    bSizer1->Add(fgSizer1, 0, wxALL|wxEXPAND, 5);
    
    m_staticText5 = new wxStaticText(this, wxID_ANY, _("Tool ID:"), wxDefaultPosition, wxSize(-1, -1), 0);
    
    fgSizer1->Add(m_staticText5, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
    
    wxArrayString m_choiceIdArr;
    m_choiceId = new wxChoice(this, wxID_ANY, wxDefaultPosition, wxSize(-1, -1), m_choiceIdArr, 0);
    m_choiceId->SetToolTip(_("Identify this tool with an ID from the given list"));
    
    fgSizer1->Add(m_choiceId, 0, wxALL|wxEXPAND, 5);
    
    fgSizer1->Add(0, 0, 1, wxEXPAND, 5);
    
    m_staticText6 = new wxStaticText(this, wxID_ANY, _("Name:"), wxDefaultPosition, wxSize(-1, -1), 0);
    
    fgSizer1->Add(m_staticText6, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
    
    m_textCtrlName = new wxTextCtrl(this, wxID_ANY, wxT(""), wxDefaultPosition, wxSize(-1, -1), 0);
    m_textCtrlName->SetToolTip(_("The name is used to identify this tool in the 'External Tools' toolbar"));
    #if wxVERSION_NUMBER >= 3000
    m_textCtrlName->SetHint(wxT(""));
    #endif
    
    fgSizer1->Add(m_textCtrlName, 0, wxALL|wxEXPAND, 5);
    
    fgSizer1->Add(0, 0, 1, wxEXPAND, 5);
    
    m_staticText1 = new wxStaticText(this, wxID_ANY, _("Tool path:"), wxDefaultPosition, wxSize(-1, -1), 0);
    
    fgSizer1->Add(m_staticText1, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
    
    m_textCtrlPath = new wxTextCtrl(this, wxID_ANY, wxT(""), wxDefaultPosition, wxSize(-1, -1), 0);
    m_textCtrlPath->SetToolTip(_("Path to the executable to run"));
    #if wxVERSION_NUMBER >= 3000
    m_textCtrlPath->SetHint(wxT(""));
    #endif
    m_textCtrlPath->AutoCompleteFileNames();
    
    fgSizer1->Add(m_textCtrlPath, 0, wxALL|wxEXPAND|wxALIGN_CENTER_VERTICAL, 5);
    
    m_buttonBrowsePath = new wxButton(this, wxID_ANY, _("..."), wxDefaultPosition, wxSize(-1, -1), wxBU_EXACTFIT);
    
    fgSizer1->Add(m_buttonBrowsePath, 0, wxALIGN_CENTER_VERTICAL, 5);
    
    m_staticText2 = new wxStaticText(this, wxID_ANY, _("Working directory:"), wxDefaultPosition, wxSize(-1, -1), 0);
    
    fgSizer1->Add(m_staticText2, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
    
    m_textCtrlWd = new wxTextCtrl(this, wxID_ANY, wxT(""), wxDefaultPosition, wxSize(-1, -1), 0);
    m_textCtrlWd->SetToolTip(_("Set the working directory for this tool"));
    #if wxVERSION_NUMBER >= 3000
    m_textCtrlWd->SetHint(wxT(""));
    #endif
    m_textCtrlWd->AutoCompleteDirectories();
    
    fgSizer1->Add(m_textCtrlWd, 1, wxALL|wxEXPAND|wxALIGN_CENTER_VERTICAL, 5);
    
    m_buttonBrowseWd = new wxButton(this, wxID_ANY, _("..."), wxDefaultPosition, wxSize(-1, -1), wxBU_EXACTFIT);
    
    fgSizer1->Add(m_buttonBrowseWd, 0, wxALIGN_CENTER_VERTICAL, 5);
    
    m_staticText3 = new wxStaticText(this, wxID_ANY, _("Arguments:"), wxDefaultPosition, wxSize(-1, -1), 0);
    
    fgSizer1->Add(m_staticText3, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
    
    m_textCtrlArguments = new wxTextCtrl(this, wxID_ANY, wxT(""), wxDefaultPosition, wxSize(-1, -1), 0);
    m_textCtrlArguments->SetToolTip(_("Set a list of arguments to pass to the tool"));
    #if wxVERSION_NUMBER >= 3000
    m_textCtrlArguments->SetHint(wxT(""));
    #endif
    
    fgSizer1->Add(m_textCtrlArguments, 1, wxALL|wxEXPAND|wxALIGN_CENTER_VERTICAL, 5);
    
    fgSizer1->Add(0, 0, 1, wxEXPAND, 5);
    
    wxStaticBoxSizer* sbSizer1 = new wxStaticBoxSizer( new wxStaticBox(this, wxID_ANY, _("Toolbar:")), wxVERTICAL);
    
    bSizer1->Add(sbSizer1, 0, wxALL|wxEXPAND, 5);
    
    wxFlexGridSizer* fgSizer2 = new wxFlexGridSizer(2, 3, 0, 0);
    fgSizer2->SetFlexibleDirection( wxBOTH );
    fgSizer2->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
    fgSizer2->AddGrowableCol(1);
    
    sbSizer1->Add(fgSizer2, 0, wxALL|wxEXPAND, 5);
    
    m_staticText8 = new wxStaticText(this, wxID_ANY, _("Toolbar icon (24x24):"), wxDefaultPosition, wxSize(-1, -1), 0);
    
    fgSizer2->Add(m_staticText8, 0, wxRIGHT|wxTOP|wxBOTTOM|wxALIGN_CENTER_VERTICAL, 5);
    
    m_textCtrlIcon24 = new wxTextCtrl(this, wxID_ANY, wxT(""), wxDefaultPosition, wxSize(-1, -1), 0);
    #if wxVERSION_NUMBER >= 3000
    m_textCtrlIcon24->SetHint(wxT(""));
    #endif
    
    fgSizer2->Add(m_textCtrlIcon24, 0, wxALL|wxEXPAND|wxALIGN_CENTER_VERTICAL, 5);
    
    m_buttonBrowseIcon24 = new wxButton(this, wxID_ANY, _("Browse..."), wxDefaultPosition, wxSize(-1, -1), 0);
    
    fgSizer2->Add(m_buttonBrowseIcon24, 0, wxALIGN_CENTER_VERTICAL, 5);
    
    m_staticText7 = new wxStaticText(this, wxID_ANY, _("Toolbar icon (16x16):"), wxDefaultPosition, wxSize(-1, -1), 0);
    
    fgSizer2->Add(m_staticText7, 0, wxRIGHT|wxTOP|wxBOTTOM|wxALIGN_CENTER_VERTICAL, 5);
    
    m_textCtrlIcon16 = new wxTextCtrl(this, wxID_ANY, wxT(""), wxDefaultPosition, wxSize(-1, -1), 0);
    #if wxVERSION_NUMBER >= 3000
    m_textCtrlIcon16->SetHint(wxT(""));
    #endif
    
    fgSizer2->Add(m_textCtrlIcon16, 1, wxALL|wxEXPAND|wxALIGN_CENTER_VERTICAL, 5);
    
    m_buttonBrowseIcon16 = new wxButton(this, wxID_ANY, _("Browse..."), wxDefaultPosition, wxSize(-1, -1), 0);
    
    fgSizer2->Add(m_buttonBrowseIcon16, 0, wxALIGN_CENTER_VERTICAL, 5);
    
    wxStaticBoxSizer* sbSizer2 = new wxStaticBoxSizer( new wxStaticBox(this, wxID_ANY, _("General:")), wxVERTICAL);
    
    bSizer1->Add(sbSizer2, 0, wxALL|wxEXPAND, 5);
    
    m_checkBoxSaveAllFilesBefore = new wxCheckBox(this, wxID_ANY, _("Save all files before executing this tool"), wxDefaultPosition, wxSize(-1, -1), 0);
    m_checkBoxSaveAllFilesBefore->SetValue(false);
    m_checkBoxSaveAllFilesBefore->SetToolTip(_("Before executing this tool, save all files"));
    
    sbSizer2->Add(m_checkBoxSaveAllFilesBefore, 0, wxALL, 5);
    
    m_checkBoxCaptureOutput = new wxCheckBox(this, wxID_ANY, _("Capture process output"), wxDefaultPosition, wxSize(-1,-1), 0);
    m_checkBoxCaptureOutput->SetValue(false);
    
    sbSizer2->Add(m_checkBoxCaptureOutput, 0, wxALL, 5);
    
    bSizer1->Add(0, 0, 1, wxALL, 5);
    
    m_stdBtnSizer2 = new wxStdDialogButtonSizer();
    
    bSizer1->Add(m_stdBtnSizer2, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 10);
    
    m_button4 = new wxButton(this, wxID_OK, wxT(""), wxDefaultPosition, wxSize(-1, -1), 0);
    m_button4->SetDefault();
    m_stdBtnSizer2->AddButton(m_button4);
    
    m_button6 = new wxButton(this, wxID_CANCEL, wxT(""), wxDefaultPosition, wxSize(-1, -1), 0);
    m_stdBtnSizer2->AddButton(m_button6);
    
    m_button8 = new wxButton(this, wxID_HELP, wxT(""), wxDefaultPosition, wxSize(-1, -1), 0);
    m_button8->SetToolTip(_("Show list of available macros"));
    m_button8->SetToolTip(_("Show list of available macros"));
    m_stdBtnSizer2->AddButton(m_button8);
    m_stdBtnSizer2->Realize();
    
    SetName(wxT("NewToolBase"));
    SetSize(-1,-1);
    if (GetSizer()) {
         GetSizer()->Fit(this);
    }
    if(GetParent()) {
        CentreOnParent(wxBOTH);
    } else {
        CentreOnScreen(wxBOTH);
    }
#if wxVERSION_NUMBER >= 2900
    if(!wxPersistenceManager::Get().Find(this)) {
        wxPersistenceManager::Get().RegisterAndRestore(this);
    } else {
        wxPersistenceManager::Get().Restore(this);
    }
#endif
    // Connect events
    m_choiceId->Connect(wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler(NewToolBase::OnIdSelected), NULL, this);
    m_buttonBrowsePath->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(NewToolBase::OnButtonBrowsePath), NULL, this);
    m_buttonBrowseWd->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(NewToolBase::OnButtonBrowseWD), NULL, this);
    m_buttonBrowseIcon24->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(NewToolBase::OnButtonBrowseIcon24), NULL, this);
    m_buttonBrowseIcon16->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(NewToolBase::OnButtonBrowseIcon16), NULL, this);
    m_button4->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(NewToolBase::OnButtonOk), NULL, this);
    m_button6->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(NewToolBase::OnButtonCancel), NULL, this);
    m_button8->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(NewToolBase::OnButtonHelp), NULL, this);
    
}

NewToolBase::~NewToolBase()
{
    m_choiceId->Disconnect(wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler(NewToolBase::OnIdSelected), NULL, this);
    m_buttonBrowsePath->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(NewToolBase::OnButtonBrowsePath), NULL, this);
    m_buttonBrowseWd->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(NewToolBase::OnButtonBrowseWD), NULL, this);
    m_buttonBrowseIcon24->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(NewToolBase::OnButtonBrowseIcon24), NULL, this);
    m_buttonBrowseIcon16->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(NewToolBase::OnButtonBrowseIcon16), NULL, this);
    m_button4->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(NewToolBase::OnButtonOk), NULL, this);
    m_button6->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(NewToolBase::OnButtonCancel), NULL, this);
    m_button8->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(NewToolBase::OnButtonHelp), NULL, this);
    
}
