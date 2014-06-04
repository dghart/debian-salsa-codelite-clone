//////////////////////////////////////////////////////////////////////
// This file was auto-generated by codelite's wxCrafter Plugin
// wxCrafter project file: UI.wxcp
// Do not modify this file by hand!
//////////////////////////////////////////////////////////////////////

#include "UI.h"


// Declare the bitmap loading function
extern void wxC32BEInitBitmapResources();

static bool bBitmapLoaded = false;


SFTPStatusPageBase::SFTPStatusPageBase(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style)
    : wxPanel(parent, id, pos, size, style)
{
    if ( !bBitmapLoaded ) {
        // We need to initialise the default bitmap handler
        wxXmlResource::Get()->AddHandler(new wxBitmapXmlHandler);
        wxC32BEInitBitmapResources();
        bBitmapLoaded = true;
    }
    
    wxBoxSizer* boxSizer2 = new wxBoxSizer(wxVERTICAL);
    this->SetSizer(boxSizer2);
    
    m_dvListCtrl = new wxDataViewListCtrl(this, wxID_ANY, wxDefaultPosition, wxSize(300,200), wxDV_SINGLE);
    
    boxSizer2->Add(m_dvListCtrl, 1, wxALL|wxEXPAND, 2);
    
    m_dvListCtrl->AppendTextColumn(_("Time"), wxDATAVIEW_CELL_INERT, 100, wxALIGN_LEFT);
    m_dvListCtrl->AppendBitmapColumn(_("Status"), m_dvListCtrl->GetColumnCount(), wxDATAVIEW_CELL_INERT, -2, wxALIGN_LEFT);
    m_dvListCtrl->AppendTextColumn(_("Account"), wxDATAVIEW_CELL_INERT, 150, wxALIGN_LEFT);
    m_dvListCtrl->AppendTextColumn(_("Message"), wxDATAVIEW_CELL_INERT, 600, wxALIGN_LEFT);
    
    SetSizeHints(-1,-1);
    if ( GetSizer() ) {
         GetSizer()->Fit(this);
    }
    Centre(wxBOTH);
    // Connect events
    m_dvListCtrl->Connect(wxEVT_COMMAND_DATAVIEW_ITEM_CONTEXT_MENU, wxDataViewEventHandler(SFTPStatusPageBase::OnContentMenu), NULL, this);
    
}

SFTPStatusPageBase::~SFTPStatusPageBase()
{
    m_dvListCtrl->Disconnect(wxEVT_COMMAND_DATAVIEW_ITEM_CONTEXT_MENU, wxDataViewEventHandler(SFTPStatusPageBase::OnContentMenu), NULL, this);
    
}

SFTPImages::SFTPImages()
    : wxImageList(16, 16, true)
{
    if ( !bBitmapLoaded ) {
        // We need to initialise the default bitmap handler
        wxXmlResource::Get()->AddHandler(new wxBitmapXmlHandler);
        wxC32BEInitBitmapResources();
        bBitmapLoaded = true;
    }
    
    {
        wxBitmap bmp;
        wxIcon icn;
        bmp = wxXmlResource::Get()->LoadBitmap(wxT("sftp_ok"));
        icn.CopyFromBitmap( bmp );
        this->Add( icn );
        m_bitmaps.insert( std::make_pair(wxT("sftp_ok"), bmp ) );
    }
    
    {
        wxBitmap bmp;
        wxIcon icn;
        bmp = wxXmlResource::Get()->LoadBitmap(wxT("sftp_error"));
        icn.CopyFromBitmap( bmp );
        this->Add( icn );
        m_bitmaps.insert( std::make_pair(wxT("sftp_error"), bmp ) );
    }
    
    {
        wxBitmap bmp;
        wxIcon icn;
        bmp = wxXmlResource::Get()->LoadBitmap(wxT("sftp_info"));
        icn.CopyFromBitmap( bmp );
        this->Add( icn );
        m_bitmaps.insert( std::make_pair(wxT("sftp_info"), bmp ) );
    }
    
    {
        wxBitmap bmp;
        wxIcon icn;
        bmp = wxXmlResource::Get()->LoadBitmap(wxT("sftp_tab"));
        icn.CopyFromBitmap( bmp );
        this->Add( icn );
        m_bitmaps.insert( std::make_pair(wxT("sftp_tab"), bmp ) );
    }
    
}

