//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//
// copyright            : (C) 2014 The CodeLite Team
// file name            : gizmos_base.cpp
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

//////////////////////////////////////////////////////////////////////
// This file was auto-generated by codelite's wxCrafter Plugin
// wxCrafter project file: gizmos.wxcp
// Do not modify this file by hand!
//////////////////////////////////////////////////////////////////////

#include "gizmos_base.h"


// Declare the bitmap loading function
extern void wxC8028InitBitmapResources();

static bool bBitmapLoaded = false;


PluginWizardBase::PluginWizardBase(wxWindow* parent, wxWindowID id, const wxString& title, const wxBitmap& bmp, const wxPoint& pos, long style)
{
    if ( !bBitmapLoaded ) {
        // We need to initialise the default bitmap handler
        wxXmlResource::Get()->AddHandler(new wxBitmapXmlHandler);
        wxC8028InitBitmapResources();
        bBitmapLoaded = true;
    }
    Create(parent, id, title, wxXmlResource::Get()->LoadBitmap(wxT("plugin")), pos, style);
    
    m_wizardPage1 = new wxWizardPageSimple(this, NULL, NULL, wxNullBitmap);
    m_pages.push_back(m_wizardPage1);
    
    wxBoxSizer* boxSizer10 = new wxBoxSizer(wxVERTICAL);
    m_wizardPage1->SetSizer(boxSizer10);
    
    wxFlexGridSizer* flexGridSizer12 = new wxFlexGridSizer(0, 2, 0, 0);
    flexGridSizer12->SetFlexibleDirection( wxBOTH );
    flexGridSizer12->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
    flexGridSizer12->AddGrowableCol(1);
    
    boxSizer10->Add(flexGridSizer12, 1, wxALL|wxEXPAND, 5);
    
    m_staticText14 = new wxStaticText(m_wizardPage1, wxID_ANY, _("Plugin name:"), wxDefaultPosition, wxSize(-1,-1), 0);
    
    flexGridSizer12->Add(m_staticText14, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
    
    m_textCtrlName = new wxTextCtrl(m_wizardPage1, wxID_ANY, wxT(""), wxDefaultPosition, wxSize(-1,-1), 0);
    m_textCtrlName->SetToolTip(_("Set the plugin name.\nThe name should be a valid C++ variable name"));
    m_textCtrlName->SetFocus();
    
    flexGridSizer12->Add(m_textCtrlName, 0, wxALL|wxEXPAND, 5);
    
    m_staticText18 = new wxStaticText(m_wizardPage1, wxID_ANY, _("Description:"), wxDefaultPosition, wxSize(-1,-1), 0);
    
    flexGridSizer12->Add(m_staticText18, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
    
    m_textCtrlDescription = new wxTextCtrl(m_wizardPage1, wxID_ANY, wxT(""), wxDefaultPosition, wxSize(-1,-1), 0);
    m_textCtrlDescription->SetToolTip(_("Provide the plugin a short description"));
    
    flexGridSizer12->Add(m_textCtrlDescription, 0, wxALL|wxEXPAND, 5);
    
    m_wizardPage2 = new wxWizardPageSimple(this, NULL, NULL, wxNullBitmap);
    m_pages.push_back(m_wizardPage2);
    if (m_pages.size() > 1) {
        for(size_t i=1; i<m_pages.size(); i++) {
            wxWizardPageSimple::Chain(m_pages.at(i-1), m_pages.at(i));
        }
    }
    GetPageAreaSizer()->Add(m_pages.at(0));
    
    wxBoxSizer* boxSizer22 = new wxBoxSizer(wxVERTICAL);
    m_wizardPage2->SetSizer(boxSizer22);
    
    wxFlexGridSizer* flexGridSizer24 = new wxFlexGridSizer(0, 2, 0, 0);
    flexGridSizer24->SetFlexibleDirection( wxBOTH );
    flexGridSizer24->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
    flexGridSizer24->AddGrowableCol(1);
    
    boxSizer22->Add(flexGridSizer24, 1, wxALL|wxEXPAND, 5);
    
    m_staticText42 = new wxStaticText(m_wizardPage2, wxID_ANY, _("codelite root dir:"), wxDefaultPosition, wxSize(-1,-1), 0);
    
    flexGridSizer24->Add(m_staticText42, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
    
    m_dirPickerCodeliteDir = new wxDirPickerCtrl(m_wizardPage2, wxID_ANY, wxEmptyString, wxT("Select a folder"), wxDefaultPosition, wxSize(-1,-1), wxDIRP_DEFAULT_STYLE|wxDIRP_USE_TEXTCTRL|wxDIRP_DIR_MUST_EXIST);
    m_dirPickerCodeliteDir->SetToolTip(_("Select the location of codelite's source tree"));
    
    flexGridSizer24->Add(m_dirPickerCodeliteDir, 0, wxALL|wxEXPAND, 5);
    
    m_staticText26 = new wxStaticText(m_wizardPage2, wxID_ANY, _("Project path:"), wxDefaultPosition, wxSize(-1,-1), 0);
    
    flexGridSizer24->Add(m_staticText26, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
    
    m_dirPickerPluginPath = new wxDirPickerCtrl(m_wizardPage2, wxID_ANY, wxEmptyString, wxT("Select a folder"), wxDefaultPosition, wxSize(350,-1), wxDIRP_DEFAULT_STYLE|wxDIRP_USE_TEXTCTRL|wxDIRP_DIR_MUST_EXIST);
    m_dirPickerPluginPath->SetToolTip(_("Select the plugin project path"));
    
    flexGridSizer24->Add(m_dirPickerPluginPath, 0, wxALL|wxEXPAND, 5);
    
    flexGridSizer24->Add(0, 0, 1, wxALL, 5);
    
    m_textCtrlPreview = new wxTextCtrl(m_wizardPage2, wxID_ANY, wxT(""), wxDefaultPosition, wxSize(-1,-1), wxTE_READONLY);
    
    flexGridSizer24->Add(m_textCtrlPreview, 0, wxALL|wxEXPAND, 5);
    
    SetSizeHints(-1,-1);
    if ( GetSizer() ) {
         GetSizer()->Fit(this);
    }
    Centre(wxBOTH);
    // Connect events
    this->Connect(wxEVT_WIZARD_PAGE_CHANGING, wxWizardEventHandler(PluginWizardBase::OnPageChanging), NULL, this);
    this->Connect(wxEVT_WIZARD_FINISHED, wxWizardEventHandler(PluginWizardBase::OnFinish), NULL, this);
    m_dirPickerPluginPath->Connect(wxEVT_COMMAND_DIRPICKER_CHANGED, wxFileDirPickerEventHandler(PluginWizardBase::OnProjectPathChanged), NULL, this);
    
}

PluginWizardBase::~PluginWizardBase()
{
    this->Disconnect(wxEVT_WIZARD_PAGE_CHANGING, wxWizardEventHandler(PluginWizardBase::OnPageChanging), NULL, this);
    this->Disconnect(wxEVT_WIZARD_FINISHED, wxWizardEventHandler(PluginWizardBase::OnFinish), NULL, this);
    m_dirPickerPluginPath->Disconnect(wxEVT_COMMAND_DIRPICKER_CHANGED, wxFileDirPickerEventHandler(PluginWizardBase::OnProjectPathChanged), NULL, this);
    
}
