//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//
// copyright            : (C) 2008 by Eran Ifrah
// file name            : debuggerpane.cpp
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
#include <wx/aui/framemanager.h>
#include "debuggerasciiviewer.h"
#include "localstable.h"
#include "dockablepane.h"
#include "editor_config.h"
#include "detachedpanesinfo.h"
 #include "wx/dcbuffer.h"
#include "memoryview.h"
#include "debuggerpane.h"
#include "simpletable.h"
#include "listctrlpanel.h"
#include "wx/xrc/xmlres.h"
#include "manager.h"
#include "breakpointdlg.h"
#include "threadlistpanel.h"

const wxString DebuggerPane::LOCALS       = wxT("Locals");
const wxString DebuggerPane::WATCHES      = wxT("Watches");
const wxString DebuggerPane::FRAMES       = wxT("Call Stack");
const wxString DebuggerPane::BREAKPOINTS  = wxT("Breakpoints");
const wxString DebuggerPane::THREADS      = wxT("Threads");
const wxString DebuggerPane::MEMORY       = wxT("Memory");
const wxString DebuggerPane::ASCII_VIEWER = wxT("Ascii Viewer");

#define IS_DETACHED(name) ( detachedPanes.Index(name) != wxNOT_FOUND ) ? true : false

BEGIN_EVENT_TABLE(DebuggerPane, wxPanel)
	EVT_BOOK_PAGE_CHANGED(wxID_ANY, DebuggerPane::OnPageChanged)
END_EVENT_TABLE()

DebuggerPane::DebuggerPane(wxWindow *parent, const wxString &caption, wxAuiManager *mgr)
		: wxPanel(parent, wxID_ANY, wxDefaultPosition, wxSize(400, 300))
		, m_caption(caption)
		, m_initDone(false)
		, m_mgr(mgr)
{
	CreateGUIControls();
}

DebuggerPane::~DebuggerPane()
{
}

void DebuggerPane::OnPageChanged(NotebookEvent &event)
{
	if (m_initDone) {
		if (event.GetEventObject() == m_book) {
			ManagerST::Get()->UpdateDebuggerPane();
		} else {
			event.Skip();
		}
	}
}