SFTPImages::~SFTPImages()
{
}

SFTPTreeViewBase::SFTPTreeViewBase(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style)
    : wxPanel(parent, id, pos, size, style)
{
    if ( !bBitmapLoaded ) {
        // We need to initialise the default bitmap handler
        wxXmlResource::Get()->AddHandler(new wxBitmapXmlHandler);
        wxC32BEInitBitmapResources();
        bBitmapLoaded = true;
    }
    
    wxBoxSizer* boxSizer16 = new wxBoxSizer(wxVERTICAL);
    this->SetSizer(boxSizer16);
    
    m_auibar = new wxAuiToolBar(this, wxID_ANY, wxDefaultPosition, wxSize(-1,-1), wxAUI_TB_PLAIN_BACKGROUND|wxAUI_TB_DEFAULT_STYLE);
    m_auibar->SetToolBitmapSize(wxSize(16,16));
    
    boxSizer16->Add(m_auibar, 0, wxEXPAND, 5);
    
    m_auibar->AddTool(ID_OPEN_ACCOUNT_MANAGER, _("Open account manager..."), wxXmlResource::Get()->LoadBitmap(wxT("ssh-16")), wxNullBitmap, wxITEM_NORMAL, _("Open account manager..."), _("Open account manager..."), NULL);
    
    m_auibar->AddTool(ID_SFTP_CONNECT, _("Connect"), wxXmlResource::Get()->LoadBitmap(wxT("connect")), wxNullBitmap, wxITEM_NORMAL, _("Establish connection to the selected account"), _("Establish connection to the selected account"), NULL);
    
    m_auibar->AddTool(ID_SFTP_DISCONNECT, _("Disconnect"), wxXmlResource::Get()->LoadBitmap(wxT("disconnect")), wxNullBitmap, wxITEM_NORMAL, _("Close the current connection"), _("Close the current connection"), NULL);
    
    m_auibar->AddTool(ID_ADD_BOOKMARK, _("Add Bookmark"), wxXmlResource::Get()->LoadBitmap(wxT("bookmark")), wxNullBitmap, wxITEM_NORMAL, _("Add Bookmark"), _("Add Bookmark"), NULL);
    wxAuiToolBarItem* m_toolbarItemAddBookmark = m_auibar->FindToolByIndex(m_auibar->GetToolCount()-1);
    if (m_toolbarItemAddBookmark) {
        m_toolbarItemAddBookmark->SetHasDropDown(true);
    }
    m_auibar->Realize();
    
    wxArrayString m_choiceAccountArr;
    m_choiceAccount = new wxChoice(this, wxID_ANY, wxDefaultPosition, wxSize(-1,-1), m_choiceAccountArr, 0);
    
    boxSizer16->Add(m_choiceAccount, 0, wxALL|wxEXPAND, 2);
    
    wxFlexGridSizer* flexGridSizer43 = new wxFlexGridSizer(0, 2, 0, 0);
    flexGridSizer43->SetFlexibleDirection( wxBOTH );
    flexGridSizer43->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
    flexGridSizer43->AddGrowableCol(1);
    
    boxSizer16->Add(flexGridSizer43, 0, wxEXPAND, 5);
    
    m_staticText49 = new wxStaticText(this, wxID_ANY, _("Go to:"), wxDefaultPosition, wxSize(-1,-1), 0);
    
    flexGridSizer43->Add(m_staticText49, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
    
    m_textCtrlQuickJump = new wxTextCtrl(this, wxID_ANY, wxT(""), wxDefaultPosition, wxSize(-1,-1), wxTE_PROCESS_ENTER);
    m_textCtrlQuickJump->SetToolTip(_("Type a path and hit ENTER"));
    
    flexGridSizer43->Add(m_textCtrlQuickJump, 0, wxALL|wxEXPAND, 5);
    
    m_treeListCtrl = new wxTreeListCtrl(this, wxID_ANY, wxDefaultPosition, wxSize(200,200), wxTL_DEFAULT_STYLE|wxTL_MULTIPLE);
    
    boxSizer16->Add(m_treeListCtrl, 1, wxLEFT|wxRIGHT|wxBOTTOM|wxEXPAND, 2);
    
    m_treeListCtrl->AppendColumn(_("Name"), 400, wxALIGN_LEFT, wxCOL_RESIZABLE|wxCOL_SORTABLE);
    m_treeListCtrl->AppendColumn(_("Type"), 100, wxALIGN_LEFT, wxCOL_RESIZABLE);
    m_treeListCtrl->AppendColumn(_("Size"), 100, wxALIGN_LEFT, wxCOL_RESIZABLE);
    
    SetSizeHints(-1,-1);
    if ( GetSizer() ) {
         GetSizer()->Fit(this);
    }
    Centre(wxBOTH);
    // Connect events
    this->Connect(ID_OPEN_ACCOUNT_MANAGER, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler(SFTPTreeViewBase::OnOpenAccountManager), NULL, this);
    this->Connect(ID_SFTP_CONNECT, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler(SFTPTreeViewBase::OnConnect), NULL, this);
    this->Connect(ID_SFTP_CONNECT, wxEVT_UPDATE_UI, wxUpdateUIEventHandler(SFTPTreeViewBase::OnConnectUI), NULL, this);
    this->Connect(ID_SFTP_DISCONNECT, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler(SFTPTreeViewBase::OnDisconnect), NULL, this);
    this->Connect(ID_SFTP_DISCONNECT, wxEVT_UPDATE_UI, wxUpdateUIEventHandler(SFTPTreeViewBase::OnDisconnectUI), NULL, this);
    this->Connect(ID_ADD_BOOKMARK, wxEVT_COMMAND_AUITOOLBAR_TOOL_DROPDOWN, wxAuiToolBarEventHandler(SFTPTreeViewBase::OnAddBookmark), NULL, this);
    this->Connect(ID_ADD_BOOKMARK, wxEVT_UPDATE_UI, wxUpdateUIEventHandler(SFTPTreeViewBase::OnAddBookmarkUI), NULL, this);
    m_choiceAccount->Connect(wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler(SFTPTreeViewBase::OnChoiceAccount), NULL, this);
    m_choiceAccount->Connect(wxEVT_UPDATE_UI, wxUpdateUIEventHandler(SFTPTreeViewBase::OnChoiceAccountUI), NULL, this);
    m_staticText49->Connect(wxEVT_UPDATE_UI, wxUpdateUIEventHandler(SFTPTreeViewBase::OnGotoLocationUI), NULL, this);
    m_textCtrlQuickJump->Connect(wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler(SFTPTreeViewBase::OnGotoLocation), NULL, this);
    m_textCtrlQuickJump->Connect(wxEVT_UPDATE_UI, wxUpdateUIEventHandler(SFTPTreeViewBase::OnGotoLocationUI), NULL, this);
    m_treeListCtrl->Connect(wxEVT_TREELIST_ITEM_EXPANDING, wxTreeListEventHandler(SFTPTreeViewBase::OnItemExpanding), NULL, this);
    m_treeListCtrl->Connect(wxEVT_TREELIST_ITEM_ACTIVATED, wxTreeListEventHandler(SFTPTreeViewBase::OnItemActivated), NULL, this);
    m_treeListCtrl->Connect(wxEVT_TREELIST_ITEM_CONTEXT_MENU, wxTreeListEventHandler(SFTPTreeViewBase::OnContextMenu), NULL, this);
    m_treeListCtrl->Connect(wxEVT_TREELIST_SELECTION_CHANGED, wxTreeListEventHandler(SFTPTreeViewBase::OnSelectionChanged), NULL, this);
    
    this->Connect(wxID_ANY, wxEVT_COMMAND_AUITOOLBAR_TOOL_DROPDOWN, wxAuiToolBarEventHandler(SFTPTreeViewBase::ShowAuiToolMenu), NULL, this);
}

SFTPTreeViewBase::~SFTPTreeViewBase()
{
    this->Disconnect(ID_OPEN_ACCOUNT_MANAGER, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler(SFTPTreeViewBase::OnOpenAccountManager), NULL, this);
    this->Disconnect(ID_SFTP_CONNECT, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler(SFTPTreeViewBase::OnConnect), NULL, this);
    this->Disconnect(ID_SFTP_CONNECT, wxEVT_UPDATE_UI, wxUpdateUIEventHandler(SFTPTreeViewBase::OnConnectUI), NULL, this);
    this->Disconnect(ID_SFTP_DISCONNECT, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler(SFTPTreeViewBase::OnDisconnect), NULL, this);
    this->Disconnect(ID_SFTP_DISCONNECT, wxEVT_UPDATE_UI, wxUpdateUIEventHandler(SFTPTreeViewBase::OnDisconnectUI), NULL, this);
    this->Disconnect(ID_ADD_BOOKMARK, wxEVT_COMMAND_AUITOOLBAR_TOOL_DROPDOWN, wxAuiToolBarEventHandler(SFTPTreeViewBase::OnAddBookmark), NULL, this);
    this->Disconnect(ID_ADD_BOOKMARK, wxEVT_UPDATE_UI, wxUpdateUIEventHandler(SFTPTreeViewBase::OnAddBookmarkUI), NULL, this);
    m_choiceAccount->Disconnect(wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler(SFTPTreeViewBase::OnChoiceAccount), NULL, this);
    m_choiceAccount->Disconnect(wxEVT_UPDATE_UI, wxUpdateUIEventHandler(SFTPTreeViewBase::OnChoiceAccountUI), NULL, this);
    m_staticText49->Disconnect(wxEVT_UPDATE_UI, wxUpdateUIEventHandler(SFTPTreeViewBase::OnGotoLocationUI), NULL, this);
    m_textCtrlQuickJump->Disconnect(wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler(SFTPTreeViewBase::OnGotoLocation), NULL, this);
    m_textCtrlQuickJump->Disconnect(wxEVT_UPDATE_UI, wxUpdateUIEventHandler(SFTPTreeViewBase::OnGotoLocationUI), NULL, this);
    m_treeListCtrl->Disconnect(wxEVT_TREELIST_ITEM_EXPANDING, wxTreeListEventHandler(SFTPTreeViewBase::OnItemExpanding), NULL, this);
    m_treeListCtrl->Disconnect(wxEVT_TREELIST_ITEM_ACTIVATED, wxTreeListEventHandler(SFTPTreeViewBase::OnItemActivated), NULL, this);
    m_treeListCtrl->Disconnect(wxEVT_TREELIST_ITEM_CONTEXT_MENU, wxTreeListEventHandler(SFTPTreeViewBase::OnContextMenu), NULL, this);
    m_treeListCtrl->Disconnect(wxEVT_TREELIST_SELECTION_CHANGED, wxTreeListEventHandler(SFTPTreeViewBase::OnSelectionChanged), NULL, this);
    
    std::map<int, wxMenu*>::iterator menuIter = m_dropdownMenus.begin();
    for( ; menuIter != m_dropdownMenus.end(); ++menuIter ) {
        wxDELETE( menuIter->second );
    }
    m_dropdownMenus.clear();

    this->Disconnect(wxID_ANY, wxEVT_COMMAND_AUITOOLBAR_TOOL_DROPDOWN, wxAuiToolBarEventHandler(SFTPTreeViewBase::ShowAuiToolMenu), NULL, this);
}


void SFTPTreeViewBase::ShowAuiToolMenu(wxAuiToolBarEvent& event)
{
    event.Skip();
    if (event.IsDropDownClicked()) {
        wxAuiToolBar* toolbar = wxDynamicCast(event.GetEventObject(), wxAuiToolBar);
        if (toolbar) {
            wxAuiToolBarItem* item = toolbar->FindTool(event.GetId());
            if (item) {
                std::map<int, wxMenu*>::iterator iter = m_dropdownMenus.find(item->GetId());
                if (iter != m_dropdownMenus.end()) {
                    event.Skip(false);
                    wxPoint pt = event.GetItemRect().GetBottomLeft();
                    pt.y++;
                    toolbar->PopupMenu(iter->second, pt);
                }
            }
        }
    }
}
SFTPManageBookmarkDlgBase::SFTPManageBookmarkDlgBase(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style)
    : wxDialog(parent, id, title, pos, size, style)
{
    if ( !bBitmapLoaded ) {
        // We need to initialise the default bitmap handler
        wxXmlResource::Get()->AddHandler(new wxBitmapXmlHandler);
        wxC32BEInitBitmapResources();
        bBitmapLoaded = true;
    }
    
    wxBoxSizer* boxSizer56 = new wxBoxSizer(wxVERTICAL);
    this->SetSizer(boxSizer56);
    
    wxBoxSizer* boxSizer64 = new wxBoxSizer(wxHORIZONTAL);
    
    boxSizer56->Add(boxSizer64, 1, wxALL|wxEXPAND, 5);
    
    wxArrayString m_listBoxBookmarksArr;
    m_listBoxBookmarks = new wxListBox(this, wxID_ANY, wxDefaultPosition, wxSize(-1,-1), m_listBoxBookmarksArr, wxLB_NEEDED_SB|wxLB_SINGLE);
    
    boxSizer64->Add(m_listBoxBookmarks, 1, wxALL|wxEXPAND, 5);
    
    wxBoxSizer* boxSizer68 = new wxBoxSizer(wxVERTICAL);
    
    boxSizer64->Add(boxSizer68, 0, wxEXPAND, 5);
    
    m_button70 = new wxButton(this, wxID_DELETE, _("Delete"), wxDefaultPosition, wxSize(-1,-1), 0);
    
    boxSizer68->Add(m_button70, 0, wxALL|wxEXPAND, 5);
    
    m_stdBtnSizer58 = new wxStdDialogButtonSizer();
    
    boxSizer56->Add(m_stdBtnSizer58, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5);
    
    m_buttonOk = new wxButton(this, wxID_OK, wxT(""), wxDefaultPosition, wxSize(-1, -1), 0);
    m_buttonOk->SetDefault();
    m_stdBtnSizer58->AddButton(m_buttonOk);
    
    m_buttonCancel = new wxButton(this, wxID_CANCEL, wxT(""), wxDefaultPosition, wxSize(-1, -1), 0);
    m_stdBtnSizer58->AddButton(m_buttonCancel);
    m_stdBtnSizer58->Realize();
    
    SetSizeHints(-1,-1);
    if ( GetSizer() ) {
         GetSizer()->Fit(this);
    }
    Centre(wxBOTH);
    // Connect events
    m_button70->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(SFTPManageBookmarkDlgBase::OnDelete), NULL, this);
    m_button70->Connect(wxEVT_UPDATE_UI, wxUpdateUIEventHandler(SFTPManageBookmarkDlgBase::OnDeleteUI), NULL, this);
    
}

SFTPManageBookmarkDlgBase::~SFTPManageBookmarkDlgBase()
{
    m_button70->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(SFTPManageBookmarkDlgBase::OnDelete), NULL, this);
    m_button70->Disconnect(wxEVT_UPDATE_UI, wxUpdateUIEventHandler(SFTPManageBookmarkDlgBase::OnDeleteUI), NULL, this);
    
}
