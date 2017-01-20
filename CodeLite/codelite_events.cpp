#include "codelite_events.h"

wxDEFINE_EVENT(wxEVT_INIT_DONE, wxCommandEvent);
wxDEFINE_EVENT(wxEVT_EDITOR_CONFIG_CHANGED, wxCommandEvent);
wxDEFINE_EVENT(wxEVT_WORKSPACE_LOADED, wxCommandEvent);
wxDEFINE_EVENT(wxEVT_WORKSPACE_CONFIG_CHANGED, wxCommandEvent);
wxDEFINE_EVENT(wxEVT_WORKSPACE_CLOSED, wxCommandEvent);
wxDEFINE_EVENT(wxEVT_WORKSPACE_CLOSING, wxCommandEvent);
wxDEFINE_EVENT(wxEVT_FILE_VIEW_INIT_DONE, wxCommandEvent);
wxDEFINE_EVENT(wxEVT_FILE_VIEW_REFRESHED, wxCommandEvent);
wxDEFINE_EVENT(wxEVT_FILE_EXP_INIT_DONE, wxCommandEvent);
wxDEFINE_EVENT(wxEVT_FILE_EXP_REFRESHED, wxCommandEvent); 
wxDEFINE_EVENT(wxEVT_CMD_FILE_EXP_ITEM_EXPANDING, wxCommandEvent);
wxDEFINE_EVENT(wxEVT_TREE_ITEM_FILE_ACTIVATED, clCommandEvent);
wxDEFINE_EVENT(wxEVT_PROJ_FILE_ADDED, clCommandEvent);
wxDEFINE_EVENT(wxEVT_PROJ_FILE_REMOVED, clCommandEvent);
wxDEFINE_EVENT(wxEVT_PROJ_REMOVED, clCommandEvent);
wxDEFINE_EVENT(wxEVT_PROJ_ADDED, clCommandEvent);
wxDEFINE_EVENT(wxEVT_FILE_SAVE_BY_BUILD_START, wxCommandEvent);
wxDEFINE_EVENT(wxEVT_FILE_SAVE_BY_BUILD_END, wxCommandEvent);
wxDEFINE_EVENT(wxEVT_FILE_SAVED, clCommandEvent);
wxDEFINE_EVENT(wxEVT_FILE_RENAMED, clFileSystemEvent);
wxDEFINE_EVENT(wxEVT_FILE_SAVEAS, clFileSystemEvent);
wxDEFINE_EVENT(wxEVT_FILE_RETAGGED, wxCommandEvent);
wxDEFINE_EVENT(wxEVT_ACTIVE_EDITOR_CHANGED, wxCommandEvent);
wxDEFINE_EVENT(wxEVT_EDITOR_CLOSING, wxCommandEvent);
wxDEFINE_EVENT(wxEVT_ALL_EDITORS_CLOSING, wxCommandEvent);
wxDEFINE_EVENT(wxEVT_ALL_EDITORS_CLOSED, wxCommandEvent);
wxDEFINE_EVENT(wxEVT_EDITOR_CLICKED, wxCommandEvent);
wxDEFINE_EVENT(wxEVT_EDITOR_SETTINGS_CHANGED, wxCommandEvent);
wxDEFINE_EVENT(wxEVT_CMD_RELOAD_EXTERNALLY_MODIFIED, wxCommandEvent);
wxDEFINE_EVENT(wxEVT_CMD_RELOAD_EXTERNALLY_MODIFIED_NOPROMPT, wxCommandEvent);
wxDEFINE_EVENT(wxEVT_CMD_PROJ_SETTINGS_SAVED, clProjectSettingsEvent);
wxDEFINE_EVENT(wxEVT_CMD_EXECUTE_ACTIVE_PROJECT, clExecuteEvent);
wxDEFINE_EVENT(wxEVT_CMD_IS_PROGRAM_RUNNING, clExecuteEvent);
wxDEFINE_EVENT(wxEVT_CMD_STOP_EXECUTED_PROGRAM, clExecuteEvent);
wxDEFINE_EVENT(wxEVT_BUILD_STARTED, clBuildEvent);
wxDEFINE_EVENT(wxEVT_BUILD_ENDED, clBuildEvent);
wxDEFINE_EVENT(wxEVT_BUILD_STARTING, clBuildEvent);
wxDEFINE_EVENT(wxEVT_GET_PROJECT_CLEAN_CMD, clBuildEvent);
wxDEFINE_EVENT(wxEVT_GET_PROJECT_BUILD_CMD, clBuildEvent);
wxDEFINE_EVENT(wxEVT_GET_IS_PLUGIN_MAKEFILE, clBuildEvent);
wxDEFINE_EVENT(wxEVT_GET_IS_PLUGIN_BUILD, clBuildEvent);
wxDEFINE_EVENT(wxEVT_GET_ADDITIONAL_COMPILEFLAGS, clBuildEvent);
wxDEFINE_EVENT(wxEVT_GET_ADDITIONAL_LINKFLAGS, clBuildEvent);
wxDEFINE_EVENT(wxEVT_PLUGIN_EXPORT_MAKEFILE, clBuildEvent);
wxDEFINE_EVENT(wxEVT_DEBUG_STARTING, clDebugEvent);
wxDEFINE_EVENT(wxEVT_DEBUG_STARTED, clDebugEvent);
wxDEFINE_EVENT(wxEVT_DEBUG_ENDING, clDebugEvent);
wxDEFINE_EVENT(wxEVT_DEBUG_ENDED, clDebugEvent);
wxDEFINE_EVENT(wxEVT_DEBUG_EDITOR_LOST_CONTROL, wxCommandEvent);
wxDEFINE_EVENT(wxEVT_DEBUG_EDITOR_GOT_CONTROL, wxCommandEvent);
wxDEFINE_EVENT(wxEVT_CC_CODE_COMPLETE, clCodeCompletionEvent);
wxDEFINE_EVENT(wxEVT_CCBOX_SELECTION_MADE, clCodeCompletionEvent);
wxDEFINE_EVENT(wxEVT_CC_CODE_COMPLETE_FUNCTION_CALLTIP, clCodeCompletionEvent);
wxDEFINE_EVENT(wxEVT_CC_CODE_COMPLETE_BOX_DISMISSED, clCodeCompletionEvent);
wxDEFINE_EVENT(wxEVT_CC_SHOW_QUICK_OUTLINE, clCodeCompletionEvent);
wxDEFINE_EVENT(wxEVT_CC_TYPEINFO_TIP, clCodeCompletionEvent);
wxDEFINE_EVENT(wxEVT_CC_CODE_COMPLETE_LANG_KEYWORD, clCodeCompletionEvent);
wxDEFINE_EVENT(wxEVT_CC_JUMP_HYPER_LINK, clCodeCompletionEvent);
wxDEFINE_EVENT(wxEVT_CC_FIND_SYMBOL, clCodeCompletionEvent);
wxDEFINE_EVENT(wxEVT_CC_GENERATE_DOXY_BLOCK, clCodeCompletionEvent);
wxDEFINE_EVENT(wxEVT_CMD_CREATE_NEW_WORKSPACE, clCommandEvent);
wxDEFINE_EVENT(wxEVT_CMD_OPEN_WORKSPACE, clCommandEvent);
wxDEFINE_EVENT(wxEVT_CMD_CLOSE_WORKSPACE, clCommandEvent);
wxDEFINE_EVENT(wxEVT_CMD_IS_WORKSPACE_OPEN, clCommandEvent);
wxDEFINE_EVENT(wxEVT_CMD_RETAG_WORKSPACE, wxCommandEvent);
wxDEFINE_EVENT(wxEVT_CMD_RETAG_WORKSPACE_FULL, wxCommandEvent);
wxDEFINE_EVENT(wxEVT_CMD_GET_WORKSPACE_FILES, wxCommandEvent);
wxDEFINE_EVENT(wxEVT_CMD_GET_ACTIVE_PROJECT_FILES, wxCommandEvent);
wxDEFINE_EVENT(wxEVT_CMD_GET_CURRENT_FILE_PROJECT_FILES, wxCommandEvent);
wxDEFINE_EVENT(wxEVT_CMD_OPEN_RESOURCE, wxCommandEvent);
wxDEFINE_EVENT(wxEVT_CMD_EDITOR_CONTEXT_MENU, wxCommandEvent);
wxDEFINE_EVENT(wxEVT_CMD_FIND_IN_FILES_DISMISSED, clCommandEvent);
wxDEFINE_EVENT(wxEVT_CMD_FIND_IN_FILES_SHOWING, clCommandEvent);
wxDEFINE_EVENT(wxEVT_CMD_RETAG_COMPLETED, wxCommandEvent);
wxDEFINE_EVENT(wxEVT_NOTIFY_PAGE_CLOSING, wxNotifyEvent);
wxDEFINE_EVENT(wxEVT_CMD_PAGE_CHANGED, wxCommandEvent);
wxDEFINE_EVENT(wxEVT_REBUILD_WORKSPACE_TREE, wxCommandEvent);
wxDEFINE_EVENT(wxEVT_ACTIVE_PROJECT_CHANGED, clProjectSettingsEvent);
wxDEFINE_EVENT(wxEVT_FINDBAR_ABOUT_TO_SHOW, clFindEvent);
wxDEFINE_EVENT(wxEVT_FINDBAR_RELEASE_EDITOR, clFindEvent);
wxDEFINE_EVENT(wxEVT_CMD_BUILD_PROJECT_ONLY, wxCommandEvent);
wxDEFINE_EVENT(wxEVT_CMD_CLEAN_PROJECT_ONLY, wxCommandEvent);
wxDEFINE_EVENT(wxEVT_CL_THEME_CHANGED, wxCommandEvent);
wxDEFINE_EVENT(wxEVT_CODEFORMATTER_INDENT_COMPLETED, wxCommandEvent);
wxDEFINE_EVENT(wxEVT_CODEFORMATTER_INDENT_STARTING, wxCommandEvent);
wxDEFINE_EVENT(wxEVT_CODELITE_MAINFRAME_GOT_FOCUS, wxCommandEvent);
wxDEFINE_EVENT(wxEVT_PROJECT_TREEITEM_CLICKED, wxCommandEvent);
wxDEFINE_EVENT(wxEVT_CODELITE_ALL_BREAKPOINTS_DELETED, wxCommandEvent);
wxDEFINE_EVENT(wxEVT_CC_SHOW_QUICK_NAV_MENU, clCodeCompletionEvent);
wxDEFINE_EVENT(wxEVT_CMD_RELOAD_WORKSPACE, clCommandEvent);
wxDEFINE_EVENT(wxEVT_COLOUR_TAB, clColourEvent);
wxDEFINE_EVENT(wxEVT_WORKSPACE_VIEW_BUILD_STARTING, clCommandEvent);
wxDEFINE_EVENT(wxEVT_WORKSPACE_VIEW_CUSTOMIZE_PROJECT, clColourEvent);
wxDEFINE_EVENT(wxEVT_GET_TAB_BORDER_COLOUR, clColourEvent);
wxDEFINE_EVENT(wxEVT_DBG_UI_START, clDebugEvent);       
wxDEFINE_EVENT(wxEVT_DBG_UI_CONTINUE, clDebugEvent);    
wxDEFINE_EVENT(wxEVT_DBG_UI_STOP, clDebugEvent);        
wxDEFINE_EVENT(wxEVT_DBG_UI_STEP_IN, clDebugEvent);     
wxDEFINE_EVENT(wxEVT_DBG_UI_STEP_OUT, clDebugEvent);    
wxDEFINE_EVENT(wxEVT_DBG_UI_NEXT, clDebugEvent);        
wxDEFINE_EVENT(wxEVT_DBG_UI_NEXT_INST, clDebugEvent);   
wxDEFINE_EVENT(wxEVT_DBG_UI_INTERRUPT, clDebugEvent);   
wxDEFINE_EVENT(wxEVT_DBG_UI_SHOW_CURSOR, clDebugEvent); 
wxDEFINE_EVENT(wxEVT_DBG_UI_RESTART, clDebugEvent);     
wxDEFINE_EVENT(wxEVT_DBG_IS_RUNNING, clDebugEvent);     
wxDEFINE_EVENT(wxEVT_DBG_UI_TOGGLE_BREAKPOINT, clDebugEvent);
wxDEFINE_EVENT(wxEVT_DBG_CAN_INTERACT, clDebugEvent );
wxDEFINE_EVENT(wxEVT_DBG_EXPR_TOOLTIP, clDebugEvent );

