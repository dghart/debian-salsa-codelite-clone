#include "debugger_predefined_types_page.h"
#include "globals.h"
#include <wx/msgdlg.h>
#include "dbgcommanddlg.h"

PreDefinedTypesPage::PreDefinedTypesPage( wxWindow* parent, const DebuggerPreDefinedTypes& preDefTypes )
	: PreDefinedTypesPageBase( parent )
	, m_selectedItem(wxNOT_FOUND)
{
	m_data = preDefTypes;
	m_listCtrl1->InsertColumn(0, wxT("Type"));
	m_listCtrl1->InsertColumn(1, wxT("Expression"));
	m_listCtrl1->InsertColumn(2, wxT("Debugger Command"));

	//Populate the list with the items from the configuration file
	DebuggerCmdDataVec cmds = m_data.GetCmds();
	for (size_t i=0; i<cmds.size(); i++) {
		DebuggerCmdData cmd = cmds.at(i);

		long item = AppendListCtrlRow(m_listCtrl1);
		SetColumnText(m_listCtrl1, item, 0, cmd.GetName());
		SetColumnText(m_listCtrl1, item, 1, cmd.GetCommand());
		SetColumnText(m_listCtrl1, item, 2, cmd.GetDbgCommand());
	}
	m_listCtrl1->SetColumnWidth(0, 100);
	m_listCtrl1->SetColumnWidth(1, 200);
}

void PreDefinedTypesPage::OnItemActivated( wxListEvent& event )
{
	m_selectedItem = event.m_itemIndex;
	DoEditItem();
}

void PreDefinedTypesPage::OnItemDeselected( wxListEvent& event )
{
	wxUnusedVar(event);
	m_selectedItem = wxNOT_FOUND;
}

void PreDefinedTypesPage::OnItemSelected( wxListEvent& event )
{
	m_selectedItem = event.m_itemIndex;
}

void PreDefinedTypesPage::OnNewShortcut( wxCommandEvent& event )
{
	wxUnusedVar(event);
	DbgCommandDlg *dlg = new DbgCommandDlg(this);
	if (dlg->ShowModal() == wxID_OK) {
		//add new command to the table
		wxString name       = dlg->GetName();
		wxString expression = dlg->GetExpression();
		wxString dbgCmd     = dlg->GetDbgCommand();
		long item;
		wxListItem info;

		//make sure that the expression does not exist
		int count = m_listCtrl1->GetItemCount();
		for(int i=0; i<count; i++) {
			wxString existingName = GetColumnText(m_listCtrl1, i, 0);
			if(name == existingName) {
				dlg->Destroy();
				wxMessageBox(_("Debugger type with the same name already exist"), wxT("CodeLite"), wxOK | wxICON_INFORMATION);
				return;
			}
		}

		// Set the item display name
		info.SetColumn(0);
		item = m_listCtrl1->InsertItem(info);

		SetColumnText(m_listCtrl1, item, 0, name       );
		SetColumnText(m_listCtrl1, item, 1, expression );
		SetColumnText(m_listCtrl1, item, 2, dbgCmd);

		m_listCtrl1->SetColumnWidth(0, 100);
		m_listCtrl1->SetColumnWidth(1, 200);
		m_listCtrl1->SetColumnWidth(1, 200);
	}
	dlg->Destroy();
}

void PreDefinedTypesPage::OnEditShortcut( wxCommandEvent& event )
{
	wxUnusedVar(event);
	DoEditItem();
}

void PreDefinedTypesPage::OnDeleteShortcut( wxCommandEvent& event )
{
	wxUnusedVar(event);
	DoDeleteItem();
}

void PreDefinedTypesPage::DoEditItem()
{
	//Edit the selection
	if (m_selectedItem == wxNOT_FOUND) {
		return;
	}

	//popup edit dialog
	DbgCommandDlg dlg(this);

	wxString name  = GetColumnText(m_listCtrl1, m_selectedItem, 0);
	wxString expr  = GetColumnText(m_listCtrl1, m_selectedItem, 1);
	wxString dbgCmd= GetColumnText(m_listCtrl1, m_selectedItem, 2);

	dlg.SetName(name);
	dlg.SetExpression(expr);
	dlg.SetDbgCommand(dbgCmd);

	if (dlg.ShowModal() == wxID_OK) {
		SetColumnText(m_listCtrl1, m_selectedItem, 0, dlg.GetName());
		SetColumnText(m_listCtrl1, m_selectedItem, 1, dlg.GetExpression());
		SetColumnText(m_listCtrl1, m_selectedItem, 2, dlg.GetDbgCommand());
	}
}

void PreDefinedTypesPage::DoDeleteItem()
{
	if (m_selectedItem == wxNOT_FOUND) {
		return;
	}
	m_listCtrl1->DeleteItem(m_selectedItem);
	m_selectedItem = wxNOT_FOUND;
}

DebuggerPreDefinedTypes PreDefinedTypesPage::GetPreDefinedTypes()
{
	int count = m_listCtrl1->GetItemCount();
	DebuggerCmdDataVec cmdArr;
	
	for(int i=0; i<count; i++) {
		DebuggerCmdData cmd;
		cmd.SetName      ( GetColumnText(m_listCtrl1, i, 0) );
		cmd.SetCommand   ( GetColumnText(m_listCtrl1, i, 1) );
		cmd.SetDbgCommand( GetColumnText(m_listCtrl1, i, 2) );
		cmdArr.push_back(cmd);
	}
	
	m_data.SetCmds(cmdArr);
	return m_data;
}
