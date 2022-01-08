#include "GridDialog.h"
#include <array>
#include <iostream>
#include <string>
#include <stdio.h>
#include <fstream>

#include <wx/gdicmn.h>
#include <dataMain.h>
#include "include/timeCalc.h"
#include "include/calcGPS.h"
#include <include/calcGlonass.h>
#include <include/downlGalileo.h>
#include <include/calcGalileo.h>
#include <include/calcBeidou.h>

#include "include/geoc2geod.h"

#include "include/getENU.h"
#include <thread>
#include <wx/window.h>
#include <mutex>
//#include <string>
//#include <iostream>
//thread

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
const long GridDialog::ID_BUTTON1 = wxNewId();
const long GridDialog::ID_GAUGE1 = wxNewId();
const long GridDialog::ID_TEXTCTRL2 = wxNewId();
const long GridDialog::ID_STATICTEXT4 = wxNewId();
const long GridDialog::ID_BUTTON2 = wxNewId();
const long GridDialog::ID_SASHWINDOW1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(GridDialog,wxDialog)
  //(*EventTable(GridDialog)
  //*)Np3mq9PeEx7
END_EVENT_TABLE()

GridDialog::GridDialog(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
  //(*Initialize(GridDialog)
  wxSashWindow* SashWindow1;

  Create(parent, wxID_ANY, _("Grid"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("wxID_ANY"));
  SetClientSize(wxSize(288,325));
  SetMinSize(wxSize(-1,-1));
  SetMaxSize(wxSize(-1,-1));
  SashWindow1 = new wxSashWindow(this, ID_SASHWINDOW1, wxPoint(0,0), wxSize(280,328), wxSW_3D, _T("ID_SASHWINDOW1"));
  TextCtrl1 = new wxTextCtrl(SashWindow1, ID_TEXTCTRL1, wxEmptyString, wxPoint(15,161), wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL1"));
  StaticText3 = new wxStaticText(SashWindow1, ID_STATICTEXT3, wxEmptyString, wxPoint(176,188), wxDefaultSize, 0, _T("ID_STATICTEXT3"));
  TextCtrl7 = new wxTextCtrl(SashWindow1, ID_TEXTCTRL7, wxEmptyString, wxPoint(14,120), wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL7"));
  StaticText1 = new wxStaticText(SashWindow1, ID_STATICTEXT1, _("Конечное значение"), wxPoint(19,104), wxDefaultSize, 0, _T("ID_STATICTEXT1"));
  wxString __wxRadioBoxChoices_1[3] =
  {
  	_("Высоте"),
  	_("Широте"),
  	_("Долготе")
  };
  RadioBox1 = new wxRadioBox(SashWindow1, ID_RADIOBOX1, _("Шаг"), wxPoint(14,10), wxSize(79,86), 3, __wxRadioBoxChoices_1, 1, 0, wxDefaultValidator, _T("ID_RADIOBOX1"));
  StaticText2 = new wxStaticText(SashWindow1, ID_STATICTEXT2, _("Значение сетки"), wxPoint(23,144), wxDefaultSize, 0, _T("ID_STATICTEXT2"));
  Button1 = new wxButton(SashWindow1, ID_BUTTON1, _("Получения сетки\n значений"), wxPoint(15,192), wxSize(112,36), 0, wxDefaultValidator, _T("ID_BUTTON1"));
  Gauge1 = new wxGauge(SashWindow1, ID_GAUGE1, 100, wxPoint(29,299), wxSize(223,28), 0, wxDefaultValidator, _T("ID_GAUGE1"));
  TextCtrl2 = new wxTextCtrl(SashWindow1, ID_TEXTCTRL2, wxEmptyString, wxPoint(167,168), wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL2"));
  StaticText4 = new wxStaticText(SashWindow1, ID_STATICTEXT4, _("Кол-во итераций"), wxPoint(172,146), wxDefaultSize, 0, _T("ID_STATICTEXT4"));
  Button2 = new wxButton(SashWindow1, ID_BUTTON2, _("Получения сетки \n со случайными \n значениями"), wxPoint(165,194), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON2"));
  SashWindow1->SetSashVisible(wxSASH_TOP,    true);
  SashWindow1->SetSashVisible(wxSASH_BOTTOM, true);
  SashWindow1->SetSashVisible(wxSASH_LEFT,   true);
  SashWindow1->SetSashVisible(wxSASH_RIGHT,  true);
  Center();

  Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&GridDialog::OnButton2Click2);
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
{
  ofstream f;
  f.open("test\\testRadioBox1.txt");
  int k;
// aa.year = 228;
  int year_down = gData.year ;
  int month_down = gData.month;
  int day_down = gData.day ;
  double grid;
  double endd;
  TextCtrl1->GetValue().ToDouble(&grid);
  TextCtrl7->GetValue().ToDouble(&endd);
  timeCalc calc(gData.day,gData.month,gData.year,gData.hour,gData.minutes,gData.sec,00);
  timeCalc calcGln(gData.day,gData.month,gData.year,gData.hour,gData.minutes,gData.sec,00);

  string text1="MCCJ_211024.agp";//gps
  const char* file; // для файла с алм
  file = (text1).c_str();
  timeCalc calcGalileo(gData.day, gData.month, gData.year, 0,0,0,0);
  string text2 = "MCCJ_211108.agl";//gl
  const char* file2; // для файла с алм
  file2 = (text2).c_str();
  const char* file3;
  string text3 = "2021-10-22.xml";//gal
  file3 = (text3).c_str();



  double sko[5];
  double Bg,Lg,Hg;


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
  double h = gData.H;
  double b = gData.B;
  double l = gData.L;
  int range=0;
  if (k == 0) // высота
  {
    range = endd-gData.H;
    Gauge1->SetRange(range);
    ofstream fgps;
    fgps.open("test\\Gps_H.txt");
    ofstream fgl;
    fgl.open("test\\Glonass_H.txt");
    ofstream fgal;
    fgal.open("test\\Galileo_H.txt");
    for (int i=0; i<=(endd-gData.H); i+=grid)
    {
      Gauge1->SetValue(i);
      calccGPS( file, sko, calc,
                (gData.B*M_PI/180.0),(gData.L*M_PI/180.0),h);

      geoc2geod(sko[0], sko[1], sko[2],&Bg,&Lg,&Hg);
      fgps<<h<<"\t"<< sko[0]<<"\t"<<sko[1]<<"\t"<<sko[2]<<"\t"<<sko[3]<<"\t"<<sko[4]<<Bg<<"\t"<<Lg<<"\t"<<Hg<<"\n";
      geoc2geod(sko[0], sko[1], sko[2],&Bg,&Lg,&Hg);
      calccGlonass( file2, sko, calcGln,(gData.B*M_PI/180.0),(gData.L*M_PI/180.0),h);
      fgl<<h<<"\t"<< sko[0]<<"\t"<<sko[1]<<"\t"<<sko[2]<<"\t"<<sko[3]<<"\t"<<sko[4]<<Bg<<"\t"<<Lg<<"\t"<<Hg<<"\n";
      calccGalileo(file3,
                   sko,
                   calc,
                   calcGalileo,
                   (gData.B*M_PI/180.0),(gData.L*M_PI/180.0),h);
      geoc2geod(sko[0], sko[1], sko[2],&Bg,&Lg,&Hg);
      fgal<<h<<"\t"<< sko[0]<<"\t"<<sko[1]<<"\t"<<sko[2]<<"\t"<<sko[3]<<"\t"<<sko[4]<<Bg<<"\t"<<Lg<<"\t"<<Hg<<"\n";
      h +=grid;
    }
    fgps.close();
    fgl.close();
    fgal.close();
  }
  if (k == 1) //широта B
  {
    range = endd-gData.B;
    Gauge1->SetRange(range);
    ofstream fgps;
    fgps.open("test\\Gps_B.txt");
    ofstream fgl;
    fgl.open("test\\Glonass_B.txt");
    ofstream fgal;
    fgal.open("test\\Galileo_B.txt");

    for (int i=0; i<=(endd-gData.B); i+=grid)
    {
      Gauge1->SetValue(i);
      calccGPS( file, sko, calc,
                (b*M_PI/180.0),(gData.L*M_PI/180.0),gData.H);
      fgps<<b<<"\t"<< sko[0]<<"\t"<<sko[1]<<"\t"<<sko[2]<<"\t"<<sko[3]<<"\t"<<sko[4]<<"\n";
      calccGlonass( file2, sko, calcGln,(b*M_PI/180.0),(gData.L*M_PI/180.0),gData.H);
      fgl<<b<<"\t"<< sko[0]<<"\t"<<sko[1]<<"\t"<<sko[2]<<"\t"<<sko[3]<<"\t"<<sko[4]<<"\n";
      calccGalileo(file3,
                   sko,
                   calc,
                   calcGalileo,
                   (b*M_PI/180.0),(gData.L*M_PI/180.0),gData.H);
      fgal<<b<<"\t"<< sko[0]<<"\t"<<sko[1]<<"\t"<<sko[2]<<"\t"<<sko[3]<<"\t"<<sko[4]<<"\n";
      b +=grid;
    }
    fgps.close();
    fgl.close();
    fgal.close();
  }
  if (k == 2)
  {
    range = endd-gData.L;
    Gauge1->SetRange(range);
    ofstream fgps;
    fgps.open("test\\Gps_L.txt");
    ofstream fgl;
    fgl.open("test\\Glonass_L.txt");
    ofstream fgal;
    fgal.open("test\\Galileo_L.txt");

    for (int i=0; i<=(endd-gData.L); i+=grid)
    {
      Gauge1->SetValue(i);
      calccGPS( file, sko, calc,
                (gData.B*M_PI/180.0),(l*M_PI/180.0),gData.H);
                //geoc2geod(sko[0], sko[1], sko[2],Bg,Lg,Hg);
      fgps<<l<<"\t"<< sko[0]<<"\t"<<sko[1]<<"\t"<<sko[2]<<"\t"<<sko[3]<<"\t"<<sko[4]<<Bg<<"\t"<<Lg<<"\t"<<Hg<<"\n";


      calccGlonass( file2, sko, calcGln,(gData.B*M_PI/180.0),(l*M_PI/180.0),gData.H);
      fgl<<l<<"\t"<< sko[0]<<"\t"<<sko[1]<<"\t"<<sko[2]<<"\t"<<sko[3]<<"\t"<<sko[4]<<"\n";
      calccGalileo(file3,
                   sko,
                   calc,
                   calcGalileo,
                   (gData.B*M_PI/180.0),(l*M_PI/180.0),gData.H);
      fgal<<l<<"\t"<< sko[0]<<"\t"<<sko[1]<<"\t"<<sko[2]<<"\t"<<sko[3]<<"\t"<<sko[4]<<"\n";
      l += grid;
    }
    fgps.close();
    fgl.close();
    fgal.close();
  }


//RadioBox1->GetItemFromPoint(k);
//int k = static_cast<int>(kk);
  f<<"choise ="<<k;


  f<<"grid = "<<grid;

// CheckListBox1->GetItem(number);
//   f<<"\nCheckListBox10 ="<<number<<"\n";
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

void GridDialog::OnTextCtrl2Text(wxCommandEvent& event)
{

}
/*
void GridDialog::testf(int iter)
{
  int year_down=2021;
  int month_down;
  int day_down;
  int hour_predsk;
  int min_predsk;
  int sec_predsk;
  string text1="MCCJ_211024.agp";//gps
  const char* file; // для файла с алм
  file = (text1).c_str();
  timeCalc calcGalileo(gData.day, gData.month, gData.year, 0,0,0,0);
  string text2 = "MCCJ_211108.agl";//gl
  const char* file2; // для файла с алм
  file2 = (text2).c_str();
  const char* file3;
  string text3 = "2021-10-22.xml";//gal
  file3 = (text3).c_str();
  double Bg,Lg,Hg;

 // Gauge1->SetRange(iter);
  ofstream fgps;
  fgps.open("test\\Gps_rand.log");
  ofstream fgl;
  fgl.open("test\\Glonass_rand.log");
  ofstream fgal;
  fgal.open("test\\Galileo_rand.log");
  ofstream ftimes;
  ftimes.open("test\\times_rand.log");
  ofstream fcoord;
  fcoord.open("test\\coord_rand.log");
  //
  fstream clear_file("test\\sumvsb.txt", ios::out);
  clear_file.close();
  fstream clear_file2("test\\sumvsbGl.txt", ios::out);
  clear_file2.close();

  ofstream fTEST;
    fTEST.open("test\\test.txt");
    double COORDD[3];
  //
   fTEST << "Xecef" <<"\t"<< "Yecef" <<"\t"<< "Zecef" <<"\t"<< "B" <<"\t"<< "L" <<"\t"<<"H" <<"\t"<<"Xecu" <<"\t"<< "Yecu" <<"\t"<< "Zecu" <<"\n";
  double H,B,L;
  double sko[5];
  for (int i = 0; i<=iter; i++)
  {
   // Gauge1->SetValue(i);
    month_down = rand() %12+1;
    day_down = rand()%30+1;
    hour_predsk = rand()%24;
    min_predsk = rand()%60;
    sec_predsk = rand()%60;
    B = rand()%180;
    if (B>90)
      B =90-B;
    L = rand()%180;
    if (L>90)
     L=90-L;
    H = rand()%1000;


    fcoord<<H<<"\t"<<B<<"\t"<<L<<"\n";
    timeCalc calc(day_down,month_down,year_down,hour_predsk,min_predsk,sec_predsk,00);
    timeCalc calcGln(day_down,month_down,year_down,hour_predsk,min_predsk,sec_predsk,00);
    timeCalc calcGalileo(day_down,month_down,year_down, 0,0,0,0);
    ftimes<<day_down<<"\t"<<month_down<<"\t"<<year_down<<"\t"<<hour_predsk<<"\t"<<min_predsk<<"\t"<<sec_predsk<<"\n";

    calccGPS( file, sko, calc,
              (B*M_PI/180.0),(L*M_PI/180.0),H);
    geoc2geod(sko[0], sko[1], sko[2],&Bg,&Lg,&Hg);
    getENU(sko[0], sko[1], sko[2],Bg,Lg,COORDD);

    fTEST<< sko[0]<<"\t"<<sko[1]<<"\t"<<sko[2]<<"\t"<<B<<"\t"<<L<<"\t"<<H<<"\t"<<COORDD[0] <<"\t"<< COORDD[1] <<"\t"<<COORDD[2]<<"\n";
    fgps<<H<<"\t"<<L<<"\t"<<B<<"\t"<< sko[0]<<"\t"<<sko[1]<<"\t"<<sko[2]<<"\t"<<sko[3]<<"\t"<<sko[4]<<"\t"<<Bg<<"\t"<<Lg<<"\t"<<Hg<<"\n";
    calccGlonass( file2, sko, calcGln,(B*M_PI/180.0),(L*M_PI/180.0),H);
    geoc2geod(sko[0], sko[1], sko[2],&Bg,&Lg,&Hg);
    fgl<<H<<"\t"<<L<<"\t"<<B<<"\t"<< sko[0]<<"\t"<<sko[1]<<"\t"<<sko[2]<<"\t"<<sko[3]<<"\t"<<sko[4]<<"\t"<<Bg<<"\t"<<Lg<<"\t"<<Hg<<"\n";
    calccGalileo(file3,
               sko,
                calc,
                calcGalileo,
                (B*M_PI/180.0),(L*M_PI/180.0),H);
   geoc2geod(sko[0], sko[1], sko[2],&Bg,&Lg,&Hg);
   fgal<<H<<"\t"<<L<<"\t"<<B<<"\t"<< sko[0]<<"\t"<<sko[1]<<"\t"<<sko[2]<<"\t"<<sko[3]<<"\t"<<sko[4]<<"\t"<<Bg<<"\t"<<Lg<<"\t"<<Hg<<"\n";
  }
  fTEST.close();
  fgps.close();
  fgl.close();
  fgal.close();
  ftimes.close();
  fcoord.close();
}*/
void testf(int iter, int* n_iter)
{
  int year_down=2021;
  int month_down;
  int day_down;
  int hour_predsk;
  int min_predsk;
  int sec_predsk;
  string text1="MCCJ_211226.agp";//gps
  const char* file; // для файла с алм
  file = (text1).c_str();
  timeCalc calcGalileo(gData.day, gData.month, gData.year, 0,0,0,0);
  string text2 = "MCCJ_211226.agl";//gl
  const char* file2; // для файла с алм
  file2 = (text2).c_str();
  const char* file3;
  string text3 = "2021-12-24.xml";//gal
  file3 = (text3).c_str();
  string text4 = "alm_beidou.txt";//gal
  const char* file4;
  file4 = (text4).c_str();
  double Bg,Lg,Hg;

 // Gauge1->SetRange(iter);
  ofstream fgps;
  fgps.open("test\\Gps_rand.log");
  ofstream fgl;
  fgl.open("test\\Glonass_rand.log");
  ofstream fgal;
  fgal.open("test\\Galileo_rand.log");
    ofstream fbeidou;
  fbeidou.open("test\\Beidou_rand.log");
 // ofstream ftimes;
 // ftimes.open("test\\times_rand.log");
  //ofstream fcoord;
  //fcoord.open("test\\coord_rand.log");
  //
 // fstream clear_file("test\\sumvsb.txt", ios::out);
 // clear_file.close();
 // fstream clear_file2("test\\sumvsbGl.txt", ios::out);
 // clear_file2.close();

 // ofstream fTEST;
  //  fTEST.open("test\\test.txt");
    double COORDD[3];
  //
  // fTEST << "Xecef" <<"\t"<< "Yecef" <<"\t"<< "Zecef" <<"\t"<< "B" <<"\t"<< "L" <<"\t"<<"H" <<"\t"<<"Xecu" <<"\t"<< "Yecu" <<"\t"<< "Zecu" <<"\n";
  double H,B,L;
  double sko[5];
  for (int i = 0; i<=iter; i++)
  {
    *n_iter = i;
   // Gauge1->SetValue(i);
    month_down = rand() %12+1;
    day_down = rand()%30+1;
    hour_predsk = rand()%23;
    min_predsk = rand()%60;
    sec_predsk = rand()%60;
    B = rand()%180;
    if (B>90)
      B =90-B;
    L = rand()%180;
    if (L>90)
     L=90-L;
    H = rand()%10000;


    //fcoord<<H<<"\t"<<B<<"\t"<<L<<"\n";
    timeCalc calc(day_down,month_down,year_down,hour_predsk,min_predsk,sec_predsk,00);
    timeCalc calcGln(day_down,month_down,year_down,hour_predsk,min_predsk,sec_predsk,00);
    timeCalc calcGalileo(day_down,month_down,year_down, 0,0,0,0);


   // ftimes<<day_down<<"\t"<<month_down<<"\t"<<year_down<<"\t"<<hour_predsk<<"\t"<<min_predsk<<"\t"<<sec_predsk<<"\n";

    calccGPS( file, sko, calc,
              (B*M_PI/180.0),(L*M_PI/180.0),H);
    geoc2geod(sko[0], sko[1], sko[2],&Bg,&Lg,&Hg);
    if (sko[0] == -10.0 && sko[1] == -10.0)
    {
      COORDD[0] = -10;
      COORDD[1] = -10;
      COORDD[2] = -10;

    }
    else{
      getENU(sko[0], sko[1], sko[2],Bg,Lg,COORDD);
    }

 //   fTEST<< sko[0]<<"\t"<<sko[1]<<"\t"<<sko[2]<<"\t"<<B<<"\t"<<L<<"\t"<<H<<"\t"<<COORDD[0] <<"\t"<< COORDD[1] <<"\t"<<COORDD[2]<<"\n";
    fgps<<H<<"\t"<<L<<"\t"<<B<<"\t"<< sko[0]<<"\t"<<sko[1]<<"\t"<<sko[2]<<"\t"<<sko[3]<<"\t"<<sko[4]<<"\t"<< COORDD[0]<<"\t"<<COORDD[1]<<"\t"<<COORDD[2]<<"\t"<<Bg<<"\t"<<Lg<<"\t"<<Hg<<"\n";
  //  fgps<<H<<"\t"<<L<<"\t"<<B<<"\t"<< COORDD[0]<<"\t"<<COORDD[1]<<"\t"<<COORDD[2]<<"\n";

    calccGlonass( file2, sko, calcGln,(B*M_PI/180.0),(L*M_PI/180.0),H);
    geoc2geod(sko[0], sko[1], sko[2],&Bg,&Lg,&Hg);
      if (sko[0] == -10.0 && sko[1] == -10.0)
    {
      COORDD[0] = -10;
      COORDD[1] = -10;
      COORDD[2] = -10;

    }
    else{
      getENU(sko[0], sko[1], sko[2],Bg,Lg,COORDD);
    }
    fgl<<H<<"\t"<<L<<"\t"<<B<<"\t"<< sko[0]<<"\t"<<sko[1]<<"\t"<<sko[2]<<"\t"<<sko[3]<<"\t"<<sko[4]<<"\t"<< COORDD[0]<<"\t"<<COORDD[1]<<"\t"<<COORDD[2]<<"\t"<<Bg<<"\t"<<Lg<<"\t"<<Hg<<"\n";
 //  fgl<<H<<"\t"<<L<<"\t"<<B<<"\t"<< COORDD[0]<<"\t"<<COORDD[1]<<"\t"<<COORDD[2]<<"\n";
    calccGalileo(file3,
               sko,
                calc,
                calcGalileo,
                (B*M_PI/180.0),(L*M_PI/180.0),H);
   geoc2geod(sko[0], sko[1], sko[2],&Bg,&Lg,&Hg);
     if (sko[0] == -10.0 && sko[1] == -10.0)
    {
      COORDD[0] = -10;
      COORDD[1] = -10;
      COORDD[2] = -10;

    }
    else{
      getENU(sko[0], sko[1], sko[2],Bg,Lg,COORDD);
    }
  fgal<<H<<"\t"<<L<<"\t"<<B<<"\t"<< sko[0]<<"\t"<<sko[1]<<"\t"<<sko[2]<<"\t"<<sko[3]<<"\t"<<sko[4]<<"\t"<< COORDD[0]<<"\t"<<COORDD[1]<<"\t"<<COORDD[2]<<"\t"<<Bg<<"\t"<<Lg<<"\t"<<Hg<<"\n";
 // fgal<<H<<"\t"<<L<<"\t"<<B<<"\t"<< COORDD[0]<<"\t"<<COORDD[1]<<"\t"<<COORDD[2]<<"\n";

 // ftimes<<day_down<<"\t"<<month_down<<"\t"<<year_down<<"\t"<<hour_predsk<<"\t"<<min_predsk<<"\t"<<sec_predsk<<"\n";
 //ftimes<<H<<"\t"<<"B:"<<B<<"\t"<<"L:"<<L<<endl;
  calccBeidou(file4, sko, calc,
              (B*M_PI/180.0),(L*M_PI/180.0),H);
  geoc2geod(sko[0], sko[1], sko[2],&Bg,&Lg,&Hg);
    if (sko[0] == -10.0 && sko[1] == -10.0)
    {
      COORDD[0] = -10;
      COORDD[1] = -10;
      COORDD[2] = -10;

    }
    else{
      getENU(sko[0], sko[1], sko[2],Bg,Lg,COORDD);
    }
 //fbeidou<<H<<"\t"<<L<<"\t"<<B<<"\t"<< sko[0]<<"\t"<<sko[1]<<"\t"<<sko[2]<<"\t"<<sko[3]<<"\t"<<sko[4]<<"\t"<<"\n";
 //   fTEST<< sko[0]<<"\t"<<sko[1]<<"\t"<<sko[2]<<"\t"<<B<<"\t"<<L<<"\t"<<H<<"\t"<<COORDD[0] <<"\t"<< COORDD[1] <<"\t"<<COORDD[2]<<"\n";
   fbeidou<<H<<"\t"<<L<<"\t"<<B<<"\t"<< sko[0]<<"\t"<<sko[1]<<"\t"<<sko[2]<<"\t"<<sko[3]<<"\t"<<sko[4]<<"\t"<< COORDD[0]<<"\t"<<COORDD[1]<<"\t"<<COORDD[2]<<"\t"<<Bg<<"\t"<<Lg<<"\t"<<Hg<<"\n";

  }
 // fTEST.close();
  fgps.close();
  fgl.close();
  fgal.close();
  fbeidou.close();
 // ftimes.close();
 // fcoord.close();
}
//std::mutex mu;

void GridDialog::OnButton2Click2(wxCommandEvent& event)
{
  int iter;
  double iteration;

  TextCtrl2 ->GetValue().ToDouble(&iteration);
  iter = static_cast<int>(iteration);
  int n_iter;
  Gauge1->SetRange(iter);
  testf(iter, &n_iter);
 // std::thread tA(testf, iter, &n_iter);
//  tA.join();
 // tA.detach();
  Gauge1->SetValue(n_iter);

  //Gauge1->SetRange(iter);
//  testf(iter);

 // testf(iteration);
 /* string text1="MCCJ_211024.agp";//gps
  const char* file; // для файла с алм
  file = (text1).c_str();
  timeCalc calcGalileo(gData.day, gData.month, gData.year, 0,0,0,0);
  string text2 = "MCCJ_211108.agl";//gl
  const char* file2; // для файла с алм
  file2 = (text2).c_str();
  const char* file3;
  string text3 = "2021-10-22.xml";//gal
  file3 = (text3).c_str();
  double Bg,Lg,Hg;
  Gauge1->SetRange(iter);
  ofstream fgps;
  fgps.open("test\\Gps_rand.log");
  ofstream fgl;
  fgl.open("test\\Glonass_rand.log");
  ofstream fgal;
  fgal.open("test\\Galileo_rand.log");
  ofstream ftimes;
  ftimes.open("test\\times_rand.log");
  ofstream fcoord;
  fcoord.open("test\\coord_rand.log");
  //
  fstream clear_file("test\\sumvsb.txt", ios::out);
  clear_file.close();
  fstream clear_file2("test\\sumvsbGl.txt", ios::out);
  clear_file2.close();

  ofstream fTEST;
    fTEST.open("test\\test.txt");
    double COORDD[3];
  //
fTEST << "Xecef" <<"\t"<< "Yecef" <<"\t"<< "Zecef" <<"\t"<< "B" <<"\t"<< "L" <<"\t"<<"H" <<"\t"<<"Xecu" <<"\t"<< "Yecu" <<"\t"<< "Zecu" <<"\n";
  double H,B,L;
  double sko[5];
  for (int i = 0; i<=iter; i++)
  {
    Gauge1->SetValue(i);
    month_down = rand() %12+1;
    day_down = rand()%30+1;
    hour_predsk = rand()%24;
    min_predsk = rand()%60;
    sec_predsk = rand()%60;
    B = rand()%180;
    if (B>90)
      B =90-B;
    L = rand()%180;
    if (L>90)
     L=90-L;
    H = rand()%1000;

    fcoord<<H<<"\t"<<B<<"\t"<<L<<"\n";
    timeCalc calc(day_down,month_down,year_down,hour_predsk,min_predsk,sec_predsk,00);
    timeCalc calcGln(day_down,month_down,year_down,hour_predsk,min_predsk,sec_predsk,00);
    timeCalc calcGalileo(day_down,month_down,year_down, 0,0,0,0);
    ftimes<<day_down<<"\t"<<month_down<<"\t"<<year_down<<"\t"<<hour_predsk<<"\t"<<min_predsk<<"\t"<<sec_predsk<<"\n";

    calccGPS( file, sko, calc,
              (B*M_PI/180.0),(L*M_PI/180.0),H);
    geoc2geod(sko[0], sko[1], sko[2],&Bg,&Lg,&Hg);
    getENU(sko[0], sko[1], sko[2],Bg,Lg,COORDD);

    fTEST<< sko[0]<<"\t"<<sko[1]<<"\t"<<sko[2]<<"\t"<<B<<"\t"<<L<<"\t"<<H<<"\t"<<COORDD[0] <<"\t"<< COORDD[1] <<"\t"<<COORDD[2]<<"\n";
    fgps<<H<<"\t"<<L<<"\t"<<B<<"\t"<< sko[0]<<"\t"<<sko[1]<<"\t"<<sko[2]<<"\t"<<sko[3]<<"\t"<<sko[4]<<"\t"<<Bg<<"\t"<<Lg<<"\t"<<Hg<<"\n";
    calccGlonass( file2, sko, calcGln,(B*M_PI/180.0),(L*M_PI/180.0),H);
    geoc2geod(sko[0], sko[1], sko[2],&Bg,&Lg,&Hg);
    fgl<<H<<"\t"<<L<<"\t"<<B<<"\t"<< sko[0]<<"\t"<<sko[1]<<"\t"<<sko[2]<<"\t"<<sko[3]<<"\t"<<sko[4]<<"\t"<<Bg<<"\t"<<Lg<<"\t"<<Hg<<"\n";
    calccGalileo(file3,
               sko,
                calc,
                calcGalileo,
                (B*M_PI/180.0),(L*M_PI/180.0),H);
   geoc2geod(sko[0], sko[1], sko[2],&Bg,&Lg,&Hg);
   fgal<<H<<"\t"<<L<<"\t"<<B<<"\t"<< sko[0]<<"\t"<<sko[1]<<"\t"<<sko[2]<<"\t"<<sko[3]<<"\t"<<sko[4]<<"\t"<<Bg<<"\t"<<Lg<<"\t"<<Hg<<"\n";
  }
  fTEST.close();
  fgps.close();
  fgl.close();
  fgal.close();
  ftimes.close();
  fcoord.close();*/
}

