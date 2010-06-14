//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//
// copyright            : (C) 2008 by Eran Ifrah
// file name            : workspace_pane.cpp
//
// -------------------------------------------------------------------------
// A
//              _____           _      _     _ _
//             /  __ \         | |    | |   (_) |
//             | /  \/ ___   __| | ___| |    _| |_ ___
//             | |    / _ \ / _  |/ _ \ |   | | __/ _ )
//             | \__/\ (_) | (_| |  __/ |___| | ||  __/
//              \____/\___/ \__,_|\___\_____/_|\__\___|
//
//                                                  F i l e
//
//    This program is free software; you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation; either version 2 of the License, or
//    (at your option) any later version.
//
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
#include <wx/app.h>
#include <wx/wupdlock.h>
#include <wx/xrc/xmlres.h>
#include "parse_thread.h"
#include "editor_config.h"
#include "configuration_manager_dlg.h"
#include "detachedpanesinfo.h"
#include "dockablepane.h"
#include "manager.h"
#include "frame.h"
#include "cl_editor.h"
#include "notebook_ex.h"
#include "cpp_symbol_tree.h"
#include "windowstack.h"
#include "macros.h"
#include "fileview.h"
#include "openwindowspanel.h"
#include "fileexplorer.h"
#include "workspacetab.h"
#include "tabgroupspane.h"
#include "workspace_pane.h"

#define OPEN_CONFIG_MGR_STR wxT("<Open Configuration Manager...>")

WorkspacePane::WorkspacePane(wxWindow *parent, const wxString &caption, wxAuiManager *mgr)
    : wxPanel(parent)
    , m_caption(caption)
    , m_mgr(mgr)
{
	CreateGUIControls();
    Connect();
}

WorkspacePane::~WorkspacePane()
{
}

#define IS_DETACHED(name) (detachedPanes.Index(name) != wxNOT_FOUND) ? true : false

