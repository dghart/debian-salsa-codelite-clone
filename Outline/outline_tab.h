//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//
// copyright            : (C) 2014 Eran Ifrah
// file name            : outline_tab.h
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

#ifndef SYMBOLVIEWTABPANEL_H
#define SYMBOLVIEWTABPANEL_H

#include "wxcrafter.h"
#include "theme_handler_helper.h"
#include "cl_command_event.h"

class IManager;
class svSymbolTree;

class OutlineTab : public OutlineTabBaseClass
{
protected:
    virtual void OnPhpItemActivated(wxTreeEvent& event);
    virtual void OnPhpItemSelected(wxTreeEvent& event);
    IManager* m_mgr;
    svSymbolTree* m_tree;
    ThemeHandlerHelper* m_themeHelper;
    bool IsIncludeFileNode();
    wxFileName m_phpFile;

public:
    OutlineTab(wxWindow* parent, IManager* mgr);
    virtual ~OutlineTab();
    void OnSearchSymbol(wxCommandEvent& event);
    void OnSearchEnter(wxCommandEvent& event);

    // Event Handlers
    ////////////////////////////////////////////////
    void OnWorkspaceClosed(wxCommandEvent& e);
    void OnActiveEditorChanged(wxCommandEvent& e);
    void OnEditorClosed(wxCommandEvent& e);
    void OnAllEditorsClosed(wxCommandEvent& e);
    void OnFilesTagged(wxCommandEvent& e);
    void OnMenu(wxContextMenuEvent& e);
    void OnGotoImpl(wxCommandEvent& e);
    void OnOpenFile(wxCommandEvent& e);
    void OnGotoDecl(wxCommandEvent& e);
    void OnFindReferenes(wxCommandEvent& e);
    void OnRenameSymbol(wxCommandEvent& e);
    void OnItemSelectedUI(wxUpdateUIEvent& e);
    void OnEditorSaved(clCommandEvent& event);
};

#endif // SYMBOLVIEWTABPANEL_H
