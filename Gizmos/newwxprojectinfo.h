//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//
// copyright            : (C) 2008 by Eran Ifrah                            
// file name            : newwxprojectinfo.h              
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
 #ifndef __newwxprojectinfo__
#define __newwxprojectinfo__

#include "wx/string.h"

//wxWidgets settings
enum {
	wxWidgetsSetMWindows = 0x00000001,
	wxWidgetsUnicode  = 0x00000002
};

//Project types
enum {
	wxProjectTypeGUI = 0,
	wxProjectTypeSimpleMain
};

class NewWxProjectInfo {
	
	wxString m_name;
	wxString m_path;
	size_t m_flags;
	int m_type;
	
public:
	NewWxProjectInfo();
	~NewWxProjectInfo();
	
	//Setters
	void SetFlags(const size_t& flags) {this->m_flags = flags;}
	void SetName(const wxString& name) {this->m_name = name;}
	void SetPath(const wxString& path) {this->m_path = path;}
	void SetType(const int& type) {this->m_type = type;}
	
	//Getters
	const size_t& GetFlags() const {return m_flags;}
	const wxString& GetName() const {return m_name;}
	const wxString& GetPath() const {return m_path;}
	const int& GetType() const {return m_type;}
	
};
#endif // __newwxprojectinfo__
