#include <wx/app.h>
#include "cl_aui_notebook_art.h"
#include "drawingutils.h"
#include <wx/xrc/xmlres.h>
#include <wx/choicebk.h>
#include <wx/notebook.h>
#include "notebook_ex_nav_dlg.h"
#include "notebook_ex.h"
#include <wx/button.h>
#include "wx/sizer.h"
#include <wx/log.h>
#include <wx/wupdlock.h>

#ifdef __WXMSW__
#    include <wx/button.h>
#    include <wx/imaglist.h>
#    include <wx/image.h>
#elif defined(__WXGTK__)
#    include <gtk/gtk.h>
#    include <wx/imaglist.h>
#endif

const wxEventType wxEVT_COMMAND_BOOK_PAGE_CHANGED         = XRCID("notebook_page_changing");
const wxEventType wxEVT_COMMAND_BOOK_PAGE_CHANGING        = XRCID("notebook_page_changed");
const wxEventType wxEVT_COMMAND_BOOK_PAGE_CLOSING         = XRCID("notebook_page_closing");
const wxEventType wxEVT_COMMAND_BOOK_PAGE_CLOSED          = XRCID("notebook_page_closed");
const wxEventType wxEVT_COMMAND_BOOK_PAGE_MIDDLE_CLICKED  = XRCID("notebook_page_middle_clicked");
const wxEventType wxEVT_COMMAND_BOOK_PAGE_X_CLICKED       = XRCID("notebook_page_x_btn_clicked");
const wxEventType wxEVT_COMMAND_BOOK_BG_DCLICK            = XRCID("notebook_page_bg_dclick");

#define SHOW_POPUP_MENU 1234534

#define X_IMG_NONE    -1
#define X_IMG_NORMAL   0
#define X_IMG_PRESSED  1
#define X_IMG_DISABLED 2

Notebook::Notebook(wxWindow *parent, wxWindowID id, const wxPoint &pos, const wxSize &size, long style)
		: wxAuiNotebook(parent, id, pos, size, style | wxNO_BORDER | wxAUI_NB_TAB_MOVE | wxAUI_NB_TAB_SPLIT)
		, m_popupWin(NULL)
		, m_contextMenu(NULL)
		, m_style(style)
		, m_leftDownTabIdx(npos)
		, m_notify (true)
{
	Initialize();

	m_leftDownPos = wxPoint();

	// Connect events
	Connect(wxEVT_COMMAND_AUINOTEBOOK_PAGE_CHANGED,       wxAuiNotebookEventHandler(Notebook::OnInternalPageChanged),  NULL, this);
	Connect(wxEVT_COMMAND_AUINOTEBOOK_PAGE_CHANGING,      wxAuiNotebookEventHandler(Notebook::OnInternalPageChanging), NULL, this);
	Connect(wxEVT_COMMAND_AUINOTEBOOK_PAGE_CLOSED,        wxAuiNotebookEventHandler(Notebook::OnInternalPageClosed),   NULL, this);
	Connect(wxEVT_COMMAND_AUINOTEBOOK_PAGE_CLOSE,         wxAuiNotebookEventHandler(Notebook::OnInternalPageClosing),  NULL, this);
	Connect(wxEVT_COMMAND_AUINOTEBOOK_TAB_MIDDLE_DOWN,    wxAuiNotebookEventHandler(Notebook::OnTabMiddle),            NULL, this);
	Connect(wxEVT_COMMAND_AUINOTEBOOK_TAB_RIGHT_DOWN,     wxAuiNotebookEventHandler(Notebook::OnTabRightDown),         NULL, this);
	Connect(wxEVT_COMMAND_AUINOTEBOOK_TAB_RIGHT_UP,       wxAuiNotebookEventHandler(Notebook::OnTabRightUp),           NULL, this);
	Connect(wxEVT_COMMAND_AUINOTEBOOK_BG_DCLICK,          wxAuiNotebookEventHandler(Notebook::OnBgDclick),             NULL, this);

#ifdef __WXMSW__
	Connect(wxEVT_SET_FOCUS,                              wxFocusEventHandler(Notebook::OnFocus),                      NULL, this);
#endif
	Connect(wxEVT_NAVIGATION_KEY,                         wxNavigationKeyEventHandler(Notebook::OnNavigationKey),      NULL, this);
	Connect(SHOW_POPUP_MENU, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(Notebook::OnInternalMenu),             NULL, this);

	// On Linux, we disable the transparent drag since it will lead to crash when used with compiz / KDE4
#if defined (__WXGTK__) && defined (__WXDEBUG__)
	m_mgr.SetFlags(wxAUI_MGR_ALLOW_FLOATING|wxAUI_MGR_ALLOW_ACTIVE_PANE|wxAUI_MGR_TRANSPARENT_DRAG|wxAUI_MGR_RECTANGLE_HINT);

#elif defined(__WXGTK__)
    m_mgr.SetFlags((m_mgr.GetFlags() | wxAUI_MGR_VENETIAN_BLINDS_HINT) & ~wxAUI_MGR_TRANSPARENT_HINT);

#endif  //

	SetArtProvider(new clAuiTabArt());
}

