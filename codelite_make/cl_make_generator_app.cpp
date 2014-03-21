#include "cl_make_generator_app.h"
#include <workspace.h>
#include <wx/filename.h>
#include <builder_gnumake.h>
#include <configuration_mapping.h>
#include <macromanager.h>
#include <wx/crt.h>
#include <globals.h>

IMPLEMENT_APP_CONSOLE(clMakeGeneratorApp)

static const wxCmdLineEntryDesc g_cmdDesc[] = {
    { wxCMD_LINE_SWITCH, "h", "help", "show this help message", wxCMD_LINE_VAL_NONE, wxCMD_LINE_OPTION_HELP},
    { wxCMD_LINE_OPTION, "w", "workspace", "codelite workspace file", wxCMD_LINE_VAL_STRING, wxCMD_LINE_OPTION_MANDATORY },
    { wxCMD_LINE_OPTION, "c", "config", "configuration name to generate", wxCMD_LINE_VAL_STRING, wxCMD_LINE_OPTION_MANDATORY },
    { wxCMD_LINE_OPTION, "p", "project",  "project to build, if non given codelite will build the active project", wxCMD_LINE_VAL_STRING },
    { wxCMD_LINE_SWITCH, "v", "verbose",  "Run in verbose move and print all log lines to the stdout/stderr" },
    { wxCMD_LINE_SWITCH, "e", "execute",  "Instead of printing the command line, execute it" },
    { wxCMD_LINE_NONE }
};

clMakeGeneratorApp::clMakeGeneratorApp()
    : m_verbose(false)
    , m_executeCommand(false)
{
}

clMakeGeneratorApp::~clMakeGeneratorApp()
{
}

int clMakeGeneratorApp::OnExit()
{
    return TRUE;
}

bool clMakeGeneratorApp::OnInit()
{
    wxLog::EnableLogging(false);
    wxCmdLineParser parser(wxAppConsole::argc, wxAppConsole::argv);
    if ( !DoParseCommandLine( parser ) )
        return false;

    wxFileName fnWorkspace(m_workspaceFile);
    if ( fnWorkspace.IsRelative() ) {
        fnWorkspace.MakeAbsolute(m_workingDirectory);
    }

    Info(wxString() << "-- Generting makefile for workspace file " << fnWorkspace.GetFullPath());
    wxString errmsg;
    if ( !WorkspaceST::Get()->OpenWorkspace(fnWorkspace.GetFullPath(), errmsg) ) {
        Error(wxString() << "Error while loading workspace: " << fnWorkspace.GetFullPath() << ". " << errmsg);
        return false;
    }

    if ( m_project.IsEmpty() ) {
        m_project = WorkspaceST::Get()->GetActiveProjectName();
    }

    // Which makefile should we create?
    BuilderGnuMake builder;
    ProjectPtr project = WorkspaceST::Get()->FindProjectByName(m_project, errmsg);
    if ( !project ) {
        Error(wxString() << "Could not find project " << m_project << ". " << errmsg);
        return false;
    }

    // Load the build configuration
    BuildConfigPtr bldConf = WorkspaceST::Get()->GetProjBuildConf(m_project, m_configuration);
    if ( !bldConf ) {
        Error(wxString() << "Could not find configuration " << m_configuration << " for project " << m_project);
        return false;
    }

    if ( bldConf->IsCustomBuild() ) {
        Notice(wxString() << "Configuration " << m_configuration << " for project " << m_project << " is using a custom build - will not generate makefile");
        Notice(wxString() << "Instead, here is the command line to use:");
        Out(wxString() << "cd " << MacroManager::Instance()->Expand(bldConf->GetCustomBuildWorkingDir(), NULL, m_project, m_configuration)
            << " && "
            << MacroManager::Instance()->Expand(bldConf->GetCustomBuildCmd(), NULL, m_project, m_configuration));
        CallAfter( &clMakeGeneratorApp::DoExitApp);
        return true;
    }

    if ( !builder.Export(m_project, m_configuration, false, true, errmsg) ) {
        Error(wxString() << "Error while exporting makefile. " << errmsg);
        return false;
    }

    wxString commandToRun;
    commandToRun = builder.GetBuildCommand(m_project, m_configuration);

    wxString workspace_path = fnWorkspace.GetPath();
    if ( workspace_path.Contains(" ") || workspace_path.Contains("\t") ) {
        workspace_path.Prepend("\"").Append("\"");
    }

    Info("-- Makefile generation completed successfully!");
    Info("-- To use the makefile, run the following commands from a terminal:");

    wxString command;
    command << "cd " << workspace_path << " && " << commandToRun;

    if ( m_executeCommand ) {
        CallAfter( &clMakeGeneratorApp::DoExecCommand, command );

    } else {
        Out( command );
        CallAfter( &clMakeGeneratorApp::DoExitApp);
    }
    return true;
}

bool clMakeGeneratorApp::DoParseCommandLine(wxCmdLineParser& parser)
{
    parser.SetDesc( g_cmdDesc );
    parser.AddUsageText(_("A makefile generator based on codelite's workspace"));

    int res = parser.Parse(false);
    if ( res == wxNOT_FOUND )
        return false;

    if ( !parser.Found("w", &m_workspaceFile) ) {
        parser.Usage();
        return false;
    }

    if ( !parser.Found("c", &m_configuration) ) {
        parser.Usage();
        return false;
    }

    if ( parser.Found("e") ) {
        m_executeCommand = true;
    }

    parser.Found("p", &m_project);
    m_verbose = (parser.FoundSwitch("v") == wxCMD_SWITCH_ON);
    m_workingDirectory = ::wxGetCwd();
    return true;
}

void clMakeGeneratorApp::DoExitApp()
{
    ExitMainLoop();
}

// Log functions
void clMakeGeneratorApp::Error(const wxString& msg)
{
    wxString e;
    e << "[ERROR ] " << msg;
    wxFprintf(stderr, "%s\n", e);
}

void clMakeGeneratorApp::Notice(const wxString& msg)
{
    if ( m_verbose ) {
        wxString e;
        e << "[NOTICE] " << msg;
        wxFprintf(stderr, "%s\n", e);
    }
}

void clMakeGeneratorApp::Info(const wxString& msg)
{
    if ( m_verbose ) {
        wxString e;
        e << "[INFO  ] " << msg;
        wxFprintf(stdout, "%s\n", e);
    }
}

void clMakeGeneratorApp::Out(const wxString& msg)
{
    wxPrintf("%s\n", msg);
}

void clMakeGeneratorApp::DoExecCommand(const wxString& command)
{
    wxString cmd = command;
    WrapInShell( cmd );
    ::wxExecute( cmd, wxEXEC_SYNC|wxEXEC_NOHIDE|wxEXEC_SHOW_CONSOLE);
    CallAfter( &clMakeGeneratorApp::DoExitApp );
}