void DebuggerPane::CreateGUIControls()
{
	wxBoxSizer *mainSizer = new wxBoxSizer(wxVERTICAL);
	SetSizer(mainSizer);

	long bookStyle = wxVB_TOP | wxAUI_NB_SCROLL_BUTTONS;
	EditorConfigST::Get()->GetLongValue(wxT("DebuggerBook"), bookStyle);

	m_book = new Notebook(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, bookStyle);
	mainSizer->Add(m_book, 1, wxEXPAND|wxALL, 1);

	// Calculate the widthest tab (the one with the 'Call Stack' label)
	int xx, yy;
	wxFont fnt = wxSystemSettings::GetFont(wxSYS_DEFAULT_GUI_FONT);
	wxWindow::GetTextExtent(wxT("Breakpoints"), &xx, &yy, NULL, NULL, &fnt);

	// load list of detached panes
	wxArrayString detachedPanes;
	DetachedPanesInfo dpi;
	EditorConfigST::Get()->ReadObject(wxT("DetachedPanesList"), &dpi);
	detachedPanes = dpi.GetPanes();


	wxString name;
	wxBitmap bmp;
	name = LOCALS;
	bmp  = wxXmlResource::Get()->LoadBitmap(wxT("locals_view"));
	// Add the 'Locals View'
	if( IS_DETACHED(name) ) {
		DockablePane *cp = new DockablePane(GetParent(), m_book, name, bmp, wxSize(200, 200));
		m_localsTable = new LocalsTable(cp);
		cp->SetChildNoReparent(m_localsTable);

	} else {
		m_localsTable = new LocalsTable(m_book);
		m_book->AddPage(m_localsTable, name, false, bmp);
	}

	// Add the 'watches View'
	name = WATCHES;
	bmp  = wxXmlResource::Get()->LoadBitmap(wxT("watches"));
	if( IS_DETACHED(name) ) {
		DockablePane *cp = new DockablePane(GetParent(), m_book, name, bmp, wxSize(200, 200));
		m_watchesTable = new WatchesTable(cp);
		cp->SetChildNoReparent(m_watchesTable);

	} else {
		m_watchesTable = new WatchesTable(m_book);
		m_book->AddPage(m_watchesTable, name, false, bmp);
	}


	// Add the 'ASCII Viewer'
	name = ASCII_VIEWER;
	bmp  = wxXmlResource::Get()->LoadBitmap(wxT("text_view"));
	if( IS_DETACHED(name) ) {
		DockablePane *cp = new DockablePane(GetParent(), m_book, name, bmp, wxSize(200, 200));
		m_asciiViewer = new DebuggerAsciiViewer(cp);
		cp->SetChildNoReparent(m_asciiViewer);

	} else {
		m_asciiViewer = new DebuggerAsciiViewer(m_book);
		m_book->AddPage(m_asciiViewer, name, false, bmp);
	}

	// Add the 'Call Stack'
	name = FRAMES;
	bmp  = wxXmlResource::Get()->LoadBitmap(wxT("frames"));
	if( IS_DETACHED(name) ) {
		DockablePane *cp = new DockablePane(GetParent(), m_book, name, bmp, wxSize(200, 200));
		m_frameList = new ListCtrlPanel(cp);
		cp->SetChildNoReparent(m_frameList);

	} else {
		m_frameList = new ListCtrlPanel(m_book);
		m_book->AddPage(m_frameList, name, false, bmp);
	}

	// Add the 'Breakpoints'
	name = BREAKPOINTS;
	bmp  = wxXmlResource::Get()->LoadBitmap(wxT("breakpoint"));
	if( IS_DETACHED(name) ) {
		DockablePane *cp = new DockablePane(GetParent(), m_book, name, bmp, wxSize(200, 200));
		m_breakpoints = new BreakpointDlg(cp);
		cp->SetChildNoReparent(m_breakpoints);

	} else {
		m_breakpoints = new BreakpointDlg(m_book);
		m_book->AddPage(m_breakpoints, name, false, bmp);
	}

	// Add the 'Breakpoints'
	name = THREADS;
	bmp  = wxXmlResource::Get()->LoadBitmap(wxT("threads"));
	if( IS_DETACHED(name) ) {
		DockablePane *cp = new DockablePane(GetParent(), m_book, name, bmp, wxSize(200, 200));
		m_threads = new ThreadListPanel(cp);
		cp->SetChildNoReparent(m_threads);

	} else {
		m_threads = new ThreadListPanel(m_book);
		m_book->AddPage(m_threads, name, false, bmp);
	}

	// Add the 'Memory View'
	name = MEMORY;
	bmp  = wxXmlResource::Get()->LoadBitmap(wxT("memory_view"));
	if( IS_DETACHED(name) ) {
		DockablePane *cp = new DockablePane(GetParent(), m_book, name, bmp, wxSize(200, 200));
		m_memory = new MemoryView(cp);
		cp->SetChildNoReparent(m_memory);

	} else {
		m_memory = new MemoryView(m_book);
		m_book->AddPage(m_memory, name, false, bmp);
	}

	m_initDone = true;
}

void DebuggerPane::SelectTab(const wxString &tabName)
{
	for (size_t i=0; i< m_book->GetPageCount(); i++) {
		if (m_book->GetPageText(i) == tabName) {
			m_book->SetSelection(i);
			break;
		}
	}
}

void DebuggerPane::Clear()
{
	GetLocalsTable()->Clear();
	GetWatchesTable()->Clear();
	GetFrameListView()->Clear();
	GetThreadsView()->Clear();
	GetMemoryView()->Clear();
}
