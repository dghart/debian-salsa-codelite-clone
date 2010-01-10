#include <wx/xrc/xmlres.h>
#include "simpletable.h"
#include "frame.h"
#include "new_quick_watch_dlg.h"
#include <wx/menu.h>
#include <wx/timer.h>
#include "windowattrmanager.h"
#include "debuggerobserver.h"
#include <wx/log.h>
#include "globals.h"

#define TIPTIMERID 34347

class QWTreeData : public wxTreeItemData {
public:
	VariableObjChild _voc;
	QWTreeData(const VariableObjChild &voc) : _voc(voc){}
	virtual ~QWTreeData(){}
};

BEGIN_EVENT_TABLE(DisplayVariableDlg, NewQuickWatch)
EVT_TIMER(TIPTIMERID, DisplayVariableDlg::OnTimer)
END_EVENT_TABLE()
DisplayVariableDlg::DisplayVariableDlg( wxWindow* parent)
		: NewQuickWatch( parent, wxID_ANY, _("Display Variable"), wxDefaultPosition, wxSize(500, 400) )
		, m_leftWindow(false)
{
	Centre();
	WindowAttrManager::Load(this, wxT("NewQuickWatchDlg"), NULL);
	m_timer = new wxTimer(this, TIPTIMERID);
}

DisplayVariableDlg::~DisplayVariableDlg()
{
	m_timer->Stop();
	delete m_timer;
	m_timer = NULL;
	WindowAttrManager::Save(this, wxT("NewQuickWatchDlg"), NULL);
}

void DisplayVariableDlg::OnExpandItem( wxTreeEvent& event )
{
	wxTreeItemId item = event.GetItem();
	if( item.IsOk()) {
		if( m_treeCtrl->ItemHasChildren(item) ) {
			wxTreeItemIdValue kookie;
			wxTreeItemId child = m_treeCtrl->GetFirstChild(item, kookie);
			while ( child.IsOk() ) {
				if( m_treeCtrl->GetItemText(child) == wxT("<dummy>") ) {
					// Dummy node, remove it and ask the debugger for information
					m_treeCtrl->SetItemText(child, wxT("Loading..."));

					QWTreeData *data = (QWTreeData *)m_treeCtrl->GetItemData(item);
					if( data ) {
						// Ask the debugger for information
						m_debugger->ListChildren(data->_voc.gdbId, DBG_USERR_QUICKWACTH);
						m_gdbId2Item[data->_voc.gdbId] = item;
					}
					break;
				}
				child = m_treeCtrl->GetNextChild(item, kookie);
			}
		}
	}
}

void DisplayVariableDlg::BuildTree(const VariableObjChildren& children, IDebugger *debugger)
{
	m_debugger = debugger;
	m_gdbId2Item.clear();
	m_gdbId2ItemLeaf.clear();
	m_treeCtrl->DeleteAllItems();
	wxTreeItemId root = m_treeCtrl->AddRoot( m_variableName );

	if( children.empty() ) return;
	DoAddChildren( root, children );
}

void DisplayVariableDlg::AddItems(const wxString& varname, const VariableObjChildren& children)
{
	std::map<wxString, wxTreeItemId>::iterator iter = m_gdbId2Item.find(varname);
	if( iter != m_gdbId2Item.end() ) {
		wxTreeItemId item = iter->second;
		DoAddChildren( item, children );
	}
}

