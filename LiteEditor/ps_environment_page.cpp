#include "ps_environment_page.h"
#include "environmentconfig.h"
#include "debuggersettings.h"
#include "debuggerconfigtool.h"

PSEnvironmentPage::PSEnvironmentPage( wxWindow* parent, ProjectSettingsDlg* dlg )
    : PSEnvironmentBasePage( parent )
    , m_dlg(dlg)
{

}

void PSEnvironmentPage::OnCmdEvtVModified( wxCommandEvent& event )
{
    wxUnusedVar(event);
    m_dlg->SetIsDirty(true);
}

void PSEnvironmentPage::Load(BuildConfigPtr buildConf)
{
    ///////////////////////////////////////////////////////////////////////////
    // Set the environment page
    ///////////////////////////////////////////////////////////////////////////
    m_choiceEnv->Clear();
    std::map<wxString, wxString> envSets = EnvironmentConfig::Instance()->GetSettings().GetEnvVarSets();
    std::map<wxString, wxString>::const_iterator iterI = envSets.begin();
    int useActiveSetIndex = m_choiceEnv->Append(wxGetTranslation(USE_WORKSPACE_ENV_VAR_SET));

    for (; iterI != envSets.end(); iterI++) {
        m_choiceEnv->Append(iterI->first);
    }
    int selEnv = m_choiceEnv->FindString( buildConf->GetEnvVarSet() );
    m_choiceEnv->SetSelection(selEnv == wxNOT_FOUND ? useActiveSetIndex : selEnv);

    m_choiceDbgEnv->Clear();
    useActiveSetIndex = m_choiceDbgEnv->Append(wxGetTranslation(USE_GLOBAL_SETTINGS));

    DebuggerSettingsPreDefMap data;
    DebuggerConfigTool::Get()->ReadObject(wxT("DebuggerCommands"), &data);
    const std::map<wxString, DebuggerPreDefinedTypes>& preDefTypes = data.GePreDefinedTypesMap();
    std::map<wxString, DebuggerPreDefinedTypes>::const_iterator iterB = preDefTypes.begin();
    for(; iterB != preDefTypes.end(); iterB++) {
        m_choiceDbgEnv->Append(iterB->first);
    }

    int selDbg = m_choiceDbgEnv->FindString( buildConf->GetDbgEnvSet() );
    m_choiceDbgEnv->SetSelection(selEnv == wxNOT_FOUND ? useActiveSetIndex : selDbg);
    m_textCtrlEnvvars->SetValue(buildConf->GetEnvvars());
}

void PSEnvironmentPage::Save(BuildConfigPtr buildConf, ProjectSettingsPtr projSettingsPtr)
{
    wxString env = m_choiceDbgEnv->GetStringSelection();
    if (env == wxGetTranslation(USE_GLOBAL_SETTINGS)) {
        // Save it untranslated
        env = USE_GLOBAL_SETTINGS;
    }
    buildConf->SetDbgEnvSet(env);

    env = m_choiceEnv->GetStringSelection();
    if (env == wxGetTranslation(USE_WORKSPACE_ENV_VAR_SET)) {
        env = USE_WORKSPACE_ENV_VAR_SET;
    }
    buildConf->SetEnvVarSet(env);
    buildConf->SetEnvvars(m_textCtrlEnvvars->GetValue().Trim().Trim(false));
}

void PSEnvironmentPage::Clear()
{
    m_choiceDbgEnv->Clear();
    m_choiceEnv->Clear();
}

void PSEnvironmentPage::OnProjectEnabledUI(wxUpdateUIEvent& event)
{
    event.Enable( m_dlg->IsProjectEnabled() );
}