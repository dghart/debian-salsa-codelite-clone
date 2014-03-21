//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//
// copyright            : (C) 2008 by Eran Ifrah                            
// file name            : threebuttondlg.h              
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
 #ifndef __threebuttondlg__
#define __threebuttondlg__

/**
@file
Subclass of ThreeButtonBaseDlg, which is generated by wxFormBuilder.
*/

#include "codelite_exports.h"
#include "threebuttonbasedlg.h"

/** Implementing ThreeButtonBaseDlg */
class WXDLLIMPEXP_SDK ThreeButtonDlg : public ThreeButtonBaseDlg
{
	
protected:
	void OnButtonYes(wxCommandEvent &e);
	void OnButtonNo(wxCommandEvent &e);
	void OnButtonCancel(wxCommandEvent &e);
	
public:
	/** Constructor */
	ThreeButtonDlg( wxWindow* parent, const wxString &msg, const wxString &caption );
	virtual ~ThreeButtonDlg();
	bool GetDontAskMeAgain() const {return m_checkBoxRememberMyAnwer->GetValue();}
};

#endif // __threebuttondlg__
