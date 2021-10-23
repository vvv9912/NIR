#ifndef GRIDDIALOG_H
#define GRIDDIALOG_H

//(*Headers(GridDialog)
#include <wx/button.h>
#include <wx/dialog.h>
#include <wx/radiobut.h>
#include <wx/sashwin.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
//*)

class GridDialog: public wxDialog
{
	public:

		GridDialog(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~GridDialog();

		//(*Declarations(GridDialog)
		wxButton* Button1;
		wxRadioButton* RadioButton1;
		wxRadioButton* RadioButton2;
		wxRadioButton* RadioButton3;
		wxSashWindow* SashWindow1;
		wxStaticText* StaticText1;
		wxStaticText* StaticText2;
		wxStaticText* StaticText3;
		wxStaticText* StaticText4;
		wxStaticText* StaticText5;
		wxTextCtrl* TextCtrl1;
		wxTextCtrl* TextCtrl2;
		wxTextCtrl* TextCtrl3;
		wxTextCtrl* TextCtrl4;
		wxTextCtrl* TextCtrl5;
		wxTextCtrl* TextCtrl6;
		wxTextCtrl* TextCtrl7;
		//*)

	protected:

		//(*Identifiers(GridDialog)
		static const long ID_BUTTON1;
		static const long ID_TEXTCTRL1;
		static const long ID_STATICTEXT3;
		static const long ID_TEXTCTRL2;
		static const long ID_TEXTCTRL3;
		static const long ID_TEXTCTRL4;
		static const long ID_TEXTCTRL5;
		static const long ID_TEXTCTRL6;
		static const long ID_RADIOBUTTON1;
		static const long ID_RADIOBUTTON2;
		static const long ID_RADIOBUTTON3;
		static const long ID_TEXTCTRL7;
		static const long ID_STATICTEXT1;
		static const long ID_STATICTEXT4;
		static const long ID_STATICTEXT5;
		static const long ID_STATICTEXT2;
		static const long ID_SASHWINDOW1;
		//*)

	private:

		//(*Handlers(GridDialog)
		void OnButton1Click(wxCommandEvent& event);
		//*)

		DECLARE_EVENT_TABLE()
};

#endif
