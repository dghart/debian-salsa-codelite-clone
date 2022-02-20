//////////////////////////////////////////////////////////////////////
// This file was auto-generated by codelite's wxCrafter Plugin
// wxCrafter project file: UI.wxcp
// Do not modify this file by hand!
//////////////////////////////////////////////////////////////////////

#include "UI.h"

// Declare the bitmap loading function
extern void wxCrafterCbL3wsInitBitmapResources();

static bool bBitmapLoaded = false;

LanguageServerSettingsDlgBase::LanguageServerSettingsDlgBase(wxWindow* parent, wxWindowID id, const wxString& title,
                                                             const wxPoint& pos, const wxSize& size, long style)
    : wxDialog(parent, id, title, pos, size, style)
{
    if(!bBitmapLoaded) {
        // We need to initialise the default bitmap handler
        wxXmlResource::Get()->AddHandler(new wxBitmapXmlHandler);
        wxCrafterCbL3wsInitBitmapResources();
        bBitmapLoaded = true;
    }

    wxBoxSizer* boxSizer2 = new wxBoxSizer(wxVERTICAL);
    this->SetSizer(boxSizer2);

    wxBoxSizer* boxSizer22 = new wxBoxSizer(wxHORIZONTAL);

    boxSizer2->Add(boxSizer22, 0, wxALL | wxEXPAND, WXC_FROM_DIP(5));

    m_checkBoxEnable = new wxCheckBox(this, wxID_ANY, _("Enable Language Server Completion"), wxDefaultPosition,
                                      wxDLG_UNIT(this, wxSize(-1, -1)), 0);
    m_checkBoxEnable->SetValue(false);

    boxSizer22->Add(m_checkBoxEnable, 0, wxALL | wxALIGN_CENTER_VERTICAL, WXC_FROM_DIP(5));

    boxSizer22->Add(0, 0, 1, wxALL, WXC_FROM_DIP(5));

    m_staticLine102 =
        new wxStaticLine(this, wxID_ANY, wxDefaultPosition, wxDLG_UNIT(this, wxSize(-1, -1)), wxLI_HORIZONTAL);

    boxSizer2->Add(m_staticLine102, 0, wxALL | wxEXPAND, WXC_FROM_DIP(5));

    m_staticText105 = new wxStaticText(this, wxID_ANY, _("Available Language Servers"), wxDefaultPosition,
                                       wxDLG_UNIT(this, wxSize(-1, -1)), 0);

    boxSizer2->Add(m_staticText105, 0, wxALL, WXC_FROM_DIP(5));

    wxBoxSizer* boxSizer106 = new wxBoxSizer(wxHORIZONTAL);

    boxSizer2->Add(boxSizer106, 1, wxEXPAND, WXC_FROM_DIP(5));

    m_notebook = new wxNotebook(this, wxID_ANY, wxDefaultPosition, wxDLG_UNIT(this, wxSize(-1, -1)), wxBK_DEFAULT);
    m_notebook->SetName(wxT("m_notebook"));

    boxSizer106->Add(m_notebook, 1, wxALL | wxEXPAND, WXC_FROM_DIP(5));

    wxBoxSizer* boxSizer108 = new wxBoxSizer(wxVERTICAL);

    boxSizer106->Add(boxSizer108, 0, wxEXPAND, WXC_FROM_DIP(5));

    m_buttonScan = new wxButton(this, wxID_FIND, _("Scan..."), wxDefaultPosition, wxDLG_UNIT(this, wxSize(-1, -1)), 0);
    m_buttonScan->SetToolTip(_("Scan for installed Language Servers insalled"));

    boxSizer108->Add(m_buttonScan, 0, wxALL, WXC_FROM_DIP(5));

    m_buttonNew = new wxButton(this, wxID_NEW, _("Add..."), wxDefaultPosition, wxDLG_UNIT(this, wxSize(-1, -1)), 0);
    m_buttonNew->SetToolTip(_("Add new Language Server"));

    boxSizer108->Add(m_buttonNew, 0, wxALL | wxEXPAND, WXC_FROM_DIP(5));

    m_buttonDelete =
        new wxButton(this, wxID_DELETE, _("Delete"), wxDefaultPosition, wxDLG_UNIT(this, wxSize(-1, -1)), 0);

    boxSizer108->Add(m_buttonDelete, 0, wxALL | wxEXPAND, WXC_FROM_DIP(5));

    m_stdBtnSizer4 = new wxStdDialogButtonSizer();

    boxSizer2->Add(m_stdBtnSizer4, 0, wxALL | wxALIGN_CENTER_HORIZONTAL, WXC_FROM_DIP(10));

    m_button6 = new wxButton(this, wxID_OK, wxT(""), wxDefaultPosition, wxDLG_UNIT(this, wxSize(-1, -1)), 0);
    m_button6->SetDefault();
    m_stdBtnSizer4->AddButton(m_button6);

    m_button8 = new wxButton(this, wxID_CANCEL, wxT(""), wxDefaultPosition, wxDLG_UNIT(this, wxSize(-1, -1)), 0);
    m_stdBtnSizer4->AddButton(m_button8);
    m_stdBtnSizer4->Realize();

    SetName(wxT("LanguageServerSettingsDlgBase"));
    SetSize(wxDLG_UNIT(this, wxSize(-1, -1)));
    if(GetSizer()) { GetSizer()->Fit(this); }
    if(GetParent()) {
        CentreOnParent(wxBOTH);
    } else {
        CentreOnScreen(wxBOTH);
    }
    // Connect events
    m_buttonScan->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(LanguageServerSettingsDlgBase::OnScan),
                          NULL, this);
    m_buttonNew->Connect(wxEVT_COMMAND_BUTTON_CLICKED,
                         wxCommandEventHandler(LanguageServerSettingsDlgBase::OnAddServer), NULL, this);
    m_buttonDelete->Connect(wxEVT_COMMAND_BUTTON_CLICKED,
                            wxCommandEventHandler(LanguageServerSettingsDlgBase::OnDeleteLSP), NULL, this);
    m_buttonDelete->Connect(wxEVT_UPDATE_UI, wxUpdateUIEventHandler(LanguageServerSettingsDlgBase::OnDeleteLSPUI), NULL,
                            this);
    m_button6->Connect(wxEVT_UPDATE_UI, wxUpdateUIEventHandler(LanguageServerSettingsDlgBase::OnOKUI), NULL, this);
}

