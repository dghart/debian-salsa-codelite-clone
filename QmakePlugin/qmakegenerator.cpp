#include "qmakegenerator.h"
#include "wxmd5.h"
#include "fileextmanager.h"
#include <wx/tokenzr.h>
#include <wx/ffile.h>
#include "globals.h"
#include "qmakeplugindata.h"
#include "workspace.h"
#include "project.h"
#include "imanager.h"

wxString QMakeProFileGenerator::prepareVariable( const wxString &variable )
{
	wxString var = ExpandAllVariables(variable, m_manager->GetWorkspace(), m_project, m_configuration, wxEmptyString);
	var.Replace(wxT("\\"), wxT("/"));
	return var;
}

QMakeProFileGenerator::QMakeProFileGenerator(IManager *manager, const wxString &project, const wxString &configuration)
		: m_manager(manager)
		, m_project(project)
		, m_configuration(configuration)
{
}

QMakeProFileGenerator::~QMakeProFileGenerator()
{
}

bool QMakeProFileGenerator::Generate()
{
	wxString                             errMsg;
	wxString                             pro_file;
	QmakePluginData::BuildConfPluginData bcpd;
	bool                                 needRegenration(true);

	ProjectPtr p = m_manager->GetWorkspace()->FindProjectByName(m_project, errMsg);
	if ( !p ) {
		return false;
	}

	wxString rawData = p->GetPluginData(wxT("qmake"));
	QmakePluginData pd( rawData );
	if ( !pd.GetDataForBuildConf(m_configuration, bcpd) ) {
		return false;
	}

	// Get codelite's build configuration
	ProjectSettingsPtr settings = p->GetSettings();
	BuildConfigPtr bldConf = settings->GetBuildConfiguration(m_configuration);
	if ( !bldConf ) {
		return false;
	}

	m_makefilePath  = p->GetFileName().GetPath(wxPATH_GET_SEPARATOR|wxPATH_GET_VOLUME);
	m_makefilePath += p->GetName();
	m_makefilePath += wxT(".mk");

	pro_file << wxT("##########################################\n");
	pro_file << wxT("# codelite's qmake configuration: ") << bcpd.m_qmakeConfig << wxT("\n");
	pro_file << wxT("# codelite's qmake exec line    : ") << bcpd.m_qmakeExecutionLine << wxT("\n");
	pro_file << wxT("##########################################\n");

	// Generate the pro file content
	pro_file << wxT("DESTDIR        = ") << p->GetFileName().GetPath(wxPATH_GET_SEPARATOR|wxPATH_GET_VOLUME) << wxT("\n");
	SetVariables( pro_file, bldConf, settings);
	SetFiles    ( pro_file, p );

	pro_file << wxT("##########################################\n");
	pro_file << wxT("# User section\n");
	pro_file << wxT("##########################################\n");
	pro_file << wxT("\n") << bcpd.m_freeText << wxT("\n");

	// incase we are building library, set the template back the lib
	wxString type = p->GetSettings()->GetProjectType( bldConf->GetName() );
	if ( type == Project::DYNAMIC_LIBRARY || type == Project::STATIC_LIBRARY ) {
		pro_file << wxT("TEMPLATE       = lib\n");
	}

	// Optimization: check to see if we really need to run qmake
	if( wxFileName::FileExists(m_makefilePath) == false ) {
		needRegenration = true;
	} else if ( wxFileName::FileExists( GetProFileName() ) == false ){
		needRegenration = true;
	} else {

		// both files exists, compare the MD5 of the pro file on the dis with the
		wxString content;
		if( !ReadFileWithConversion(GetProFileName(), content) ){
			needRegenration = true;
		} else {
			wxString diskMD5 = wxMD5::GetDigest( content );
			wxString mem_MD5 = wxMD5::GetDigest( pro_file);

			if( diskMD5 != mem_MD5 ) {
				needRegenration = true;
			} else {
				needRegenration = false;
			}
		}
	}

	// dump the content to a file
	wxFFile output;
	output.Open(GetProFileName(), wxT("w+b"));
	if (output.IsOpened()) {
		output.Write( pro_file );
		output.Close();
	}

	return needRegenration;
}

