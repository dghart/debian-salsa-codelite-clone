//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//
// copyright            : (C) 2010 by Eran Ifrah
// file name            : tabgroupmanager.cpp
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

#include <wx/xml/xml.h>
#include <wx/filename.h>
#include <wx/dir.h>
#include <wx/stdpaths.h>

#include "manager.h"
#include "xmlutils.h"
#include "wx_xml_compatibility.h"
#include "tabgroupmanager.h"

TabgroupManager::~TabgroupManager()
{
	m_tabgroups.clear();
}

vTabGrps& TabgroupManager::GetTabgroups()
{
	if (m_tabgroups.empty()) {
		LoadKnownTabgroups();	// Of course there might just not *be* any, but safer to try loading
	}
	return m_tabgroups;
}

bool TabgroupManager::FindTabgroup(const wxString& tabgroupname, wxArrayString& items)
{
	items.Empty();
	vTabGrps::const_iterator iter = m_tabgroups.begin();
	for (; iter != m_tabgroups.end(); ++iter) {
		if (iter->first == tabgroupname) {
			items = iter->second;
			return true;
		}
	}
	return false;
}

wxString TabgroupManager::GetTabgroupDirectory()
{
	if (m_tabgroupdir.IsEmpty()) {
		SetTabgroupDirectory();
	}
	return m_tabgroupdir;
}

void TabgroupManager::SetTabgroupDirectory()
{
	wxFileName TabgrpPath = wxFileName::DirName(WorkspaceST::Get()->GetPrivateFolder() + wxT("/tabgroups/"));
	if (!TabgrpPath.DirExists()) {
		TabgrpPath.Mkdir(0777, wxPATH_MKDIR_FULL);
	}
	m_tabgroupdir = TabgrpPath.GetPath();
}

void TabgroupManager::LoadKnownTabgroups()
{
	wxArrayString Tabgrpfiles;
	// Load tabgroups from the tabgroup dir
	wxDir::GetAllFiles ( GetTabgroupDirectory(), &Tabgrpfiles, wxT("*.tabgroup"), wxDIR_FILES );
	for (size_t n=0; n < Tabgrpfiles.GetCount(); ++n) {
		LoadTabgroupData(Tabgrpfiles.Item(n));
	}
}

void TabgroupManager::LoadTabgroupData(const wxString& tabgroup)
{
	// 'tabgroup' is the filepath of the tabgroup to load
	if (tabgroup.IsEmpty()) {
		return;
	}

	// Load the data: we're only interested in the tab names here, not each CurrentLine etc
	TabGroupEntry session;
	wxString filepath = tabgroup.BeforeLast(wxT('.')); // FindSession() doesn't want the .ext here
	if (SessionManager::Get().GetSession(filepath, session, "tabgroup", tabgroupTag) ) {
		wxArrayString tabnames;
		const std::vector<TabInfo> &vTabInfoArr = session.GetTabInfoArr();
		for (size_t i = 0; i < vTabInfoArr.size(); ++i) {
			const TabInfo &ti = vTabInfoArr[i];
			tabnames.Add(ti.GetFileName());
		}
		std::pair<wxString,wxArrayString> TabgroupItem(tabgroup, tabnames);
		m_tabgroups.push_back(TabgroupItem);
	}
}

bool TabgroupManager::DoAddItemToTabgroup(wxXmlDocument& doc, wxXmlNode* node, const wxString& filepath, const wxString& nextitemfilepath)
{
	wxXmlNode* TabInfoArrayNode = XmlUtils::FindFirstByTagName(doc.GetRoot(), wxT("TabInfoArray"));
	if (!TabInfoArrayNode) {
		return false;
	}

	// If previousnode is valid, insert the new tab after it
	wxXmlNode* previousnode = NULL;
	if (!nextitemfilepath.IsEmpty()) {
		previousnode = FindTabgroupItem(doc, filepath, nextitemfilepath);
	}
	if (previousnode) {
#if wxVERSION_NUMBER >= 2808
		return TabInfoArrayNode->InsertChildAfter(node, previousnode); // >=2.8.8 has a convenient function to do this
#else
		wxXmlNode* nextnode = previousnode->GetNext();
		if (nextnode) {
			return TabInfoArrayNode->InsertChild(node, nextnode);
		} else {
			TabInfoArrayNode->AddChild(node);
			return true;
		}
#endif
	} else {
		TabInfoArrayNode->AddChild(node);
	}

return true;
}


wxXmlNode* TabgroupManager::FindTabgroupItem(wxXmlDocument& doc, const wxString& filepath, const wxString& itemfilepath)
{
	wxXmlNode* TabInfoArrayNode = XmlUtils::FindFirstByTagName(doc.GetRoot(), wxT("TabInfoArray"));
	if (TabInfoArrayNode) {
		wxXmlNode* TabInfoNode = TabInfoArrayNode->GetChildren();
		while (TabInfoNode) {
			wxXmlNode* child = XmlUtils::FindFirstByTagName(TabInfoNode, wxT("wxString"));
			if (child && child->GetPropVal(wxT("Value"), wxEmptyString) == itemfilepath) {
				// Found it. Return the data in TabInfoNode
				return TabInfoNode;
			}
			TabInfoNode = TabInfoNode->GetNext();
		}
	}
	// The Find failed, so return null
	return NULL;
}

wxXmlNode* TabgroupManager::DoDeleteTabgroupItem(wxXmlDocument& doc, const wxString& filepath, const wxString& itemfilepath)
{
	wxXmlNode* TabInfoArrayNode = XmlUtils::FindFirstByTagName(doc.GetRoot(), wxT("TabInfoArray"));
	if (TabInfoArrayNode) {
		wxXmlNode* TabInfoNode = TabInfoArrayNode->GetChildren();
		while (TabInfoNode) {
			wxXmlNode* child = XmlUtils::FindFirstByTagName(TabInfoNode, wxT("wxString"));
			if (child && child->GetPropVal(wxT("Value"), wxEmptyString) == itemfilepath) {
				TabInfoArrayNode->RemoveChild(TabInfoNode);
				doc.Save(filepath);
				return TabInfoNode;
			}
			TabInfoNode = TabInfoNode->GetNext();
		}
	}

	return NULL;
}