LanguageServerSettingsDlgBase::~LanguageServerSettingsDlgBase()
{
    m_buttonScan->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(LanguageServerSettingsDlgBase::OnScan),
                             NULL, this);
    m_buttonNew->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED,
                            wxCommandEventHandler(LanguageServerSettingsDlgBase::OnAddServer), NULL, this);
    m_buttonDelete->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED,
                               wxCommandEventHandler(LanguageServerSettingsDlgBase::OnDeleteLSP), NULL, this);
    m_buttonDelete->Disconnect(wxEVT_UPDATE_UI, wxUpdateUIEventHandler(LanguageServerSettingsDlgBase::OnDeleteLSPUI),
                               NULL, this);
    m_button6->Disconnect(wxEVT_UPDATE_UI, wxUpdateUIEventHandler(LanguageServerSettingsDlgBase::OnOKUI), NULL, this);
}

LanguageServerPageBase::LanguageServerPageBase(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size,
                                               long style)
    : wxPanel(parent, id, pos, size, style)
{
    if(!bBitmapLoaded) {
        // We need to initialise the default bitmap handler
        wxXmlResource::Get()->AddHandler(new wxBitmapXmlHandler);
        wxCrafterCbL3wsInitBitmapResources();
        bBitmapLoaded = true;
    }

    wxBoxSizer* boxSizer31 = new wxBoxSizer(wxVERTICAL);
    this->SetSizer(boxSizer31);

    wxFlexGridSizer* flexGridSizer432 = new wxFlexGridSizer(0, 2, 0, 0);
    flexGridSizer432->SetFlexibleDirection(wxBOTH);
    flexGridSizer432->SetNonFlexibleGrowMode(wxFLEX_GROWMODE_SPECIFIED);
    flexGridSizer432->AddGrowableCol(1);
    flexGridSizer432->AddGrowableRow(2);

    boxSizer31->Add(flexGridSizer432, 1, wxALL | wxEXPAND, WXC_FROM_DIP(5));

    flexGridSizer432->Add(0, 0, 1, wxALL, WXC_FROM_DIP(5));

    m_checkBoxEnabled =
        new wxCheckBox(this, wxID_ANY, _("Enabled"), wxDefaultPosition, wxDLG_UNIT(this, wxSize(-1, -1)), 0);
    m_checkBoxEnabled->SetValue(true);

    flexGridSizer432->Add(m_checkBoxEnabled, 0, wxALL, WXC_FROM_DIP(5));

    m_staticText453 =
        new wxStaticText(this, wxID_ANY, _("Name"), wxDefaultPosition, wxDLG_UNIT(this, wxSize(-1, -1)), 0);
    m_staticText453->SetToolTip(_("Give this language server a unique name"));

    flexGridSizer432->Add(m_staticText453, 0, wxALL | wxALIGN_RIGHT | wxALIGN_CENTER_VERTICAL, WXC_FROM_DIP(5));

    m_textCtrlName = new wxTextCtrl(this, wxID_ANY, wxT(""), wxDefaultPosition, wxDLG_UNIT(this, wxSize(300, -1)), 0);
    m_textCtrlName->SetFocus();
#if wxVERSION_NUMBER >= 3000
    m_textCtrlName->SetHint(wxT(""));
#endif

    flexGridSizer432->Add(m_textCtrlName, 0, wxALL | wxEXPAND | wxALIGN_CENTER_VERTICAL, WXC_FROM_DIP(5));

    m_staticText495 =
        new wxStaticText(this, wxID_ANY, _("Command:"), wxDefaultPosition, wxDLG_UNIT(this, wxSize(-1, -1)), 0);
    m_staticText495->SetToolTip(_("The language server executable"));

    flexGridSizer432->Add(m_staticText495, 0, wxALL | wxALIGN_RIGHT | wxALIGN_TOP, WXC_FROM_DIP(5));

    m_stcCommand = new wxStyledTextCtrl(this, wxID_ANY, wxDefaultPosition, wxDLG_UNIT(this, wxSize(-1, 40)), 0);
    // Configure the fold margin
    m_stcCommand->SetMarginType(4, wxSTC_MARGIN_SYMBOL);
    m_stcCommand->SetMarginMask(4, wxSTC_MASK_FOLDERS);
    m_stcCommand->SetMarginSensitive(4, true);
    m_stcCommand->SetMarginWidth(4, 0);

    // Configure the tracker margin
    m_stcCommand->SetMarginWidth(1, 0);

    // Configure the symbol margin
    m_stcCommand->SetMarginType(2, wxSTC_MARGIN_SYMBOL);
    m_stcCommand->SetMarginMask(2, ~(wxSTC_MASK_FOLDERS));
    m_stcCommand->SetMarginWidth(2, 0);
    m_stcCommand->SetMarginSensitive(2, true);

    // Configure the line numbers margin
    m_stcCommand->SetMarginType(0, wxSTC_MARGIN_NUMBER);
    m_stcCommand->SetMarginWidth(0, 0);

    // Configure the line symbol margin
    m_stcCommand->SetMarginType(3, wxSTC_MARGIN_FORE);
    m_stcCommand->SetMarginMask(3, 0);
    m_stcCommand->SetMarginWidth(3, 0);
    // Select the lexer
    m_stcCommand->SetLexer(wxSTC_LEX_NULL);
    // Set default font / styles
    m_stcCommand->StyleClearAll();
    m_stcCommand->SetWrapMode(2);
    m_stcCommand->SetIndentationGuides(0);
    m_stcCommand->SetKeyWords(0, wxT(""));
    m_stcCommand->SetKeyWords(1, wxT(""));
    m_stcCommand->SetKeyWords(2, wxT(""));
    m_stcCommand->SetKeyWords(3, wxT(""));
    m_stcCommand->SetKeyWords(4, wxT(""));

    flexGridSizer432->Add(m_stcCommand, 1, wxALL | wxEXPAND, WXC_FROM_DIP(5));

    m_staticText579 = new wxStaticText(this, wxID_ANY, _("Working directory:"), wxDefaultPosition,
                                       wxDLG_UNIT(this, wxSize(-1, -1)), 0);
    m_staticText579->SetToolTip(_("Set the language server working directory"));

    flexGridSizer432->Add(m_staticText579, 0, wxALL | wxALIGN_RIGHT | wxALIGN_CENTER_VERTICAL, WXC_FROM_DIP(5));

    wxBoxSizer* boxSizer1131 = new wxBoxSizer(wxHORIZONTAL);

    flexGridSizer432->Add(boxSizer1131, 1, wxALL | wxEXPAND, WXC_FROM_DIP(5));

    m_textCtrlWD = new wxTextCtrl(this, wxID_ANY, wxT(""), wxDefaultPosition, wxDLG_UNIT(this, wxSize(-1, -1)), 0);
#if wxVERSION_NUMBER >= 3000
    m_textCtrlWD->SetHint(wxT(""));
#endif

    boxSizer1131->Add(m_textCtrlWD, 1, wxALIGN_CENTER_VERTICAL, WXC_FROM_DIP(5));

    m_button1153 =
        new wxButton(this, wxID_ANY, _("..."), wxDefaultPosition, wxDLG_UNIT(this, wxSize(-1, -1)), wxBU_EXACTFIT);
    m_button1153->SetToolTip(_("Browse..."));

    boxSizer1131->Add(m_button1153, 0, wxLEFT | wxALIGN_CENTER_VERTICAL, WXC_FROM_DIP(5));

    m_staticText6311 =
        new wxStaticText(this, wxID_ANY, _("Languages:"), wxDefaultPosition, wxDLG_UNIT(this, wxSize(-1, -1)), 0);
    m_staticText6311->SetToolTip(_("List of supported languages by this Language Server"));

    flexGridSizer432->Add(m_staticText6311, 0, wxALL | wxALIGN_RIGHT | wxALIGN_CENTER_VERTICAL, WXC_FROM_DIP(10));

    wxBoxSizer* boxSizer113 = new wxBoxSizer(wxHORIZONTAL);

    flexGridSizer432->Add(boxSizer113, 1, wxALL | wxEXPAND, WXC_FROM_DIP(5));

    m_textCtrlLanguages =
        new wxTextCtrl(this, wxID_ANY, wxT(""), wxDefaultPosition, wxDLG_UNIT(this, wxSize(-1, -1)), 0);
#if wxVERSION_NUMBER >= 3000
    m_textCtrlLanguages->SetHint(wxT(""));
#endif

    boxSizer113->Add(m_textCtrlLanguages, 1, wxALIGN_CENTER_VERTICAL, WXC_FROM_DIP(5));

    m_button115 =
        new wxButton(this, wxID_ANY, _("..."), wxDefaultPosition, wxDLG_UNIT(this, wxSize(-1, -1)), wxBU_EXACTFIT);
    m_button115->SetToolTip(_("Show List of Languages"));

    boxSizer113->Add(m_button115, 0, wxLEFT | wxALIGN_CENTER_VERTICAL, WXC_FROM_DIP(5));

    m_staticText117 = new wxStaticText(this, wxID_ANY, _("Connection string:"), wxDefaultPosition,
                                       wxDLG_UNIT(this, wxSize(-1, -1)), 0);
    m_staticText117->SetToolTip(_("Set the connection string here.\nIf the server connects using 'stdio', choose the "
                                  "'stdio' entry\nOtherwise, set a connection in the form of:\ntcp://127.0.0.1:12345"));

    flexGridSizer432->Add(m_staticText117, 0, wxALL | wxALIGN_RIGHT | wxALIGN_CENTER_VERTICAL, WXC_FROM_DIP(5));

    wxArrayString m_comboBoxConnectionArr;
    m_comboBoxConnectionArr.Add(wxT("stdio"));
    m_comboBoxConnection = new wxComboBox(this, wxID_ANY, wxT(""), wxDefaultPosition, wxDLG_UNIT(this, wxSize(-1, -1)),
                                          m_comboBoxConnectionArr, 0);
    m_comboBoxConnection->SetToolTip(
        _("If the language server is using TCP\nType the connection string in the format of:\n\ntcp://host:port"));
#if wxVERSION_NUMBER >= 3000
    m_comboBoxConnection->SetHint(wxT(""));
#endif
    m_comboBoxConnection->SetSelection(0);

    flexGridSizer432->Add(m_comboBoxConnection, 0, wxALL | wxEXPAND, WXC_FROM_DIP(5));

    m_staticText125 =
        new wxStaticText(this, wxID_ANY, _("Priority:"), wxDefaultPosition, wxDLG_UNIT(this, wxSize(-1, -1)), 0);
    m_staticText125->SetToolTip(
        _("Multiple Plugins / Servers can compete for providing code completion\nfor a given language. Set here the "
          "server priority.\nThe server with the highest priority will be triggered first\n\nNote that the builtin "
          "plugins are using priority in the range of 10 - 75\nIf you want that the LSP will be the first in the "
          "chain, set its priority to a value that is higher than 75"));

    flexGridSizer432->Add(m_staticText125, 0, wxALL | wxALIGN_RIGHT | wxALIGN_CENTER_VERTICAL, WXC_FROM_DIP(5));

    m_sliderPriority =
        new wxSlider(this, wxID_ANY, 50, 0, 200, wxDefaultPosition, wxDLG_UNIT(this, wxSize(-1, -1)), wxSL_LABELS);

    flexGridSizer432->Add(m_sliderPriority, 0, wxALL | wxEXPAND, WXC_FROM_DIP(5));

    flexGridSizer432->Add(0, 0, 1, wxALL, WXC_FROM_DIP(5));

    m_checkBoxDiagnostics = new wxCheckBox(this, wxID_ANY, _("Display diagnostics"), wxDefaultPosition,
                                           wxDLG_UNIT(this, wxSize(-1, -1)), 0);
    m_checkBoxDiagnostics->SetValue(true);

    flexGridSizer432->Add(m_checkBoxDiagnostics, 0, wxALL, WXC_FROM_DIP(5));

    SetName(wxT("LanguageServerPageBase"));
    SetSize(wxDLG_UNIT(this, wxSize(-1, -1)));
    if(GetSizer()) { GetSizer()->Fit(this); }
    // Connect events
    m_stcCommand->Connect(wxEVT_UPDATE_UI, wxUpdateUIEventHandler(LanguageServerPageBase::OnCommandUI), NULL, this);
    m_button1153->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(LanguageServerPageBase::OnBrowseWD), NULL,
                          this);
    m_button115->Connect(wxEVT_COMMAND_BUTTON_CLICKED,
                         wxCommandEventHandler(LanguageServerPageBase::OnSuggestLanguages), NULL, this);
}

