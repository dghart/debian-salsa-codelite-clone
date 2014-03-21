//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//
// copyright            : (C) 2013 by Eran Ifrah
// file name            : editorsettingsfoldingbase.h
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
// C++ code generated with wxFormBuilder (version Mar 22 2011)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __editorsettingsfoldingbase__
#define __editorsettingsfoldingbase__

#include <wx/intl.h>

#include <wx/string.h>
#include <wx/checkbox.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/stattext.h>
#include <wx/choice.h>
#include <wx/sizer.h>
#include <wx/statbox.h>
#include <wx/panel.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class EditorSettingsFoldingBase
///////////////////////////////////////////////////////////////////////////////
class EditorSettingsFoldingBase : public wxPanel 
{
	private:
	
	protected:
		wxCheckBox* m_displayMargin;
		wxCheckBox* m_underlineFolded;
		wxCheckBox* m_foldElse;
		wxCheckBox* m_foldPreprocessors;
		wxCheckBox* m_foldCompact;
		wxStaticText* m_staticText2;
		wxChoice* m_foldStyle;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnFoldingMarginUI( wxUpdateUIEvent& event ) { event.Skip(); }
		
	
	public:
		
		EditorSettingsFoldingBase( wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( -1,-1 ), long style = wxTAB_TRAVERSAL ); 
		~EditorSettingsFoldingBase();
	
};

#endif //__editorsettingsfoldingbase__