void WorkspacePane::CreateGUIControls()
{
	wxBoxSizer *mainSizer = new wxBoxSizer(wxVERTICAL);
	SetSizer(mainSizer);

    // selected configuration:

	wxBoxSizer *hsz = new wxBoxSizer(wxHORIZONTAL);
	mainSizer->Add(hsz, 0, wxEXPAND|wxTOP|wxBOTTOM, 5);

	wxArrayString choices;
	m_workspaceConfig = new wxChoice(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, choices);
	m_workspaceConfig->SetToolTip(wxT("Select the workspace build configuration"));

	m_workspaceConfig->Enable(false);
	m_workspaceConfig->Append(OPEN_CONFIG_MGR_STR);
	ConnectChoice(m_workspaceConfig, WorkspacePane::OnConfigurationManagerChoice);
	hsz->Add(m_workspaceConfig, 1, wxEXPAND| wxALL, 1);

#ifdef __WXMAC__
	m_workspaceConfig->SetWindowVariant(wxWINDOW_VARIANT_SMALL);
#endif

    // add notebook for tabs
	long bookStyle = wxVB_LEFT | wxAUI_NB_SCROLL_BUTTONS;
	m_book = new Notebook(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, bookStyle);

	// Calculate the widthest tab (the one with the 'Workspcae' label)
	int xx, yy;
	wxFont fnt = wxSystemSettings::GetFont(wxSYS_DEFAULT_GUI_FONT);
	wxWindow::GetTextExtent(wxT("Workspace"), &xx, &yy, NULL, NULL, &fnt);

	mainSizer->Add(m_book, 1, wxEXPAND | wxALL, 0);

    // create tabs (possibly detached)
	DetachedPanesInfo dpi;
	EditorConfigST::Get()->ReadObject(wxT("DetachedPanesList"), &dpi);


	wxArrayString detachedPanes;
	detachedPanes = dpi.GetPanes();

	// Add the workspace tab
	wxString  name;

	name = wxT("Workspace");
	if(IS_DETACHED(name)) {
		DockablePane *cp = new DockablePane(GetParent(), m_book, name, wxNullBitmap, wxSize(200, 200));
		m_workspaceTab = new WorkspaceTab(cp, name);
		cp->SetChildNoReparent(m_workspaceTab);
	} else {
		m_workspaceTab = new WorkspaceTab(m_book, name);
		m_book->AddPage(m_workspaceTab, name, true);
	}

	// Add the explorer tab
	name = wxT("Explorer");
	if(IS_DETACHED(name)) {
		DockablePane *cp = new DockablePane(GetParent(), m_book, name, wxNullBitmap, wxSize(200, 200));
		m_explorer = new FileExplorer(cp, name);
		cp->SetChildNoReparent(m_explorer);
	} else {
		m_explorer = new FileExplorer(m_book, name);
		m_book->AddPage(m_explorer, name, false);
	}

	// Add the Outline tab
	name = wxT("Outline");
	if(IS_DETACHED(name)) {
		DockablePane *cp = new DockablePane(GetParent(), m_book,  name, wxNullBitmap, wxSize(200, 200));
		m_winStack = new WindowStack(cp);
		cp->SetChildNoReparent(m_winStack);
	} else {
		m_winStack = new WindowStack(m_book);
		m_book->AddPage(m_winStack, name, false);
	}

	// Add the Open Windows Panel (Tabs)
	name = wxT("Tabs");
	if(IS_DETACHED(name)) {
		DockablePane *cp = new DockablePane(GetParent(), m_book,  name, wxNullBitmap, wxSize(200, 200));
		m_openWindowsPane = new OpenWindowsPanel(cp, name);
		cp->SetChildNoReparent(m_openWindowsPane);
	} else {
		m_openWindowsPane = new OpenWindowsPanel(m_book, name);
		m_book->AddPage(m_openWindowsPane, name, false);
	}

	// Add the Tabgroups tab
	name = wxT("Tabgroups");
	if(IS_DETACHED(name)) {
		DockablePane *cp = new DockablePane(GetParent(), m_book,  name, wxNullBitmap, wxSize(200, 200));
		m_TabgroupsPane = new TabgroupsPane(cp, name);
		cp->SetChildNoReparent(m_TabgroupsPane);
	} else {
		m_TabgroupsPane = new TabgroupsPane(m_book, name);
		m_book->AddPage(m_TabgroupsPane, name, false);
	}

	if (m_book->GetPageCount() > 0) {
		m_book->SetSelection((size_t)0);
	}
	m_mgr->Update();
}

void WorkspacePane::Connect()
{
	wxTheApp->Connect(wxEVT_WORKSPACE_LOADED,         wxCommandEventHandler(WorkspacePane::OnWorkspaceConfig),     NULL, this);
	wxTheApp->Connect(wxEVT_WORKSPACE_CONFIG_CHANGED, wxCommandEventHandler(WorkspacePane::OnWorkspaceConfig),     NULL, this);
	wxTheApp->Connect(wxEVT_WORKSPACE_CLOSED,         wxCommandEventHandler(WorkspacePane::OnWorkspaceClosed),     NULL, this);
	wxTheApp->Connect(wxEVT_PROJ_FILE_ADDED,          wxCommandEventHandler(WorkspacePane::OnProjectFileAdded),    NULL, this);
	wxTheApp->Connect(wxEVT_PROJ_FILE_REMOVED,        wxCommandEventHandler(WorkspacePane::OnProjectFileRemoved),  NULL, this);
	wxTheApp->Connect(wxEVT_SYNBOL_TREE_UPDATE_ITEM,  wxCommandEventHandler(WorkspacePane::OnSymbolsUpdated),      NULL, this);
	wxTheApp->Connect(wxEVT_SYNBOL_TREE_DELETE_ITEM,  wxCommandEventHandler(WorkspacePane::OnSymbolsDeleted),      NULL, this);
	wxTheApp->Connect(wxEVT_SYNBOL_TREE_ADD_ITEM,     wxCommandEventHandler(WorkspacePane::OnSymbolsAdded),        NULL, this);
	wxTheApp->Connect(wxEVT_FILE_RETAGGED,            wxCommandEventHandler(WorkspacePane::OnFileRetagged),        NULL, this);
	wxTheApp->Connect(wxEVT_ACTIVE_EDITOR_CHANGED,    wxCommandEventHandler(WorkspacePane::OnActiveEditorChanged), NULL, this);
	wxTheApp->Connect(wxEVT_EDITOR_CLOSING,           wxCommandEventHandler(WorkspacePane::OnEditorClosing),       NULL, this);
	wxTheApp->Connect(wxEVT_ALL_EDITORS_CLOSED,       wxCommandEventHandler(WorkspacePane::OnAllEditorsClosed),    NULL, this);

    wxTheApp->Connect(XRCID("configuration_manager"), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler (WorkspacePane::OnConfigurationManager),   NULL, this);
    wxTheApp->Connect(XRCID("configuration_manager"), wxEVT_UPDATE_UI,             wxUpdateUIEventHandler(WorkspacePane::OnConfigurationManagerUI), NULL, this);
}


