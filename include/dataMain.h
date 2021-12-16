/***************************************************************
 * Name:      dataMain.h
 * Purpose:   Defines Application Frame
 * Author:    aaa ()
 * Created:   2019-08-14
 * Copyright: aaa ()
 * License:
 **************************************************************/

#ifndef dataMAIN_H
#define dataMAIN_H

//(*Headers(dataDialog)
#include <wx/button.h>
#include <wx/choice.h>
#include <wx/datectrl.h>
#include <wx/dateevt.h>
#include <wx/dialog.h>
#include <wx/notebook.h>
#include <wx/sashwin.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/timectrl.h>
//*)
#include <wx/grid.h>
#include <wx/spinctrl.h>
//#include <wx/gdicmn.h>


class dataDialog: public wxDialog
{
    public:
        dataDialog(wxWindow* parent,wxWindowID id = -1);
         int type;
        virtual ~dataDialog();

    private:

        //(*Handlers(dataDialog)
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        void OnSashWindow1SashDragged(wxSashEvent& event);
        void OnButton1Click(wxCommandEvent& event);
        void OnButton2Click(wxCommandEvent& event);
        void OnComboBox1Selected(wxCommandEvent& event);
        void OnButton3Click(wxCommandEvent& event);
        void OnTextCtrl1Text(wxCommandEvent& event);
        void OnInit(wxInitDialogEvent& event);
        void OnGrid1CellLeftClick(wxGridEvent& event);
        void OnTextCtrl1Text1(wxCommandEvent& event);
        void OnButton1Click1(wxCommandEvent& event);
        void OnRichTextCtrl1Text(wxCommandEvent& event);
        void OnSpinCtrl1Change(wxSpinEvent& event);
        void OnCustom1Paint(wxPaintEvent& event);
        void OnTextCtrlLText(wxCommandEvent& event);
        void OnTextCtrlTEST1Text(wxCommandEvent& event);
        void OnTextCtrlZText(wxCommandEvent& event);
        void OnButton1Click2(wxCommandEvent& event);
        void OnDatePickerCtrl1Changed(wxDateEvent& event);
        void OnButton3Click1(wxCommandEvent& event);
        void OnButton3Click2(wxCommandEvent& event);
        void OnTimePickerCtrl1Changed(wxDateEvent& event);
        void OnButton1Click3(wxCommandEvent& event);
        void OnChoice1Select6(wxCommandEvent& event);
        void OnTextCtrlBText(wxCommandEvent& event);
        void OnTextCtrlLText1(wxCommandEvent& event);
        //*)

        int typeSys();

        void Gridd(const char* file);
        //(*Identifiers(dataDialog)
        static const long ID_DATEPICKERCTRL1;
        static const long ID_CHOICE1;
        static const long ID_BUTTON2;
        static const long ID_NOTEBOOK1;
        static const long ID_BUTTON1;
        static const long ID_TEXTCTRL1;
        static const long ID_TEXTCTRL2;
        static const long ID_TEXTCTRL3;
        static const long ID_STATICTEXT1;
        static const long ID_STATICTEXT2;
        static const long ID_STATICTEXT3;
        static const long ID_STATICTEXT4;
        static const long ID_TIMEPICKERCTRL1;
        static const long ID_BUTTON4;
        static const long ID_STATICTEXT5;
        static const long ID_BUTTON3;
        static const long ID_SASHWINDOW1;
        //*)
     // static const long ID_STATICTEXT4;
        static const long ID_GRID;
        //(*Declarations(dataDialog)
        wxButton* Button1;
        wxButton* Button2;
        wxButton* Button3;
        wxButton* Down;
        wxChoice* Choice1;
        wxDatePickerCtrl* DatePickerCtrl1;
        wxNotebook* Notebook1;
        wxSashWindow* SashWindow1;
        wxStaticText* StaticText1;
        wxStaticText* StaticText2;
        wxStaticText* StaticText3;
        wxStaticText* StaticText4;
        wxStaticText* StaticText5;
        wxTextCtrl* TextCtrlB;
        wxTextCtrl* TextCtrlH;
        wxTextCtrl* TextCtrlL;
        wxTimePickerCtrl* TimePickerCtrl1;
        //*)

       // wxStaticText* StaticText4;
        wxGrid* Grid;

        DECLARE_EVENT_TABLE()
};

#endif // dataMAIN_H
