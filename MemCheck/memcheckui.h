//////////////////////////////////////////////////////////////////////
// This file was auto-generated by codelite's wxCrafter Plugin
// wxCrafter project file: memcheckui.wxcp
// Do not modify this file by hand!
//////////////////////////////////////////////////////////////////////

#ifndef _CODELITE_MEMCHECK_MEMCHECKUI_BASE_CLASSES_H
#define _CODELITE_MEMCHECK_MEMCHECKUI_BASE_CLASSES_H

#include <wx/settings.h>
#include <wx/xrc/xmlres.h>
#include <wx/xrc/xh_bmp.h>
#include <wx/imaglist.h>
#include <wx/bitmap.h>
#include <wx/artprov.h>
#include <map>
#include <wx/icon.h>
#include <wx/panel.h>
#include <wx/sizer.h>
#include <wx/pen.h>
#include <wx/aui/auibar.h>
#include <wx/menu.h>
#include <wx/toolbar.h>
#include <wx/notebook.h>
#include <wx/dataview.h>
#include "memcheckdvcerrorsmodel.h"
#include <wx/bmpbuttn.h>
#include <wx/textctrl.h>
#include <wx/stattext.h>
#include <wx/splitter.h>
#include <wx/choice.h>
#include <wx/arrstr.h>
#include <wx/button.h>
#include <wx/srchctrl.h>
#include <wx/checkbox.h>
#include <wx/listctrl.h>
#include "memchecklistctrlerrors.h"
#include <wx/dialog.h>
#include <wx/iconbndl.h>
#include <wx/treebook.h>
#include <wx/slider.h>
#include <wx/filepicker.h>
#include <wx/statbox.h>
#include <wx/listbox.h>
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


class MemCheckIcons16 : public wxImageList
{
protected:
    // Maintain a map of all bitmaps representd by their name
    std::map<wxString, wxBitmap> m_bitmaps;
    // The requested image resolution (can be one of @2x, @1.5x, @1.25x or an empty string (the default)
    wxString m_resolution;
    int m_imagesWidth;
    int m_imagesHeight;


protected:

public:
    MemCheckIcons16();
    const wxBitmap& Bitmap(const wxString &name) const {
        if ( !m_bitmaps.count(name + m_resolution) )
            return wxNullBitmap;
        return m_bitmaps.find(name + m_resolution)->second;
    }

    void SetBitmapResolution(const wxString &res = wxEmptyString) {
        m_resolution = res;
    }

    virtual ~MemCheckIcons16();
};


class MemCheckIcons24 : public wxImageList
{
protected:
    // Maintain a map of all bitmaps representd by their name
    std::map<wxString, wxBitmap> m_bitmaps;
    // The requested image resolution (can be one of @2x, @1.5x, @1.25x or an empty string (the default)
    wxString m_resolution;
    int m_imagesWidth;
    int m_imagesHeight;


protected:

public:
    MemCheckIcons24();
    const wxBitmap& Bitmap(const wxString &name) const {
        if ( !m_bitmaps.count(name + m_resolution) )
            return wxNullBitmap;
        return m_bitmaps.find(name + m_resolution)->second;
    }

    void SetBitmapResolution(const wxString &res = wxEmptyString) {
        m_resolution = res;
    }

    virtual ~MemCheckIcons24();
};


class MemCheckOutputViewBase : public wxPanel
{
public:
    enum {
        ID_TOOL_STOP_PROCESS = 8001,
    };
protected:
    wxAuiToolBar* m_auibar223;
    wxNotebook* m_notebookOutputView;
    wxPanel* m_panelErrors;
    wxDataViewCtrl* m_dataViewCtrlErrors;
    wxObjectDataPtr<MemCheckDVCErrorsModel> m_dataViewCtrlErrorsModel;

