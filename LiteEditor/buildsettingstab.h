//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//
// copyright            : (C) 2008 by Eran Ifrah
// file name            : buildsettingstab.h
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
#ifndef __buildsettingstab__
#define __buildsettingstab__

/**
@file
Subclass of BuildTabSettingsBase, which is generated by wxFormBuilder.
*/

#include "buildsettingstabbase.h"

/** Implementing BuildTabSettingsBase */
class BuildTabSetting : public BuildTabSettingsBase
{
public:
    /** Constructor */
    BuildTabSetting(wxWindow* parent);
    void Save();
    void OnUpdateUI(wxUpdateUIEvent& event);
};

#endif // __buildsettingstab__
