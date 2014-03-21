//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//
// copyright            : (C) 2013 by Eran Ifrah
// file name            : filechecklistbase.h
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

///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Nov 18 2010)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __filechecklistbase__
#define __filechecklistbase__

#include <wx/intl.h>

#include <wx/string.h>
#include <wx/stattext.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/statline.h>
#include <wx/checklst.h>
#include <wx/button.h>
#include <wx/sizer.h>
#include <wx/textctrl.h>
#include <wx/dialog.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class FileCheckListBase
///////////////////////////////////////////////////////////////////////////////
class FileCheckListBase : public wxDialog 
{
	private:
	
	protected:
		wxStaticText* m_caption;
		wxStaticLine* m_staticline2;
		wxCheckListBox* m_fileCheckList;
		wxButton* m_clearAll;
		wxButton* m_checkAllButton;
		wxTextCtrl* m_selectedFilePath;
		wxStaticLine* m_staticline1;
		wxButton* m_okButton;
		wxButton* m_cancelButton;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnFileSelected( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnFileCheckChanged( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnClearAll( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnCheckAll( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		FileCheckListBase( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Select Files"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( -1,-1 ), long style = wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER|wxSTAY_ON_TOP ); 
		~FileCheckListBase();
	
};

#endif //__filechecklistbase__