    wxBitmapButton* m_bmpButtonPageFirst;
    wxBitmapButton* m_bmpButtonPagePrev;
    wxTextCtrl* m_textCtrlPageNumber;
    wxStaticText* m_staticText622;
    wxStaticText* m_staticTextPageMax;
    wxBitmapButton* m_bmpButtonPageNext;
    wxBitmapButton* m_bmpButtonPageLast;
    wxPanel* m_panelSupp;
    wxSplitterWindow* m_splitter542;
    wxPanel* m_splitterPageFilter;
    wxStaticText* m_staticText657;
    wxChoice* m_choiceSuppFile;
    wxButton* m_buttonSuppOpen;
    wxSearchCtrl* m_searchCtrlFilter;
    wxBitmapButton* m_buttonClearFilter;
    wxCheckBox* m_checkBoxInvert;
    wxCheckBox* m_checkBoxCase;
    wxCheckBox* m_checkBoxWord;
    wxCheckBox* m_checkBoxRegexp;
    wxStaticText* m_staticTextSuppStatus;
    wxPanel* m_splitterPageList;
    MemCheckListCtrlErrors* m_listCtrlErrors;
    wxButton* m_buttonSuppressAll;
    wxButton* m_buttonSuppressSelected;

protected:
    virtual void OnStop(wxCommandEvent& event) { event.Skip(); }
    virtual void OnStopUI(wxUpdateUIEvent& event) { event.Skip(); }
    virtual void OnExpandAll(wxCommandEvent& event) { event.Skip(); }
    virtual void OnMemCheckUI(wxUpdateUIEvent& event) { event.Skip(); }
    virtual void OnJumpToNext(wxCommandEvent& event) { event.Skip(); }
    virtual void OnJumpToPrev(wxCommandEvent& event) { event.Skip(); }
    virtual void OnClearOutput(wxCommandEvent& event) { event.Skip(); }
    virtual void OnClearOutputUpdateUI(wxUpdateUIEvent& event) { event.Skip(); }
    virtual void OnOpenPlain(wxCommandEvent& event) { event.Skip(); }
    virtual void OutputViewPageChanged(wxNotebookEvent& event) { event.Skip(); }
    virtual void OnActivated(wxDataViewEvent& event) { event.Skip(); }
    virtual void OnValueChanged(wxDataViewEvent& event) { event.Skip(); }
    virtual void OnContextMenu(wxDataViewEvent& event) { event.Skip(); }
    virtual void OnSelectionChanged(wxDataViewEvent& event) { event.Skip(); }
    virtual void OnPageFirst(wxCommandEvent& event) { event.Skip(); }
    virtual void OnErrorsPanelUI(wxUpdateUIEvent& event) { event.Skip(); }
    virtual void OnPagePrev(wxCommandEvent& event) { event.Skip(); }
    virtual void OnPageSelect(wxCommandEvent& event) { event.Skip(); }
    virtual void OnPageNext(wxCommandEvent& event) { event.Skip(); }
    virtual void OnPageLast(wxCommandEvent& event) { event.Skip(); }
    virtual void OnSuppFileSelected(wxCommandEvent& event) { event.Skip(); }
    virtual void OnSuppPanelUI(wxUpdateUIEvent& event) { event.Skip(); }
    virtual void OnSuppFileOpen(wxCommandEvent& event) { event.Skip(); }
    virtual void OnFilterErrors(wxCommandEvent& event) { event.Skip(); }
    virtual void OnClearFilter(wxCommandEvent& event) { event.Skip(); }
    virtual void OnListCtrlErrorsResize(wxSizeEvent& event) { event.Skip(); }
    virtual void OnListCtrlErrorsMouseMotion(wxMouseEvent& event) { event.Skip(); }
    virtual void OnListCtrlErrorsActivated(wxListEvent& event) { event.Skip(); }
    virtual void OnListCtrlErrorsSelected(wxListEvent& event) { event.Skip(); }
    virtual void OnListCtrlErrorsDeselected(wxListEvent& event) { event.Skip(); }
    virtual void OnListCtrlErrorsKeyDown(wxKeyEvent& event) { event.Skip(); }
    virtual void OnListCtrlErrorsKeyUp(wxKeyEvent& event) { event.Skip(); }
    virtual void OnListCtrlErrorsChar(wxKeyEvent& event) { event.Skip(); }
    virtual void OnListCtrlErrorsLeftDown(wxMouseEvent& event) { event.Skip(); }
    virtual void OnListCtrlErrorsLeftUp(wxMouseEvent& event) { event.Skip(); }
    virtual void OnListCtrlErrorsMouseLeave(wxMouseEvent& event) { event.Skip(); }
    virtual void OnSuppressAll(wxCommandEvent& event) { event.Skip(); }
    virtual void OnSuppressSelected(wxCommandEvent& event) { event.Skip(); }

public:
    wxAuiToolBar* GetAuibar223() { return m_auibar223; }
    wxDataViewCtrl* GetDataViewCtrlErrors() { return m_dataViewCtrlErrors; }
    wxBitmapButton* GetBmpButtonPageFirst() { return m_bmpButtonPageFirst; }
    wxBitmapButton* GetBmpButtonPagePrev() { return m_bmpButtonPagePrev; }
    wxTextCtrl* GetTextCtrlPageNumber() { return m_textCtrlPageNumber; }
    wxStaticText* GetStaticText622() { return m_staticText622; }
    wxStaticText* GetStaticTextPageMax() { return m_staticTextPageMax; }
    wxBitmapButton* GetBmpButtonPageNext() { return m_bmpButtonPageNext; }
    wxBitmapButton* GetBmpButtonPageLast() { return m_bmpButtonPageLast; }
    wxPanel* GetPanelErrors() { return m_panelErrors; }
    wxStaticText* GetStaticText657() { return m_staticText657; }
    wxChoice* GetChoiceSuppFile() { return m_choiceSuppFile; }
    wxButton* GetButtonSuppOpen() { return m_buttonSuppOpen; }
    wxSearchCtrl* GetSearchCtrlFilter() { return m_searchCtrlFilter; }
    wxBitmapButton* GetButtonClearFilter() { return m_buttonClearFilter; }
    wxCheckBox* GetCheckBoxInvert() { return m_checkBoxInvert; }
    wxCheckBox* GetCheckBoxCase() { return m_checkBoxCase; }
    wxCheckBox* GetCheckBoxWord() { return m_checkBoxWord; }
    wxCheckBox* GetCheckBoxRegexp() { return m_checkBoxRegexp; }
    wxStaticText* GetStaticTextSuppStatus() { return m_staticTextSuppStatus; }
    wxPanel* GetSplitterPageFilter() { return m_splitterPageFilter; }
    MemCheckListCtrlErrors* GetListCtrlErrors() { return m_listCtrlErrors; }
    wxButton* GetButtonSuppressAll() { return m_buttonSuppressAll; }
    wxButton* GetButtonSuppressSelected() { return m_buttonSuppressSelected; }
    wxPanel* GetSplitterPageList() { return m_splitterPageList; }
    wxSplitterWindow* GetSplitter542() { return m_splitter542; }
    wxPanel* GetPanelSupp() { return m_panelSupp; }
    wxNotebook* GetNotebookOutputView() { return m_notebookOutputView; }
    MemCheckOutputViewBase(wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize(-1,-1), long style = wxTAB_TRAVERSAL);
    virtual ~MemCheckOutputViewBase();
};


