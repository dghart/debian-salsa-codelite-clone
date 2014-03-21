///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Aug 25 2009)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "quickfindbarbase.h"
#include <wx/xrc/xmlres.h>
#include "pluginmanager.h"
#include <wx/button.h>

#if USE_AUI_TOOLBAR

#include <wx/pen.h>
#include <wx/sizer.h>
#include <wx/bitmap.h>
#include <wx/aui/auibar.h>
#include "drawingutils.h"

class CLQuickFindTbArt : public wxAuiDefaultToolBarArt
{
public:
	CLQuickFindTbArt()
	{}

	virtual ~CLQuickFindTbArt()
	{}

	virtual void DrawBackground(wxDC& dc, wxWindow* wnd, const wxRect& rect)
	{
		wxColor col1 = DrawingUtils::GetPanelBgColour();
		wxColor col2 = DrawingUtils::GetPanelBgColour();
		DrawingUtils::PaintStraightGradientBox(dc, rect, col1, col2, true);
	}
};
#endif

///////////////////////////////////////////////////////////////////////////

QuickFindBarBase::QuickFindBarBase( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style ) : wxPanel( parent, id, pos, size, style )
{
	wxBoxSizer* mainSizer;
	mainSizer = new wxBoxSizer( wxHORIZONTAL );
	BitmapLoader *bmpLoader = PluginManager::Get()->GetStdIcons();

	m_toolBar1 = new clToolBar( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, clTB_DEFAULT_STYLE);
#if USE_AUI_TOOLBAR
	m_toolBar1->SetArtProvider(new CLQuickFindTbArt());
#endif
	m_toolBar1->SetToolSeparation( 2 );

	// Use red theme buttons
	m_toolBar1->AddTool( wxID_HIDE,                  _("tool"), bmpLoader->LoadBitmap(wxT("quickfindbar/16/close")),                 _("Hide the Find Bar"), wxITEM_NORMAL);
	m_toolBar1->AddTool( wxID_SHOW_REPLACE_CONTROLS, _("tool"), bmpLoader->LoadBitmap(wxT("quickfindbar/16/show_replace_controls")), _("Toggle 'Replace With' Controls"), wxITEM_CHECK);
	m_toolBar1->Realize();

	mainSizer->Add( m_toolBar1, 0, wxALIGN_CENTER_VERTICAL, 5 );

	m_staticline3 = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_VERTICAL );
	mainSizer->Add( m_staticline3, 0, wxEXPAND|wxRIGHT, 5 );

	wxFlexGridSizer* fgSizer1;
	fgSizer1 = new wxFlexGridSizer( 0, 6, 0, 0 );
	fgSizer1->AddGrowableCol( 1 );
	fgSizer1->AddGrowableCol( 4 );
	fgSizer1->SetFlexibleDirection( wxBOTH );
	fgSizer1->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_ALL );

	m_staticTextFind = new wxStaticText( this, wxID_ANY, _("Find:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextFind->Wrap( -1 );
	fgSizer1->Add( m_staticTextFind, 0, wxALIGN_CENTER_VERTICAL|wxALL, 2 );

	m_findWhat = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER|wxTE_RICH2 );
	m_findWhat->SetToolTip( _("Hit ENTER to search, or Shift + ENTER to search backward") );

	fgSizer1->Add( m_findWhat, 1, wxALIGN_CENTER_VERTICAL|wxALL|wxEXPAND, 2 );

	m_toolBar2 = new clToolBar( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, clTB_DEFAULT_STYLE);
#if USE_AUI_TOOLBAR
	m_toolBar2->SetArtProvider(new CLQuickFindTbArt());
#endif

	m_toolBar2->AddTool( wxID_FIND_NEXT,         _("tool"), bmpLoader->LoadBitmap(wxT("quickfindbar/16/find_next")), _("Find Next Match"),       wxITEM_NORMAL);
	m_toolBar2->AddTool( wxID_FIND_PREVIOUS,     _("tool"), bmpLoader->LoadBitmap(wxT("quickfindbar/16/find_prev")), _("Find Previous Match"),   wxITEM_NORMAL);
	m_toolBar2->AddTool( wxID_HIGHLIGHT_MATCHES, _("tool"), bmpLoader->LoadBitmap(wxT("quickfindbar/16/markall")),   _("Highlight All Matches"), wxITEM_CHECK);
	m_toolBar2->Realize();

	fgSizer1->Add( m_toolBar2, 0, wxEXPAND, 5 );

	m_replaceStaticText = new wxStaticText( this, wxID_ANY, _("Replace with:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_replaceStaticText->Wrap( -1 );
	fgSizer1->Add( m_replaceStaticText, 0, wxALIGN_CENTER_VERTICAL|wxALL, 2 );

	m_replaceWith = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER|wxTE_RICH2 );
	fgSizer1->Add( m_replaceWith, 1, wxALIGN_CENTER_VERTICAL|wxALL|wxEXPAND, 2 );

	m_toolBarReplace = new clToolBar( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, clTB_DEFAULT_STYLE );
#if USE_AUI_TOOLBAR
	m_toolBarReplace->SetArtProvider(new CLQuickFindTbArt());
#endif

	wxButton *replaceButton = new wxButton(m_toolBarReplace, wxID_TOOL_REPLACE, _("Replace"));
	m_toolBarReplace->AddControl( replaceButton );
	m_toolBarReplace->Realize();

	fgSizer1->Add( m_toolBarReplace, 0, wxEXPAND, 5 );

	mainSizer->Add( fgSizer1, 1, wxALIGN_CENTER_VERTICAL, 0 );

	m_staticline1 = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_VERTICAL );
	mainSizer->Add( m_staticline1, 0, wxEXPAND|wxRIGHT|wxLEFT, 2 );

	optionsSizer = new wxBoxSizer( wxHORIZONTAL );

	m_checkBoxCase = new wxCheckBox( this, wxID_ANY, _("Case"), wxDefaultPosition, wxDefaultSize, 0 );
	optionsSizer->Add( m_checkBoxCase, 0, 0, 1 );

	m_checkBoxWord = new wxCheckBox( this, wxID_ANY, _("Word"), wxDefaultPosition, wxDefaultSize, 0 );
	optionsSizer->Add( m_checkBoxWord, 0, wxRIGHT|wxLEFT, 1 );

	m_checkBoxRegex = new wxCheckBox( this, wxID_ANY, _("Regexp"), wxDefaultPosition, wxDefaultSize, 0 );
	optionsSizer->Add( m_checkBoxRegex, 0, wxRIGHT|wxLEFT, 1 );

	mainSizer->Add( optionsSizer, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 1 );

	this->SetSizer( mainSizer );
	this->Layout();
	mainSizer->Fit( this );

	// Connect Events
	this->Connect( wxID_HIDE, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( QuickFindBarBase::OnHide ) );
	this->Connect( wxID_SHOW_REPLACE_CONTROLS, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( QuickFindBarBase::OnToggleReplaceControls ) );
	this->Connect( wxID_SHOW_REPLACE_CONTROLS, wxEVT_UPDATE_UI, wxUpdateUIEventHandler( QuickFindBarBase::OnToggleReplaceControlsUI ) );
	m_findWhat->Connect( wxEVT_KEY_DOWN, wxKeyEventHandler( QuickFindBarBase::OnKeyDown ), NULL, this );
	m_findWhat->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( QuickFindBarBase::OnText ), NULL, this );
	m_findWhat->Connect( wxEVT_SET_FOCUS, wxFocusEventHandler( QuickFindBarBase::OnReceivingFocus ), NULL, this );
	m_findWhat->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( QuickFindBarBase::OnEnter ), NULL, this );
	this->Connect( wxID_FIND_NEXT, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( QuickFindBarBase::OnNext ) );
	this->Connect( wxID_FIND_NEXT, wxEVT_UPDATE_UI, wxUpdateUIEventHandler( QuickFindBarBase::OnUpdateUI ) );
	this->Connect( wxID_FIND_PREVIOUS, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( QuickFindBarBase::OnPrev ) );
	this->Connect( wxID_FIND_PREVIOUS, wxEVT_UPDATE_UI, wxUpdateUIEventHandler( QuickFindBarBase::OnUpdateUI ) );
	m_replaceWith->Connect( wxEVT_KEY_DOWN, wxKeyEventHandler( QuickFindBarBase::OnKeyDown ), NULL, this );
	m_replaceWith->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( QuickFindBarBase::OnReplaceEnter ), NULL, this );
	m_replaceWith->Connect( wxEVT_SET_FOCUS, wxFocusEventHandler( QuickFindBarBase::OnReceivingFocus ), NULL, this );
	m_replaceWith->Connect( wxEVT_UPDATE_UI, wxUpdateUIEventHandler( QuickFindBarBase::OnReplaceUI ), NULL, this );
	this->Connect( wxID_TOOL_REPLACE, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( QuickFindBarBase::OnReplace ) );
	this->Connect( wxID_TOOL_REPLACE, wxEVT_UPDATE_UI, wxUpdateUIEventHandler( QuickFindBarBase::OnReplaceUI ) );
	this->Connect( wxID_HIGHLIGHT_MATCHES, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( QuickFindBarBase::OnHighlightMatches ) );
	this->Connect( wxID_HIGHLIGHT_MATCHES, wxEVT_UPDATE_UI, wxUpdateUIEventHandler( QuickFindBarBase::OnHighlightMatchesUI ) );
	m_checkBoxCase->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( QuickFindBarBase::OnCheckBoxCase ), NULL, this );
	m_checkBoxWord->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( QuickFindBarBase::OnCheckBoxWord ), NULL, this );
	m_checkBoxRegex->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( QuickFindBarBase::OnCheckBoxRegex ), NULL, this );
}

