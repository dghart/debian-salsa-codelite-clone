//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//
// copyright            : (C) 2008 by Eran Ifrah
// file name            : simpletable.h
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
#ifndef __simpletable__
#define __simpletable__

/**
@file
Subclass of SimpleTableBase, which is generated by wxFormBuilder.
*/

#include "simpletablebase.h"
#include <map>
#include "debuggerobserver.h"
#include "cl_command_event.h"

#define QUERY_NUM_CHILDS  500
#define LIST_WATCH_CHILDS 501

class IDebugger;
class WatchesTable;

class WatchDropTarget : public wxTextDropTarget
{
    WatchesTable* m_parent;
public:
    WatchDropTarget(WatchesTable* parent) : m_parent(parent) {}
    virtual ~WatchDropTarget() {}
    virtual bool OnDropText(wxCoord x, wxCoord y, const wxString& text);
};

/** Implementing SimpleTableBase */
class WatchesTable : public DebuggerTreeListCtrlBase
{
    wxMenu *m_rclickMenu;
protected:
    // Handlers for SimpleTableBase events.
    void OnListKeyDown( wxTreeEvent& event );
    void OnItemRightClick(wxTreeEvent& event);
    void OnItemExpanding(wxTreeEvent& event);
    void OnListEditLabelBegin(wxTreeEvent& event);
    void OnListEditLabelEnd(wxTreeEvent& event);

    // Menu events
    void OnNewWatch         (wxCommandEvent &event);
    void OnNewWatchUI       (wxUpdateUIEvent &event);
    void OnDeleteAll        (wxCommandEvent &event);
    void OnDeleteAllUI      (wxUpdateUIEvent &event);
    void OnDeleteWatch      (wxCommandEvent &event);
    void OnDeleteWatchUI    (wxUpdateUIEvent &event);
    void OnMenuEditExpr     (wxCommandEvent &event);
    void OnMenuEditExprUI   (wxUpdateUIEvent &event);
    void OnMenuCopyValue    (wxCommandEvent &event);
    void OnMenuCopyBoth     (wxCommandEvent &event);
    void OnMenuDisplayFormat(wxCommandEvent &event);
    void OnNewWatch_Internal(wxCommandEvent &event);

protected:
    void InitTable();
    void DoUpdateExpression(const wxTreeItemId& item, const wxString &newExpr);

public:
    virtual void OnTypeResolveError(clCommandEvent& event);
    virtual void OnRefreshUI(wxUpdateUIEvent& event);
    virtual void OnRefresh(wxCommandEvent& event);
    /**
     * @brief a callback called from the global manager when the debugger
     * responded for our CreateVariableObject call
     * @param event
     */
    void OnCreateVariableObject  (const DebuggerEventData &event);

    /**
     * @brief a type resolving is completed, we can now add the watch
     */
    void OnTypeResolved(const DebuggerEventData &event);
    /**
     * @brief a callback called from the global manager when the debugger
     * responded for our ListChildren call
     * @param event
     */
    void OnListChildren( const DebuggerEventData &event );

    void OnUpdateVariableObject(const DebuggerEventData &event);
public:
    /** Constructor */
    WatchesTable( wxWindow* parent );
    virtual ~WatchesTable();

    void AddExpression(const wxString &expr);
    wxArrayString GetExpressions();
    void Clear();
    void RefreshValues(bool repositionEditor = true);
};

#endif // __simpletable__
