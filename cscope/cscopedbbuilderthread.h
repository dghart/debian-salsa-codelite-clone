//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//
// copyright            : (C) 2008 by Eran Ifrah                            
// file name            : cscopedbbuilderthread.h              
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
 #ifndef __cscopedbbuilderthread__
#define __cscopedbbuilderthread__


#include "cscopeentrydata.h"
#include "singleton.h"
#include "worker_thread.h"
#include "wx/thread.h"
#include "wx/event.h"
#include <map>
#include <vector>

extern int wxEVT_CSCOPE_THREAD_DONE;
extern int wxEVT_CSCOPE_THREAD_UPDATE_STATUS;

typedef std::map<wxString, std::vector< CscopeEntryData >* > CscopeResultTable;

/**
 * \class CscopeRequest
 * \brief 
 * \author eran
 * \date 01/23/08
 */
class CscopeRequest : public ThreadRequest
{
	wxEvtHandler *m_owner;
	wxString m_cmd;
	wxString m_workingDir;
	wxString m_outfile;
	wxString m_endMsg;
	
public:
	CscopeRequest() {};
	~CscopeRequest() {};
	

//Setters
	void SetCmd(const wxString& cmd) {
		this->m_cmd = cmd;
	}
	void SetOutfile(const wxString& outfile) {
		this->m_outfile = outfile;
	}
	void SetOwner(wxEvtHandler* owner) {
		this->m_owner = owner;
	}
	
	void SetWorkingDir(const wxString& workingDir) {
		this->m_workingDir = workingDir;
	}
//Getters
	const wxString& GetCmd() const {
		return m_cmd;
	}
	const wxString& GetOutfile() const {
		return m_outfile;
	}
	wxEvtHandler* GetOwner() {
		return m_owner;
	}
	const wxString& GetWorkingDir() const {
		return m_workingDir;
	}
	
	void SetEndMsg(const wxString& endMsg) {this->m_endMsg = endMsg;}
	const wxString& GetEndMsg() const {return m_endMsg;}
};

class CscopeDbBuilderThread : public WorkerThread
{
	friend class Singleton< CscopeDbBuilderThread >;
protected:
	void ProcessRequest(ThreadRequest *req);
	CscopeResultTable* ParseResults(const wxArrayString &output);
	
protected:
	void SendStatusEvent(const wxString &msg, int percent, wxEvtHandler *owner);

public:
	CscopeDbBuilderThread();
	~CscopeDbBuilderThread();
};

typedef Singleton< CscopeDbBuilderThread > CScopeThreadST;
#endif // __cscopedbbuilderthread__