extern wxImageList* CreateSymbolTreeImages();

void WorkspacePane::ShowCurrentOutline()
{
    LEditor *editor = Frame::Get()->GetMainBook()->GetActiveEditor();
    if (!editor || editor->GetProjectName().IsEmpty()) {
        m_winStack->SelectNone();
        return;
    }
    wxString path = editor->GetFileName().GetFullPath();
    if (m_winStack->GetSelectedKey() != path) {
        m_winStack->Freeze();
        if (m_winStack->Find(path) == NULL) {
            CppSymbolTree *tree = new CppSymbolTree(m_winStack, wxID_ANY);
            tree->SetSymbolsImages(CreateSymbolTreeImages());
            tree->BuildTree(path);
            m_winStack->Add(tree, path);
        }
        m_winStack->Select(path);
        m_winStack->Thaw();
    }
}

void WorkspacePane::OnActiveEditorChanged(wxCommandEvent& e)
{
    e.Skip();
    ShowCurrentOutline();
}

void WorkspacePane::OnAllEditorsClosed(wxCommandEvent& e)
{
    e.Skip();
    m_winStack->Clear();
}

void WorkspacePane::OnEditorClosing(wxCommandEvent& e)
{
    e.Skip();
    IEditor *editor = (IEditor*) e.GetClientData();
    if (editor && !editor->GetProjectName().IsEmpty()) {
        m_winStack->Delete(editor->GetFileName().GetFullPath());
    }
}

void WorkspacePane::OnFileRetagged(wxCommandEvent& e)
{
    e.Skip();
    std::vector<wxFileName> *files = (std::vector<wxFileName>*) e.GetClientData();
	if (files && !files->empty()) {
        m_winStack->Freeze();
        // toss out any out-of-date outlines
        for (size_t i = 0; i < files->size(); i++) {
            m_winStack->Delete(files->at(i).GetFullPath());
        }
        ShowCurrentOutline(); // in case active editor's file was one of them
        m_winStack->Thaw();
    }
}

void WorkspacePane::OnProjectFileAdded(wxCommandEvent& e)
{
    e.Skip();
    ShowCurrentOutline(); // in case the active editor's file is now tagged
}

void WorkspacePane::OnProjectFileRemoved(wxCommandEvent& e)
{
    e.Skip();
    wxArrayString *files = (wxArrayString*) e.GetClientData();
	if (files && !files->IsEmpty()) {
        for (size_t i = 0; i < files->Count(); i++) {
            m_winStack->Delete(files->Item(i));
        }
        ShowCurrentOutline(); // in case active editor's file is no longer tagged
    }
}

