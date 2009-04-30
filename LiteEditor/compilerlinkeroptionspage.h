#ifndef __compilerlinkeroptionspage__
#define __compilerlinkeroptionspage__

/**
@file
Subclass of CompilerLinkerOptionsBase, which is generated by wxFormBuilder.
*/

#include "compiler_pages.h"
#include "compiler.h"
#include "advanced_settings.h"
#include "compilercompileroptionspage.h" // for CompilerOptionDialog

/** Implementing CompilerCompilerOptionsBase */
class CompilerLinkerOptionsPage : public CompilerLinkerOptionsBase, public ICompilerSubPage
{
	wxString m_cmpname;
	long m_selectedLnkOption;
public:
	/** Constructor */
	CompilerLinkerOptionsPage( wxWindow* parent, const wxString &cmpname );
	virtual void Save(CompilerPtr cmp);

protected:
	// Virtual event handlers from wxFormBuilder base class
	virtual void OnLinkerOptionActivated( wxListEvent& event );
	virtual void OnLinkerOptionDeSelected( wxListEvent& event );
	virtual void OnLinkerOptionSelected( wxListEvent& event );
	virtual void OnNewLinkerOption( wxCommandEvent& event );
	virtual void OnDeleteLinkerOption( wxCommandEvent& event );
};

class CompilerLinkerOptionDialog : public CompilerOptionDialog
{
public:
	CompilerLinkerOptionDialog(wxWindow* parent, const wxString& name, const wxString& help)
	: CompilerOptionDialog(parent, wxT("Linker option"), name, help)
	{
	}
};

#endif // __compilerlinkeroptionspage__