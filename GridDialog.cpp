#include "GridDialog.h"
#include <array>
#include <iostream>
#include <string>
#include <stdio.h>
#include <fstream>
#include <wx/gdicmn.h>
#include <dataMain.h>
#include "timeCalc.h"
#include "calcGPS.h"
#include <calcGlonass.h>
#include <downlGalileo.h>
#include <calcGalileo.h>

using namespace std;
//(*InternalHeaders(GridDialog)
#include <wx/intl.h>
#include <wx/string.h>
//*)

//(*IdInit(GridDialog)
const long GridDialog::ID_TEXTCTRL1 = wxNewId();
const long GridDialog::ID_STATICTEXT3 = wxNewId();
const long GridDialog::ID_TEXTCTRL7 = wxNewId();
const long GridDialog::ID_STATICTEXT1 = wxNewId();
const long GridDialog::ID_RADIOBOX1 = wxNewId();
const long GridDialog::ID_STATICTEXT2 = wxNewId();
const long GridDialog::ID_CHECKLISTBOX1 = wxNewId();
const long GridDialog::ID_BUTTON1 = wxNewId();
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
	SashWindow1 = new wxSashWindow(this, ID_SASHWINDOW1, wxPoint(80,112), wxSize(304,328), wxSW_3D|wxCLIP_CHILDREN, _T("ID_SASHWINDOW1"));
	TextCtrl1 = new wxTextCtrl(SashWindow1, ID_TEXTCTRL1, wxEmptyString, wxPoint(36,171), wxSize(74,21), 0, wxDefaultValidator, _T("ID_TEXTCTRL1"));
	StaticText3 = new wxStaticText(SashWindow1, ID_STATICTEXT3, wxEmptyString, wxPoint(176,188), wxDefaultSize, 0, _T("ID_STATICTEXT3"));
	TextCtrl7 = new wxTextCtrl(SashWindow1, ID_TEXTCTRL7, wxEmptyString, wxPoint(163,89), wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL7"));
	StaticText1 = new wxStaticText(SashWindow1, ID_STATICTEXT1, _("Конечное значение"), wxPoint(163,71), wxDefaultSize, 0, _T("ID_STATICTEXT1"));
	wxString __wxRadioBoxChoices_1[3] =
	{
		_("Высоте"),
		_("Широте"),
		_("Долготе")
	};
	RadioBox1 = new wxRadioBox(SashWindow1, ID_RADIOBOX1, _("Шаг"), wxPoint(36,51), wxSize(79,86), 3, __wxRadioBoxChoices_1, 1, 0, wxDefaultValidator, _T("ID_RADIOBOX1"));
	StaticText2 = new wxStaticText(SashWindow1, ID_STATICTEXT2, _("Значение сетки"), wxPoint(33,155), wxDefaultSize, 0, _T("ID_STATICTEXT2"));
	CheckListBox1 = new wxCheckListBox(SashWindow1, ID_CHECKLISTBOX1, wxPoint(34,235), wxSize(98,63), 0, 0, 0, wxDefaultValidator, _T("ID_CHECKLISTBOX1"));
	CheckListBox1->Append(_("GDOP"));
	CheckListBox1->Append(_("HDOP"));
	Button1 = new wxButton(SashWindow1, ID_BUTTON1, _("Label"), wxPoint(211,252), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
	SashWindow1->SetSashVisible(wxSASH_TOP,    true);
	SashWindow1->SetSashVisible(wxSASH_BOTTOM, true);
	SashWindow1->SetSashVisible(wxSASH_LEFT,   true);
	SashWindow1->SetSashVisible(wxSASH_RIGHT,  true);
	Center();

	Connect(ID_RADIOBOX1,wxEVT_COMMAND_RADIOBOX_SELECTED,(wxObjectEventFunction)&GridDialog::OnRadioBox1Select);
	Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&GridDialog::OnButton1Click2);

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

void GridDialog::OnRadioButton1Select(wxCommandEvent& event)
{
}

void GridDialog::OnRadioBox1Select(wxCommandEvent& event)
{
}
void GridDialog::OnButton1Click2(wxCommandEvent& event)
{  ofstream f;
  f.open("test\\testRadioBox1.txt");
  int k;
// aa.year = 228;
  int year_down = gData.year ;
  int month_down = gData.month;
  int day_down = gData.day ;
  int hour_predsk;
  int min_predsk;
  int sec_predsk;
  double grid;
  double endd;
  TextCtrl1->GetValue().ToDouble(&grid);
  TextCtrl7->GetValue().ToDouble(&endd);
  timeCalc calc(gData.day,gData.month,gData.year ,gData.hour ,gData.minutes ,gData.sec ,00);
  timeCalc calcGln(gData.day,gData.month,gData.year ,gData.hour ,gData.minutes ,gData.sec ,00);
  int zz = 2021;
  string text1="MCCJ_211024.agp";//gps
  const char* file; // для файла с алм
  file = (text1).c_str();
  timeCalc calcGalileo(gData.day, gData.month, gData.year, 0,0,0,0);
  string text2 = "MCCJ_211024.agl";//gl
  const char* file2; // для файла с алм
  file2 = (text2).c_str();
  const char* file3;
  string text3 = "2021-10-22.xml";//gal
  file3 = (text3).c_str();
  ofstream fgps;
  fgps.open("test\\testCickleGps.txt");
  ofstream fgl;
  fgl.open("test\\testCickleGlonass.txt");
  ofstream fgal;
  fgal.open("test\\testCickleGalileo.txt");
  double sko[5];
  for (int i=0; i<=(endd-gData.H); i+=grid)
  {

  calccGPS( file, sko, calc,
           (gData.B*M_PI/180.0),(gData.L*M_PI/180.0),gData.H);
  fgps<<gData.H<<"\t"<< sko[0]<<"\t"<<sko[1]<<"\t"<<sko[2]<<"\t"<<sko[3]<<"\t"<<sko[4]<<"\n";
  calccGlonass( file2, sko, calcGln,(gData.B*M_PI/180.0),(gData.L*M_PI/180.0),gData.H);
  fgl<<gData.H<<"\t"<< sko[0]<<"\t"<<sko[1]<<"\t"<<sko[2]<<"\t"<<sko[3]<<"\t"<<sko[4]<<"\n";
  calccGalileo(file3,
                  sko,
                  calc,
                  calcGalileo,
                  (gData.B*M_PI/180.0),(gData.L*M_PI/180.0),gData.H);
 fgal<<gData.H<<"\t"<< sko[0]<<"\t"<<sko[1]<<"\t"<<sko[2]<<"\t"<<sko[3]<<"\t"<<sko[4]<<"\n";
  gData.H +=grid;
  }
  fgps.close();
  fgl.close();
  fgal.close();
  //  wxDateTime T;
//  T = DatePickerCtrl1->GetValue();
//  day_predsk = T.GetDay(); //для скачивания файла
 // month_predsk = T.GetMonth()+1; // тк 1 месяц равен 0;
 // year_predsk = T.GetYear();
//получаем дату и время
// Дата и время от которой предсказывать:
  //dataDialog *a;
 // a->TimePickerCtrl1->GetTime(&hour_predsk, &min_predsk, &sec_predsk);
//wxPoint(int k);
 k = RadioBox1->GetSelection(); // получение высоты/широты/долготы
//RadioBox1->GetItemFromPoint(k);
//int k = static_cast<int>(kk);
 f<<"choise ="<<k;


  f<<"grid = "<<grid;
  int number = CheckListBox1->IsChecked(0); //Выбран ли элемент.
// CheckListBox1->GetItem(number);
//   f<<"\nCheckListBox10 ="<<number<<"\n";
    f<<"CheckListBox11 ="<<number<<"\n";
     f<<"day_down ="<<day_down<<"\n";
     f<<"month_down ="<<month_down<<"\n";
     f<<"year_down ="<<year_down<<"\n";
      f<<"gData.hour ="<<gData.hour<<"\n";
       f<<"minutes ="<<gData.minutes<<"\n";
        f<<"sec ="<<gData.sec<<"\n";
        f<<"B ="<<gData.B<<"\n";
        f<<"L ="<<gData.L<<"\n";
        f<<"H ="<<gData.H<<"\n";
     f<<"t ="<<gData.typeGnss<<"\n";
 f.close();
}