void QMakeProFileGenerator::SetVariables(wxString& pro_file, BuildConfigPtr bldConf, ProjectSettingsPtr settings)
{
	//--------------------------------------------
	// Define the TEMPLATE variable
	//--------------------------------------------
	wxString type = settings->GetProjectType( bldConf->GetName() );

	if ( type == Project::EXECUTABLE ) {
		pro_file << wxT("TEMPLATE       = app\n");
		pro_file << wxT("CONFIG         = release qt lex yacc uic resources warn_on precompile_header\n");

	} else if ( type == Project::DYNAMIC_LIBRARY ) {
		pro_file << wxT("TEMPLATE       = lib\n");
		pro_file << wxT("CONFIG         = release qt dll lex yacc uic resources warn_on precompile_header\n");

	} else {
		pro_file << wxT("TEMPLATE       = lib\n");
		pro_file << wxT("CONFIG         = release qt staticlib lex yacc uic resources warn_on precompile_header\n");
	}

	pro_file << wxT("MAKEFILE       = ") << m_makefilePath << wxT("\n");

	//--------------------------------------------
	// Define the intermediate directory and
	// the output file
	//--------------------------------------------
	pro_file << wxT("OBJECTS_DIR    = ") << bldConf->GetIntermediateDirectory() << wxT("\n");
	pro_file << wxT("TARGET         = ") << prepareVariable(bldConf->GetOutputFileName()) << wxT("\n");

	//--------------------------------------------
	// Prepare the include path
	//--------------------------------------------
	wxString includes = bldConf->GetIncludePath();
	includes.Replace(wxT(";"), wxT(" "));
	pro_file << wxT("INCLUDEPATH    = ") << includes << wxT("\n");

	//--------------------------------------------
	// Compiler options
	//--------------------------------------------
	wxString buildOpts = bldConf->GetCompileOptions();
	buildOpts.Replace(wxT(";"), wxT(" "));
	pro_file << wxT("QMAKE_CFLAGS_RELEASE   = ") << buildOpts << wxT("\n");
	pro_file << wxT("QMAKE_CXXFLAGS_RELEASE = ") << buildOpts << wxT("\n");

	//--------------------------------------------
	// Preprocessor
	//--------------------------------------------
	wxString defines = bldConf->GetPreprocessor();
	defines.Replace(wxT(";"), wxT(" "));
	pro_file << wxT("DEFINES        = ") << defines << wxT("\n");

	//--------------------------------------------
	// Prepare linker options
	//--------------------------------------------
	wxString links = bldConf->GetLinkOptions();
	links.Replace(wxT(";"), wxT(" "));
	pro_file << wxT("QMAKE_LFLAGS_RELEASE   = ") << links << wxT("\n");

	//--------------------------------------------
	// Lib path
	//--------------------------------------------
	wxString libPaths = bldConf->GetLibPath();
	libPaths.Replace(wxT(";"), wxT(" "));
	pro_file << wxT("LIBS           = ") << libPaths << wxT("\n");

	//--------------------------------------------
	// Libraries
	//--------------------------------------------
	wxString libs = bldConf->GetLibraries();
	libs.Replace(wxT(";"), wxT(" "));
	pro_file << wxT("LIBS           += ") << libs << wxT("\n");

}

void QMakeProFileGenerator::SetFiles(wxString& pro_file, ProjectPtr proj)
{
	std::vector<wxFileName> files;
	proj->GetFiles( files, true );

	wxString sources, headers, forms, yacc, lex, qresources;

	sources    << wxT("SOURCES     = \\\n");
	headers    << wxT("HEADERS     = \\\n");
	forms      << wxT("FORMS       = \\\n");
	yacc       << wxT("YACCSOURCES = \\\n");
	lex        << wxT("LEXSOURCES  = \\\n");
	qresources << wxT("RESOURCES   = \\\n");
	wxString BUFF(wxT("             "));

	for (size_t i=0; i<files.size(); i++) {
		wxFileName fn = files.at(i);

		switch ( FileExtManager::GetType( fn.GetFullName() )) {
		case FileExtManager::TypeSource:
			sources << BUFF << fn.GetFullPath() << wxT("\\\n");
			break;
		case FileExtManager::TypeHeader:
			headers << BUFF << fn.GetFullPath() << wxT("\\\n");
			break;
		case FileExtManager::TypeQtForm:
			forms << BUFF << fn.GetFullPath() << wxT("\\\n");
			break;
		case FileExtManager::TypeYacc:
			yacc << BUFF << fn.GetFullPath() << wxT("\\\n");
			break;
		case FileExtManager::TypeLex:
			lex << BUFF << fn.GetFullPath() << wxT("\\\n");
			break;
		case FileExtManager::TypeQtResource:
			qresources << BUFF << fn.GetFullPath() << wxT("\\\n");
			break;
		default:
			break;
		}
	}

	pro_file << sources    << wxT("\n");
	pro_file << headers    << wxT("\n");
	pro_file << forms      << wxT("\n");
	pro_file << yacc       << wxT("\n");
	pro_file << lex        << wxT("\n");
	pro_file << qresources << wxT("\n");
}

wxString QMakeProFileGenerator::GetProFileName()
{
	wxString errMsg;
	ProjectPtr p = m_manager->GetWorkspace()->FindProjectByName(m_project, errMsg);
	if( p ) {
		wxFileName fn (wxString::Format(wxT("%s/%s.pro"), p->GetFileName().GetPath(wxPATH_GET_SEPARATOR|wxPATH_GET_VOLUME).c_str(), m_project.c_str()));
		return fn.GetFullPath();
	}

	return wxEmptyString;
}