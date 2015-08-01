//////////////////////////////////////////////////////////////////////
// This file was auto-generated by codelite's wxCrafter Plugin
// wxCrafter project file: qmaketabbase.wxcp
// Do not modify this file by hand!
//////////////////////////////////////////////////////////////////////

#ifndef CODELITE_QMAKEPLUGIN_QMAKETABBASE_BASE_CLASSES_H
#define CODELITE_QMAKEPLUGIN_QMAKETABBASE_BASE_CLASSES_H

#include <wx/settings.h>
#include <wx/xrc/xmlres.h>
#include <wx/xrc/xh_bmp.h>
#include <wx/panel.h>
#include <wx/artprov.h>
#include <wx/sizer.h>
#include <wx/checkbox.h>
#include <wx/stattext.h>
#include <wx/choice.h>
#include <wx/arrstr.h>
#include <wx/textctrl.h>
#if wxVERSION_NUMBER >= 2900
#include <wx/persist.h>
#include <wx/persist/toplevel.h>
#include <wx/persist/bookctrl.h>
#include <wx/persist/treebook.h>
#endif

class QMakeTabBase : public wxPanel
{
protected:
    wxCheckBox* m_checkBoxUseQmake;
    wxStaticText* m_staticText3;
    wxChoice* m_choiceQmakeSettings;
    wxStaticText* m_staticText4;
    wxTextCtrl* m_textCtrlQmakeExeLine;
    wxStaticText* m_staticText5;
    wxTextCtrl* m_textCtrlFreeText;

protected:
    virtual void OnUseQmake(wxUpdateUIEvent& event) { event.Skip(); }

public:
    wxCheckBox* GetCheckBoxUseQmake() { return m_checkBoxUseQmake; }
    wxStaticText* GetStaticText3() { return m_staticText3; }
    wxChoice* GetChoiceQmakeSettings() { return m_choiceQmakeSettings; }
    wxStaticText* GetStaticText4() { return m_staticText4; }
    wxTextCtrl* GetTextCtrlQmakeExeLine() { return m_textCtrlQmakeExeLine; }
    wxStaticText* GetStaticText5() { return m_staticText5; }
    wxTextCtrl* GetTextCtrlFreeText() { return m_textCtrlFreeText; }
    QMakeTabBase(wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize(-1,-1), long style = wxTAB_TRAVERSAL);
    virtual ~QMakeTabBase();
};

#endif
