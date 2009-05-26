// main wxWidgets header file
#include <wx/wx.h>

int main( int argc, char** argv )
{
	// initialize wxWidgets
	wxInitializer init;
	
	wxPrintf( wxT("Hello in wxWidgets World!\n\n") );
	
	// print some system info...
	wxPuts(wxGetHomeDir());
	wxPuts(wxGetOsDescription());
	wxPuts(wxGetUserName());
	wxPuts(wxGetFullHostName());

	long mem = wxGetFreeMemory().ToLong();
	wxPrintf(wxT("Memory: %ld\n"), mem);

	return 0;
}