class MemCheckSettingsDialogBase : public wxDialog
{
protected:
    wxTreebook* m_treebook251;
    wxPanel* m_panel259;
    wxStaticText* m_staticText349;
    wxChoice* m_choiceEngine;
    wxStaticText* m_staticText638;
    wxSlider* m_sliderPageCapacity;
    wxCheckBox* m_checkBoxOmitNonWorkspace;
    wxCheckBox* m_checkBoxOmitDuplications;
    wxCheckBox* m_checkBoxOmitSuppressed;
    wxCheckBox* m_checkBoxOmitSuppressionsUnchanged;
    wxPanel* m_panel263;
    wxPanel* m_panel669;
    wxStaticText* m_staticText271;
    wxFilePickerCtrl* m_filePickerValgrindBinary;
    wxStaticText* m_staticText333;
    wxTextCtrl* m_textCtrlValgrindMandatoryOptions;
    wxStaticText* m_staticText337;
    wxTextCtrl* m_textCtrlValgrindOptions;
    wxBitmapButton* m_bmpButton341;
    wxCheckBox* m_checkBoxOutputInPrivateFolder;
    wxFilePickerCtrl* m_filePickerValgrindOutputFile;
    wxPanel* m_panel671;
    wxCheckBox* m_checkBoxSuppFileInPrivateFolder;
    wxListBox* m_listBoxSuppFiles;
    wxStdDialogButtonSizer* m_stdBtnSizer511;
    wxButton* m_button513;
    wxButton* m_button515;

protected:
    virtual void ValgrindResetOptions(wxCommandEvent& event) { event.Skip(); }
    virtual void OnValgrindOutputFileChanged(wxFileDirPickerEvent& event) { event.Skip(); }
    virtual void OnFilePickerValgrindOutputFileUI(wxUpdateUIEvent& event) { event.Skip(); }
    virtual void OnSuppListRightDown(wxMouseEvent& event) { event.Skip(); }
    virtual void OnOK(wxCommandEvent& event) { event.Skip(); }

public:
    wxStaticText* GetStaticText349() { return m_staticText349; }
    wxChoice* GetChoiceEngine() { return m_choiceEngine; }
    wxStaticText* GetStaticText638() { return m_staticText638; }
    wxSlider* GetSliderPageCapacity() { return m_sliderPageCapacity; }
    wxCheckBox* GetCheckBoxOmitNonWorkspace() { return m_checkBoxOmitNonWorkspace; }
    wxCheckBox* GetCheckBoxOmitDuplications() { return m_checkBoxOmitDuplications; }
    wxCheckBox* GetCheckBoxOmitSuppressed() { return m_checkBoxOmitSuppressed; }
    wxCheckBox* GetCheckBoxOmitSuppressionsUnchanged() { return m_checkBoxOmitSuppressionsUnchanged; }
    wxPanel* GetPanel259() { return m_panel259; }
    wxStaticText* GetStaticText271() { return m_staticText271; }
    wxFilePickerCtrl* GetFilePickerValgrindBinary() { return m_filePickerValgrindBinary; }
    wxStaticText* GetStaticText333() { return m_staticText333; }
    wxTextCtrl* GetTextCtrlValgrindMandatoryOptions() { return m_textCtrlValgrindMandatoryOptions; }
    wxStaticText* GetStaticText337() { return m_staticText337; }
    wxTextCtrl* GetTextCtrlValgrindOptions() { return m_textCtrlValgrindOptions; }
    wxBitmapButton* GetBmpButton341() { return m_bmpButton341; }
    wxCheckBox* GetCheckBoxOutputInPrivateFolder() { return m_checkBoxOutputInPrivateFolder; }
    wxFilePickerCtrl* GetFilePickerValgrindOutputFile() { return m_filePickerValgrindOutputFile; }
    wxPanel* GetPanel669() { return m_panel669; }
    wxCheckBox* GetCheckBoxSuppFileInPrivateFolder() { return m_checkBoxSuppFileInPrivateFolder; }
    wxListBox* GetListBoxSuppFiles() { return m_listBoxSuppFiles; }
    wxPanel* GetPanel671() { return m_panel671; }
    wxPanel* GetPanel263() { return m_panel263; }
    wxTreebook* GetTreebook251() { return m_treebook251; }
    MemCheckSettingsDialogBase(wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("MemCheck Settings"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize(-1,-1), long style = wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER);
    virtual ~MemCheckSettingsDialogBase();
};

#endif
