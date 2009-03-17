//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//
// copyright            : (C) 2008 by Eran Ifrah                            
// file name            : importfilesdlg.cpp              
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
 #include "importfilessettings.h"
#include "importfilesdlg.h"
#include "editor_config.h"
#include "ctags_manager.h"
#include "wx/dir.h"

ImportFilesDlg::ImportFilesDlg( wxWindow* parent, const wxString &baseDir )
: ImportFilesBaseDlg( parent )
, m_baseDir(baseDir)
{
//read the data from the configuration file
	ImportFilesSettings options;
	if(!EditorConfigST::Get()->ReadObject(wxT("import_dir_options"), &options)){
		//first time, read the settings from the ctags options
		options.SetFileMask( TagsManagerST::Get()->GetCtagsOptions().GetFileSpec() );
		bool noExt = TagsManagerST::Get()->GetCtagsOptions().GetFlags() & CC_PARSE_EXT_LESS_FILES ? true : false;
		size_t flags(0);
		if(noExt){
			flags |= IFS_INCLUDE_FILES_WO_EXT;
		}
		options.SetFlags(flags);
	}
	
	m_textCtrlDirPath->SetValue(m_baseDir);
	m_textCtrlFileMask->SetValue( options.GetFileMask() );
	m_checkBoxNoExtFiles->SetValue( options.GetFlags() & IFS_INCLUDE_FILES_WO_EXT ? true : false );
	m_buttonBrowse->SetFocus();
	Centre();
}

void ImportFilesDlg::OnButtonCancel(wxCommandEvent &e)
{
	wxUnusedVar(e);
	EndModal(wxID_CANCEL);
}

void ImportFilesDlg::OnButtonOK(wxCommandEvent &e)
{
	wxUnusedVar(e);
	
	//validate that the input directory does exists
	if( !wxDir::Exists(m_textCtrlDirPath->GetValue()) ){
		wxMessageBox(_("'") + m_textCtrlDirPath->GetValue() + wxT("': No such directory"), wxT("CodeLite"), wxICON_WARNING|wxOK);
		return;
	}
	
	//save the current settings 
	ImportFilesSettings options;
	options.SetFileMask( m_textCtrlFileMask->GetValue() );
	size_t flags(0);
	if(m_checkBoxNoExtFiles->IsChecked()){
		flags |= IFS_INCLUDE_FILES_WO_EXT;
	}
	
	options.SetFlags(flags);
	EditorConfigST::Get()->WriteObject(wxT("import_dir_options"), &options);
	
	EndModal(wxID_OK);
}

void ImportFilesDlg::OnBrowse(wxCommandEvent& e)
{
	wxString path = wxDirSelector(wxT("Select a folder:"), m_baseDir);
	m_textCtrlDirPath->SetValue(path);
	
	if(path.IsEmpty() == false){
		m_baseDir = path;
	}
}
