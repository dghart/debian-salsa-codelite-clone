//////////////////////////////////////////////////////////////////////
// This file was auto-generated by codelite's wxCrafter Plugin
// Do not modify this file by hand!
//////////////////////////////////////////////////////////////////////

#include "wxcrafter.h"


// Declare the bitmap loading function
extern void wxC38D8InitBitmapResources();

static bool bBitmapLoaded = false;


SvnCommitDialogBaseClass::SvnCommitDialogBaseClass(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style)
    : wxDialog(parent, id, title, pos, size, style)
{
    if ( !bBitmapLoaded ) {
        // We need to initialise the default bitmap handler
        wxXmlResource::Get()->AddHandler(new wxBitmapXmlHandler);
        wxC38D8InitBitmapResources();
        bBitmapLoaded = true;
    }
    
    wxBoxSizer* boxSizer1 = new wxBoxSizer(wxVERTICAL);
    this->SetSizer(boxSizer1);
    
    wxFlexGridSizer* flexGridSizer5 = new wxFlexGridSizer(  0, 2, 0, 0);
    flexGridSizer5->SetFlexibleDirection( wxBOTH );
    flexGridSizer5->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
    flexGridSizer5->AddGrowableCol(1);
    
    boxSizer1->Add(flexGridSizer5, 0, wxALL|wxEXPAND, 5);
    
    m_staticText32 = new wxStaticText(this, wxID_ANY, _("Feature Request ID:"), wxDefaultPosition, wxSize(-1,-1), 0);
    
    flexGridSizer5->Add(m_staticText32, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxALL, 5);
    
    m_textCtrlFrID = new wxTextCtrl(this, wxID_ANY, wxT(""), wxDefaultPosition, wxSize(-1,-1), 0);
    
    flexGridSizer5->Add(m_textCtrlFrID, 0, wxALL|wxEXPAND, 5);
    
    m_staticTextBugID = new wxStaticText(this, wxID_ANY, _("Bug ID:"), wxDefaultPosition, wxSize(-1,-1), 0);
    
    flexGridSizer5->Add(m_staticTextBugID, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxALL, 5);
    
    m_textCtrlBugID = new wxTextCtrl(this, wxID_ANY, wxT(""), wxDefaultPosition, wxSize(-1,-1), 0);
    
    flexGridSizer5->Add(m_textCtrlBugID, 0, wxALL|wxEXPAND, 5);
    
    m_splitterV = new wxSplitterWindow(this, wxID_ANY, wxDefaultPosition, wxSize(-1,-1), wxSP_LIVE_UPDATE);
    m_splitterV->SetSashGravity(0.5);
    m_splitterV->SetMinimumPaneSize(10);
    
    boxSizer1->Add(m_splitterV, 1, wxALL|wxEXPAND, 5);
    
    m_splitterPage52 = new wxPanel(m_splitterV, wxID_ANY, wxDefaultPosition, wxSize(-1,-1), wxTAB_TRAVERSAL);
    
    wxBoxSizer* boxSizer58 = new wxBoxSizer(wxVERTICAL);
    m_splitterPage52->SetSizer(boxSizer58);
    
    m_splitterH = new wxSplitterWindow(m_splitterPage52, wxID_ANY, wxDefaultPosition, wxSize(-1,-1), wxSP_LIVE_UPDATE|wxSP_3DSASH);
    m_splitterH->SetSashGravity(0.5);
    m_splitterH->SetMinimumPaneSize(10);
    
    boxSizer58->Add(m_splitterH, 1, wxALL|wxEXPAND, 5);
    
    m_panel1 = new wxPanel(m_splitterH, wxID_ANY, wxDefaultPosition, wxSize(-1,-1), wxTAB_TRAVERSAL);
    
    wxBoxSizer* boxSizer15 = new wxBoxSizer(wxVERTICAL);
    m_panel1->SetSizer(boxSizer15);
    
    m_staticText17 = new wxStaticText(m_panel1, wxID_ANY, _("Modified Paths:"), wxDefaultPosition, wxSize(-1,-1), 0);
    
    boxSizer15->Add(m_staticText17, 0, wxALL|wxALIGN_LEFT, 5);
    
    wxArrayString m_checkListFilesArr;
    m_checkListFiles = new wxCheckListBox(m_panel1, wxID_ANY, wxDefaultPosition, wxSize(-1,-1), m_checkListFilesArr, wxLB_SINGLE);
    
    boxSizer15->Add(m_checkListFiles, 1, wxEXPAND, 5);
    
    m_splitterPage14 = new wxPanel(m_splitterH, wxID_ANY, wxDefaultPosition, wxSize(-1,-1), wxTAB_TRAVERSAL);
    m_splitterH->SplitVertically(m_panel1, m_splitterPage14, 0);
    
    wxBoxSizer* boxSizer16 = new wxBoxSizer(wxVERTICAL);
    m_splitterPage14->SetSizer(boxSizer16);
    
    m_staticText19 = new wxStaticText(m_splitterPage14, wxID_ANY, _("Diff:"), wxDefaultPosition, wxSize(-1,-1), 0);
    
    boxSizer16->Add(m_staticText19, 0, wxALL|wxALIGN_LEFT, 5);
    
    m_stcDiff = new wxStyledTextCtrl(m_splitterPage14, wxID_ANY, wxDefaultPosition, wxSize(-1,-1), 0);
    // Configure the fold margin
    m_stcDiff->SetMarginType     (4, wxSTC_MARGIN_SYMBOL);
    m_stcDiff->SetMarginMask     (4, wxSTC_MASK_FOLDERS);
    m_stcDiff->SetMarginSensitive(4, true);
    m_stcDiff->SetMarginWidth    (4, 0);
    
    // Configure the tracker margin
    m_stcDiff->SetMarginWidth(1, 0);
    
    // Configure the symbol margin
    m_stcDiff->SetMarginType (2, wxSTC_MARGIN_SYMBOL);
    m_stcDiff->SetMarginMask (2, ~(wxSTC_MASK_FOLDERS));
    m_stcDiff->SetMarginWidth(2, 0);
    m_stcDiff->SetMarginSensitive(2, true);
    
    // Configure the line numbers margin
    int m_stcDiff_PixelWidth = 4 + 5 *m_stcDiff->TextWidth(wxSTC_STYLE_LINENUMBER, wxT("9"));
    m_stcDiff->SetMarginType(0, wxSTC_MARGIN_NUMBER);
    m_stcDiff->SetMarginWidth(0,m_stcDiff_PixelWidth);
    
    // Configure the line symbol margin
    m_stcDiff->SetMarginType(3, wxSTC_MARGIN_FORE);
    m_stcDiff->SetMarginMask(3, 0);
    m_stcDiff->SetMarginWidth(3,1);
    // Select the lexer
    m_stcDiff->SetLexer(wxSTC_LEX_NULL);
    // Set default font / styles
    m_stcDiff->StyleClearAll();
    m_stcDiff->SetWrapMode(0);
    m_stcDiff->SetIndentationGuides(0);
    m_stcDiff->SetKeyWords(0, wxT(""));
    m_stcDiff->SetKeyWords(1, wxT(""));
    m_stcDiff->SetKeyWords(2, wxT(""));
    m_stcDiff->SetKeyWords(3, wxT(""));
    m_stcDiff->SetKeyWords(4, wxT(""));
    
    boxSizer16->Add(m_stcDiff, 1, wxEXPAND, 5);
    
    m_splitterPage56 = new wxPanel(m_splitterV, wxID_ANY, wxDefaultPosition, wxSize(-1,-1), wxTAB_TRAVERSAL);
    m_splitterV->SplitHorizontally(m_splitterPage52, m_splitterPage56, 0);
    
    wxBoxSizer* boxSizer60 = new wxBoxSizer(wxVERTICAL);
    m_splitterPage56->SetSizer(boxSizer60);
    
    m_staticText62 = new wxStaticText(m_splitterPage56, wxID_ANY, _("Commit message:"), wxDefaultPosition, wxSize(-1,-1), 0);
    
    boxSizer60->Add(m_staticText62, 0, wxALL, 5);
    
    m_textCtrlMessage = new wxTextCtrl(m_splitterPage56, wxID_ANY, wxT(""), wxDefaultPosition, wxSize(-1,-1), wxTE_RICH2|wxTE_PROCESS_ENTER|wxTE_MULTILINE);
    #ifdef __WXMSW__
    // To get the newer version of the font on MSW, we use font wxSYS_DEFAULT_GUI_FONT with family set to wxFONTFAMILY_TELETYPE
    wxFont m_textCtrlMessageFont = wxSystemSettings::GetFont(wxSYS_DEFAULT_GUI_FONT);
    m_textCtrlMessageFont.SetFamily(wxFONTFAMILY_TELETYPE);
    #else
    wxFont m_textCtrlMessageFont = wxSystemSettings::GetFont(wxSYS_ANSI_FIXED_FONT);
    #endif
    m_textCtrlMessage->SetFont(m_textCtrlMessageFont);
    
    boxSizer60->Add(m_textCtrlMessage, 1, wxALL|wxEXPAND, 5);
    
    wxStaticBoxSizer* statixBoxSizer24 = new wxStaticBoxSizer( new wxStaticBox(this, wxID_ANY, _("Recent commit messages:")), wxVERTICAL);
    
    boxSizer1->Add(statixBoxSizer24, 0, wxEXPAND|wxALL, 5);
    
    wxArrayString m_choiceMessagesArr;
    m_choiceMessages = new wxChoice(this, wxID_ANY, wxDefaultPosition, wxSize(-1,-1), m_choiceMessagesArr, 0);
    
    statixBoxSizer24->Add(m_choiceMessages, 0, wxEXPAND|wxALL, 5);
    
    wxBoxSizer* boxSizer2 = new wxBoxSizer(wxHORIZONTAL);
    
    boxSizer1->Add(boxSizer2, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);
    
    m_button3 = new wxButton(this, wxID_OK, _("C&ommit"), wxDefaultPosition, wxSize(-1,-1), 0);
    m_button3->SetDefault();
    m_button3->SetToolTip(_("Commit"));
    
    boxSizer2->Add(m_button3, 0, wxALL, 5);
    
    m_button4 = new wxButton(this, wxID_CANCEL, _("Cancel"), wxDefaultPosition, wxSize(-1,-1), 0);
    
    boxSizer2->Add(m_button4, 0, wxALL, 5);
    
    SetSizeHints(-1,-1);
    if ( GetSizer() ) {
         GetSizer()->Fit(this);
    }
    Centre(wxBOTH);
    // Connect events
    m_checkListFiles->Connect(wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler(SvnCommitDialogBaseClass::OnFileSelected), NULL, this);
    m_choiceMessages->Connect(wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler(SvnCommitDialogBaseClass::OnChoiceMessage), NULL, this);
    
}