QuickFindBarBase::~QuickFindBarBase()
{
	// Disconnect Events
	this->Disconnect( wxID_HIDE, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( QuickFindBarBase::OnHide ) );
	this->Disconnect( wxID_SHOW_REPLACE_CONTROLS, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( QuickFindBarBase::OnToggleReplaceControls ) );
	this->Disconnect( wxID_SHOW_REPLACE_CONTROLS, wxEVT_UPDATE_UI, wxUpdateUIEventHandler( QuickFindBarBase::OnToggleReplaceControlsUI ) );
	m_findWhat->Disconnect( wxEVT_KEY_DOWN, wxKeyEventHandler( QuickFindBarBase::OnKeyDown ), NULL, this );
	m_findWhat->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( QuickFindBarBase::OnText ), NULL, this );
	m_findWhat->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( QuickFindBarBase::OnEnter ), NULL, this );
	this->Disconnect( wxID_FIND_NEXT, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( QuickFindBarBase::OnNext ) );
	this->Disconnect( wxID_FIND_NEXT, wxEVT_UPDATE_UI, wxUpdateUIEventHandler( QuickFindBarBase::OnUpdateUI ) );
	this->Disconnect( wxID_FIND_PREVIOUS, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( QuickFindBarBase::OnPrev ) );
	this->Disconnect( wxID_FIND_PREVIOUS, wxEVT_UPDATE_UI, wxUpdateUIEventHandler( QuickFindBarBase::OnUpdateUI ) );
	m_replaceWith->Disconnect( wxEVT_KEY_DOWN, wxKeyEventHandler( QuickFindBarBase::OnKeyDown ), NULL, this );
	m_replaceWith->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( QuickFindBarBase::OnReplaceEnter ), NULL, this );
	m_replaceWith->Disconnect( wxEVT_UPDATE_UI, wxUpdateUIEventHandler( QuickFindBarBase::OnReplaceUI ), NULL, this );
	this->Disconnect( wxID_TOOL_REPLACE, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( QuickFindBarBase::OnReplace ) );
	this->Disconnect( wxID_TOOL_REPLACE, wxEVT_UPDATE_UI, wxUpdateUIEventHandler( QuickFindBarBase::OnReplaceUI ) );
	m_checkBoxCase->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( QuickFindBarBase::OnCheckBoxCase ), NULL, this );
	m_checkBoxWord->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( QuickFindBarBase::OnCheckBoxWord ), NULL, this );
	m_checkBoxRegex->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( QuickFindBarBase::OnCheckBoxRegex ), NULL, this );
	this->Disconnect( wxID_HIGHLIGHT_MATCHES, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( QuickFindBarBase::OnHighlightMatches ) );
	this->Disconnect( wxID_HIGHLIGHT_MATCHES, wxEVT_UPDATE_UI, wxUpdateUIEventHandler( QuickFindBarBase::OnHighlightMatchesUI ) );
}
