#ifndef GRIDDIALOG_H
#define GRIDDIALOG_H

//(*Headers(GridDialog)
#include <wx/button.h>
#include <wx/checklst.h>
#include <wx/dialog.h>
#include <wx/radiobox.h>
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
		wxCheckListBox* CheckListBox1;
		wxRadioBox* RadioBox1;
		wxSashWindow* SashWindow1;
		wxStaticText* StaticText1;
		wxStaticText* StaticText2;
		wxStaticText* StaticText3;
		wxTextCtrl* TextCtrl1;
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
		static const long ID_CHECKLISTBOX1;
		static const long ID_BUTTON1;
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
		void OnButton1Click1(wxCommandEvent& event);
		//*)

		DECLARE_EVENT_TABLE()
};

#endif
