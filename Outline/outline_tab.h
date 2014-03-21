#ifndef SYMBOLVIEWTABPANEL_H
#define SYMBOLVIEWTABPANEL_H

#include "wxcrafter.h"
#include "theme_handler_helper.h"

class IManager;
class svSymbolTree;

class OutlineTab : public OutlineTabBaseClass
{
protected:
    IManager* m_mgr;
    svSymbolTree* m_tree;
    ThemeHandlerHelper* m_themeHelper;
    bool IsIncludeFileNode();
    
public:
    OutlineTab(wxWindow* parent, IManager* mgr);
    virtual ~OutlineTab();
    void OnSearchSymbol(wxCommandEvent& event);
    void OnSearchEnter(wxCommandEvent& event);

    // Event Handlers
    ////////////////////////////////////////////////
    void OnWorkspaceLoaded(wxCommandEvent &e);
    void OnWorkspaceClosed(wxCommandEvent &e);
    void OnActiveEditorChanged(wxCommandEvent &e);
    void OnEditorClosed(wxCommandEvent &e);
    void OnAllEditorsClosed(wxCommandEvent &e);
    void OnFilesTagged(wxCommandEvent &e);
    void OnMenu(wxContextMenuEvent &e);
    void OnGotoImpl(wxCommandEvent &e);
    void OnOpenFile(wxCommandEvent &e);
    void OnGotoDecl(wxCommandEvent &e);
    void OnFindReferenes(wxCommandEvent &e);
    void OnRenameSymbol(wxCommandEvent &e);
    void OnItemSelectedUI(wxUpdateUIEvent &e);
};

#endif // SYMBOLVIEWTABPANEL_H
