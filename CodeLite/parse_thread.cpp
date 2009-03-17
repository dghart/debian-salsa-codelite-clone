//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//
// copyright            : (C) 2008 by Eran Ifrah
// file name            : parse_thread.cpp
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
#include "precompiled_header.h"

#include "parse_thread.h"
#include "ctags_manager.h"
#include "tags_database.h"
#include <wx/stopwatch.h>

DEFINE_EVENT_TYPE(wxEVT_COMMAND_SYMBOL_TREE_UPDATE_ITEM)
DEFINE_EVENT_TYPE(wxEVT_COMMAND_SYMBOL_TREE_DELETE_ITEM)
DEFINE_EVENT_TYPE(wxEVT_COMMAND_SYMBOL_TREE_ADD_ITEM)
DEFINE_EVENT_TYPE(wxEVT_COMMAND_SYMBOL_TREE_DELETE_PROJECT)

const wxEventType wxEVT_PARSE_THREAD_UPDATED_FILE_SYMBOLS = wxNewId();

ParseThread::ParseThread()
		: WorkerThread()
		, m_pDb( new TagsDatabase() )
{
}

ParseThread::~ParseThread()
{
}

void ParseThread::ProcessRequest(ThreadRequest * request)
{
	// request is delete by the parent WorkerThread after this method is completed
	ParseRequest *req = (ParseRequest*)request;
	wxString dbfile  = req->getDbfile();
	wxString file  = req->getFile();

	// req->tags should contain the tags
	// convert the file to tags
	TagsManager *tagmgr = TagsManagerST::Get();

	//convert the file content into tags
	wxString tags;
	wxString file_name(req->getFile());
	tagmgr->SourceToTags(file_name, tags);

	req->setTags(tags);

	//----------------------------------------------
	// Build a tree from project/file/project
	// from the value which are set in the database
	//----------------------------------------------
	TagTreePtr oldTree;
	try {
		wxSQLite3ResultSet rs = m_pDb->SelectTagsByFile(file, wxFileName(dbfile));

		// Load the records and build a language tree
		TagEntry root;
		root.SetName(wxT("<ROOT>"));
		oldTree.Reset( new TagTree(wxT("<ROOT>"), root) );
		while ( rs.NextRow() ) {
			TagEntry entry(rs);
			oldTree->AddEntry(entry);
		}
		rs.Finalize();
	} catch (wxSQLite3Exception& e) {
		wxUnusedVar(e);
	}

	// Build second tree from the updated file
	TagTreePtr newTree;
	std::vector<DbRecordPtr> comments;

	TagsManager *mgr = TagsManagerST::Get();
	if (mgr->GetParseComments() ) {
		newTree = mgr->ParseSourceFile2(wxFileName(file), req->getTags(), &comments);
	} else {
		newTree = mgr->ParseSourceFile2(wxFileName(file), req->getTags());
	}

	//-------------------------------------------------------------------
	// Now what is left to be done here, is to update the GUI tree
	// The GUI tree needs to be updated item by item, to avoid total tree
	// Collapsing
	//-------------------------------------------------------------------


	// Compare old tree vs new tree
	std::vector<std::pair<wxString, TagEntry> >  deletedItems;
	std::vector<std::pair<wxString, TagEntry> >  newItems;
	std::vector<std::pair<wxString, TagEntry> >  goodNewItems;
	std::vector<std::pair<wxString, TagEntry> >  modifiedItems;

	oldTree->Compare(newTree.Get(), deletedItems, modifiedItems, newItems);
	// Delete old entries
	size_t i=0;


	m_pDb->Begin();

	// Prepare sql statements
	TagEntry dummy;
	if ( TagsManagerST::Get()->GetParseComments() ) {
		// drop all old entries from this file
		try {
			wxString sql;
			sql << wxT("DELETE FROM COMMENTS WHERE FILE='") << file << wxT("'");
			m_pDb->ExecuteUpdate( sql );
			m_pDb->Store( comments, wxFileName(), false );
		} catch ( wxSQLite3Exception & e) {
			wxUnusedVar(e);
		}
	}

	try {
		wxSQLite3Statement insertStmt = m_pDb->PrepareStatement( dummy.GetInsertOneStatement() );
		wxSQLite3Statement updateStmt = m_pDb->PrepareStatement( dummy.GetUpdateOneStatement() );
		wxSQLite3Statement deleteStmt = m_pDb->PrepareStatement( dummy.GetDeleteOneStatement() );

		for (i=0; i<deletedItems.size(); i++)
			deletedItems[i].second.Delete(deleteStmt);

		for (i=0; i<newItems.size(); i++) {
			if (newItems[i].second.Store(insertStmt, m_pDb.get()) == TagOk) {
				goodNewItems.push_back(newItems[i]);
			}
		}

		for (i=0; i<modifiedItems.size(); i++)
			modifiedItems[i].second.Update(updateStmt);

		///////////////////////////////////////////
		// update the file retag timestamp
		///////////////////////////////////////////

		std::vector<DbRecordPtr> entries;

		FileEntry *fe = new FileEntry();
		fe->SetFile(file);
		fe->SetLastRetaggedTimestamp((int)time(NULL));

		DbRecordPtr fep(fe);
		entries.push_back(fep);
		m_pDb->Store(entries, wxFileName(), false);

	} catch (wxSQLite3Exception &e) {
		wxUnusedVar(e);
	}

	m_pDb->Commit();


	// If there is no event handler set to handle this comaprison
	// results, then nothing more to be done
	if (m_notifiedWindow == NULL)
		return;

	// send "end" event
	wxCommandEvent e(wxEVT_PARSE_THREAD_UPDATED_FILE_SYMBOLS);
	wxPostEvent(m_notifiedWindow, e);

	// Send an event for each operation type
	if ( !deletedItems.empty() )
		SendEvent(wxEVT_COMMAND_SYMBOL_TREE_DELETE_ITEM, req->getFile(), deletedItems);

	if ( !newItems.empty() )
		SendEvent(wxEVT_COMMAND_SYMBOL_TREE_ADD_ITEM, req->getFile(), goodNewItems);

	if ( !modifiedItems.empty() ) {
		std::vector<std::pair<wxString, TagEntry> >  realModifiedItems;
		for (size_t i=0; i<modifiedItems.size(); i++) {
			std::pair<wxString, TagEntry> p = modifiedItems.at(i);
			if (!p.second.GetDifferOnByLineNumber()) {
				realModifiedItems.push_back(p);
			}
		}
		if (realModifiedItems.empty() == false) {
			SendEvent(wxEVT_COMMAND_SYMBOL_TREE_UPDATE_ITEM, req->getFile(), realModifiedItems);
		}
	}
}

void ParseThread::SendEvent(int evtType, const wxString &fileName, std::vector<std::pair<wxString, TagEntry> >  &items)
{
	SymbolTreeEvent event(items, evtType);
	event.SetFileName(fileName.c_str());
	wxPostEvent(m_notifiedWindow, event);
}

//--------------------------------------------------------------------------------------
// Parse Request Class
//--------------------------------------------------------------------------------------
void ParseRequest::setDbFile(const wxString& dbfile)
{
	_dbfile = dbfile.c_str();
}

void ParseRequest::setTags(const wxString& tags)
{
	_tags = tags.c_str();
}

ParseRequest::ParseRequest(const ParseRequest& rhs)
{
	if (this == &rhs) {
		return;
	}
	*this = rhs;
}

ParseRequest &ParseRequest::operator =(const ParseRequest& rhs)
{
	setFile(rhs._file);
	setDbFile(rhs._dbfile);
	setTags(rhs._tags);
	return *this;
}

void ParseRequest::setFile(const wxString& file)
{
	_file = file.c_str();
}

ParseRequest::~ParseRequest()
{
}