Notebook::~Notebook()
{
	Disconnect(wxEVT_COMMAND_AUINOTEBOOK_PAGE_CHANGED,    wxAuiNotebookEventHandler(Notebook::OnInternalPageChanged),  NULL, this);
	Disconnect(wxEVT_COMMAND_AUINOTEBOOK_PAGE_CHANGING,   wxAuiNotebookEventHandler(Notebook::OnInternalPageChanging), NULL, this);
	Disconnect(wxEVT_COMMAND_AUINOTEBOOK_PAGE_CLOSED,     wxAuiNotebookEventHandler(Notebook::OnInternalPageClosed),   NULL, this);
	Disconnect(wxEVT_COMMAND_AUINOTEBOOK_PAGE_CLOSE,      wxAuiNotebookEventHandler(Notebook::OnInternalPageClosing),  NULL, this);
	Disconnect(wxEVT_COMMAND_AUINOTEBOOK_TAB_MIDDLE_DOWN, wxAuiNotebookEventHandler(Notebook::OnTabMiddle),            NULL, this);
	Disconnect(wxEVT_COMMAND_AUINOTEBOOK_TAB_RIGHT_DOWN,  wxAuiNotebookEventHandler(Notebook::OnTabRightDown),         NULL, this);
	Disconnect(wxEVT_COMMAND_AUINOTEBOOK_BG_DCLICK,       wxAuiNotebookEventHandler(Notebook::OnBgDclick),             NULL, this);
	Disconnect(wxEVT_COMMAND_AUINOTEBOOK_TAB_RIGHT_UP,    wxAuiNotebookEventHandler(Notebook::OnTabRightUp),           NULL, this);
	
	Disconnect(wxEVT_NAVIGATION_KEY,                 wxNavigationKeyEventHandler(Notebook::OnNavigationKey),  NULL, this);
#ifdef __WXMSW__
	Disconnect(wxEVT_SET_FOCUS,                              wxFocusEventHandler(Notebook::OnFocus),                      NULL, this);
#endif
	Disconnect(SHOW_POPUP_MENU, wxEVT_COMMAND_MENU_SELECTED,          wxCommandEventHandler(Notebook::OnInternalMenu),   NULL, this);
}

bool Notebook::AddPage(wxWindow *win, const wxString &text, bool selected, const wxBitmap& bmp)
{
	wxWindowUpdateLocker locker(this);
	win->Reparent(this);
	if(wxAuiNotebook::InsertPage(GetPageCount(), win, text, selected, bmp)){
		win->Connect(wxEVT_KEY_DOWN, wxKeyEventHandler(Notebook::OnKeyDown),  NULL, this);
		PushPageHistory(win);
		return true;
	}
	return false;
}

bool Notebook::InsertPage(size_t index, wxWindow* win, const wxString& text, bool selected, const wxBitmap &bmp)
{
	win->Reparent(this);
	if(wxAuiNotebook::InsertPage(index, win, text, selected, bmp)){
		win->Connect(wxEVT_KEY_DOWN, wxKeyEventHandler(Notebook::OnKeyDown),  NULL, this);
		PushPageHistory(win);
		return true;
	}
	return false;
}


void Notebook::Initialize()
{
}

void Notebook::SetSelection(size_t page, bool notify)
{
	if (page >= GetPageCount())
		return;

	m_notify = notify;
	wxAuiNotebook::SetSelection(page);
	m_notify = true;

	PushPageHistory(GetPage(page));
}

size_t Notebook::GetSelection()
{
	return static_cast<size_t>(wxAuiNotebook::GetSelection());
}

wxWindow* Notebook::GetPage(size_t page)
{
	if (page >= GetPageCount())
		return NULL;

	return wxAuiNotebook::GetPage(page);
}

