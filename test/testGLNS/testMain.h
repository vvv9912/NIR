/***************************************************************
 * Name:      testMain.h
 * Purpose:   Defines Application Frame
 * Author:    b ()
 * Created:   2020-06-08
 * Copyright: b ()
 * License:
 **************************************************************/

#ifndef TESTMAIN_H
#define TESTMAIN_H

//(*Headers(testDialog)
#include <wx/button.h>
#include <wx/dialog.h>
#include <wx/sizer.h>
#include <wx/statline.h>
#include <wx/stattext.h>
//*)

class testDialog: public wxDialog
{
    public:

        testDialog(wxWindow* parent,wxWindowID id = -1);
        virtual ~testDialog();

    private:

        //(*Handlers(testDialog)
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        //*)

        //(*Identifiers(testDialog)
        static const long ID_STATICTEXT1;
        static const long ID_BUTTON1;
        static const long ID_STATICLINE1;
        static const long ID_BUTTON2;
        //*)

        //(*Declarations(testDialog)
        wxBoxSizer* BoxSizer1;
        wxBoxSizer* BoxSizer2;
        wxButton* Button1;
        wxButton* Button2;
        wxStaticLine* StaticLine1;
        wxStaticText* StaticText1;
        //*)

        DECLARE_EVENT_TABLE()
};

#endif // TESTMAIN_H
