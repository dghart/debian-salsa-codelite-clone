//////////////////////////////////////////////////////////////////////
// This file was auto-generated by codelite's wxCrafter Plugin
// wxCrafter project file: codeformatterdlg.wxcp
// Do not modify this file by hand!
//////////////////////////////////////////////////////////////////////

#include "codeformatterdlgbase.h"
#include "formatoptions.h"
#include "PHPFormatterBuffer.h"


// Declare the bitmap loading function
extern void wxCrafterGgLOZbInitBitmapResources();

static bool bBitmapLoaded = false;


CodeFormatterBaseDlg::CodeFormatterBaseDlg(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style)
    : wxDialog(parent, id, title, pos, size, style)
{
    if ( !bBitmapLoaded ) {
        // We need to initialise the default bitmap handler
        wxXmlResource::Get()->AddHandler(new wxBitmapXmlHandler);
        wxCrafterGgLOZbInitBitmapResources();
        bBitmapLoaded = true;
    }
    
    wxBoxSizer* bSizerMain = new wxBoxSizer(wxVERTICAL);
    this->SetSizer(bSizerMain);
    
    m_treebook = new wxTreebook(this, wxID_ANY, wxDefaultPosition, wxSize(-1,-1), wxBK_DEFAULT);
    wxImageList* m_treebook_il = new wxImageList(16, 16);
    m_treebook->AssignImageList(m_treebook_il);
    
    bSizerMain->Add(m_treebook, 1, wxALL|wxEXPAND, 5);
    
    m_panel133 = new wxPanel(m_treebook, wxID_ANY, wxDefaultPosition, wxSize(-1,-1), wxTAB_TRAVERSAL);
    int m_panel133ImgIndex;
    m_panel133ImgIndex = m_treebook_il->Add(wxXmlResource::Get()->LoadBitmap(wxT("configure")));
    m_treebook->AddPage(m_panel133, _("General"), true, m_panel133ImgIndex);
    
    wxBoxSizer* boxSizer179 = new wxBoxSizer(wxVERTICAL);
    m_panel133->SetSizer(boxSizer179);
    
    wxFlexGridSizer* flexGridSizer158 = new wxFlexGridSizer(0, 2, 0, 0);
    flexGridSizer158->SetFlexibleDirection( wxBOTH );
    flexGridSizer158->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
    flexGridSizer158->AddGrowableCol(1);
    
    boxSizer179->Add(flexGridSizer158, 1, wxALL|wxEXPAND, 2);
    
    m_staticText162 = new wxStaticText(m_panel133, wxID_ANY, _("Format editor on file save:"), wxDefaultPosition, wxSize(-1,-1), 0);
    
    flexGridSizer158->Add(m_staticText162, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
    
    m_checkBoxFormatOnSave = new wxCheckBox(m_panel133, wxID_ANY, wxT(""), wxDefaultPosition, wxSize(-1,-1), 0);
    m_checkBoxFormatOnSave->SetValue(false);
    m_checkBoxFormatOnSave->SetToolTip(_("When saving a file, automatically format it"));
    
    flexGridSizer158->Add(m_checkBoxFormatOnSave, 0, wxRIGHT|wxTOP|wxBOTTOM|wxALIGN_LEFT, 5);
    
    m_staticText115 = new wxStaticText(m_panel133, wxID_ANY, _("Select C++ formatter:"), wxDefaultPosition, wxSize(-1,-1), 0);
    
    flexGridSizer158->Add(m_staticText115, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
    
    wxArrayString m_choiceCxxEngineArr;
    m_choiceCxxEngineArr.Add(wxT("AStyle"));
    m_choiceCxxEngineArr.Add(wxT("clang-format"));
    m_choiceCxxEngine = new wxChoice(m_panel133, wxID_ANY, wxDefaultPosition, wxSize(-1,-1), m_choiceCxxEngineArr, 0);
    m_choiceCxxEngine->SetToolTip(_("Select the formatter engine for C/C++\nNote that JavaScript, clang-format is always used"));
    m_choiceCxxEngine->SetSelection(1);
    
    flexGridSizer158->Add(m_choiceCxxEngine, 0, wxBOTTOM|wxEXPAND|wxALIGN_CENTER_VERTICAL, 5);
    
    int m_panelCxxImgIndex;
    m_panelCxxImgIndex = m_treebook_il->Add(wxXmlResource::Get()->LoadBitmap(wxT("page_white_cplusplus")));
    m_treebook->AddPage(NULL, _("C++"), false, m_panelCxxImgIndex);
    
    m_panelAstyle = new wxPanel(m_treebook, wxID_ANY, wxDefaultPosition, wxSize(-1,-1), wxTAB_TRAVERSAL);
    int m_panelAstyleImgIndex;
    m_panelAstyleImgIndex = m_treebook_il->Add(wxXmlResource::Get()->LoadBitmap(wxT("astyle")));
    m_treebook->InsertSubPage(1, m_panelAstyle, _("AStyle"), false, m_panelAstyleImgIndex);
    
    wxBoxSizer* boxSizer95 = new wxBoxSizer(wxVERTICAL);
    m_panelAstyle->SetSizer(boxSizer95);
    
    m_splitter145 = new wxSplitterWindow(m_panelAstyle, wxID_ANY, wxDefaultPosition, wxSize(-1,-1), wxSP_LIVE_UPDATE);
    m_splitter145->SetSashGravity(0.5);
    m_splitter145->SetMinimumPaneSize(10);
    
    boxSizer95->Add(m_splitter145, 1, wxEXPAND, 5);
    
    m_splitterPage149 = new wxPanel(m_splitter145, wxID_ANY, wxDefaultPosition, wxSize(-1,-1), wxTAB_TRAVERSAL);
    
    wxBoxSizer* boxSizer155 = new wxBoxSizer(wxVERTICAL);
    m_splitterPage149->SetSizer(boxSizer155);
    
    wxArrayString m_pgMgrAstyleArr;
    wxUnusedVar(m_pgMgrAstyleArr);
    wxArrayInt m_pgMgrAstyleIntArr;
    wxUnusedVar(m_pgMgrAstyleIntArr);
    m_pgMgrAstyle = new wxPropertyGridManager(m_splitterPage149, wxID_ANY, wxDefaultPosition, wxSize(-1,-1), wxPG_DESCRIPTION|wxPG_SPLITTER_AUTO_CENTER|wxPG_BOLD_MODIFIED);
    
    boxSizer155->Add(m_pgMgrAstyle, 1, wxALL|wxEXPAND, 2);
    
    m_pgPropAstyleOptions = m_pgMgrAstyle->Append(  new wxPropertyCategory( _("AStyle Options") ) );
    m_pgPropAstyleOptions->SetHelpString(wxT(""));
    
    m_pgMgrAstyleArr.Clear();
    m_pgMgrAstyleIntArr.Clear();
    m_pgMgrAstyleArr.Add(_("GNU"));
    m_pgMgrAstyleArr.Add(_("Java"));
    m_pgMgrAstyleArr.Add(_("K&R"));
    m_pgMgrAstyleArr.Add(_("Linux"));
    m_pgMgrAstyleArr.Add(_("ANSI"));
    m_pgPropPreDefinedStyles = m_pgMgrAstyle->AppendIn( m_pgPropAstyleOptions,  new wxEnumProperty( _("PreDefined Styles"), wxPG_LABEL, m_pgMgrAstyleArr, m_pgMgrAstyleIntArr, 0) );
    m_pgPropPreDefinedStyles->SetHelpString(_("Choose the formatting from one of the known styles"));
    
    m_pgMgrAstyleArr.Clear();
    m_pgMgrAstyleIntArr.Clear();
    m_pgMgrAstyleArr.Add(_("Break closing"));
    m_pgMgrAstyleArr.Add(_("Attach"));
    m_pgMgrAstyleArr.Add(_("Linux"));
    m_pgMgrAstyleArr.Add(_("Break"));
    m_pgMgrAstyleArr.Add(_("None"));
    m_pgPropBrackets = m_pgMgrAstyle->AppendIn( m_pgPropAstyleOptions,  new wxEnumProperty( _("Brackets"), wxPG_LABEL, m_pgMgrAstyleArr, m_pgMgrAstyleIntArr, 0) );
    m_pgPropBrackets->SetHelpString(_("Bracket Style options define the bracket style to use"));
    
    m_pgMgrAstyleArr.Clear();
    m_pgMgrAstyleIntArr.Clear();
    m_pgMgrAstyleArr.Add(_("Class"));
    m_pgMgrAstyleArr.Add(_("Brackets"));
    m_pgMgrAstyleArr.Add(_("Switches"));
    m_pgMgrAstyleArr.Add(_("Namespaces"));
    m_pgMgrAstyleArr.Add(_("Case"));
    m_pgMgrAstyleArr.Add(_("Labels"));
    m_pgMgrAstyleArr.Add(_("Blocks"));
    m_pgMgrAstyleArr.Add(_("Preprocessors"));
    m_pgMgrAstyleArr.Add(_("Max Instatement Indent"));
    m_pgMgrAstyleArr.Add(_("Min Instatement Indent"));
    m_pgMgrAstyleIntArr.Add(AS_INDENT_CLASS);
    m_pgMgrAstyleIntArr.Add(AS_INDENT_BRACKETS);
    m_pgMgrAstyleIntArr.Add(AS_INDENT_SWITCHES);
    m_pgMgrAstyleIntArr.Add(AS_INDENT_NAMESPACES);
    m_pgMgrAstyleIntArr.Add(AS_INDENT_CASE);
    m_pgMgrAstyleIntArr.Add(AS_INDENT_LABELS);
    m_pgMgrAstyleIntArr.Add(AS_INDENT_BLOCKS);
    m_pgMgrAstyleIntArr.Add(AS_INDENT_PREPROCESSORS);
    m_pgMgrAstyleIntArr.Add(AS_MAX_INSTATEMENT_INDENT);
    m_pgMgrAstyleIntArr.Add(AS_MIN_COND_INDENT);
    m_pgPropIndentation = m_pgMgrAstyle->AppendIn( m_pgPropAstyleOptions,  new wxFlagsProperty( _("Indentation"), wxPG_LABEL, m_pgMgrAstyleArr, m_pgMgrAstyleIntArr, 0) );
    m_pgPropIndentation->SetHelpString(wxT(""));
    
    m_pgMgrAstyleArr.Clear();
    m_pgMgrAstyleIntArr.Clear();
    m_pgMgrAstyleArr.Add(_("Break Blocks"));
    m_pgMgrAstyleArr.Add(_("Pad Parenthesis"));
    m_pgMgrAstyleArr.Add(_("Break Blocks All"));
    m_pgMgrAstyleArr.Add(_("Pad Parenthesis Outside"));
    m_pgMgrAstyleArr.Add(_("Break else-if"));
    m_pgMgrAstyleArr.Add(_("Pad Parenthesis Inside"));
    m_pgMgrAstyleArr.Add(_("Pad Operators"));
    m_pgMgrAstyleArr.Add(_("UnPad Parenthesis"));
    m_pgMgrAstyleArr.Add(_("One Line Keep Statement"));
    m_pgMgrAstyleArr.Add(_("Fill Empty Lines"));
    m_pgMgrAstyleArr.Add(_("One Line Keep Blocks"));
    m_pgMgrAstyleIntArr.Add(AS_BREAK_BLOCKS);
    m_pgMgrAstyleIntArr.Add(AS_PAD_PARENTHESIS);
    m_pgMgrAstyleIntArr.Add(AS_BREAK_BLOCKS_ALL);
    m_pgMgrAstyleIntArr.Add(AS_PAD_PARENTHESIS_OUT);
    m_pgMgrAstyleIntArr.Add(AS_BREAK_ELSEIF);
    m_pgMgrAstyleIntArr.Add(AS_PAD_PARENTHESIS_IN);
    m_pgMgrAstyleIntArr.Add(AS_PAD_OPER);
    m_pgMgrAstyleIntArr.Add(AS_UNPAD_PARENTHESIS);
    m_pgMgrAstyleIntArr.Add(AS_ONE_LINE_KEEP_STATEMENT);
    m_pgMgrAstyleIntArr.Add(AS_FILL_EMPTY_LINES);
    m_pgMgrAstyleIntArr.Add(AS_ONE_LINE_KEEP_BLOCKS);
    m_pgPropFormatting = m_pgMgrAstyle->AppendIn( m_pgPropAstyleOptions,  new wxFlagsProperty( _("Formatting"), wxPG_LABEL, m_pgMgrAstyleArr, m_pgMgrAstyleIntArr, 0) );
    m_pgPropFormatting->SetHelpString(_("Select one or more formatting option from the list below"));
    
    wxBoxSizer* bCustomSettingsSizer = new wxBoxSizer(wxVERTICAL);
    
    boxSizer155->Add(bCustomSettingsSizer, 0, wxALL|wxEXPAND, 2);
    
    wxBoxSizer* boxSizer57 = new wxBoxSizer(wxHORIZONTAL);
    
    bCustomSettingsSizer->Add(boxSizer57, 0, wxEXPAND, 5);
    
    m_staticText59 = new wxStaticText(m_splitterPage149, wxID_ANY, _("AStyle Only:"), wxDefaultPosition, wxSize(-1,-1), 0);
    wxFont m_staticText59Font = wxSystemSettings::GetFont(wxSYS_DEFAULT_GUI_FONT);
    m_staticText59Font.SetWeight(wxFONTWEIGHT_BOLD);
    m_staticText59->SetFont(m_staticText59Font);
    
    boxSizer57->Add(m_staticText59, 0, wxRIGHT|wxTOP|wxBOTTOM, 5);
    
    m_staticText3 = new wxStaticText(m_splitterPage149, wxID_ANY, _("Custom user settings"), wxDefaultPosition, wxSize(-1, -1), 0);
    
    boxSizer57->Add(m_staticText3, 0, wxALL, 5);
    
    m_textCtrlUserFlags = new wxTextCtrl(m_splitterPage149, wxID_ANY, wxT(""), wxDefaultPosition, wxSize(-1,80), wxTE_RICH2|wxTE_PROCESS_TAB|wxTE_PROCESS_ENTER|wxTE_MULTILINE);
    wxFont m_textCtrlUserFlagsFont(10, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxT("Sans"));
    m_textCtrlUserFlags->SetFont(m_textCtrlUserFlagsFont);
    
    bCustomSettingsSizer->Add(m_textCtrlUserFlags, 1, wxEXPAND, 5);
    
    m_splitterPage153 = new wxPanel(m_splitter145, wxID_ANY, wxDefaultPosition, wxSize(-1,-1), wxTAB_TRAVERSAL);
    m_splitter145->SplitVertically(m_splitterPage149, m_splitterPage153, 0);
    
    wxBoxSizer* boxSizer157 = new wxBoxSizer(wxVERTICAL);
    m_splitterPage153->SetSizer(boxSizer157);
    
    m_textCtrlPreview = new wxStyledTextCtrl(m_splitterPage153, wxID_ANY, wxDefaultPosition, wxSize(-1,-1), 0);
    // Configure the fold margin
    m_textCtrlPreview->SetMarginType     (4, wxSTC_MARGIN_SYMBOL);
    m_textCtrlPreview->SetMarginMask     (4, wxSTC_MASK_FOLDERS);
    m_textCtrlPreview->SetMarginSensitive(4, true);
    m_textCtrlPreview->SetMarginWidth    (4, 0);
    
    // Configure the tracker margin
    m_textCtrlPreview->SetMarginWidth(1, 0);
    
    // Configure the symbol margin
    m_textCtrlPreview->SetMarginType (2, wxSTC_MARGIN_SYMBOL);
    m_textCtrlPreview->SetMarginMask (2, ~(wxSTC_MASK_FOLDERS));
    m_textCtrlPreview->SetMarginWidth(2, 0);
    m_textCtrlPreview->SetMarginSensitive(2, true);
    
    // Configure the line numbers margin
    m_textCtrlPreview->SetMarginType(0, wxSTC_MARGIN_NUMBER);
    m_textCtrlPreview->SetMarginWidth(0,0);
    
    // Configure the line symbol margin
    m_textCtrlPreview->SetMarginType(3, wxSTC_MARGIN_FORE);
    m_textCtrlPreview->SetMarginMask(3, 0);
    m_textCtrlPreview->SetMarginWidth(3,0);
    // Select the lexer
    m_textCtrlPreview->SetLexer(wxSTC_LEX_NULL);
    // Set default font / styles
    m_textCtrlPreview->StyleClearAll();
    m_textCtrlPreview->SetWrapMode(0);
    m_textCtrlPreview->SetIndentationGuides(0);
    m_textCtrlPreview->SetKeyWords(0, wxT(""));
    m_textCtrlPreview->SetKeyWords(1, wxT(""));
    m_textCtrlPreview->SetKeyWords(2, wxT(""));
    m_textCtrlPreview->SetKeyWords(3, wxT(""));
    m_textCtrlPreview->SetKeyWords(4, wxT(""));
    
    boxSizer157->Add(m_textCtrlPreview, 1, wxALL|wxEXPAND, 2);
    
    m_panelClang = new wxPanel(m_treebook, wxID_ANY, wxDefaultPosition, wxSize(-1,-1), wxTAB_TRAVERSAL);
    int m_panelClangImgIndex;
    m_panelClangImgIndex = m_treebook_il->Add(wxXmlResource::Get()->LoadBitmap(wxT("clang")));
    m_treebook->InsertSubPage(1, m_panelClang, _("clang-format"), false, m_panelClangImgIndex);
    
    wxBoxSizer* boxSizer97 = new wxBoxSizer(wxVERTICAL);
    m_panelClang->SetSizer(boxSizer97);
    
    m_splitter165 = new wxSplitterWindow(m_panelClang, wxID_ANY, wxDefaultPosition, wxSize(-1,-1), wxSP_LIVE_UPDATE);
    m_splitter165->SetSashGravity(0.5);
    m_splitter165->SetMinimumPaneSize(10);
    
    boxSizer97->Add(m_splitter165, 1, wxEXPAND, 5);
    
    m_splitterPage169 = new wxPanel(m_splitter165, wxID_ANY, wxDefaultPosition, wxSize(-1,-1), wxTAB_TRAVERSAL);
    
    wxBoxSizer* boxSizer175 = new wxBoxSizer(wxVERTICAL);
    m_splitterPage169->SetSizer(boxSizer175);
    
    wxArrayString m_pgMgrClangArr;
    wxUnusedVar(m_pgMgrClangArr);
    wxArrayInt m_pgMgrClangIntArr;
    wxUnusedVar(m_pgMgrClangIntArr);
    m_pgMgrClang = new wxPropertyGridManager(m_splitterPage169, wxID_ANY, wxDefaultPosition, wxSize(-1,-1), wxPG_DESCRIPTION|wxPG_SPLITTER_AUTO_CENTER|wxPG_BOLD_MODIFIED);
    
    boxSizer175->Add(m_pgMgrClang, 1, wxALL|wxEXPAND, 2);
    
    m_pgPropClangFormat = m_pgMgrClang->Append(  new wxPropertyCategory( _("ClangFormat Options") ) );
    m_pgPropClangFormat->SetHelpString(wxT(""));
    
    m_pgPropClangFormatExePath = m_pgMgrClang->AppendIn( m_pgPropClangFormat,  new wxFileProperty( _("clang-format path"), wxPG_LABEL, wxT("")) );
    #if !defined(__WXOSX__) && !defined(_WIN64)
    m_pgMgrClang->SetPropertyAttribute(m_pgPropClangFormatExePath, wxPG_FILE_WILDCARD, wxT(""));
    #endif // !defined(__WXOSX__) && !defined(_WIN64)
    m_pgPropClangFormatExePath->SetHelpString(_("Select the path to clang-format executable tool"));
    
    m_pgPropColumnLimit = m_pgMgrClang->AppendIn( m_pgPropClangFormat,  new wxIntProperty( _("Column Limit"), wxPG_LABEL, 0) );
    m_pgPropColumnLimit->SetHelpString(_("The column limit\nA column limit of 0 means that there is no column limit.\nIn this case, clang-format will respect the input's line breaking decisions within statements unless they contradict other rules"));
    
    m_pgMgrClangArr.Clear();
    m_pgMgrClangIntArr.Clear();
    m_pgMgrClangArr.Add(_("Linux"));
    m_pgMgrClangArr.Add(_("Attach"));
    m_pgMgrClangArr.Add(_("Stroustrup"));
    m_pgMgrClangArr.Add(_("Allman"));
    m_pgMgrClangArr.Add(_("GNU"));
    m_pgMgrClangIntArr.Add(kLinux);
    m_pgMgrClangIntArr.Add(kAttach);
    m_pgMgrClangIntArr.Add(kStroustrup);
    m_pgMgrClangIntArr.Add(kAllman);
    m_pgMgrClangIntArr.Add(kGNU);
    m_pgPropClangBraceBreakStyle = m_pgMgrClang->AppendIn( m_pgPropClangFormat,  new wxEnumProperty( _("Brace breaking style"), wxPG_LABEL, m_pgMgrClangArr, m_pgMgrClangIntArr, 0) );
    m_pgPropClangBraceBreakStyle->SetHelpString(_("The brace breaking style to use."));
    
    m_pgMgrClangArr.Clear();
    m_pgMgrClangIntArr.Clear();
    m_pgMgrClangArr.Add(_("LLVM"));
    m_pgMgrClangArr.Add(_("Google"));
    m_pgMgrClangArr.Add(_("WebKit"));
    m_pgMgrClangArr.Add(_("Chromium"));
    m_pgMgrClangArr.Add(_("Mozilla"));
    m_pgMgrClangIntArr.Add(kClangFormatLLVM);
    m_pgMgrClangIntArr.Add(kClangFormatGoogle);
    m_pgMgrClangIntArr.Add(kClangFormatWebKit);
    m_pgMgrClangIntArr.Add(kClangFormatChromium);
    m_pgMgrClangIntArr.Add(kClangFormatMozilla);
    m_pgPropClangFormatStyle = m_pgMgrClang->AppendIn( m_pgPropClangFormat,  new wxEnumProperty( _("Style"), wxPG_LABEL, m_pgMgrClangArr, m_pgMgrClangIntArr, 0) );
    m_pgPropClangFormatStyle->SetHelpString(_("Coding style"));
    
    m_pgMgrClangArr.Clear();
    m_pgMgrClangIntArr.Clear();
    m_pgMgrClangArr.Add(_("Align Escaped Newlines Left"));
    m_pgMgrClangArr.Add(_("Align Trailing Comments"));
    m_pgMgrClangArr.Add(_("Allow All Parameters Of Declaration On Next Line"));
    m_pgMgrClangArr.Add(_("Allow Short Functions On A Single Line"));
    m_pgMgrClangArr.Add(_("Allow Short Blocks On A Single Line"));
    m_pgMgrClangArr.Add(_("Allow Short Loops On A Single Line"));
    m_pgMgrClangArr.Add(_("Allow Short If Statements On A SingleLine"));
    m_pgMgrClangArr.Add(_("Always Break Before Multiline Strings"));
    m_pgMgrClangArr.Add(_("Always Break Template Declarations"));
    m_pgMgrClangArr.Add(_("Bin Pack Parameters"));
    m_pgMgrClangArr.Add(_("Break Before Binary Operators"));
    m_pgMgrClangArr.Add(_("Break Before Ternary Operators"));
    m_pgMgrClangArr.Add(_("Break Constructor Initializers Before Comma"));
    m_pgMgrClangArr.Add(_("Indent Case Labels"));
    m_pgMgrClangArr.Add(_("Indent Function DeclarationAfterType"));
    m_pgMgrClangArr.Add(_("Space Before Assignment Operators"));
    m_pgMgrClangArr.Add(_("Space Before Parentheses"));
    m_pgMgrClangArr.Add(_("Spaces In Parentheses"));
    m_pgMgrClangArr.Add(_("Pointer And Reference Aligned to the Right"));
    m_pgMgrClangIntArr.Add(kAlignEscapedNewlinesLeft);
    m_pgMgrClangIntArr.Add(kAlignTrailingComments);
    m_pgMgrClangIntArr.Add(kAllowAllParametersOfDeclarationOnNextLine);
    m_pgMgrClangIntArr.Add(kAllowShortFunctionsOnASingleLine);
    m_pgMgrClangIntArr.Add(kAllowShortBlocksOnASingleLine);
    m_pgMgrClangIntArr.Add(kAllowShortLoopsOnASingleLine);
    m_pgMgrClangIntArr.Add(kAllowShortIfStatementsOnASingleLine);
    m_pgMgrClangIntArr.Add(kAlwaysBreakBeforeMultilineStrings);
    m_pgMgrClangIntArr.Add(kAlwaysBreakTemplateDeclarations);
    m_pgMgrClangIntArr.Add(kBinPackParameters);
    m_pgMgrClangIntArr.Add(kBreakBeforeBinaryOperators);
    m_pgMgrClangIntArr.Add(kBreakBeforeTernaryOperators);
    m_pgMgrClangIntArr.Add(kBreakConstructorInitializersBeforeComma);
    m_pgMgrClangIntArr.Add(kIndentCaseLabels);
    m_pgMgrClangIntArr.Add(kIndentFunctionDeclarationAfterType);
    m_pgMgrClangIntArr.Add(kSpaceBeforeAssignmentOperators);
    m_pgMgrClangIntArr.Add(kSpaceBeforeParens);
    m_pgMgrClangIntArr.Add(kSpacesInParentheses);
    m_pgMgrClangIntArr.Add(kPointerAlignmentRight);
    m_pgPropClangFormattingOptions = m_pgMgrClang->AppendIn( m_pgPropClangFormat,  new wxFlagsProperty( _("Clang Formatting Options"), wxPG_LABEL, m_pgMgrClangArr, m_pgMgrClangIntArr, 0) );
    m_pgPropClangFormattingOptions->SetHelpString(wxT(""));
    
    m_splitterPage173 = new wxPanel(m_splitter165, wxID_ANY, wxDefaultPosition, wxSize(-1,-1), wxTAB_TRAVERSAL);
    m_splitter165->SplitVertically(m_splitterPage169, m_splitterPage173, 0);
    
    wxBoxSizer* boxSizer177 = new wxBoxSizer(wxVERTICAL);
    m_splitterPage173->SetSizer(boxSizer177);
    
    m_textCtrlPreview_Clang = new wxStyledTextCtrl(m_splitterPage173, wxID_ANY, wxDefaultPosition, wxSize(-1,-1), 0);
    // Configure the fold margin
    m_textCtrlPreview_Clang->SetMarginType     (4, wxSTC_MARGIN_SYMBOL);
    m_textCtrlPreview_Clang->SetMarginMask     (4, wxSTC_MASK_FOLDERS);
    m_textCtrlPreview_Clang->SetMarginSensitive(4, true);
    m_textCtrlPreview_Clang->SetMarginWidth    (4, 0);
    
    // Configure the tracker margin
    m_textCtrlPreview_Clang->SetMarginWidth(1, 0);
    
    // Configure the symbol margin
    m_textCtrlPreview_Clang->SetMarginType (2, wxSTC_MARGIN_SYMBOL);
    m_textCtrlPreview_Clang->SetMarginMask (2, ~(wxSTC_MASK_FOLDERS));
    m_textCtrlPreview_Clang->SetMarginWidth(2, 0);
    m_textCtrlPreview_Clang->SetMarginSensitive(2, true);
    
    // Configure the line numbers margin
    m_textCtrlPreview_Clang->SetMarginType(0, wxSTC_MARGIN_NUMBER);
    m_textCtrlPreview_Clang->SetMarginWidth(0,0);
    
    // Configure the line symbol margin
    m_textCtrlPreview_Clang->SetMarginType(3, wxSTC_MARGIN_FORE);
    m_textCtrlPreview_Clang->SetMarginMask(3, 0);
    m_textCtrlPreview_Clang->SetMarginWidth(3,0);
    // Select the lexer
    m_textCtrlPreview_Clang->SetLexer(wxSTC_LEX_NULL);
    // Set default font / styles
    m_textCtrlPreview_Clang->StyleClearAll();
    m_textCtrlPreview_Clang->SetWrapMode(0);
    m_textCtrlPreview_Clang->SetIndentationGuides(0);
    m_textCtrlPreview_Clang->SetKeyWords(0, wxT(""));
    m_textCtrlPreview_Clang->SetKeyWords(1, wxT(""));
    m_textCtrlPreview_Clang->SetKeyWords(2, wxT(""));
    m_textCtrlPreview_Clang->SetKeyWords(3, wxT(""));
    m_textCtrlPreview_Clang->SetKeyWords(4, wxT(""));
    
    boxSizer177->Add(m_textCtrlPreview_Clang, 1, wxALL|wxEXPAND, 2);
    
    m_panelPHP = new wxPanel(m_treebook, wxID_ANY, wxDefaultPosition, wxSize(-1,-1), wxTAB_TRAVERSAL);
    int m_panelPHPImgIndex;
    m_panelPHPImgIndex = m_treebook_il->Add(wxXmlResource::Get()->LoadBitmap(wxT("php")));
    m_treebook->AddPage(m_panelPHP, _("PHP"), false, m_panelPHPImgIndex);
    
    wxBoxSizer* boxSizer99 = new wxBoxSizer(wxVERTICAL);
    m_panelPHP->SetSizer(boxSizer99);
    
    m_splitter119 = new wxSplitterWindow(m_panelPHP, wxID_ANY, wxDefaultPosition, wxSize(-1,-1), wxSP_LIVE_UPDATE);
    m_splitter119->SetSashGravity(0.5);
    m_splitter119->SetMinimumPaneSize(10);
    
    boxSizer99->Add(m_splitter119, 1, wxEXPAND, 5);
    
    m_splitterPage123 = new wxPanel(m_splitter119, wxID_ANY, wxDefaultPosition, wxSize(-1,-1), wxTAB_TRAVERSAL);
    
    wxBoxSizer* boxSizer129 = new wxBoxSizer(wxVERTICAL);
    m_splitterPage123->SetSizer(boxSizer129);
    
    wxArrayString m_pgMgrPhpArr;
    wxUnusedVar(m_pgMgrPhpArr);
    wxArrayInt m_pgMgrPhpIntArr;
    wxUnusedVar(m_pgMgrPhpIntArr);
    m_pgMgrPhp = new wxPropertyGridManager(m_splitterPage123, wxID_ANY, wxDefaultPosition, wxSize(-1,-1), wxPG_DESCRIPTION|wxPG_SPLITTER_AUTO_CENTER|wxPG_BOLD_MODIFIED);
    
    boxSizer129->Add(m_pgMgrPhp, 1, wxALL|wxEXPAND, 2);
    
    m_pgPropPhpFormatter = m_pgMgrPhp->Append(  new wxPropertyCategory( _("PHP") ) );
    m_pgPropPhpFormatter->SetHelpString(_("PHP related settings"));
    
    m_pgMgrPhpArr.Clear();
    m_pgMgrPhpIntArr.Clear();
    m_pgMgrPhpArr.Add(_("Break before class"));
    m_pgMgrPhpArr.Add(_("Break before function"));
    m_pgMgrPhpArr.Add(_("Break before 'while'"));
    m_pgMgrPhpArr.Add(_("Break before 'foreach'"));
    m_pgMgrPhpArr.Add(_("'else' doesn't break"));
    m_pgMgrPhpArr.Add(_("Break after 'heredoc' statement"));
    m_pgMgrPhpIntArr.Add(kPFF_BreakBeforeClass);
    m_pgMgrPhpIntArr.Add(kPFF_BreakBeforeFunction);
    m_pgMgrPhpIntArr.Add(kPFF_BreakBeforeWhile);
    m_pgMgrPhpIntArr.Add(kPFF_BreakBeforeForeach);
    m_pgMgrPhpIntArr.Add(kPFF_ElseOnSameLineAsClosingCurlyBrace);
    m_pgMgrPhpIntArr.Add(kPFF_BreakAfterHeredoc);
    m_pgPropPhpFormatterOptions = m_pgMgrPhp->AppendIn( m_pgPropPhpFormatter,  new wxFlagsProperty( _("PHPFormatter Options"), wxPG_LABEL, m_pgMgrPhpArr, m_pgMgrPhpIntArr, 0) );
    m_pgPropPhpFormatterOptions->SetHelpString(wxT(""));
    
    m_splitterPage127 = new wxPanel(m_splitter119, wxID_ANY, wxDefaultPosition, wxSize(-1,-1), wxTAB_TRAVERSAL);
    m_splitter119->SplitVertically(m_splitterPage123, m_splitterPage127, 0);
    
    wxBoxSizer* boxSizer131 = new wxBoxSizer(wxVERTICAL);
    m_splitterPage127->SetSizer(boxSizer131);
    
    m_stcPhpPreview = new wxStyledTextCtrl(m_splitterPage127, wxID_ANY, wxDefaultPosition, wxSize(-1,-1), 0);
    // Configure the fold margin
    m_stcPhpPreview->SetMarginType     (4, wxSTC_MARGIN_SYMBOL);
    m_stcPhpPreview->SetMarginMask     (4, wxSTC_MASK_FOLDERS);
    m_stcPhpPreview->SetMarginSensitive(4, true);
    m_stcPhpPreview->SetMarginWidth    (4, 0);
    
    // Configure the tracker margin
    m_stcPhpPreview->SetMarginWidth(1, 0);
    
    // Configure the symbol margin
    m_stcPhpPreview->SetMarginType (2, wxSTC_MARGIN_SYMBOL);
    m_stcPhpPreview->SetMarginMask (2, ~(wxSTC_MASK_FOLDERS));
    m_stcPhpPreview->SetMarginWidth(2, 0);
    m_stcPhpPreview->SetMarginSensitive(2, true);
    
    // Configure the line numbers margin
    m_stcPhpPreview->SetMarginType(0, wxSTC_MARGIN_NUMBER);
    m_stcPhpPreview->SetMarginWidth(0,0);
    
    // Configure the line symbol margin
    m_stcPhpPreview->SetMarginType(3, wxSTC_MARGIN_FORE);
    m_stcPhpPreview->SetMarginMask(3, 0);
    m_stcPhpPreview->SetMarginWidth(3,0);
    // Select the lexer
    m_stcPhpPreview->SetLexer(wxSTC_LEX_HTML);
    // Set default font / styles
    m_stcPhpPreview->StyleClearAll();
    m_stcPhpPreview->SetWrapMode(0);
    m_stcPhpPreview->SetIndentationGuides(0);
    m_stcPhpPreview->SetKeyWords(0, wxT(""));
    m_stcPhpPreview->SetKeyWords(1, wxT(""));
    m_stcPhpPreview->SetKeyWords(2, wxT(""));
    m_stcPhpPreview->SetKeyWords(3, wxT(""));
    m_stcPhpPreview->SetKeyWords(4, wxT(""));
    
    boxSizer131->Add(m_stcPhpPreview, 1, wxALL|wxEXPAND, 2);
    
    wxBoxSizer* bSizerButtons = new wxBoxSizer(wxHORIZONTAL);
    
    bSizerMain->Add(bSizerButtons, 0, wxALIGN_CENTER_HORIZONTAL, 5);
    
    m_stdBtnSizer30 = new wxStdDialogButtonSizer();
    
    bSizerButtons->Add(m_stdBtnSizer30, 0, wxALL, 5);
    
    m_buttonOK = new wxButton(this, wxID_OK, wxT(""), wxDefaultPosition, wxSize(-1, -1), 0);
    m_buttonOK->SetDefault();
    m_stdBtnSizer30->AddButton(m_buttonOK);
    
    m_buttonApply = new wxButton(this, wxID_APPLY, wxT(""), wxDefaultPosition, wxSize(-1, -1), 0);
    m_stdBtnSizer30->AddButton(m_buttonApply);
    
    m_buttonCancel = new wxButton(this, wxID_CANCEL, wxT(""), wxDefaultPosition, wxSize(-1, -1), 0);
    m_stdBtnSizer30->AddButton(m_buttonCancel);
    
    m_buttonHelp = new wxButton(this, wxID_HELP, wxT(""), wxDefaultPosition, wxSize(-1, -1), 0);
    m_stdBtnSizer30->AddButton(m_buttonHelp);
    m_stdBtnSizer30->Realize();
    
    m_treebook->ExpandNode( 0, true );
    m_treebook->ExpandNode( 1, true );
    m_treebook->ExpandNode( 2, true );
    m_treebook->ExpandNode( 3, true );
    m_treebook->ExpandNode( 4, true );
    
    SetSizeHints(-1,-1);
    if ( GetSizer() ) {
         GetSizer()->Fit(this);
    }
    Centre(wxBOTH);
    // Connect events
    m_checkBoxFormatOnSave->Connect(wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler(CodeFormatterBaseDlg::OnFormatOnSave), NULL, this);
    m_choiceCxxEngine->Connect(wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler(CodeFormatterBaseDlg::OnChoicecxxengineChoiceSelected), NULL, this);
    m_pgMgrAstyle->Connect(wxEVT_PG_CHANGED, wxPropertyGridEventHandler(CodeFormatterBaseDlg::OnPgmgrastylePgChanged), NULL, this);
    m_textCtrlUserFlags->Connect(wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(CodeFormatterBaseDlg::OnCustomAstyleFlags), NULL, this);
    m_pgMgrClang->Connect(wxEVT_PG_CHANGED, wxPropertyGridEventHandler(CodeFormatterBaseDlg::OnPgmgrclangPgChanged), NULL, this);
    m_pgMgrPhp->Connect(wxEVT_PG_CHANGED, wxPropertyGridEventHandler(CodeFormatterBaseDlg::OnPgmgrphpPgChanged), NULL, this);
    m_buttonOK->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(CodeFormatterBaseDlg::OnOK), NULL, this);
    m_buttonApply->Connect(wxEVT_UPDATE_UI, wxUpdateUIEventHandler(CodeFormatterBaseDlg::OnApplyUI), NULL, this);
    m_buttonApply->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(CodeFormatterBaseDlg::OnApply), NULL, this);
    m_buttonHelp->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(CodeFormatterBaseDlg::OnHelp), NULL, this);
    
}

