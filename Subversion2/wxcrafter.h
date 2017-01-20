//////////////////////////////////////////////////////////////////////
// This file was auto-generated by codelite's wxCrafter Plugin
// wxCrafter project file: wxcrafter.wxcp
// Do not modify this file by hand!
//////////////////////////////////////////////////////////////////////

#ifndef CODELITE_SUBVERSION2_WXCRAFTER_BASE_CLASSES_H
#define CODELITE_SUBVERSION2_WXCRAFTER_BASE_CLASSES_H

#include <wx/settings.h>
#include <wx/xrc/xmlres.h>
#include <wx/xrc/xh_bmp.h>
#include <wx/dialog.h>
#include <wx/iconbndl.h>
#include <wx/artprov.h>
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/splitter.h>
#include <wx/panel.h>
#include <wx/checklst.h>
#include <wx/stc/stc.h>
#include <wx/pen.h>
#include <wx/aui/auibar.h>
#include <map>
#include <wx/menu.h>
#include <wx/toolbar.h>
#include <wx/button.h>
#include <wx/filepicker.h>
#include <wx/checkbox.h>
#if wxVERSION_NUMBER >= 2900
#include <wx/persist.h>
#include <wx/persist/toplevel.h>
#include <wx/persist/bookctrl.h>
#include <wx/persist/treebook.h>
#endif

#ifdef WXC_FROM_DIP
#undef WXC_FROM_DIP
#endif
#if wxVERSION_NUMBER >= 3100
#define WXC_FROM_DIP(x) wxWindow::FromDIP(x, NULL)
#else
#define WXC_FROM_DIP(x) x
#endif


class SvnCommitDialogBaseClass : public wxDialog
{
public:
    enum {
        ID_SHOW_COMMIT_HISTORY = 9001,
        ID_TOOL_CLEAR_HISTORY = 9002,
    };
protected:
    wxStaticText* m_staticText32;
    wxTextCtrl* m_textCtrlFrID;
    wxStaticText* m_staticTextBugID;
    wxTextCtrl* m_textCtrlBugID;
    wxSplitterWindow* m_splitterV;
    wxPanel* m_splitterPage52;
    wxSplitterWindow* m_splitterH;
    wxPanel* m_panel1;
    wxStaticText* m_staticText17;
    wxCheckListBox* m_checkListFiles;
    wxPanel* m_splitterPage14;
    wxStaticText* m_staticText19;
    wxStyledTextCtrl* m_stcDiff;
    wxPanel* m_splitterPage56;
    wxAuiToolBar* m_auibar76;
    wxStyledTextCtrl* m_stcMessage;
    wxButton* m_button88;
    wxButton* m_button90;

protected:
    virtual void OnFileSelected(wxCommandEvent& event) { event.Skip(); }
    virtual void OnShowCommitHistory(wxCommandEvent& event) { event.Skip(); }
    virtual void OnShowCommitHistoryUI(wxUpdateUIEvent& event) { event.Skip(); }
    virtual void OnClearHistory(wxCommandEvent& event) { event.Skip(); }
    virtual void OnClearHistoryUI(wxUpdateUIEvent& event) { event.Skip(); }

public:
    wxStaticText* GetStaticText32() { return m_staticText32; }
    wxTextCtrl* GetTextCtrlFrID() { return m_textCtrlFrID; }
    wxStaticText* GetStaticTextBugID() { return m_staticTextBugID; }
    wxTextCtrl* GetTextCtrlBugID() { return m_textCtrlBugID; }
    wxStaticText* GetStaticText17() { return m_staticText17; }
    wxCheckListBox* GetCheckListFiles() { return m_checkListFiles; }
    wxPanel* GetPanel1() { return m_panel1; }
    wxStaticText* GetStaticText19() { return m_staticText19; }
    wxStyledTextCtrl* GetStcDiff() { return m_stcDiff; }
    wxPanel* GetSplitterPage14() { return m_splitterPage14; }
    wxSplitterWindow* GetSplitterH() { return m_splitterH; }
    wxPanel* GetSplitterPage52() { return m_splitterPage52; }
    wxAuiToolBar* GetAuibar76() { return m_auibar76; }
    wxStyledTextCtrl* GetStcMessage() { return m_stcMessage; }
    wxPanel* GetSplitterPage56() { return m_splitterPage56; }
    wxSplitterWindow* GetSplitterV() { return m_splitterV; }
    wxButton* GetButton88() { return m_button88; }
    wxButton* GetButton90() { return m_button90; }
    SvnCommitDialogBaseClass(wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Svn Commit"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize(-1,-1), long style = wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER);
    virtual ~SvnCommitDialogBaseClass();
};


class SvnSyncDialogBaseClass : public wxDialog
{
protected:
    wxStaticText* m_staticText31;
    wxStaticText* m_staticTextSvnInfo;
    wxStaticText* m_staticText34;
    wxDirPickerCtrl* m_dirPickerRootDir;
    wxStaticText* m_staticText40;
    wxTextCtrl* m_textCtrlExclude;
    wxCheckBox* m_checkBoxBin;
    wxButton* m_button28;
    wxButton* m_button29;

protected:
    virtual void OnOkUI(wxUpdateUIEvent& event) { event.Skip(); }
    virtual void OnButtonOK(wxCommandEvent& event) { event.Skip(); }

public:
    wxStaticText* GetStaticText31() { return m_staticText31; }
    wxStaticText* GetStaticTextSvnInfo() { return m_staticTextSvnInfo; }
    wxStaticText* GetStaticText34() { return m_staticText34; }
    wxDirPickerCtrl* GetDirPickerRootDir() { return m_dirPickerRootDir; }
    wxStaticText* GetStaticText40() { return m_staticText40; }
    wxTextCtrl* GetTextCtrlExclude() { return m_textCtrlExclude; }
    wxCheckBox* GetCheckBoxBin() { return m_checkBoxBin; }
    wxButton* GetButton28() { return m_button28; }
    wxButton* GetButton29() { return m_button29; }
    SvnSyncDialogBaseClass(wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Sync Workspace to SVN"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize(-1,-1), long style = wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER);
    virtual ~SvnSyncDialogBaseClass();
};

#endif
