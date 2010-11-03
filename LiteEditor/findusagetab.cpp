#include "findusagetab.h"
#include "findresultstab.h"
#include <wx/xrc/xmlres.h>
#include <wx/ffile.h>
#include <wx/tokenzr.h>
#include "ctags_manager.h"
#include "cl_editor.h"
#include "frame.h"

FindUsageTab::FindUsageTab(wxWindow* parent, const wxString &name)
: OutputTabWindow(parent, wxID_ANY, name)
{
	FindResultsTab::SetStyles(m_sci);
	m_tb->RemoveTool ( XRCID ( "repeat_output" ) );
	m_tb->Realize();
}

FindUsageTab::~FindUsageTab()
{
}

void FindUsageTab::Clear()
{
	m_matches.clear();
	OutputTabWindow::Clear();
}

void FindUsageTab::OnClearAll(wxCommandEvent& e)
{
	Clear();
}

void FindUsageTab::OnMouseDClick(wxScintillaEvent& e)
{
	long pos = e.GetPosition();
	int line = m_sci->LineFromPosition(pos);
	int style = m_sci->GetStyleAt(pos);

	if (style == wxSCI_LEX_FIF_FILE || style == wxSCI_LEX_FIF_PROJECT) {
		m_sci->ToggleFold(line);
	} else {
		UsageResultsMap::const_iterator iter = m_matches.find(line);
		if (iter != m_matches.end()) {
			DoOpenResult( iter->second );
		}
	}

	m_sci->SetSelection(wxNOT_FOUND, pos);
}

void FindUsageTab::OnClearAllUI(wxUpdateUIEvent& e)
{
	e.Enable(m_sci && m_sci->GetLength());
}

void FindUsageTab::ShowUsage(const std::list<CppToken>& matches, const wxString& searchWhat)
{
	Clear();
	int           lineNumber(0);
	wxString      text;
	wxString      curfile;
	wxString      curfileContent;
	wxArrayString lines;
	
	text << wxT("===== Finding references of '") << searchWhat << wxT("' =====\n");
	lineNumber++;
	
	std::list<CppToken>::const_iterator iter = matches.begin();
	for(; iter != matches.end(); iter++) {
		
		// Print the line number
		if(curfile != iter->getFilename()) {
			curfile = iter->getFilename();
			wxFileName fn(iter->getFilename());
			fn.MakeRelativeTo();
			
			text << fn.GetFullPath() << wxT("\n");
			lineNumber++;
			
			// Load the file content
			wxLogNull nolog;
			wxFFile thefile(iter->getFilename(), wxT("rb"));
			if(thefile.IsOpened()) {
				
				wxFileOffset size = thefile.Length();
				wxString fileData;
				fileData.Alloc(size);
				curfileContent.Clear();
				
				wxCSConv fontEncConv(wxFONTENCODING_ISO8859_1);
				thefile.ReadAll( &curfileContent, fontEncConv );
				
				// break the current file into lines, a line can be an empty string
				lines = wxStringTokenize(curfileContent, wxT("\n"), wxTOKEN_RET_EMPTY_ALL);
			}
			
		}
		
		// Keep the match
		m_matches[lineNumber] = *iter;
		
		// Format the message
		wxString linenum = wxString::Format(wxT(" %4u: "), iter->getLineNumber() + 1);
		wxString scopeName (wxT("<global>"));
		TagEntryPtr tag = TagsManagerST::Get()->FunctionFromFileLine(iter->getFilename(), iter->getLineNumber());
		if(tag) {
			scopeName = tag->GetPath();
		}
		
		text << linenum << wxT("[ ") << scopeName << wxT(" ] ");
		if(lines.GetCount() > iter->getLineNumber()) {
			text << lines.Item(iter->getLineNumber()).Trim().Trim(false);
		}
		
		text << wxT("\n");
		lineNumber++;
	}
	text << wxT("===== Found total of ") << m_matches.size() << wxT(" matches =====\n");
	AppendText( text );
}

void FindUsageTab::DoOpenResult(const CppToken& token)
{
	if (token.getFilename().IsEmpty() == false) {
		LEditor *editor = clMainFrame::Get()->GetMainBook()->OpenFile(token.getFilename(), wxEmptyString, token.getLineNumber()-1);
		if(editor) {
			editor->SetSelection(token.getOffset(), token.getOffset() + token.getName().length());
		}
	}
}
