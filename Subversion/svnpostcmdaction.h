//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//
// copyright            : (C) 2008 by Eran Ifrah
// file name            : svnpostcmdaction.h
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
#ifndef __svnpostcmdaction__
#define __svnpostcmdaction__

#include <wx/arrstr.h>

class SvnPostCmdAction
{
protected:
	wxArrayString m_text;
	wxString m_file;
	
public:
	SvnPostCmdAction();
	virtual ~SvnPostCmdAction();

	virtual void DoCommand() = 0;
	virtual void AddText(const wxString &text){m_text.Add(text);}
	virtual void SetFile(const wxString &file){m_file = file.c_str();}
};
#endif // __svnpostcmdaction__
