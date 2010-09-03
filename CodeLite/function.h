//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//
// copyright            : (C) 2009 by Eran Ifrah
// file name            : function.h
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

#ifndef FUNCTION_H
#define FUNCTION_H

#include "string"
#include "list"
#include "variable.h"
#include <stdio.h>

class clFunction
{
public:
	std::string     m_name;
	std::string     m_scope;					//functions' scope
	std::string     m_retrunValusConst;			// is the return value a const?
	std::string     m_signature;
	Variable        m_returnValue;
	int             m_lineno;
	bool            m_isVirtual;
	bool            m_isPureVirtual;
	bool            m_isConst;

public:
	clFunction();
	virtual ~clFunction();

	//clear the class content
	void Reset();

	//print the variable to stdout
	void Print();
};

typedef std::list<clFunction> FunctionList;
#endif //FUNCTION_H