SvnCommitDialogBaseClass::~SvnCommitDialogBaseClass()
{
    m_checkListFiles->Disconnect(wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler(SvnCommitDialogBaseClass::OnFileSelected), NULL, this);
    m_choiceMessages->Disconnect(wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler(SvnCommitDialogBaseClass::OnChoiceMessage), NULL, this);
    
}

SvnSyncDialogBaseClass::SvnSyncDialogBaseClass(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style)
    : wxDialog(parent, id, title, pos, size, style)
{
    if ( !bBitmapLoaded ) {
        // We need to initialise the default bitmap handler
        wxXmlResource::Get()->AddHandler(new wxBitmapXmlHandler);
        wxC38D8InitBitmapResources();
        bBitmapLoaded = true;
    }
    
    wxBoxSizer* boxSizer26 = new wxBoxSizer(wxVERTICAL);
    this->SetSizer(boxSizer26);
    
    wxBoxSizer* boxSizer32 = new wxBoxSizer(wxHORIZONTAL);
    
    boxSizer26->Add(boxSizer32, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);
    
    m_staticText31 = new wxStaticText(this, wxID_ANY, _("Root URL:"), wxDefaultPosition, wxSize(-1,-1), 0);
    wxFont m_staticText31Font = wxSystemSettings::GetFont(wxSYS_DEFAULT_GUI_FONT);
    m_staticText31Font.SetWeight(wxFONTWEIGHT_BOLD);
    m_staticText31->SetFont(m_staticText31Font);
    
    boxSizer32->Add(m_staticText31, 0, wxALL, 5);
    
    m_staticTextSvnInfo = new wxStaticText(this, wxID_ANY, _("<none detected>"), wxDefaultPosition, wxSize(-1,-1), 0);
    
    boxSizer32->Add(m_staticTextSvnInfo, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);
    
    wxFlexGridSizer* flexGridSizer37 = new wxFlexGridSizer(  0, 2, 0, 0);
    flexGridSizer37->SetFlexibleDirection( wxBOTH );
    flexGridSizer37->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
    flexGridSizer37->AddGrowableCol(1);
    
    boxSizer26->Add(flexGridSizer37, 0, wxALL|wxEXPAND, 5);
    
    m_staticText34 = new wxStaticText(this, wxID_ANY, _("Root Directory:"), wxDefaultPosition, wxSize(-1,-1), 0);
    
    flexGridSizer37->Add(m_staticText34, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxALL, 5);
    
    m_dirPickerRootDir = new wxDirPickerCtrl(this, wxID_ANY, wxEmptyString, wxT("Select a folder"), wxDefaultPosition, wxSize(-1,-1), wxDIRP_DEFAULT_STYLE);
    
    flexGridSizer37->Add(m_dirPickerRootDir, 0, wxEXPAND|wxALL, 5);
    
    m_staticText40 = new wxStaticText(this, wxID_ANY, _("Exclude these file extensions:"), wxDefaultPosition, wxSize(-1,-1), 0);
    
    flexGridSizer37->Add(m_staticText40, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxALL, 5);
    
    m_textCtrlExclude = new wxTextCtrl(this, wxID_ANY, wxT(""), wxDefaultPosition, wxSize(-1,-1), wxTE_RICH2);
    
    flexGridSizer37->Add(m_textCtrlExclude, 0, wxEXPAND|wxALL, 5);
    
    flexGridSizer37->Add(0, 0, 0, wxALL, 5);
    
    m_checkBoxBin = new wxCheckBox(this, wxID_ANY, _("Exclude binary (application/octet-stream) files"), wxDefaultPosition, wxSize(-1,-1), 0);
    m_checkBoxBin->SetValue(false);
    
    flexGridSizer37->Add(m_checkBoxBin, 0, wxALL, 5);
    
    boxSizer26->Add(0, 0, 1, wxEXPAND|wxALL, 5);
    
    wxBoxSizer* boxSizer27 = new wxBoxSizer(wxHORIZONTAL);
    
    boxSizer26->Add(boxSizer27, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);
    
    m_button28 = new wxButton(this, wxID_OK, _("&OK"), wxDefaultPosition, wxSize(-1,-1), 0);
    m_button28->SetDefault();
    
    boxSizer27->Add(m_button28, 0, wxALL, 5);
    
    m_button29 = new wxButton(this, wxID_CANCEL, _("&Cancel"), wxDefaultPosition, wxSize(-1,-1), 0);
    
    boxSizer27->Add(m_button29, 0, wxALL, 5);
    
    SetSizeHints(500,200);
    if ( GetSizer() ) {
         GetSizer()->Fit(this);
    }
    Centre(wxBOTH);
    // Connect events
    m_button28->Connect(wxEVT_UPDATE_UI, wxUpdateUIEventHandler(SvnSyncDialogBaseClass::OnOkUI), NULL, this);
    m_button28->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(SvnSyncDialogBaseClass::OnButtonOK), NULL, this);
    
}

SvnSyncDialogBaseClass::~SvnSyncDialogBaseClass()
{
    m_button28->Disconnect(wxEVT_UPDATE_UI, wxUpdateUIEventHandler(SvnSyncDialogBaseClass::OnOkUI), NULL, this);
    m_button28->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(SvnSyncDialogBaseClass::OnButtonOK), NULL, this);
    
}