LanguageServerPageBase::~LanguageServerPageBase()
{
    m_stcCommand->Disconnect(wxEVT_UPDATE_UI, wxUpdateUIEventHandler(LanguageServerPageBase::OnCommandUI), NULL, this);
    m_button1153->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(LanguageServerPageBase::OnBrowseWD),
                             NULL, this);
    m_button115->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED,
                            wxCommandEventHandler(LanguageServerPageBase::OnSuggestLanguages), NULL, this);
}

NewLanguageServerDlgBase::NewLanguageServerDlgBase(wxWindow* parent, wxWindowID id, const wxString& title,
                                                   const wxPoint& pos, const wxSize& size, long style)
    : wxDialog(parent, id, title, pos, size, style)
{
    if(!bBitmapLoaded) {
        // We need to initialise the default bitmap handler
        wxXmlResource::Get()->AddHandler(new wxBitmapXmlHandler);
        wxCrafterCbL3wsInitBitmapResources();
        bBitmapLoaded = true;
    }

    wxBoxSizer* boxSizer35 = new wxBoxSizer(wxVERTICAL);
    this->SetSizer(boxSizer35);

    m_stdBtnSizer37 = new wxStdDialogButtonSizer();

    boxSizer35->Add(m_stdBtnSizer37, 0, wxALL | wxALIGN_CENTER_HORIZONTAL, WXC_FROM_DIP(10));

    m_buttonOK = new wxButton(this, wxID_OK, wxT(""), wxDefaultPosition, wxDLG_UNIT(this, wxSize(-1, -1)), 0);
    m_buttonOK->SetDefault();
    m_stdBtnSizer37->AddButton(m_buttonOK);

    m_button41 = new wxButton(this, wxID_CANCEL, wxT(""), wxDefaultPosition, wxDLG_UNIT(this, wxSize(-1, -1)), 0);
    m_stdBtnSizer37->AddButton(m_button41);
    m_stdBtnSizer37->Realize();

    SetName(wxT("NewLanguageServerDlgBase"));
    SetSize(wxDLG_UNIT(this, wxSize(-1, -1)));
    if(GetSizer()) { GetSizer()->Fit(this); }
    if(GetParent()) {
        CentreOnParent(wxBOTH);
    } else {
        CentreOnScreen(wxBOTH);
    }
    // Connect events
    m_buttonOK->Connect(wxEVT_UPDATE_UI, wxUpdateUIEventHandler(NewLanguageServerDlgBase::OnOKUI), NULL, this);
}

NewLanguageServerDlgBase::~NewLanguageServerDlgBase()
{
    m_buttonOK->Disconnect(wxEVT_UPDATE_UI, wxUpdateUIEventHandler(NewLanguageServerDlgBase::OnOKUI), NULL, this);
}