wxDEFINE_EVENT(wxEVT_DBG_IS_PLUGIN_DEBUGGER, clDebugEvent);
wxDEFINE_EVENT(wxEVT_DBG_UI_QUICK_DEBUG, clDebugEvent);            
wxDEFINE_EVENT(wxEVT_DBG_UI_CORE_FILE, clDebugEvent);              
wxDEFINE_EVENT(wxEVT_DBG_UI_ATTACH_TO_PROCESS, clDebugEvent);      
wxDEFINE_EVENT(wxEVT_DBG_UI_DELTE_ALL_BREAKPOINTS, clDebugEvent);  
wxDEFINE_EVENT(wxEVT_DBG_UI_ENABLE_ALL_BREAKPOINTS, clDebugEvent); 
wxDEFINE_EVENT(wxEVT_DBG_UI_DISABLE_ALL_BREAKPOINTS, clDebugEvent);
wxDEFINE_EVENT(wxEVT_CMD_OPEN_PROJ_SETTINGS, clCommandEvent);
wxDEFINE_EVENT(wxEVT_WORKSPACE_RELOAD_STARTED, clCommandEvent);
wxDEFINE_EVENT(wxEVT_WORKSPACE_RELOAD_ENDED, clCommandEvent);
wxDEFINE_EVENT(wxEVT_NEW_PROJECT_WIZARD_SHOWING, clNewProjectEvent);
wxDEFINE_EVENT(wxEVT_NEW_PROJECT_WIZARD_FINISHED, clNewProjectEvent);
wxDEFINE_EVENT(wxEVT_COMPILER_LIST_UPDATED, clCompilerEvent);
wxDEFINE_EVENT(wxEVT_SAVE_ALL_EDITORS, clCommandEvent);
wxDEFINE_EVENT(wxEVT_FORMAT_STRING, clSourceFormatEvent);
wxDEFINE_EVENT(wxEVT_FORMAT_FILE, clSourceFormatEvent);
wxDEFINE_EVENT(wxEVT_CONTEXT_MENU_EDITOR, clContextMenuEvent);
wxDEFINE_EVENT(wxEVT_CONTEXT_MENU_EDITOR_MARGIN, clContextMenuEvent);
wxDEFINE_EVENT(wxEVT_CONTEXT_MENU_FOLDER, clContextMenuEvent);
wxDEFINE_EVENT(wxEVT_CONTEXT_MENU_VIRTUAL_FOLDER, clContextMenuEvent);
wxDEFINE_EVENT(wxEVT_CONTEXT_MENU_FILE, clContextMenuEvent);
wxDEFINE_EVENT(wxEVT_CONTEXT_MENU_PROJECT, clContextMenuEvent);
wxDEFINE_EVENT(wxEVT_CONTEXT_MENU_WORKSPACE, clContextMenuEvent);
wxDEFINE_EVENT(wxEVT_CONTEXT_MENU_TAB_LABEL, clContextMenuEvent);
wxDEFINE_EVENT(wxEVT_CMD_COLOURS_FONTS_UPDATED, clCommandEvent);
wxDEFINE_EVENT(wxEVT_FILE_LOADED, clCommandEvent);
wxDEFINE_EVENT(wxEVT_CL_FRAME_TITLE, clCommandEvent); 
wxDEFINE_EVENT(wxEVT_BEFORE_EDITOR_SAVE, clCommandEvent);
wxDEFINE_EVENT(wxEVT_EDITOR_MODIFIED, clCommandEvent);
wxDEFINE_EVENT(wxEVT_CLANG_CODE_COMPLETE_MESSAGE, clCommandEvent);
wxDEFINE_EVENT(wxEVT_GOING_DOWN, clCommandEvent);
wxDEFINE_EVENT(wxEVT_PROJ_RENAMED, clCommandEvent);
wxDEFINE_EVENT(wxEVT_EDITOR_INITIALIZING, clCommandEvent);
wxDEFINE_EVENT(wxEVT_FILE_SYSTEM_UPDATED, clFileSystemEvent);
wxDEFINE_EVENT(wxEVT_FILES_MODIFIED_REPLACE_IN_FILES, clFileSystemEvent);
wxDEFINE_EVENT(wxEVT_SAVE_SESSION_NEEDED, clCommandEvent);
wxDEFINE_EVENT(wxEVT_ENVIRONMENT_VARIABLES_MODIFIED, clCommandEvent);
wxDEFINE_EVENT(wxEVT_DND_FOLDER_DROPPED, clCommandEvent);
wxDEFINE_EVENT(wxEVT_DND_FILE_DROPPED, clCommandEvent);
wxDEFINE_EVENT(wxEVT_RESTART_CODELITE, clCommandEvent);
wxDEFINE_EVENT(wxEVT_SHOW_WORKSPACE_TAB, clCommandEvent);
wxDEFINE_EVENT(wxEVT_SHOW_OUTPUT_TAB, clCommandEvent);
wxDEFINE_EVENT(wxEVT_PAGE_MODIFIED_UPDATE_UI, clCommandEvent);
wxDEFINE_EVENT(wxEVT_EDITOR_CONFIG_LOADING, clEditorConfigEvent);
