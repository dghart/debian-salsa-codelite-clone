//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//
// copyright            : (C) 2008 by Eran Ifrah                            
// file name            : newprojectbasedlg.h              
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

#ifndef __newprojectbasedlg__
#define __newprojectbasedlg__

#include <wx/string.h>
#include <wx/listbox.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/button.h>
#include <wx/sizer.h>
#include <wx/choice.h>
#include <wx/checkbox.h>
#include <wx/statbox.h>
#include <wx/statline.h>
#include <wx/dialog.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class NewProjectBaseDlg
///////////////////////////////////////////////////////////////////////////////
class NewProjectBaseDlg : public wxDialog 
{
	private:
	
	protected:
		wxListBox* m_projTypes;
		wxStaticText* m_staticText11;
		wxTextCtrl* m_textCtrlProjName;
		wxStaticText* m_staticText12;
		wxTextCtrl* m_textCtrlProjectPath;
		wxButton* m_buttonProjectDirPicker;
		wxStaticText* m_staticText14;
		wxChoice* m_choiceCompilerType;
		wxCheckBox* m_checkBoxCreateSeparateDir;
		wxStaticText* m_staticTextProjectFileFullPath;
		wxTextCtrl* m_textCtrlDescription;
		wxStaticLine* m_staticline4;
		wxButton* m_buttonCreateProject;
		wxButton* m_buttonCancel;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnItemSelected( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnProjectPathUpdated( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnProjectPathPicker( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnButtonCreate( wxCommandEvent& event ){ event.Skip(); }
		
	
	public:
		NewProjectBaseDlg( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("New Project"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 735,426 ), long style = wxDEFAULT_DIALOG_STYLE );
		~NewProjectBaseDlg();
	
};

#endif //__newprojectbasedlg__
