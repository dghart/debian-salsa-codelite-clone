#ifndef __svn_patch_dlg__
#define __svn_patch_dlg__

/**
@file
Subclass of PatchDlgBase, which is generated by wxFormBuilder.
*/

#include "subversion2_ui.h"

//// end generated include

/** Implementing PatchDlgBase */
class PatchDlg : public PatchDlgBase
{
public:
    /** Constructor */
    PatchDlg( wxWindow* parent );
    //// end generated class members

    virtual ~PatchDlg();
    
    wxFilePickerCtrl* GetFilePicker() const {
        return m_filePicker;
    }
    
    wxRadioBox* GetRadioBoxPolicy() const {
        return m_radioBoxEOLPolicy;
    }
};

#endif // __svn_patch_dlg__
