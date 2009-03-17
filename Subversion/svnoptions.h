//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//
// copyright            : (C) 2008 by Eran Ifrah
// file name            : svnoptions.h
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
#ifndef SVNOPTIONS_H
#define SVNOPTIONS_H

#include "serialized_object.h"

enum SvnOptionsFlags {
	SvnUseIcons             = 0x00000001,
	SvnKeepIconsUpdated     = 0x00000002,
	SvnAutoAddFiles         = 0x00000004,
	SvnUpdateAfterSave      = 0x00000008,
	SvnCaptureDiffOutput    = 0x00000010,
	SvnUseExternalDiff      = 0x00000020
};

class SvnOptions : public SerializedObject
{
	size_t   m_flags;
	wxString m_exePath;
	wxString m_pattern;
	wxString m_diffCmd;
	wxString m_diffArgs;
	bool     m_keepTagUpToDate;
	wxString m_sshClient;
	wxString m_sshClientArguments;

public:
	SvnOptions();
	virtual ~SvnOptions();

	void DeSerialize(Archive &arch);
	void Serialize(Archive &arch);

	const size_t& GetFlags() const {
		return m_flags;
	}
	void SetFlags(const size_t& flags) {
		m_flags = flags;
	}

	const wxString &GetExePath() const {
		return m_exePath;
	}
	void SetExePath(const wxString &path) {
		m_exePath = path;
	}

	void SetPattern(const wxString& pattern) {
		this->m_pattern = pattern;
	}
	const wxString& GetPattern() const {
		return m_pattern;
	}

	void SetDiffCmd(const wxString& diffCmd) {
		this->m_diffCmd = diffCmd;
	}
	const wxString& GetDiffCmd() const {
		return m_diffCmd;
	}

	void SetDiffArgs(const wxString& diffArgs) {
		this->m_diffArgs = diffArgs;
	}
	const wxString& GetDiffArgs() const {
		return m_diffArgs;
	}
	void SetKeepTagUpToDate(const bool& keepTagUpToDate) {
		this->m_keepTagUpToDate = keepTagUpToDate;
	}
	const bool& GetKeepTagUpToDate() const {
		return m_keepTagUpToDate;
	}

	void SetSshClient(const wxString& sshClient) {
		this->m_sshClient = sshClient;
	}
	const wxString& GetSshClient() const {
		return m_sshClient;
	}
	void SetSshClientArguments(const wxString& sshClientArguments) {
		this->m_sshClientArguments = sshClientArguments;
	}
	const wxString& GetSshClientArguments() const {
		return m_sshClientArguments;
	}
};

#endif //SVNOPTIONS_H
