#ifndef __clauidockart__
#define __clauidockart__

#include <wx/aui/framemanager.h>
#include <wx/aui/dockart.h>

class CLAuiDockArt : public wxAuiDefaultDockArt
{
	wxBitmap m_bmp_close;
	wxBitmap m_bmp_close_active;

public:
	CLAuiDockArt();
	virtual ~CLAuiDockArt();
	
	void DrawBackground(wxDC& dc, wxWindow* window, int oriantation, const wxRect& rect);
	void DrawPaneButton(wxDC& dc, wxWindow *window, int button, int button_state, const wxRect& rect, wxAuiPaneInfo& pane);
	void DrawGripper   (wxDC& dc, wxWindow *window, const wxRect& rect, wxAuiPaneInfo& pane);
};
#endif // __clauidockart__
