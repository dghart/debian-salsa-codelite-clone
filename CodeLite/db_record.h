//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//
// copyright            : (C) 2008 by Eran Ifrah                            
// file name            : db_record.h              
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
 #ifndef CODELITE_DB_RECORD_H
#define CODELITE_DB_RECORD_H

#include <wx/wxsqlite3.h>
#include "smart_ptr.h"

#ifdef WXMAKINGDLL_CODELITE
#    define WXDLLIMPEXP_CL WXEXPORT
#elif defined(WXUSINGDLL_CODELITE)
#    define WXDLLIMPEXP_CL WXIMPORT
#else /* not making nor using FNB as DLL */
#    define WXDLLIMPEXP_CL
#endif // WXMAKINGDLL_CODELITE

class TagsDatabase;

enum
{
	TagOk = 0,
	TagExist,
	TagError
};

/**
 * \ingroup CodeLite
 * \version 1.0
 * first version
 *
 * \date 09-21-2006
 *
 * \author Eran
 * Base class for any database record
 */
class WXDLLIMPEXP_CL DbRecord
{
public:
	DbRecord(){}
	virtual ~DbRecord(){}

public:
	/**
	 * Save this record into db.
	 * \param insertPreparedStmnt Prepared statement for insert operation
	 * \return TagOk, TagExist, TagError
	 */
	virtual int Store(wxSQLite3Statement& insertPreparedStmnt, TagsDatabase *db) = 0;

	/**
	 * Update this record into db.
	 * \param insertPreparedStmnt Prepared statement for insert operation
	 * \return TagOk, TagError
	 */
	virtual int Update(wxSQLite3Statement& updatePreparedStmnt) = 0;

	/**
	 * Delete this record from db.
	 * \param deletePreparedStmnt Prepared statement for delete operation
	 * \return TagOk, TagError
	 */
	virtual int Delete(wxSQLite3Statement& deletePreparedStmnt) = 0;

	/**
	 * \return delete preapred statement
	 */
	virtual wxString GetDeleteOneStatement() = 0;

	/**
	 * \return update preapred statement
	 */
	virtual wxString GetUpdateOneStatement() = 0;

	/**
	 * \return insert preapred statement
	 */
	virtual wxString GetInsertOneStatement() = 0;
};

typedef SmartPtr<DbRecord> DbRecordPtr;

#endif // CODELITE_DB_RECORD_H
