#include "includepathlocator.h"
#include <wx/dir.h>
#include <wx/utils.h>
#include "procutils.h"
#include <wx/fileconf.h>
#include "editor_config.h"

// Helper method
static wxArrayString ExecCommand(const wxString &cmd)
{
	wxArrayString outputArr;
#ifdef __WXMSW__	
	ProcUtils::SafeExecuteCommand(cmd, outputArr);
#else
	wxArrayString o, e;
	wxExecute(cmd, o, e);
	outputArr = o;
	for(size_t i=0; i<e.size(); i++)
		outputArr.Add(e.Item(i));
	
#endif
	return outputArr;
}

IncludePathLocator::IncludePathLocator(IManager *mgr)
		: m_mgr(mgr)
{
}

IncludePathLocator::~IncludePathLocator()
{
}

void IncludePathLocator::Locate(wxArrayString& paths, wxArrayString &excludePaths)
{
	// Common compiler paths - should be placed at top of the include path!
	wxString tmpfile = wxFileName::CreateTempFileName(wxT("codelite"));
	wxString command;
	
#ifdef __WXMAC__
	// Mac does not like the standard command
	command = wxString::Format(wxT("cpp -v -x=c++ %s"), tmpfile.c_str());
#else
	command = wxString::Format(wxT("cpp -x c++ -v %s"), tmpfile.c_str());
#endif

	wxArrayString outputArr = ExecCommand( command );
	wxRemoveFile( tmpfile );
	
	// Analyze the output
	bool collect(false);
	for(size_t i=0; i<outputArr.GetCount(); i++) {
		if(outputArr[i].Contains(wxT("#include <...> search starts here:"))) {
			collect = true;
			continue;
		}

		if(outputArr[i].Contains(wxT("End of search list."))) {
			break;
		}

		if(collect) {
			
			wxString file = outputArr.Item(i).Trim().Trim(false);
			
			// on Mac, (framework directory) appears also, 
			// but it is harmless to use it under all OSs
			file.Replace(wxT("(framework directory)"), wxT(""));
			file.Trim().Trim(false);
			
			wxFileName includePath(file, wxT(""));
			includePath.Normalize();

			paths.Add( includePath.GetPath() );
		}
	}

	// try to locate QMAKE
	wxFileConfig  qmakeConf(wxEmptyString, wxEmptyString, m_mgr->GetStartupDirectory() + wxT("/config/qmake.ini"));
	wxString      groupName;
	long          index(0);
	wxArrayString out;
	wxString      qmake(wxT("qmake"));

	if (qmakeConf.GetFirstGroup(groupName, index)) {
		// we got qmake configuration, use it instead of the default qmake command
		qmake = qmakeConf.Read(groupName + wxT("/qmake"));
	}

	// Run: qmake -query QT_INSTALL_PREFIX
	wxString cmd;
	cmd << qmake << wxT(" -query QT_INSTALL_PREFIX");
	out = ExecCommand(cmd);

	if (out.IsEmpty() == false ) {

		wxString qt_output (out.Item(0));
		qt_output.Trim().Trim(false);

#if defined(__WXGTK__)||defined(__WXMAC__)
		wxString pathQt4, pathQt3, pathQt;
		pathQt4 << qt_output << wxFileName::GetPathSeparator() << wxT("include") << wxFileName::GetPathSeparator() << wxT("qt4");
		pathQt3 << qt_output << wxFileName::GetPathSeparator() << wxT("include") << wxFileName::GetPathSeparator() << wxT("qt3");
		pathQt  << qt_output << wxFileName::GetPathSeparator() << wxT("include");

		if (wxDir::Exists( pathQt4 )) {
			wxString tmpPath;

			tmpPath = pathQt4 + wxT("/QtCore");
			if(wxFileName::DirExists(tmpPath))
				paths.Add( tmpPath );

			tmpPath = pathQt4 + wxT("/QtGui");
			if(wxFileName::DirExists(tmpPath))
				paths.Add( tmpPath );

			tmpPath = pathQt4 + wxT("/QtXml");
			if(wxFileName::DirExists(tmpPath))
				paths.Add( tmpPath );

		} else if (wxDir::Exists( pathQt3 ) ) {

			wxString tmpPath;

			tmpPath = pathQt3 + wxT("/QtCore");
			if(wxFileName::DirExists(tmpPath))
				paths.Add( tmpPath );

			tmpPath = pathQt3 + wxT("/QtGui");
			if(wxFileName::DirExists(tmpPath))
				paths.Add( tmpPath );

			tmpPath = pathQt3 + wxT("/QtXml");
			if(wxFileName::DirExists(tmpPath))
				paths.Add( tmpPath );

		} else if (wxDir::Exists( pathQt ) ) {

			wxString tmpPath;

			tmpPath = pathQt + wxT("/QtCore");
			if(wxFileName::DirExists(tmpPath))
				paths.Add( tmpPath );

			tmpPath = pathQt + wxT("/QtGui");
			if(wxFileName::DirExists(tmpPath))
				paths.Add( pathQt );

			tmpPath = pathQt + wxT("/QtXml");
			if(wxFileName::DirExists(tmpPath))
				paths.Add( tmpPath );
		}

#else // __WXMSW__
		wxString pathWin;
		pathWin << qt_output << wxFileName::GetPathSeparator() << wxT("include") << wxFileName::GetPathSeparator();
		if (wxDir::Exists( pathWin )) {

			wxString tmpPath;

			tmpPath = pathWin + wxT("QtCore");
			if(wxFileName::DirExists(tmpPath)){
				wxFileName fn(tmpPath, wxT(""));
				paths.Add( fn.GetPath() );
			}

			tmpPath = pathWin + wxT("QtGui");
			if(wxFileName::DirExists(tmpPath)) {
				wxFileName fn(tmpPath, wxT(""));
				paths.Add( fn.GetPath() );
			}

			tmpPath = pathWin + wxT("QtXml");
			if(wxFileName::DirExists(tmpPath)) {
				wxFileName fn(tmpPath, wxT(""));
				paths.Add( fn.GetPath() );
			}
		}
#endif
	}

	// Try wxWidgets
#ifdef __WXMSW__
	// On Windows, just read the content of the WXWIN environment variable
	wxString wxwin;
	if (wxGetEnv(wxT("WX_INCL_HOME"), &wxwin)) {
		// we got the path to the installation of wxWidgets
		if (wxDir::Exists(wxwin)) {
			paths.Add( wxwin );
			excludePaths.Add( wxwin + wxT("\\univ") );
			excludePaths.Add( wxwin + wxT("\\unix") );
		}
	}
#else
	// run wx-config and parse the output
	out.Clear();
	out = ExecCommand(wxT("wx-config --cxxflags"));
	if (out.IsEmpty() == false) {
		wxString line ( out.Item(0) );
		int where = line.Find(wxT(" -I"));
		while (where != wxNOT_FOUND) {
			line = line.Mid(where + 3);
			paths.Add( line.BeforeFirst(wxT(' ')) );

			where = line.Find(wxT(" -I"));
		}
	}
#endif
}

