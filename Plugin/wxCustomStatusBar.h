#ifndef WXCUSTOMSTATUSBAR_H
#define WXCUSTOMSTATUSBAR_H

#include <wx/statusbr.h>
#include <wx/colour.h>
#include <wx/sharedptr.h>
#include <wx/bitmap.h>
#include "codelite_exports.h"
#include "cl_command_event.h"
#include "wxPNGAnimation.h"

class wxCustomStatusBar;
class WXDLLIMPEXP_SDK wxCustomStatusBarArt
{
protected:
    wxColour m_penColour;
    wxColour m_bgColour;
    wxColour m_textColour;
    wxColour m_textShadowColour;
    wxColour m_separatorColour;

public:
    typedef wxSharedPtr<wxCustomStatusBarArt> Ptr_t;

public:
    wxCustomStatusBarArt();
    virtual ~wxCustomStatusBarArt() {}

    void DrawText(wxDC& dc, wxCoord x, wxCoord y, const wxString& text);
    void DrawFieldSeparator(wxDC& dc, const wxRect& fieldRect);

    void SetBgColour(const wxColour& bgColour) { this->m_bgColour = bgColour; }
    void SetPenColour(const wxColour& penColour) { this->m_penColour = penColour; }
    void SetTextColour(const wxColour& textColour) { this->m_textColour = textColour; }
    const wxColour& GetBgColour() const { return m_bgColour; }
    const wxColour& GetPenColour() const { return m_penColour; }
    const wxColour& GetTextColour() const { return m_textColour; }
    void SetTextShadowColour(const wxColour& textShadowColour) { this->m_textShadowColour = textShadowColour; }
    const wxColour& GetTextShadowColour() const { return m_textShadowColour; }
    void SetSeparatorColour(const wxColour& separatorColour) { this->m_separatorColour = separatorColour; }
    const wxColour& GetSeparatorColour() const { return m_separatorColour; }
};

//================---------------
// Base field
//================---------------
class WXDLLIMPEXP_SDK wxCustomStatusBarField : public wxEvtHandler
{
protected:
    wxRect m_rect;
    wxString m_tooltip;

public:
    typedef wxSharedPtr<wxCustomStatusBarField> Ptr_t;
    typedef std::vector<wxCustomStatusBarField::Ptr_t> Vect_t;

    wxCustomStatusBarField() {}
    virtual ~wxCustomStatusBarField() {}

    /**
     * @brief render the field content
     * @param dc the device content
     * @param rect the field bounding rect
     */
    virtual void Render(wxDC& dc, const wxRect& rect, wxCustomStatusBarArt::Ptr_t art) = 0;

    /**
     * @brief return the field length
     */
    virtual size_t GetWidth() const = 0;

    /**
     * @brief return true if this field requires frequest refreshes
     * e.g. animation field needs it
     */
    virtual bool IsRequireFrequentRefresh() const { return false; }

    /**
     * @brief return true if 'point' is inside the current field
     * @param point position in parent coordinates
     */
    bool HitTest(const wxPoint& point) const;

    virtual void SetTooltip(const wxString& tooltip) { this->m_tooltip = tooltip; }
    const wxString& GetTooltip() const { return m_tooltip; }
    template <typename T> T* Cast() const { return dynamic_cast<T*>(const_cast<wxCustomStatusBarField*>(this)); }
};

//================---------------
// Text field
//================---------------
class WXDLLIMPEXP_SDK wxCustomStatusBarFieldText : public wxCustomStatusBarField
{
    wxString m_text;
    size_t m_width;

public:
    wxCustomStatusBarFieldText(size_t width)
        : m_width(width)
    {
    }
    virtual ~wxCustomStatusBarFieldText() {}
    virtual void Render(wxDC& dc, const wxRect& rect, wxCustomStatusBarArt::Ptr_t art);
    void SetText(const wxString& text) { this->m_text = text; }
    const wxString& GetText() const { return m_text; }
    void SetWidth(size_t width) { this->m_width = width; }
    size_t GetWidth() const { return m_width; }
};

