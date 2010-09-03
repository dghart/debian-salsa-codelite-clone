//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//
// copyright            : (C) 2009 by Eran Ifrah
// file name            : diff_dialog.h
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

#ifndef __diff_dialog__
#define __diff_dialog__

/**
@file
Subclass of DiffDialogBase, which is generated by wxFormBuilder.
*/

#include "subversion2_ui.h"

//// end generated include
class IManager;
/** Implementing DiffDialogBase */
class DiffDialog : public DiffDialogBase
{
protected:
	IManager *m_manager;

public:
	/** Constructor */
	DiffDialog( wxWindow* parent, IManager *manager );
	//// end generated class members

	virtual ~DiffDialog();
	wxString GetFromRevision() const;
	wxString GetToRevision() const;
};

#endif // __diff_dialog__
