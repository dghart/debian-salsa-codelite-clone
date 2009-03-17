//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//
// copyright            : (C) 2008 by Eran Ifrah                            
// file name            : quickwatchbasedlg.h              
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
// C++ code generated with wxFormBuilder (version Apr 16 2008)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __quickwatchbasedlg__
#define __quickwatchbasedlg__

#include <wx/string.h>
#include <wx/textctrl.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include "localvarstree.h"
#include <wx/sizer.h>
#include <wx/panel.h>
#include <wx/button.h>
#include <wx/dialog.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class QuickWatchBaseDlg
///////////////////////////////////////////////////////////////////////////////
class QuickWatchBaseDlg : public wxDialog 
{
	private:
	
	protected:
		wxPanel* m_panel1;
		wxTextCtrl* m_textCtrl1;
		LocalVarsTree *m_localVarsTree;
		wxButton* m_buttonEvaluate;
		wxButton* m_buttonClose;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnReEvaluate( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnButtonClose( wxCommandEvent& event ){ event.Skip(); }
		
	
	public:
		QuickWatchBaseDlg( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Quick Watch"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 524,419 ), long style = wxDEFAULT_DIALOG_STYLE );
		~QuickWatchBaseDlg();
	
};

#endif //__quickwatchbasedlg__
