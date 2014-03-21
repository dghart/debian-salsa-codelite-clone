//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//
// copyright            : (C) 2013 by Eran Ifrah
// file name            : ps_compiler_page.h
//
// -------------------------------------------------------------------------
// A
//              _____           _      _     _ _
//             /  __ \         | |    | |   (_) |
//             | /  \/ ___   __| | ___| |    _| |_ ___
//             | |    / _ \ / _  |/ _ \ |   | | __/ _ )
//             | \__/\ (_) | (_| |  __/ |___| | ||  __/
//              \____/\___/ \__,_|\___\_____/_|\__\___|
//
//                                                  F i l e
//
//    This program is free software; you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation; either version 2 of the License, or
//    (at your option) any later version.
//
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

#ifndef __ps_compiler_page__
#define __ps_compiler_page__

/**
@file
Subclass of PSCompilerPageBase, which is generated by wxFormBuilder.
*/

#include "project_settings_base_dlg.h"
#include "project_settings_dlg.h"
#include "build_config.h"

//// end generated include
class ProjectSettingsDlg;
class PSGeneralPage;

/** Implementing PSCompilerPageBase */
class PSCompilerPage : public PSCompilerPageBase, public IProjectSettingsPage
{
    ProjectSettingsDlg *m_dlg;
    wxString            m_projectName;
    PSGeneralPage *     m_gp;

protected:
    virtual void OnButtonAddAssemblerOptions(wxCommandEvent& event);
    virtual void OnProjectEnabledUI(wxUpdateUIEvent& event);
    // Handlers for PSCompilerPageBase events.
    void OnCheckCompilerNeeded( wxCommandEvent& event );
    void OnCompiledNotNeededUI( wxUpdateUIEvent& event );
    void OnCmdEvtVModified( wxCommandEvent& event );
    void OnButtonAddCompilerOptions( wxCommandEvent& event );
    void OnAddSearchPath( wxCommandEvent& event );
    void OnButtonAddPreprocessor( wxCommandEvent& event );
    void OnBrowsePreCmpHeader( wxCommandEvent& event );
    void OnProjectCustumBuildUI(wxUpdateUIEvent& event);
    void OnButtonAddCCompilerOptions(wxCommandEvent& event);
    void OnEnablePCHFLagsUI(wxUpdateUIEvent& event);


public:
    /** Constructor */
    PSCompilerPage( wxWindow* parent, const wxString &projectName, ProjectSettingsDlg *dlg, PSGeneralPage *gp );
    //// end generated class members

    virtual void Load(BuildConfigPtr buildConf);
    virtual void Save(BuildConfigPtr buildConf, ProjectSettingsPtr projSettingsPtr);
    virtual void Clear();
};

#endif // __ps_compiler_page__