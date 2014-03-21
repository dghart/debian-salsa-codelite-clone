#include "code_completion_page.h"
#include "localworkspace.h"
#include "clang_code_completion.h"
#include <wx/tokenzr.h>
#include "globals.h"

CodeCompletionPage::CodeCompletionPage(wxWindow *parent, int type)
    : CodeCompletionBasePage(parent)
    , m_type(type)
    , m_ccChanged(false)
{
    if(m_type == TypeWorkspace) {

        wxArrayString excludePaths, includePaths;
        wxString opts, c_opts;
        wxString macros;

        LocalWorkspaceST::Get()->GetParserPaths(includePaths, excludePaths);
        LocalWorkspaceST::Get()->GetParserMacros(macros);

        m_textCtrlSearchPaths->SetValue( wxImplode(includePaths, wxT("\n")) );
        m_textCtrlMacros->SetValue(macros );
        
        m_checkBoxCpp11->SetValue( LocalWorkspaceST::Get()->GetParserFlags() & LocalWorkspace::EnableCpp11 );
    }
}

CodeCompletionPage::~CodeCompletionPage()
{
}

wxArrayString CodeCompletionPage::GetIncludePaths() const
{
    return wxStringTokenize(m_textCtrlSearchPaths->GetValue(), wxT("\n\r"), wxTOKEN_STRTOK);
}

wxString CodeCompletionPage::GetMacros() const
{
    return m_textCtrlMacros->GetValue();
}

wxString CodeCompletionPage::GetIncludePathsAsString() const
{
    return m_textCtrlSearchPaths->GetValue();
}

void CodeCompletionPage::Save()
{
    if(m_type == TypeWorkspace) {
        size_t flags = 0;
        LocalWorkspaceST::Get()->SetParserPaths(GetIncludePaths(), wxArrayString());
        LocalWorkspaceST::Get()->SetParserMacros(GetMacros());

        if ( m_checkBoxCpp11->IsChecked() ) flags |= LocalWorkspace::EnableCpp11;
        LocalWorkspaceST::Get()->SetParserFlags( flags );
        LocalWorkspaceST::Get()->Flush();

#if HAS_LIBCLANG
        if(m_ccChanged) {
            ClangCodeCompletion::Instance()->ClearCache();
            m_ccChanged = false;
        }
#endif
    }
}

void CodeCompletionPage::OnCCContentModified(wxCommandEvent& event)
{
    m_ccChanged = true;
}
