#ifndef __debuggerasciiviewer__
#define __debuggerasciiviewer__

/**
@file
Subclass of DebuggerAsciiViewerBase, which is generated by wxFormBuilder.
*/

#include "debuggerasciiviewerbase.h"

class IDebugger;

/** Implementing DebuggerAsciiViewerBase */
class DebuggerAsciiViewer : public DebuggerAsciiViewerBase
{
	IDebugger *m_debugger;
	wxString   m_dbgCommand;
protected:
	// Handlers for DebuggerAsciiViewerBase events.
	void OnEnter( wxCommandEvent& event );
	void DoUpdateView();

public:
	/** Constructor */
	DebuggerAsciiViewer( wxWindow* parent     );
	void SetExpression (const wxString &expr  );
	void SetDebugger   (IDebugger *debugger   );
	void SetDbgCommand (const wxString &dbgCmd);
	void UpdateView();
};

#endif // __debuggerasciiviewer__