bool Notebook::RemovePage(size_t page, bool notify)
{
	if (notify) {
		//send event to noitfy that the page has changed
		NotebookEvent event(wxEVT_COMMAND_BOOK_PAGE_CLOSING, GetId());
		event.SetSelection( page );
		event.SetEventObject( this );
		GetEventHandler()->ProcessEvent(event);

		if (!event.IsAllowed()) {
			return false;
		}
	}

	wxWindow* win = GetPage(page);
	win->Disconnect(wxEVT_KEY_DOWN, wxKeyEventHandler(Notebook::OnKeyDown),  NULL, this);

	bool rc = wxAuiNotebook::RemovePage(page);
	if (rc) {
		PopPageHistory(win);
	}

	if (rc && notify) {
		//send event to noitfy that the page has been closed
		NotebookEvent event(wxEVT_COMMAND_BOOK_PAGE_CLOSED, GetId());
		event.SetSelection( page );
		event.SetEventObject( this );
		GetEventHandler()->AddPendingEvent(event);
	}

	return rc;
}

bool Notebook::DeletePage(size_t page, bool notify)
{
	if (page >= GetPageCount())
		return false;

	if (notify) {
		//send event to noitfy that the page has changed
		NotebookEvent event(wxEVT_COMMAND_BOOK_PAGE_CLOSING, GetId());
		event.SetSelection( page );
		event.SetEventObject( this );
		GetEventHandler()->ProcessEvent(event);

		if (!event.IsAllowed()) {
			return false;
		}
	}

	wxWindow* win = GetPage(page);
	win->Disconnect(wxEVT_KEY_DOWN, wxKeyEventHandler(Notebook::OnKeyDown),  NULL, this);

	bool rc = wxAuiNotebook::DeletePage(page);
	if (rc) {
		PopPageHistory(win);
	}

	if (rc && notify) {
		//send event to noitfy that the page has been closed
		NotebookEvent event(wxEVT_COMMAND_BOOK_PAGE_CLOSED, GetId());
		event.SetSelection( page );
		event.SetEventObject( this );
		GetEventHandler()->ProcessEvent(event);
	}

	return rc;

}

wxString Notebook::GetPageText(size_t page) const
{
	if (page >= GetPageCount())
		return wxT("");

	return wxAuiNotebook::GetPageText(page);
}

void Notebook::OnNavigationKey(wxNavigationKeyEvent &e)
{
	if ( e.IsWindowChange() ) {
		if (DoNavigate())
			return;
	}
	e.Skip();
}

const wxArrayPtrVoid& Notebook::GetHistory() const
{
	return m_history;
}

void Notebook::SetRightClickMenu(wxMenu* menu)
{
	m_contextMenu = menu;
}

wxWindow* Notebook::GetCurrentPage()
{
	size_t selection = GetSelection();
	if (selection != Notebook::npos) {
		return GetPage(selection);
	}
	return NULL;
}

size_t Notebook::GetPageIndex(wxWindow *page)
{
	if ( !page )
		return Notebook::npos;

	for (size_t i=0; i< GetPageCount(); i++) {
		if (GetPage(i) == page) {
			return i;
		}
	}
	return Notebook::npos;
}

size_t Notebook::GetPageIndex(const wxString& text)
{
	for (size_t i=0; i< GetPageCount(); i++) {

		if (GetPageText(i) == text) {
			return i;
		}
	}
	return Notebook::npos;
}

bool Notebook::SetPageText(size_t index, const wxString &text)
{
	if (index >= GetPageCount())
		return false;
	return wxAuiNotebook::SetPageText(index, text);
}

bool Notebook::DeleteAllPages(bool notify)
{
	bool res = true;
	size_t count = GetPageCount();
	for (size_t i=0; i<count && res; i++) {
		res = this->DeletePage(0, notify);
	}
	return res;
}

void Notebook::PushPageHistory(wxWindow *page)
{
	if (page == NULL)
		return;

	int where = m_history.Index(page);
	//remove old entry of this page and re-insert it as first
	if (where != wxNOT_FOUND) {
		m_history.Remove(page);
	}
	m_history.Insert(page, 0);
}

void Notebook::PopPageHistory(wxWindow *page)
{
	if( !page )
		return;

	int where = m_history.Index(page);
	while (where != wxNOT_FOUND) {
		wxWindow *tab = static_cast<wxWindow *>(m_history.Item(where));
		m_history.Remove(tab);

		//remove all appearances of this page
		where = m_history.Index(page);
	}
}

wxWindow* Notebook::GetPreviousSelection()
{
	if (m_history.empty()) {
		return NULL;
	}
	//return the top of the heap
	return static_cast<wxWindow*>( m_history.Item(0));
}

void Notebook::OnInternalPageChanged(wxAuiNotebookEvent &e)
{
	DoPageChangedEvent(e);
}

void Notebook::OnInternalPageChanging(wxAuiNotebookEvent &e)
{
	DoPageChangingEvent(e);
}

