///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Sep  8 2010)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __debuggersettingsbasedlg__
#define __debuggersettingsbasedlg__

#include <wx/gdicmn.h>
#include <wx/treebook.h>
#include <wx/notebook.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/string.h>
#include <wx/statline.h>
#include <wx/button.h>
#include <wx/sizer.h>
#include <wx/dialog.h>
#include <wx/textctrl.h>
#include <wx/panel.h>
#include <wx/listctrl.h>
#include <wx/stattext.h>
#include <wx/choice.h>
#include <wx/checkbox.h>
#include <wx/statbox.h>
#include <wx/spinctrl.h>
#include <wx/choicebk.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class DebuggerSettingsBaseDlg
///////////////////////////////////////////////////////////////////////////////
class DebuggerSettingsBaseDlg : public wxDialog
{
	private:

	protected:
		wxTreebook* m_notebook2;
		wxStaticLine* m_staticline1;
		wxButton* m_buttonOK;
		wxButton* m_buttonCancel;

		// Virtual event handlers, overide them in your derived class
		virtual void OnButtonCancel( wxCommandEvent& event ) { event.Skip(); }


	public:

		DebuggerSettingsBaseDlg( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Debugger Settings"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( -1,-1 ), long style = wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER );
		~DebuggerSettingsBaseDlg();

};

///////////////////////////////////////////////////////////////////////////////
/// Class DbgPageStartupCmdsBase
///////////////////////////////////////////////////////////////////////////////
class DbgPageStartupCmdsBase : public wxPanel
{
	private:

	protected:
		wxTextCtrl* m_textCtrlStartupCommands;

	public:

		DbgPageStartupCmdsBase( wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( -1,-1 ), long style = wxTAB_TRAVERSAL );
		~DbgPageStartupCmdsBase();

};

///////////////////////////////////////////////////////////////////////////////
/// Class PreDefinedTypesPageBase
///////////////////////////////////////////////////////////////////////////////
class PreDefinedTypesPageBase : public wxPanel
{
	private:

	protected:
		wxPanel* m_panel2;
		wxListCtrl* m_listCtrl1;
		wxButton* m_buttonNewType;
		wxButton* m_buttonEdit;
		wxButton* m_buttonDelete;

		// Virtual event handlers, overide them in your derived class
		virtual void OnItemActivated( wxListEvent& event ) { event.Skip(); }
		virtual void OnItemDeselected( wxListEvent& event ) { event.Skip(); }
		virtual void OnItemSelected( wxListEvent& event ) { event.Skip(); }
		virtual void OnNewShortcut( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnEditShortcut( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnDeleteShortcut( wxCommandEvent& event ) { event.Skip(); }


	public:

		PreDefinedTypesPageBase( wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( -1,-1 ), long style = wxTAB_TRAVERSAL );
		~PreDefinedTypesPageBase();

};

///////////////////////////////////////////////////////////////////////////////
/// Class NewPreDefinedSetDlg
///////////////////////////////////////////////////////////////////////////////
class NewPreDefinedSetDlg : public wxDialog
{
	private:

	protected:
		wxStaticText* m_staticText3;
		wxStaticText* m_staticText4;


		wxStaticLine* m_staticline2;
		wxButton* m_button9;
		wxButton* m_button10;

	public:
		wxTextCtrl* m_textCtrlName;
		wxChoice* m_choiceCopyFrom;
		wxCheckBox* m_checkBoxMakeActive;

		NewPreDefinedSetDlg( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Create a new 'PreDefined Types' set..."), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER );
		~NewPreDefinedSetDlg();

};

///////////////////////////////////////////////////////////////////////////////
/// Class DbgPageGeneralBase
///////////////////////////////////////////////////////////////////////////////
class DbgPageGeneralBase : public wxPanel
{
	private:

	protected:
		wxPanel* m_panel6;
		wxStaticText* m_staticText1;
		wxTextCtrl* m_textCtrDbgPath;
		wxButton* m_buttonBrowse;
		wxCheckBox* m_checkBreakAtWinMain;
		wxCheckBox* m_catchThrow;
		wxCheckBox* m_checkBoxSetBreakpointsAfterMain;
		wxCheckBox* m_checkBoxEnablePendingBreakpoints;
		wxCheckBox* m_showTooltips;
		wxCheckBox* m_checkBoxAutoExpand;
		wxStaticText* m_staticText2;
		wxSpinCtrl* m_spinCtrlNumElements;
		wxCheckBox* m_checkBoxExpandLocals;


		// Virtual event handlers, overide them in your derived class
		virtual void OnBrowse( wxCommandEvent& event ) { event.Skip(); }


	public:

		DbgPageGeneralBase( wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( -1,-1 ), long style = wxTAB_TRAVERSAL );
		~DbgPageGeneralBase();

};

///////////////////////////////////////////////////////////////////////////////
/// Class DbgPageMiscBase
///////////////////////////////////////////////////////////////////////////////
class DbgPageMiscBase : public wxPanel
{
	private:

	protected:
		wxPanel* m_panel7;
		wxCheckBox* m_checkBoxEnableLog;
		wxCheckBox* m_checkShowTerminal;
		wxCheckBox* m_checkUseRelativePaths;
		wxCheckBox* m_checkBoxDebugAssert;
		wxStaticText* m_staticText5;
		wxTextCtrl* m_textCtrlCygwinPathCommand;

		// Virtual event handlers, overide them in your derived class
		virtual void OnDebugAssert( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnWindowsUI( wxUpdateUIEvent& event ) { event.Skip(); }


	public:

		DbgPageMiscBase( wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( -1,-1 ), long style = wxTAB_TRAVERSAL );
		~DbgPageMiscBase();

};

///////////////////////////////////////////////////////////////////////////////
/// Class DbgPagePreDefTypesBase
///////////////////////////////////////////////////////////////////////////////
class DbgPagePreDefTypesBase : public wxPanel
{
	private:

	protected:
		wxPanel* m_panel6;
		wxButton* m_buttonNewSet;
		wxButton* m_buttonDeleteSet;
		wxChoicebook* m_notebookPreDefTypes;

		// Virtual event handlers, overide them in your derived class
		virtual void OnNewSet( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnDeleteSet( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnDeleteSetUI( wxUpdateUIEvent& event ) { event.Skip(); }
		virtual void OnPageChanged( wxChoicebookEvent& event ) { event.Skip(); }


	public:

		DbgPagePreDefTypesBase( wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( -1,-1 ), long style = wxTAB_TRAVERSAL );
		~DbgPagePreDefTypesBase();

};

#endif //__debuggersettingsbasedlg__
