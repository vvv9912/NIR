#ifndef GRIDDIALOG_H
#define GRIDDIALOG_H

//(*Headers(GridDialog)
#include <wx/button.h>
#include <wx/dialog.h>
#include <wx/gauge.h>
#include <wx/radiobox.h>
#include <wx/sashwin.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
//*)
extern struct GlobalData{
  int year;
  int month;
  int day;
  int hour;
  int minutes;
  int sec;
  int typeGnss; //0 - Glonass;
  double B;//**PI/180
  double L;
  double H;
} gData;
//extern mydata aa;
class GridDialog: public wxDialog
{
	public:

		GridDialog(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~GridDialog();

		//(*Declarations(GridDialog)
		wxButton* Button1;
		wxButton* Button2;
		wxGauge* Gauge1;
		wxRadioBox* RadioBox1;
		wxStaticText* StaticText1;
		wxStaticText* StaticText2;
		wxStaticText* StaticText3;
		wxStaticText* StaticText4;
		wxTextCtrl* TextCtrl1;
		wxTextCtrl* TextCtrl2;
		wxTextCtrl* TextCtrl7;
		//*)

	protected:

		//(*Identifiers(GridDialog)
		static const long ID_TEXTCTRL1;
		static const long ID_STATICTEXT3;
		static const long ID_TEXTCTRL7;
		static const long ID_STATICTEXT1;
		static const long ID_RADIOBOX1;
		static const long ID_STATICTEXT2;
		static const long ID_BUTTON1;
		static const long ID_GAUGE1;
		static const long ID_TEXTCTRL2;
		static const long ID_STATICTEXT4;
		static const long ID_BUTTON2;
		static const long ID_SASHWINDOW1;
		//*)

	private:

		//(*Handlers(GridDialog)
		void OnButton1Click(wxCommandEvent& event);
		void OnRadioButton1Select(wxCommandEvent& event);
		void OnRadioBox1Select(wxCommandEvent& event);
		void OnCheckListBox1Toggled(wxCommandEvent& event);
		void OnCheckListBox1Toggled1(wxCommandEvent& event);
		void OnSashWindow1SashDragged(wxSashEvent& event);
		void OnButton1Click2(wxCommandEvent& event);
		void OnTextCtrl2Text(wxCommandEvent& event);
		void OnButton2Click(wxCommandEvent& event);
		//*)

		DECLARE_EVENT_TABLE()
};

#endif