void Notebook::DoPageChangedEvent(wxAuiNotebookEvent& e)
{
	if (!m_notify) {
		e.Skip();
		return;
	}

	//send event to noitfy that the page is changing
	NotebookEvent event(wxEVT_COMMAND_BOOK_PAGE_CHANGED, GetId());
	event.SetSelection   ( e.GetSelection()    );
	event.SetOldSelection( e.GetOldSelection() );
	event.SetEventObject ( this );
	GetEventHandler()->AddPendingEvent(event);

	PushPageHistory( GetPage(e.GetSelection()) );
	e.Skip();
}

void Notebook::DoPageChangingEvent(wxAuiNotebookEvent& e)
{
	if (!m_notify) {
		e.Skip();
		return;
	}

	//send event to noitfy that the page is changing
	NotebookEvent event(wxEVT_COMMAND_BOOK_PAGE_CHANGING, GetId());
	event.SetSelection   ( e.GetSelection()    );
	event.SetOldSelection( e.GetOldSelection() );
	event.SetEventObject ( this );
	GetEventHandler()->ProcessEvent(event);

	if ( !event.IsAllowed() ) {
		e.Veto();
	}
	e.Skip();
}

void Notebook::OnKeyDown(wxKeyEvent& e)
{
	if (e.GetKeyCode() == WXK_TAB && e.m_controlDown ) {
		if (DoNavigate())
			return;

	} else {
		e.Skip();
	}
}

bool Notebook::DoNavigate()
{
	if ( !m_popupWin && GetPageCount() > 1) {

		m_popupWin = new NotebookNavDialog( this );
		m_popupWin->ShowModal();

		wxWindow *page = m_popupWin->GetSelection();
		m_popupWin->Destroy();
		m_popupWin = NULL;

		SetSelection( GetPageIndex(page), true );


		return true;
	}
	return false;
}

void Notebook::OnFocus(wxFocusEvent& e)
{
	if( m_style & wxVB_PASS_FOCUS) {
		wxWindow *w = GetCurrentPage();
		if(w) {
			w->SetFocus();
		}
	}
	e.Skip();
}

void Notebook::OnInternalPageClosing(wxAuiNotebookEvent& e)
{
	e.Skip();

	NotebookEvent event(wxEVT_COMMAND_BOOK_PAGE_CLOSING, GetId());
	event.SetSelection( (int)GetSelection() );
	event.SetEventObject( this );
	GetEventHandler()->ProcessEvent(event);

	if (!event.IsAllowed()) {
		e.Veto();

	} else {
		// This page is likely to be removed, remove it from the history
		PopPageHistory( GetPage( static_cast<size_t>( GetSelection() ) ) );
	}
}

void Notebook::OnInternalPageClosed(wxAuiNotebookEvent& e)
{
	e.Skip();

	NotebookEvent event(wxEVT_COMMAND_BOOK_PAGE_CLOSED, GetId());
	event.SetSelection( (int) GetSelection() );
	event.SetEventObject( this );
	GetEventHandler()->AddPendingEvent(event);

}

void Notebook::OnTabMiddle(wxAuiNotebookEvent& e)
{
	if (e.GetSelection() != wxNOT_FOUND && HasCloseMiddle()) {
		//send event to noitfy that the page is changing
		NotebookEvent event(wxEVT_COMMAND_BOOK_PAGE_MIDDLE_CLICKED, GetId());
		event.SetSelection   ( e.GetSelection() );
		event.SetOldSelection( wxNOT_FOUND );
		event.SetEventObject ( this );
		GetEventHandler()->AddPendingEvent(event);
	}
}

void Notebook::OnTabRightDown(wxAuiNotebookEvent& e)
{
	if(m_contextMenu) {

		int where = e.GetSelection();
		if(where != wxNOT_FOUND && where == static_cast<int>(GetSelection())) {

			PopupMenu(m_contextMenu);
			
		} else {
			
			e.Skip();

		}
	} else {

		e.Skip();

	}
}

void Notebook::OnInternalMenu(wxCommandEvent& e)
{
	if(m_contextMenu) {
		PopupMenu(m_contextMenu);
	}
}

void Notebook::OnBgDclick(wxAuiNotebookEvent& e)
{
	NotebookEvent event(wxEVT_COMMAND_BOOK_BG_DCLICK, GetId());
	event.SetSelection   ( wxNOT_FOUND );
	event.SetOldSelection( wxNOT_FOUND );
	event.SetEventObject ( this );
	GetEventHandler()->AddPendingEvent(event);
}

void Notebook::OnTabRightUp(wxAuiNotebookEvent& e)
{
	e.Skip();
}
