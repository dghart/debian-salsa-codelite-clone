#include "qmakeplugindata.h"
#include <wx/tokenzr.h>
#include <wx/log.h>

static wxString readString(wxString &str) {

	wxString sLen  = str.Mid(0, 4);
	str = str.Mid(4);

	long nLen( 0 );
	sLen.ToLong( &nLen );

	wxString s = str.Mid(0, nLen);
	str = str.Mid( nLen );

	return s;
}

static void writeString(wxString &str, const wxString &srcToWrite) {
	if(srcToWrite.IsEmpty()) {
		str << wxT("0000");
	} else {
		str << wxString::Format(wxT("%04d"), srcToWrite.Length()) << srcToWrite;
	}
}

QmakePluginData::QmakePluginData(const wxString &data)
{
	wxString num  = data.Mid(0, 4);
	wxString rest = data.Mid(4);

	long nCount( 0 );
	num.ToLong( &nCount );

	for(long i=0; i<nCount; i++) {

		BuildConfPluginData bcpd;
		bcpd.m_enabled            = readString( rest ) == wxT("Y") ? true : false;
		bcpd.m_buildConfName      = readString( rest );
		bcpd.m_qmakeConfig        = readString( rest );
		bcpd.m_qmakeExecutionLine = readString( rest );
		bcpd.m_freeText           = readString( rest );

		m_pluginsData[bcpd.m_buildConfName] = bcpd;
	}
}

QmakePluginData::~QmakePluginData()
{
}

wxString QmakePluginData::ToString()
{
	wxString serializedStr (wxEmptyString);
	serializedStr << wxString::Format(wxT("%04d"), m_pluginsData.size());
	std::map<wxString, BuildConfPluginData>::iterator iter = m_pluginsData.begin();
	for(; iter != m_pluginsData.end(); iter++){
		writeString( serializedStr, iter->second.m_enabled ? wxT("Y") : wxT("N"));
		writeString( serializedStr, iter->second.m_buildConfName                );
		writeString( serializedStr, iter->second.m_qmakeConfig                  );
		writeString( serializedStr, iter->second.m_qmakeExecutionLine           );
		writeString( serializedStr, iter->second.m_freeText                     );
	}
	return serializedStr;
}

 bool QmakePluginData::GetDataForBuildConf(const wxString& configName, BuildConfPluginData &bcpd)
{
	std::map<wxString, BuildConfPluginData>::iterator iter = m_pluginsData.find(configName);
	if(iter == m_pluginsData.end()) {
		return false;
	}

	bcpd = iter->second;
	return true;
}

void QmakePluginData::SetDataForBuildConf(const wxString& configName, const BuildConfPluginData& cd)
{
	m_pluginsData[configName] = cd;
}
