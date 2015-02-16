//////////////////////////////////////////////////////////////////////
// This file was auto-generated by codelite's wxCrafter Plugin
// wxCrafter project file: OpenWindowsPanelBase.wxcp
// Do not modify this file by hand!
//////////////////////////////////////////////////////////////////////

#ifndef OPENWINDOWSPANELBASE_BASE_CLASSES_H
#define OPENWINDOWSPANELBASE_BASE_CLASSES_H

#include <wx/settings.h>
#include <wx/xrc/xmlres.h>
#include <wx/xrc/xh_bmp.h>
#include <wx/panel.h>
#include <wx/artprov.h>
#include <wx/sizer.h>
#include <wx/pen.h>
#include <wx/aui/auibar.h>
#include <map>
#include <wx/menu.h>
#include <wx/toolbar.h>
#include <wx/dataview.h>

class OpenWindowsPanelBase : public wxPanel
{
protected:
    wxAuiToolBar* m_auibar;
    wxDataViewListCtrl* m_dvListCtrl;

protected:
    virtual void OnSortItems(wxCommandEvent& event) { event.Skip(); }
    virtual void OnSortItemsUpdateUI(wxUpdateUIEvent& event) { event.Skip(); }
    virtual void OnTabSelected(wxDataViewEvent& event) { event.Skip(); }
    virtual void OnTabActivated(wxDataViewEvent& event) { event.Skip(); }
    virtual void OnMenu(wxDataViewEvent& event) { event.Skip(); }

public:
    wxAuiToolBar* GetAuibar() { return m_auibar; }
    wxDataViewListCtrl* GetDvListCtrl() { return m_dvListCtrl; }
    OpenWindowsPanelBase(wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize(500,300), long style = wxWANTS_CHARS|wxTAB_TRAVERSAL);
    virtual ~OpenWindowsPanelBase();
};

#endif
