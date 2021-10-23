#include "GridDialog.h"

//(*InternalHeaders(GridDialog)
#include <wx/intl.h>
#include <wx/string.h>
//*)

//(*IdInit(GridDialog)
const long GridDialog::ID_BUTTON1 = wxNewId();
const long GridDialog::ID_TEXTCTRL1 = wxNewId();
const long GridDialog::ID_STATICTEXT3 = wxNewId();
const long GridDialog::ID_TEXTCTRL2 = wxNewId();
const long GridDialog::ID_TEXTCTRL3 = wxNewId();
const long GridDialog::ID_TEXTCTRL4 = wxNewId();
const long GridDialog::ID_TEXTCTRL5 = wxNewId();
const long GridDialog::ID_TEXTCTRL6 = wxNewId();
const long GridDialog::ID_RADIOBUTTON1 = wxNewId();
const long GridDialog::ID_RADIOBUTTON2 = wxNewId();
const long GridDialog::ID_RADIOBUTTON3 = wxNewId();
const long GridDialog::ID_TEXTCTRL7 = wxNewId();
const long GridDialog::ID_STATICTEXT1 = wxNewId();
const long GridDialog::ID_STATICTEXT4 = wxNewId();
const long GridDialog::ID_STATICTEXT5 = wxNewId();
const long GridDialog::ID_STATICTEXT2 = wxNewId();
const long GridDialog::ID_SASHWINDOW1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(GridDialog,wxDialog)
	//(*EventTable(GridDialog)
	//*)
END_EVENT_TABLE()

GridDialog::GridDialog(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(GridDialog)
	Create(parent, wxID_ANY, _("Grid"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("wxID_ANY"));
	SetClientSize(wxSize(679,551));
	SetMinSize(wxSize(-1,-1));
	SetMaxSize(wxSize(-1,-1));
	SashWindow1 = new wxSashWindow(this, ID_SASHWINDOW1, wxPoint(80,112), wxSize(472,328), wxSW_3D|wxCLIP_CHILDREN, _T("ID_SASHWINDOW1"));
	Button1 = new wxButton(SashWindow1, ID_BUTTON1, _("Label"), wxPoint(137,30), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
	TextCtrl1 = new wxTextCtrl(SashWindow1, ID_TEXTCTRL1, _("Text"), wxPoint(177,104), wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL1"));
	StaticText3 = new wxStaticText(SashWindow1, ID_STATICTEXT3, wxEmptyString, wxPoint(176,188), wxDefaultSize, 0, _T("ID_STATICTEXT3"));
	TextCtrl2 = new wxTextCtrl(SashWindow1, ID_TEXTCTRL2, _("Text"), wxPoint(175,165), wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL2"));
	TextCtrl3 = new wxTextCtrl(SashWindow1, ID_TEXTCTRL3, _("Text"), wxPoint(175,206), wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL3"));
	TextCtrl4 = new wxTextCtrl(SashWindow1, ID_TEXTCTRL4, _("Text"), wxPoint(21,123), wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL4"));
	TextCtrl5 = new wxTextCtrl(SashWindow1, ID_TEXTCTRL5, _("Text"), wxPoint(19,169), wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL5"));
	TextCtrl6 = new wxTextCtrl(SashWindow1, ID_TEXTCTRL6, _("Text"), wxPoint(314,98), wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL6"));
	RadioButton1 = new wxRadioButton(SashWindow1, ID_RADIOBUTTON1, _("Шаг по высоте"), wxPoint(167,80), wxSize(117,13), 0, wxDefaultValidator, _T("ID_RADIOBUTTON1"));
	RadioButton2 = new wxRadioButton(SashWindow1, ID_RADIOBUTTON2, _("Шаг по широте"), wxPoint(162,138), wxSize(115,13), 0, wxDefaultValidator, _T("ID_RADIOBUTTON2"));
	RadioButton3 = new wxRadioButton(SashWindow1, ID_RADIOBUTTON3, _("Шаг по долготе"), wxPoint(161,190), wxDefaultSize, 0, wxDefaultValidator, _T("ID_RADIOBUTTON3"));
	TextCtrl7 = new wxTextCtrl(SashWindow1, ID_TEXTCTRL7, _("Text"), wxPoint(23,82), wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL7"));
	StaticText1 = new wxStaticText(SashWindow1, ID_STATICTEXT1, _("Высота начальная"), wxPoint(30,64), wxDefaultSize, 0, _T("ID_STATICTEXT1"));
	StaticText4 = new wxStaticText(SashWindow1, ID_STATICTEXT4, _("Широта начальная"), wxPoint(32,108), wxDefaultSize, 0, _T("ID_STATICTEXT4"));
	StaticText5 = new wxStaticText(SashWindow1, ID_STATICTEXT5, _("Высота конечнеая"), wxPoint(319,78), wxDefaultSize, 0, _T("ID_STATICTEXT5"));
	StaticText2 = new wxStaticText(SashWindow1, ID_STATICTEXT2, _("Долгота начальная"), wxPoint(21,151), wxDefaultSize, 0, _T("ID_STATICTEXT2"));
	SashWindow1->SetSashVisible(wxSASH_TOP,    true);
	SashWindow1->SetSashVisible(wxSASH_BOTTOM, true);
	SashWindow1->SetSashVisible(wxSASH_LEFT,   true);
	SashWindow1->SetSashVisible(wxSASH_RIGHT,  true);
	Center();

	Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&GridDialog::OnButton1Click);
	//*)
}

GridDialog::~GridDialog()
{
	//(*Destroy(GridDialog)
	//*)
}


void GridDialog::OnButton1Click(wxCommandEvent& event)
{
}