void DisplayVariableDlg::DoAddChildren(wxTreeItemId& item, const VariableObjChildren& children)
{
	if( item.IsOk() == false ) return;

	if(m_treeCtrl->GetRootItem() != item && m_treeCtrl->ItemHasChildren(item)) {
		// delete the <dummy> node
		wxTreeItemIdValue kookie;
		wxTreeItemId child = m_treeCtrl->GetFirstChild(item, kookie);
		while ( child.IsOk() ) {
			wxString itemText = m_treeCtrl->GetItemText(child);
			if( itemText == wxT("<dummy>") || itemText == wxT("Loading...")) {
				m_treeCtrl->Delete( child );
			}
			child = m_treeCtrl->GetNextChild(item, kookie);
		}
	}

	for(size_t i=0; i<children.size(); i++) {
		VariableObjChild ch = children.at(i);
		if ( ch.varName != wxT("public") && ch.varName != wxT("private") && ch.varName != wxT("protected") ) {
			// Real node
			wxTreeItemId child = m_treeCtrl->AppendItem(item, ch.varName, -1, -1, new QWTreeData(ch));
			if ( ch.numChilds > 0 ) {
				// add fake node to this item, so it will have the [+] on the side
				m_treeCtrl->AppendItem(child, wxT("<dummy>"));
			}
			// ask gdb for the value for this node
			m_debugger->EvaluateVariableObject( ch.gdbId, DBG_USERR_QUICKWACTH );
			m_gdbId2ItemLeaf[ch.gdbId] = child;
		} else {
			// Fake node
			m_debugger->ListChildren(ch.gdbId, DBG_USERR_QUICKWACTH);
			m_gdbId2Item[ch.gdbId] = item;
		}
	}
}

void DisplayVariableDlg::OnBtnCancel(wxCommandEvent& e)
{
	DoCleanUp();
	e.Skip();
}

void DisplayVariableDlg::UpdateValue(const wxString& varname, const wxString& value)
{
	std::map<wxString, wxTreeItemId>::iterator iter = m_gdbId2ItemLeaf.find(varname);
	if( iter != m_gdbId2ItemLeaf.end() ) {
		wxTreeItemId item = iter->second;
		if ( item.IsOk() ) {
			wxString curtext = m_treeCtrl->GetItemText( item );
			curtext << wxT(" = ") << value;
			m_treeCtrl->SetItemText( item, curtext );
		}
	}
}

void DisplayVariableDlg::OnCloseEvent(wxCloseEvent& e)
{
	DoCleanUp();
	e.Skip();
}

void DisplayVariableDlg::DoCleanUp()
{
	if(m_debugger && m_mainVariableObject.IsEmpty() == false) {
		m_debugger->DeleteVariableObject(m_mainVariableObject);
	}
	m_gdbId2Item.clear();
	m_gdbId2ItemLeaf.clear();
	m_mainVariableObject = wxT("");
	m_variableName = wxT("");
}

void DisplayVariableDlg::HideDialog()
{
	DoCleanUp();
	wxDialog::Show(false);
}

void DisplayVariableDlg::OnKeyDown(wxKeyEvent& event)
{
	if( event.GetKeyCode() == WXK_ESCAPE ) {
		HideDialog();
	} else {
		event.Skip();
	}
}

void DisplayVariableDlg::ShowDialog(bool center)
{
	m_treeCtrl->SetFocus();
	if ( center ) {
		Centre();
	} else {
		Move( wxGetMousePosition() );

	}
	wxDialog::Show();
}

void DisplayVariableDlg::OnLeftDown(wxMouseEvent& e)
{
	int flags;
	wxTreeItemId item = m_treeCtrl->HitTest(e.GetPosition(), flags);
	if ( item.IsOk() && m_treeCtrl->ItemHasChildren(item) && (flags & wxTREE_HITTEST_ONITEMLABEL )) {
		if ( m_treeCtrl->IsExpanded(item) ) {
			m_treeCtrl->Collapse( item );
		} else {
			m_treeCtrl->Expand( item );
		}
	}
	e.Skip();
}


void DisplayVariableDlg::OnItemExpanded(wxTreeEvent& event)
{
	event.Skip();
}

void DisplayVariableDlg::OnMouseLeaveWindow(wxMouseEvent& e)
{
	m_leftWindow = true;
	m_timer->Start(500, true);
	e.Skip();
}

void DisplayVariableDlg::OnMouseEnterWindow(wxMouseEvent& e)
{
	m_leftWindow = false;
	e.Skip();
}

