/***************************************************************
 * Name:      InterfazMain.h
 * Purpose:   Defines Application Frame
 * Author:    Herman  ()
 * Created:   2023-09-11
 * Copyright: Herman  ()
 * License:
 **************************************************************/

#ifndef INTERFAZMAIN_H
#define INTERFAZMAIN_H

#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

#include "InterfazApp.h"


#include <wx/button.h>
#include <wx/statline.h>
class InterfazDialog: public wxDialog
{
    public:
        InterfazDialog(wxDialog *dlg, const wxString& title);
        ~InterfazDialog();

    protected:
        enum
        {
            idBtnQuit = 1000,
            idBtnAbout
        };
        wxStaticText* m_staticText1;
        wxButton* BtnAbout;
        wxStaticLine* m_staticline1;
        wxButton* BtnQuit;

    private:
        void OnClose(wxCloseEvent& event);
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        DECLARE_EVENT_TABLE()
};

#endif // INTERFAZMAIN_H
