//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//
// copyright            : (C) 2008 by Eran Ifrah
// file name            : svnhandler.cpp
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
#include "svnhandler.h"
#include "async_executable_cmd.h"
#include "svndriver.h"
#include "wx/tokenzr.h"
#include <wx/regex.h>
#include "subversion.h"
#include "svnxmlparser.h"

void SvnDefaultCmdHandler::ProcessEvent(wxCommandEvent &event)
{
	wxString text(event.GetString());
	if (event.GetEventType() == wxEVT_ASYNC_PROC_STARTED) {
		text = wxEmptyString;
	} else if (event.GetEventType() == wxEVT_ASYNC_PROC_ENDED) {
		text = wxT("----\n");
	}

	text = text.Trim();
	text = text.Trim(false);

	if (text != wxT(".")) {
		if (m_needLf) {
			m_needLf = false;
			//previous text entered was '.'
			//so we probably will need a new Line Feed
			text.Prepend(wxT("\n"));
		}
		text << wxT("\n");
	} else {
		m_needLf = true;
	}

	if (m_postCmd) {
		m_postCmd->AddText(text);
	}

	m_svnDriver->PrintMessage(text);
	if (IsVerificationNeeded(text)) {
		wxString message, answer;
		message << wxT("SVN: Error validating server certificate\n")
		<< wxT("You can choose to accept the server certification permanently by clicking 'Yes',\n")
		<< wxT("Or you can reject it by clicking 'No'");
		int res = wxMessageBox(message, wxT("Accept Server Certification?"), wxYES_NO | wxICON_QUESTION | wxCANCEL);
		if (res == wxYES) {
			answer = wxT("p");
		} else if (res == wxNO) {
			answer = wxT("R");
		} else {
			answer = wxEmptyString;
		}

		if (answer.IsEmpty() == false) {
			m_svnDriver->Svn()->GetProcess()->Write(answer + wxT("\n"));
		}
	}

	if ( IsConflictWasFound(text) ) {
		// Conflict was detected during update, postpone it
		m_svnDriver->Svn()->GetProcess()->Write(wxT("p\n"));
		m_svnDriver->SetConflictFound(true);
	}

#ifdef __WXMSW__
	if (IsAuthFailed(text)) {
		m_svnDriver->PrintMessage(wxT("Authentication requires\nplease wait for the login dialog ...\n"));
		m_svnDriver->SetCommitWithPassword(true);
		m_svnDriver->Svn()->GetProcess()->Terminate();
	}
#else
	if (IsAuthFailed(text)) {
		wxString password = wxGetPasswordFromUser(wxT("SVN Password:"), wxT("Password:"));
		if (password.IsEmpty() == false) {
			m_svnDriver->Svn()->GetProcess()->Write(password + wxT("\n"));
		}
	}

	if (IsUsernameRequired(text)) {
		wxString username = wxGetTextFromUser(wxT("SVN Username:"), wxT("Username:"));
		if (username.IsEmpty() == false) {
			m_svnDriver->Svn()->GetProcess()->Write(username + wxT("\n"));
		}
	}

#endif
}

bool SvnDefaultCmdHandler::IsUsernameRequired(wxString text)
{
	if (text.MakeLower().Contains(wxT("username:"))) {
		return true;
	}
	return false;
}

bool SvnDefaultCmdHandler::IsAuthFailed(wxString text)
{
#ifdef __WXMSW__
	if (text.MakeLower().Contains(wxT("authentication realm:"))) {
		return true;
	}
	return false;
#else
	if (text.MakeLower().Contains(wxT("password for '"))) {
		return true;
	}
	return false;
#endif
}

bool SvnDefaultCmdHandler::IsVerificationNeeded(wxString text)
{
	if (text.MakeLower().Contains(wxT("(r)eject, accept (t)emporarily or accept (p)ermanently"))) {
		return true;
	}
	return false;
}

void SvnCommitCmdHandler::ProcessEvent(wxCommandEvent &e)
{
	//call default handling
	SvnDefaultCmdHandler::ProcessEvent(e);
}


void SvnDiffCmdHandler::ProcessEvent(wxCommandEvent &event)
{
	wxString text(event.GetString());
	if (event.GetEventType() == wxEVT_ASYNC_PROC_STARTED) {
		text = wxT("----\n");
	} else if (event.GetEventType() == wxEVT_ASYNC_PROC_ENDED) {
		text = wxT("----\n");
	}

	if (event.GetEventType() == wxEVT_ASYNC_PROC_ADDLINE) {
		m_content << text;
		// diff format is whitespace-sensitive.  do not trim or alter.
		//m_content = m_content.Trim().Trim(false);
		//m_content << wxT("\n");
	} else {
		if (!text.IsEmpty()) {
			m_svnDriver->PrintMessage(text);
		}
		if (event.GetEventType() == wxEVT_ASYNC_PROC_ENDED) {
			//Create a diff file and open it in the editor
			m_svnDriver->DisplayDiffFile(m_fileName, m_content);
		}
	}
}

void SvnChangeLogCmdHandler::ProcessEvent(wxCommandEvent &event)
{
	wxString text(event.GetString());
	if (event.GetEventType() == wxEVT_ASYNC_PROC_STARTED) {
		text = wxT("----\n");
	} else if (event.GetEventType() == wxEVT_ASYNC_PROC_ENDED) {
		text = wxT("----\n");
	}

	if (event.GetEventType() == wxEVT_ASYNC_PROC_ADDLINE) {

		// filter non interesting lines
		if ( m_flags & SvnChangeLog_Compact ) {
			if (text.StartsWith(wxT("------------------------------------------------------------------------"))) {
				// skip this line
				return;
			}
		}

		if ( m_flags & SvnChangeLog_Compact ) {
			wxRegEx re(wxT("r[0-9]+ \\|"));
			if (re.Matches(text)) {
				// skip this line as well
				return;
			}
		}

		text = text.Trim().Trim(false);
		if ( m_flags & SvnChangeLog_Compact ) {
			if (text.IsEmpty() || text == wxT("\"")) {
				return;
			}
		}

		m_content << text;
		m_content = m_content.Trim().Trim(false);
		m_content << wxT("\n");

	} else {

		m_svnDriver->PrintMessage(text);
		if (event.GetEventType() == wxEVT_ASYNC_PROC_ENDED) {
			//Create a diff file and open it in the editor
			m_svnDriver->DisplayLog(m_outputFile, m_content);
		}

	}
}

bool SvnDefaultCmdHandler::IsConflictWasFound(wxString text)
{
	if( text.MakeLower().Contains(wxT("conflict discovered in ")) ) {
		return true;
	} else {
		return false;
	}
}
