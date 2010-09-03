//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//
// copyright            : (C) 2008 by Eran Ifrah
// file name            : renamesymboldlg.h
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
 #ifndef __renamesymboldlg__
#define __renamesymboldlg__


/**
@file
Subclass of RenameSymbolBase, which is generated by wxFormBuilder.
*/

#include "cpptoken.h"
#include "renamesymbolbase.h"
#include <list>
#include <vector>

/** Implementing RenameSymbolBase */
class RenameSymbol : public RenameSymbolBase
{
	std::vector<CppToken> m_tokens;

protected:
	void OnButtonOK    (wxCommandEvent &e);
	void AddMatch      (const CppToken &token, bool check);
	void DoSelectFile  (const CppToken &token);
	void OnItemSelected( wxListEvent& event );
public:
	/** Constructor */
	RenameSymbol( wxWindow* parent, const std::list<CppToken>& candidates, const std::list<CppToken> &possCandidates, const wxString& oldname = wxT("") );
	void GetMatches(std::list<CppToken>& matches);
	wxString GetWord() const { return m_textCtrlNewName->GetValue(); }
};

#endif // __renamesymboldlg__
