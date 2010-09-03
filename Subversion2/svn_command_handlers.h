//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//
// copyright            : (C) 2009 by Eran Ifrah
// file name            : svn_command_handlers.h
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

#ifndef SVNCOMMITHANDLER_H
#define SVNCOMMITHANDLER_H

#include "svn_default_command_handler.h" // Base class

//----------------------------------------------------
// Commit Handler
//----------------------------------------------------

class SvnCommitHandler : public SvnDefaultCommandHandler {
public:
	SvnCommitHandler(Subversion2 *plugin, int commandId, wxEvtHandler *owner) : SvnDefaultCommandHandler(plugin, commandId, owner) {};
	virtual ~SvnCommitHandler(){};

public:
	virtual void Process(const wxString &output);
};

//----------------------------------------------------
// Update Handler
//----------------------------------------------------

class SvnUpdateHandler : public SvnDefaultCommandHandler {

public:
	SvnUpdateHandler(Subversion2 *plugin, int commandId, wxEvtHandler *owner) : SvnDefaultCommandHandler(plugin, commandId, owner) {};
	virtual ~SvnUpdateHandler(){};

public:
	virtual void Process(const wxString &output);
};

//----------------------------------------------------
// Diff Handler
//----------------------------------------------------

class SvnDiffHandler : public SvnDefaultCommandHandler {

public:
	SvnDiffHandler(Subversion2 *plugin, int commandId, wxEvtHandler *owner) : SvnDefaultCommandHandler(plugin, commandId, owner) {};
	virtual ~SvnDiffHandler(){};

public:
	virtual void Process(const wxString &output);
};

//----------------------------------------------------
// Patch Handler
//----------------------------------------------------

class SvnPatchHandler : public SvnDefaultCommandHandler {

public:
	SvnPatchHandler(Subversion2 *plugin, int commandId, wxEvtHandler *owner) : SvnDefaultCommandHandler(plugin, commandId, owner) {};
	virtual ~SvnPatchHandler(){};

public:
	virtual void Process(const wxString &output);
};

//----------------------------------------------------
// Dry-Run Patch Handler
//----------------------------------------------------

class SvnPatchDryRunHandler : public SvnDefaultCommandHandler {

public:
	SvnPatchDryRunHandler(Subversion2 *plugin, int commandId, wxEvtHandler *owner) : SvnDefaultCommandHandler(plugin, commandId, owner) {};
	virtual ~SvnPatchDryRunHandler(){};

public:
	virtual void Process(const wxString &output);
};

//----------------------------------------------------
//Svn version handler
//----------------------------------------------------

class SvnVersionHandler : public SvnDefaultCommandHandler {

public:
	SvnVersionHandler(Subversion2 *plugin, int commandId, wxEvtHandler *owner) : SvnDefaultCommandHandler(plugin, commandId, owner) {};
	virtual ~SvnVersionHandler(){};

public:
	virtual void Process(const wxString &output);
};

//----------------------------------------------------
//Svn Log handler
//----------------------------------------------------

class SvnLogHandler : public SvnDefaultCommandHandler {
	bool     m_compact;
	wxString m_url;

protected:
	wxString Compact(const wxString &message);
public:
	SvnLogHandler(Subversion2 *plugin, const wxString &url, bool compact, int commandId, wxEvtHandler *owner)
	: SvnDefaultCommandHandler(plugin, commandId, owner)
	, m_compact(compact)
	, m_url(url)
	{}

	virtual ~SvnLogHandler(){}

public:
	virtual void Process(const wxString &output);
};

//----------------------------------------------------
// Svn Checkout handler
//----------------------------------------------------

class SvnCheckoutHandler : public SvnDefaultCommandHandler {
public:
	SvnCheckoutHandler(Subversion2 *plugin, int commandId, wxEvtHandler *owner) : SvnDefaultCommandHandler(plugin, commandId, owner){};
	virtual ~SvnCheckoutHandler(){};

public:
	virtual void Process(const wxString &output);
};

//----------------------------------------------------
// Svn blame handler
//----------------------------------------------------

class SvnBlameHandler : public SvnCommandHandler {
public:
	SvnBlameHandler(Subversion2 *plugin, int commandId, wxEvtHandler *owner) : SvnCommandHandler(plugin, commandId, owner){};
	virtual ~SvnBlameHandler(){};

public:
	virtual void Process(const wxString &output);
};

#endif // SVNCOMMITHANDLER_H
