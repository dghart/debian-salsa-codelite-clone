//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//
// copyright            : (C) 2008 by Eran Ifrah                            
// file name            : importfilesdlg.h              
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
 #ifndef __importfilesdlg__
#define __importfilesdlg__

/**
@file
Subclass of ImportFilesBaseDlg, which is generated by wxFormBuilder.
*/

#include "importfilesbasedlg.h"

/** Implementing ImportFilesBaseDlg */
class ImportFilesDlg : public ImportFilesBaseDlg
{
	wxString m_baseDir;
	
protected:
	void OnButtonCancel(wxCommandEvent &e);
	void OnButtonOK(wxCommandEvent &e);
	void OnBrowse(wxCommandEvent &e);
public:
	/** Constructor */
	ImportFilesDlg( wxWindow* parent, const wxString &baseDir );
	bool GetIncludeFilesWoExt() const {return m_checkBoxNoExtFiles->IsChecked();}
	wxString GetFileMask() const {return m_textCtrlFileMask->GetValue();}
	wxString GetBaseDir() const {return m_textCtrlDirPath->GetValue();}
};

#endif // __importfilesdlg__