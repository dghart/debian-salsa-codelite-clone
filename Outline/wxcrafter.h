//////////////////////////////////////////////////////////////////////
// This file was auto-generated by codelite's wxCrafter Plugin
// wxCrafter project file: wxcrafter.wxcp
// Do not modify this file by hand!
//////////////////////////////////////////////////////////////////////

#ifndef WXCRAFTER_BASE_CLASSES_H
#define WXCRAFTER_BASE_CLASSES_H

#include <wx/settings.h>
#include <wx/xrc/xmlres.h>
#include <wx/xrc/xh_bmp.h>
#include <wx/panel.h>
#include <wx/artprov.h>
#include <wx/sizer.h>
#include <wx/textctrl.h>
#include <wx/simplebook.h>
#include <wx/imaglist.h>
#include <wx/treectrl.h>
#include "PHPOutlineTree.h"

class OutlineTabBaseClass : public wxPanel
{
protected:
    wxTextCtrl* m_textCtrlSearch;
    wxSimplebook* m_simpleBook;
    wxPanel* m_panelCxx;
    wxPanel* m_panelPhp;
    PHPOutlineTree* m_treeCtrlPhp;

protected:
    virtual void OnSearchSymbol(wxCommandEvent& event) { event.Skip(); }
    virtual void OnSearchEnter(wxCommandEvent& event) { event.Skip(); }
    virtual void OnPhpItemSelected(wxTreeEvent& event) { event.Skip(); }

public:
    wxTextCtrl* GetTextCtrlSearch() { return m_textCtrlSearch; }
    wxPanel* GetPanelCxx() { return m_panelCxx; }
    PHPOutlineTree* GetTreeCtrlPhp() { return m_treeCtrlPhp; }
    wxPanel* GetPanelPhp() { return m_panelPhp; }
    wxSimplebook* GetSimpleBook() { return m_simpleBook; }
    OutlineTabBaseClass(wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize(-1,-1), long style = wxTAB_TRAVERSAL);
    virtual ~OutlineTabBaseClass();
};

#endif
