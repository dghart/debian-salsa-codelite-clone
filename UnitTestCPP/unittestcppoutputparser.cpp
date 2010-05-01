//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//
// copyright            : (C) 2008 by Eran Ifrah
// file name            : unittestcppoutputparser.cpp
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


#include "unittestcppoutputparser.h"
#include <wx/regex.h>
#include "wx/log.h"

#include <wx/arrimpl.cpp> // this is a magic incantation which must be done!
WX_DEFINE_OBJARRAY(ErrorLineInfoArray);

UnitTestCppOutputParser::~UnitTestCppOutputParser()
{
}

UnitTestCppOutputParser::UnitTestCppOutputParser(const wxArrayString& output)
		: m_output(output)
{

}

void UnitTestCppOutputParser::Parse(TestSummary *summary)
{
// define the regexes
// group1: total number of tests
	static wxRegEx reSuccess(wxT("Success: ([0-9]*) tests passed"));

// main.cpp(82): error: Failure in Test4: false
// group1: file name
// group2: line number
	static wxRegEx reError(wxT("(^[a-zA-Z:]{0,2}[a-zA-Z\\.0-9_/\\+\\-]+)\\(([0-9]*)\\): error:"));

// failure summary line:
// FAILURE: 1 out of 6 tests failed (1 failures).
// group1: number of failures
// group2: total number of tests
	static wxRegEx reErrorSummary(wxT("FAILURE: ([0-9]*) out of ([0-9]*) tests failed"));

	for (size_t i=0; i<m_output.GetCount(); i++) {
		wxString line = m_output.Item(i);

		if (reSuccess.IsValid()) {
			// if the Summary line is in the format of: Success! ,,,
			// nothing is left to be checked
			if (reSuccess.Matches(m_output.Item(i))) {
				size_t len(0);
				size_t start(0);
				wxString match;

				reSuccess.GetMatch(&start, &len, 1);
				match = m_output.Item(i).Mid(start, len);
				match.ToLong((long*)&summary->totalTests);
				summary->errorCount = 0;
				summary->errorLines.Clear();
				return;
			}
		}

		// test for error line

		if (line.Contains(wxT(": error: Failure"))) {
			// increase the error count

			int where = line.Find(wxT(": error: Failure"));
			if ( where != wxNOT_FOUND ) {
				ErrorLineInfo info;

#if defined (__WXGTK__) || defined (__WXMSW__)
				// for some reason the output for Mac is different from the one
				// on Windows & GTK
				// main.cpp(82): error: Failure in Test4: false
				info.file = line.BeforeFirst(wxT('('));
				line = line.AfterFirst(wxT('('));

				info.line = line.BeforeFirst(wxT(')'));
				info.description = line.AfterFirst(wxT(')'));
#else
				// Mac output is:
				// main.cpp:82: error: Failure in Test4: false
				info.description = line.Mid((size_t)where);

				// remove the description
				line = line.Mid(0, (size_t)where);
				info.line = line.AfterLast(wxT(':'));
				info.file = line.BeforeLast(wxT(':'));
#endif
				summary->errorLines.Add(info);
				summary->errorCount++;
			}
		}

		// test for error summary line
		if (reErrorSummary.IsValid()) {
			if (reErrorSummary.Matches(m_output.Item(i))) {
				// increase the error count
				size_t len(0);
				size_t start(0);
				wxString match;

				reErrorSummary.GetMatch(&start, &len, 1);
				match = m_output.Item(i).Mid(start, len);
				match.ToLong((long*)&summary->errorCount);

				reErrorSummary.GetMatch(&start, &len, 2);
				match = m_output.Item(i).Mid(start, len);
				match.ToLong((long*)&summary->totalTests);
			}
		}
	}
}

//-----------------------------------------------------------------------------------

TestSummary::TestSummary()
		: errorCount(0)
		, totalTests(0)
{
	errorLines.Clear();
}

TestSummary::~TestSummary()
{
	errorLines.Clear();
}

void TestSummary::PrintSelf()
{
	wxPrintf(wxT("Total tests            : %d\n"), totalTests);
	wxPrintf(wxT("Total errors           : %d\n"), errorCount);
	wxPrintf(wxT("Total error lines found: %d\n"), errorLines.size());
}