void WorkspacePane::OnSymbolsAdded(wxCommandEvent& e)
{
    e.Skip();
    ParseThreadEventData *data = (ParseThreadEventData*) e.GetClientData();
	if (data && !data->GetItems().empty()) {
        CppSymbolTree *tree = (CppSymbolTree*) m_winStack->Find(data->GetFileName());
        if (tree) {
            tree->AddSymbols(data->GetItems());
        }
    }
}

void WorkspacePane::OnSymbolsDeleted(wxCommandEvent& e)
{
    e.Skip();
    ParseThreadEventData *data = (ParseThreadEventData*) e.GetClientData();
	if (data && !data->GetItems().empty()) {
        CppSymbolTree *tree = (CppSymbolTree*) m_winStack->Find(data->GetFileName());
        if (tree) {
            tree->DeleteSymbols(data->GetItems());
        }
    }
}

void WorkspacePane::OnSymbolsUpdated(wxCommandEvent& e)
{
    e.Skip();
    ParseThreadEventData *data = (ParseThreadEventData*) e.GetClientData();
	if (data && !data->GetItems().empty()) {
        CppSymbolTree *tree = (CppSymbolTree*) m_winStack->Find(data->GetFileName());
        if (tree) {
            tree->UpdateSymbols(data->GetItems());
        }
    }
}

void WorkspacePane::OnWorkspaceConfig(wxCommandEvent& e)
{
    e.Skip();

    BuildMatrixPtr matrix = WorkspaceST::Get()->GetBuildMatrix();
	std::list<WorkspaceConfigurationPtr> confs = matrix->GetConfigurations();

	m_workspaceConfig->Freeze();
    m_workspaceConfig->Enable(true);
	m_workspaceConfig->Clear();
	for (std::list<WorkspaceConfigurationPtr>::iterator iter = confs.begin() ; iter != confs.end(); iter++) {
		m_workspaceConfig->Append((*iter)->GetName());
	}
	if (m_workspaceConfig->GetCount() > 0) {
        m_workspaceConfig->SetStringSelection(matrix->GetSelectedConfigurationName());
	}
	m_workspaceConfig->Append(OPEN_CONFIG_MGR_STR);
	m_workspaceConfig->Thaw();
}

void WorkspacePane::OnWorkspaceClosed(wxCommandEvent& e)
{
    e.Skip();
    m_workspaceConfig->Clear();
    m_workspaceConfig->Enable(false);
    m_winStack->Clear();
}

void WorkspacePane::OnConfigurationManagerUI(wxUpdateUIEvent& e)
{
	e.Enable(ManagerST::Get()->IsWorkspaceOpen());
}

void WorkspacePane::OnConfigurationManagerChoice(wxCommandEvent &event)
{
	wxString selection = m_workspaceConfig->GetStringSelection();
	if(selection == OPEN_CONFIG_MGR_STR){
		wxCommandEvent e(wxEVT_COMMAND_MENU_SELECTED, XRCID("configuration_manager"));
		e.SetEventObject(this);
		ProcessEvent(e);
		return;
	}

	BuildMatrixPtr matrix = ManagerST::Get()->GetWorkspaceBuildMatrix();
	matrix->SetSelectedConfigurationName(selection);
	ManagerST::Get()->SetWorkspaceBuildMatrix(matrix);

	// Set the focus to the active editor if any
	LEditor *editor = Frame::Get()->GetMainBook()->GetActiveEditor();
	if(editor)
		editor->SetActive();

}

void WorkspacePane::OnConfigurationManager(wxCommandEvent& e)
{
	wxUnusedVar(e);
	ConfigurationManagerDlg dlg(this);
	dlg.ShowModal();

	BuildMatrixPtr matrix = ManagerST::Get()->GetWorkspaceBuildMatrix();
	m_workspaceConfig->SetStringSelection(matrix->GetSelectedConfigurationName());
}
