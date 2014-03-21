#ifndef __QMakePlugin__
#define __QMakePlugin__

#include "plugin.h"
#include "qmakeplugindata.h"
#include "cl_command_event.h"

class QMakeTab;
class QmakeConf;

class QMakePlugin : public IPlugin
{
    std::map<wxString, QMakeTab*> m_pages;
    QmakeConf *                   m_conf;

protected:
    QMakeTab * DoGetQmakeTab     (const wxString &config);
    void       DoUnHookAllTabs   (wxBookCtrlBase *book);
    bool       DoGetData         (const wxString &project, const wxString &conf, QmakePluginData::BuildConfPluginData &bcpd);
    wxString   DoGetBuildCommand (const wxString &project, const wxString &config, bool projectOnly);

public:
    QMakePlugin(IManager *manager);
    ~QMakePlugin();

    //--------------------------------------------
    //Abstract methods
    //--------------------------------------------
    virtual clToolBar *CreateToolBar     (wxWindow *parent);
    virtual void CreatePluginMenu        (wxMenu *pluginsMenu);
    virtual void HookPopupMenu           (wxMenu *menu, MenuType type);
    virtual void HookProjectSettingsTab  (wxBookCtrlBase *book, const wxString &projectName, const wxString &configName);
    virtual void UnHookProjectSettingsTab(wxBookCtrlBase *book, const wxString &projectName, const wxString &configName);
    virtual void UnPlug                  ();

    // event handlers
    void OnSaveConfig          (wxCommandEvent &event);
    void OnBuildStarting       (clBuildEvent &event);
    void OnSettings            (wxCommandEvent &event);
    void OnGetCleanCommand     (clBuildEvent &event);
    void OnGetBuildCommand     (clBuildEvent &event);
    void OnGetIsPluginMakefile (clBuildEvent &event);
    void OnNewQmakeBasedProject(wxCommandEvent &event);
    void OnOpenFile            (wxCommandEvent &event);
    void OnExportMakefile      (clBuildEvent& event);
};

#endif //QMakePlugin