CodeFormatterBaseDlg::~CodeFormatterBaseDlg()
{
    m_checkBoxFormatOnSave->Disconnect(wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler(CodeFormatterBaseDlg::OnFormatOnSave), NULL, this);
    m_choiceCxxEngine->Disconnect(wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler(CodeFormatterBaseDlg::OnChoicecxxengineChoiceSelected), NULL, this);
    m_pgMgrAstyle->Disconnect(wxEVT_PG_CHANGED, wxPropertyGridEventHandler(CodeFormatterBaseDlg::OnPgmgrastylePgChanged), NULL, this);
    m_textCtrlUserFlags->Disconnect(wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(CodeFormatterBaseDlg::OnCustomAstyleFlags), NULL, this);
    m_pgMgrClang->Disconnect(wxEVT_PG_CHANGED, wxPropertyGridEventHandler(CodeFormatterBaseDlg::OnPgmgrclangPgChanged), NULL, this);
    m_pgMgrPhp->Disconnect(wxEVT_PG_CHANGED, wxPropertyGridEventHandler(CodeFormatterBaseDlg::OnPgmgrphpPgChanged), NULL, this);
    m_buttonOK->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(CodeFormatterBaseDlg::OnOK), NULL, this);
    m_buttonApply->Disconnect(wxEVT_UPDATE_UI, wxUpdateUIEventHandler(CodeFormatterBaseDlg::OnApplyUI), NULL, this);
    m_buttonApply->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(CodeFormatterBaseDlg::OnApply), NULL, this);
    m_buttonHelp->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(CodeFormatterBaseDlg::OnHelp), NULL, this);
    
}
