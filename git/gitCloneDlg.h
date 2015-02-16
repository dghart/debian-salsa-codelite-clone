//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//
// copyright            : (C) 2014 The CodeLite Team
// file name            : gitCloneDlg.h
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

#ifndef GITCLONEDLG_H
#define GITCLONEDLG_H

#include "gitui.h"

class gitCloneDlg : public gitCloneDlgBaseClass
{
public:
    gitCloneDlg(wxWindow* parent);
    virtual ~gitCloneDlg();

protected:
    virtual void OnOKUI(wxUpdateUIEvent& event);

public:
    wxString GetCloneURL() const;
    wxString GetTargetDirectory() const { return m_dirPickerTargetDir->GetPath(); }
};
#endif // GITCLONEDLG_H