//================---------------
// Bitmap field
//================---------------
class WXDLLIMPEXP_SDK wxCustomStatusBarBitmapField : public wxCustomStatusBarField
{
    size_t m_width;
    wxBitmap m_bitmap;

public:
    wxCustomStatusBarBitmapField(size_t width)
        : m_width(width)
    {
    }
    virtual ~wxCustomStatusBarBitmapField() {}
    virtual void Render(wxDC& dc, const wxRect& rect, wxCustomStatusBarArt::Ptr_t art);
    void SetWidth(size_t width) { this->m_width = width; }
    size_t GetWidth() const { return m_width; }
    void SetBitmap(const wxBitmap& bitmap) { this->m_bitmap = bitmap; }
    const wxBitmap& GetBitmap() const { return m_bitmap; }
};

//================---------------
// Animation field
//================---------------
class WXDLLIMPEXP_SDK wxCustomStatusBarAnimationField : public wxCustomStatusBarField
{
    size_t m_width;
    wxPNGAnimation* m_animation;
protected:
    void OnAnimationClicked(wxMouseEvent& event);
    
public:
    /**
     * @brief construct animation field.
     */
    wxCustomStatusBarAnimationField(wxCustomStatusBar* parent,
                                    const wxBitmap& sprite,
                                    wxOrientation spriteOrientation,
                                    const wxSize& animSize);

    virtual ~wxCustomStatusBarAnimationField();
    virtual void Render(wxDC& dc, const wxRect& rect, wxCustomStatusBarArt::Ptr_t art);
    void SetWidth(size_t width) { this->m_width = width; }
    size_t GetWidth() const { return m_width; }
    /**
     * @brief start the animation with a given refresh rate (milliseconds)
     */
    void Start(long refreshRate = 50);
    void Stop();
    /**
     * @brief is the animation running?
     */
    bool IsRunning() const { return m_animation->IsRunning(); }
    
    /**
     * @brief set the tooltip to the animation as well
     */
    virtual void SetTooltip(const wxString& tooltip)
    {
        this->m_tooltip = tooltip;
        if(m_animation) {
            m_animation->SetToolTip(tooltip);
        }
    }
};

//================---------------
// Custom status bar
//================---------------
class WXDLLIMPEXP_SDK wxCustomStatusBar : public wxStatusBar
{
    wxCustomStatusBarArt::Ptr_t m_art;
    wxCustomStatusBarField::Vect_t m_fields;
    wxString m_text;

protected:
    size_t DoGetFieldsWidth();

    // Event handlers
    void OnPaint(wxPaintEvent& event);
    void OnEraseBackround(wxEraseEvent& event);
    void OnLeftDown(wxMouseEvent& event);
    void OnMouseMotion(wxMouseEvent& event);

public:
    /**
     * @brief animation control owned by 'field' was clicked
     */
    void AnimationClicked(wxCustomStatusBarField* field);
    
public:
    wxCustomStatusBar(wxWindow* parent, wxWindowID id = wxID_ANY, long style = 0);
    virtual ~wxCustomStatusBar();

    void SetArt(wxCustomStatusBarArt::Ptr_t art) { this->m_art = art; }
    wxCustomStatusBarArt::Ptr_t GetArt() { return m_art; }

    void AddField(wxCustomStatusBarField::Ptr_t field) { m_fields.push_back(field); }

    /**
     * @brief set text in the main status bar text area
     */
    void SetText(const wxString& message);
    /**
     * @brief clear the main text
     */
    void ClearText();
    /**
     * @brief return pointer to the field at given index
     * if index is out of bounds, return NULL
     */
    wxCustomStatusBarField::Ptr_t GetField(size_t index);

    /**
     * @brief remove status bar field by index
     */
    void RemoveField(size_t index);

    /**
     * @brief return the number of fields
     */
    size_t GetFieldsCount() const { return m_fields.size(); }
};
wxDECLARE_EXPORTED_EVENT(WXDLLIMPEXP_SDK, wxEVT_STATUSBAR_CLICKED, clCommandEvent);
#endif // WXCUSTOMSTATUSBAR_H