void DisplayVariableDlg::OnTimer(wxTimerEvent& e)
{
	if( m_leftWindow ) {
		wxMouseState state = wxGetMouseState();
		// This is to fix a 'MouseCapture' bug on Linux while leaving the mouse Window
		// and mouse button is clicked and scrolling the scrollbar (H or Vertical)
		// The UI hangs
		if(state.LeftDown()) {
			// Don't Hide, just restart the timer
			m_timer->Start(500, true);
			return;
		}

		// The wxEVT_LEAVE_WINDOW event happened when the mouse leaves the *client* area
		// That makes it impossible to resize the dialog, or even to use the scrollbar
		// So test if we're still inside the NC area + a bit to spare
		wxRect rect = GetScreenRect().Inflate(10,30);
		if ( rect.Contains(wxGetMousePosition()) ) {
			// Don't Hide, just restart the timer
			m_timer->Start(500, true);
		} else {
			m_leftWindow = false;
			HideDialog();
		}
	}
}

void DisplayVariableDlg::OnItemMenu(wxTreeEvent& event)
{
	event.Skip();
	wxTreeItemId item = event.GetItem();

	if(item.IsOk())
		m_treeCtrl->SelectItem(item);

	// Dont show popup menu for fake nodes
	if (IsFakeItem(item) )
		return;

	// Popup the menu
	wxMenu menu;

	menu.Append(XRCID("tip_add_watch"),  wxT("Add Watch"));
	menu.Append(XRCID("tip_copy_value"), wxT("Copy Value to Clipboard"));

	menu.Connect(XRCID("tip_add_watch"), wxEVT_COMMAND_MENU_SELECTED,  wxCommandEventHandler(DisplayVariableDlg::OnMenuSelection), NULL, this);
	menu.Connect(XRCID("tip_copy_value"), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(DisplayVariableDlg::OnMenuSelection), NULL, this);

	m_treeCtrl->PopupMenu( &menu );
}

wxString DisplayVariableDlg::DoGetItemPath(const wxTreeItemId& treeItem)
{
	wxString fullpath;
	wxTreeItemId item = treeItem;
	while ( item.IsOk() ) {
		wxString text = m_treeCtrl->GetItemText(item);
		text = text.BeforeFirst(wxT('='));
		text.Trim().Trim(false);

		if ( item != m_treeCtrl->GetRootItem() ) {
			if ( IsFakeItem(item) == false ) {
				text.Prepend(wxT("."));
				fullpath.Prepend(text);
			}
		} else {
			// Root item
			fullpath.Prepend(text);
		}

		// Are we at root yet?
		if ( m_treeCtrl->GetRootItem() == item )
			break;

		item = m_treeCtrl->GetItemParent(item);
	}
	return fullpath;
}

bool DisplayVariableDlg::IsFakeItem(const wxTreeItemId& item)
{
	if ( item.IsOk() == false ) return true; // fake

	if ( item != m_treeCtrl->GetRootItem() ) {
		QWTreeData *data = (QWTreeData *)m_treeCtrl->GetItemData(item);
		if( data )
			return data->_voc.isAFake;

		return false;

	} else {
		return false;
	}
}

void DisplayVariableDlg::OnMenuSelection(wxCommandEvent& e)
{
	wxTreeItemId item = m_treeCtrl->GetSelection();
	if(item.IsOk() && !IsFakeItem(item)) {
		if(e.GetId() == XRCID("tip_add_watch")) {
			wxString fullpath = DoGetItemPath(item);
			Frame::Get()->GetDebuggerPane()->GetWatchesTable()->AddExpression(fullpath);
			Frame::Get()->GetDebuggerPane()->SelectTab(DebuggerPane::WATCHES);
			Frame::Get()->GetDebuggerPane()->GetWatchesTable()->RefreshValues();

		} else if (e.GetId() == XRCID("tip_copy_value")) {
			wxString itemText = m_treeCtrl->GetItemText(item);
			itemText = itemText.AfterFirst(wxT('='));
			CopyToClipboard( itemText );
		}
	}
}

