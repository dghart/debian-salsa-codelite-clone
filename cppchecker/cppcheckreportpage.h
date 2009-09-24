#ifndef __cppcheckreportpage__
#define __cppcheckreportpage__

/**
@file
Subclass of CppCheckReportBasePage, which is generated by wxFormBuilder.
*/

#include "cppcheckreportbasepage.h"
#include <vector>
#include <map>

extern const wxEventType wxEVT_CPPCHECK_ASK_STOP;

class IManager;
class CppCheckPlugin;

/**
 * cppcheck result
 */
struct CppCheckResult
{
	wxString id;
	wxString filename;
	long     lineno;
	wxString severity;
	wxString msg;
};

typedef std::vector<CppCheckResult> CppCheckFileResults;

typedef std::map<wxString, CppCheckFileResults> CppCheckResults;

/** Implementing CppCheckReportBasePage */
class CppCheckReportPage : public CppCheckReportBasePage
{
	IManager*       m_mgr;
	CppCheckPlugin* m_plugin;
	CppCheckResults m_results;

protected:
	// Handlers for CppCheckReportBasePage events.

	void OnListCtrlItemActivated( wxListEvent& event );
	void OnClearReport          ( wxCommandEvent& event );
	void OnStopChecking         ( wxCommandEvent& event );
	void OnStopCheckingUI       (wxUpdateUIEvent &event);
	void OnClearReportUI        (wxUpdateUIEvent &event);
	void OnSkipFile             ( wxCommandEvent& event );
	void OnSkipFileUI           (wxUpdateUIEvent &event);
protected:
	void DoClearReport          ();

public:
	/** Constructor */
	CppCheckReportPage(wxWindow* parent, IManager* mgr, CppCheckPlugin* plugin);

	void AddResults   (const CppCheckResults* results);
	void SetStatus    (const wxString& status);
	void FileSelected ( const wxString &filename );
	void Clear        ();
};

#endif // __cppcheckreportpage__