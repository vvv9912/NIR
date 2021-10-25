/***************************************************************
 * Name:      dataMain.cpp
 * Purpose:   Code for Application Frame
 * Author:    aaa ()
 * Created:   2019-08-14
 * Copyright: aaa ()
 * License:
 **************************************************************/

#include "dataMain.h"
#include "FTPdownl.h"
#include "parser.h"
#include "parserGPS.H"
#include "angle.h"
#include "ephemerids.h"
#include "xyz2enu.h"
#include "parserGLNS.H"
#include "ephemeridsGLNS.h"
#include "timeCalc.h"
#include <wx/msgdlg.h>
#include <windows.h>
#include <wininet.h>

#include <urlmon.h> //winApi htttp#
#include "parserGalileo.h"

#include "GridDialog.h"

#include "calcGPS.h"
#include <calcGlonass.h>
#include <downlGalileo.h>
#include <calcGalileo.h>
#include <parserEphGAL.h>
#include <parserEphGPS.h>
#include <parserEphGLNS.h>
//
#include <iostream>
#include <string>
#include <stdio.h>
#include <armadillo>
#include <fstream>
//

#include <wx/window.h>
#include <wx/string.h>
#include <wx/textfile.h>
#include <wx/dialog.h>
#include <wx/msgdlg.h>
#include <wx/spinctrl.h>
#include <wx/intl.h>
#include <wx/settings.h>
#include <wx/wx.h>
#include <wx/choice.h>
#include <wx/timectrl.h>
//

#define SQUARE(val) val * val

using namespace std;
using namespace arma;
int type;
GlobalData gData;
//(*InternalHeaders(dataDialog)
#include <wx/intl.h>
#include <wx/settings.h>
#include <wx/string.h>
//*)

//helper functions
enum wxbuildinfoformat
{
  short_f, long_f
};

wxString wxbuildinfo(wxbuildinfoformat format)
{
  wxString wxbuild(wxVERSION_STRING);

  if (format == long_f )
  {
#if defined(__WXMSW__)
    wxbuild << _T("-Windows");
#elif defined(__UNIX__)
    wxbuild << _T("-Linux");
#endif

#if wxUSE_UNICODE
    wxbuild << _T("-Unicode build");
#else
    wxbuild << _T("-ANSI build");
#endif // wxUSE_UNICODE
  }

  return wxbuild;
}

//(*IdInit(dataDialog)
const long dataDialog::ID_DATEPICKERCTRL1 = wxNewId();
const long dataDialog::ID_CHOICE1 = wxNewId();
const long dataDialog::ID_BUTTON2 = wxNewId();
const long dataDialog::ID_NOTEBOOK1 = wxNewId();
const long dataDialog::ID_BUTTON1 = wxNewId();
const long dataDialog::ID_TEXTCTRL1 = wxNewId();
const long dataDialog::ID_TEXTCTRL2 = wxNewId();
const long dataDialog::ID_TEXTCTRL3 = wxNewId();
const long dataDialog::ID_STATICTEXT1 = wxNewId();
const long dataDialog::ID_STATICTEXT2 = wxNewId();
const long dataDialog::ID_STATICTEXT3 = wxNewId();
const long dataDialog::ID_STATICTEXT4 = wxNewId();
const long dataDialog::ID_TIMEPICKERCTRL1 = wxNewId();
const long dataDialog::ID_BUTTON4 = wxNewId();
const long dataDialog::ID_STATICTEXT5 = wxNewId();
const long dataDialog::ID_BUTTON3 = wxNewId();
const long dataDialog::ID_SASHWINDOW1 = wxNewId();
//*)

const long dataDialog::ID_GRID = wxNewId();
BEGIN_EVENT_TABLE(dataDialog,wxDialog)
  //(*EventTable(dataDialog)
  //*)
END_EVENT_TABLE()
/*
bool download(LPCSTR server, LPCSTR login, LPCSTR pass, LPCSTR local_file, LPCSTR remote_file)
{
  bool status;
  HINTERNET hOpen, hConnection;

  hOpen = InternetOpen(NULL, INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);
  if (hOpen == NULL)
   return false;

  hConnection = InternetConnectA(hOpen, server, 21, login, pass, INTERNET_SERVICE_FTP, INTERNET_FLAG_PASSIVE, 0 );
  if (hConnection == NULL)
 {
   InternetCloseHandle(hOpen);
  return false;
 }

  status=FtpGetFileA(hConnection, local_file, remote_file, true, 0, FTP_TRANSFER_TYPE_UNKNOWN, 0);
  InternetCloseHandle(hConnection);
  InternetCloseHandle(hOpen);
  return status;
}
*/
//Функция скачивания;
/*
URLDownloadToFileA(NULL, "http://www.gsc-europa.eu/sites/default/files/sites/all/files/2021_09_28.xml",
                     "b111.txt", 0,NULL);
*/
dataDialog::dataDialog(wxWindow* parent,wxWindowID id)
{
  //(*Initialize(dataDialog)
  Create(parent, wxID_ANY, _("Data app"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("wxID_ANY"));
  SetClientSize(wxSize(596,556));
  SetMinSize(wxSize(-1,-1));
  SetMaxSize(wxSize(-1,-1));
  SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_INACTIVEBORDER));
  SashWindow1 = new wxSashWindow(this, ID_SASHWINDOW1, wxPoint(56,40), wxSize(480,504), wxSW_3D|wxCLIP_CHILDREN, _T("ID_SASHWINDOW1"));
  SashWindow1->SetForegroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_WINDOWTEXT));
  SashWindow1->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_MENUBAR));
  DatePickerCtrl1 = new wxDatePickerCtrl(SashWindow1, ID_DATEPICKERCTRL1, wxDefaultDateTime, wxPoint(305,65), wxSize(85,21), wxDP_DEFAULT|wxDP_SHOWCENTURY, wxDefaultValidator, _T("ID_DATEPICKERCTRL1"));
  DatePickerCtrl1->SetForegroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_ACTIVEBORDER));
  DatePickerCtrl1->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_HIGHLIGHT));
  Choice1 = new wxChoice(SashWindow1, ID_CHOICE1, wxPoint(33,16), wxSize(244,21), 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE1"));
  Choice1->SetSelection( Choice1->Append(_("Glonass")) );
  Choice1->Append(_("GPS"));
  Choice1->Append(_("Galileo"));
  Choice1->Append(_("Beidou"));
  Choice1->Append(_("QZSS"));
  Button2 = new wxButton(SashWindow1, ID_BUTTON2, _("Загрузить"), wxPoint(305,16), wxSize(127,23), 0, wxDefaultValidator, _T("ID_BUTTON2"));
  Notebook1 = new wxNotebook(SashWindow1, ID_NOTEBOOK1, wxPoint(124,214), wxDefaultSize, 0, _T("ID_NOTEBOOK1"));
  Down = new wxButton(SashWindow1, ID_BUTTON1, _("Обработка "), wxPoint(305,266), wxSize(127,23), 0, wxDefaultValidator, _T("ID_BUTTON1"));
  TextCtrlH = new wxTextCtrl(SashWindow1, ID_TEXTCTRL1, _("0"), wxPoint(305,145), wxSize(127,-1), 0, wxDefaultValidator, _T("ID_TEXTCTRL1"));
  TextCtrlB = new wxTextCtrl(SashWindow1, ID_TEXTCTRL2, _("0"), wxPoint(305,190), wxSize(127,-1), 0, wxDefaultValidator, _T("ID_TEXTCTRL2"));
  TextCtrlL = new wxTextCtrl(SashWindow1, ID_TEXTCTRL3, _("0"), wxPoint(305,235), wxSize(127,-1), 0, wxDefaultValidator, _T("ID_TEXTCTRL3"));
  StaticText1 = new wxStaticText(SashWindow1, ID_STATICTEXT1, _("Введите значение высоты в метрах:"), wxPoint(305,127), wxDefaultSize, 0, _T("ID_STATICTEXT1"));
  StaticText2 = new wxStaticText(SashWindow1, ID_STATICTEXT2, _("Введите значение B в градусах:"), wxPoint(305,172), wxDefaultSize, 0, _T("ID_STATICTEXT2"));
  StaticText3 = new wxStaticText(SashWindow1, ID_STATICTEXT3, _("Введите значение L в градусах:"), wxPoint(305,217), wxDefaultSize, 0, _T("ID_STATICTEXT3"));
  StaticText4 = new wxStaticText(SashWindow1, ID_STATICTEXT4, _("Значения СКО:"), wxPoint(306,294), wxDefaultSize, 0, _T("ID_STATICTEXT4"));
  TimePickerCtrl1 = new wxTimePickerCtrl(SashWindow1, ID_TIMEPICKERCTRL1, wxDateTime::Now(), wxPoint(305,93), wxSize(85,21), 0, wxDefaultValidator, _T("ID_TIMEPICKERCTRL1"));
  Button3 = new wxButton(SashWindow1, ID_BUTTON4, _("для отладки/test"), wxPoint(303,463), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON4"));
  StaticText5 = new wxStaticText(SashWindow1, ID_STATICTEXT5, _("Время прогнозирования по UTC(+3)"), wxPoint(305,49), wxDefaultSize, 0, _T("ID_STATICTEXT5"));
  Button1 = new wxButton(SashWindow1, ID_BUTTON3, _("grid"), wxPoint(312,436), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON3"));
  SashWindow1->SetSashVisible(wxSASH_TOP,    true);
  SashWindow1->SetSashVisible(wxSASH_BOTTOM, true);
  SashWindow1->SetSashVisible(wxSASH_LEFT,   true);
  SashWindow1->SetSashVisible(wxSASH_RIGHT,  true);

  Connect(ID_DATEPICKERCTRL1,wxEVT_DATE_CHANGED,(wxObjectEventFunction)&dataDialog::OnDatePickerCtrl1Changed);
  Connect(ID_CHOICE1,wxEVT_COMMAND_CHOICE_SELECTED,(wxObjectEventFunction)&dataDialog::OnChoice1Select6);
  Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&dataDialog::OnButton2Click);
  Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&dataDialog::OnButton1Click1);
  Connect(ID_TEXTCTRL1,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&dataDialog::OnTextCtrl1Text1);
  Connect(ID_TEXTCTRL2,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&dataDialog::OnTextCtrlBText);
  Connect(ID_TEXTCTRL3,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&dataDialog::OnTextCtrlLText1);
  Connect(ID_TIMEPICKERCTRL1,wxEVT_DATE_CHANGED,(wxObjectEventFunction)&dataDialog::OnTimePickerCtrl1Changed);
  Connect(ID_BUTTON4,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&dataDialog::OnButton3Click2);
  Connect(ID_BUTTON3,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&dataDialog::OnButton1Click3);
  Connect(ID_SASHWINDOW1,wxEVT_SASH_DRAGGED,(wxObjectEventFunction)&dataDialog::OnSashWindow1SashDragged);
  Connect(wxID_ANY,wxEVT_INIT_DIALOG,(wxObjectEventFunction)&dataDialog::OnInit);
  //*)
  gData.typeGnss = Choice1->GetSelection();
  wxDateTime T;
  T = DatePickerCtrl1->GetValue();
  gData.day = T.GetDay(); //для скачивания файла
  gData.month = T.GetMonth()+1; // тк 1 месяц равен 0;
  gData.year = T.GetYear();
  TimePickerCtrl1->GetTime(&gData.hour, &gData.minutes, &gData.sec);
  Grid = new wxGrid(SashWindow1, ID_GRID, wxPoint(33,60), wxSize(244,490), 0, _T("ID_GRID"));

  Grid->CreateGrid(24,2);
  Grid->SetColLabelValue(0, _("SISRE, m"));
  Grid->SetColLabelValue(1, _("SISVE, mm/s"));
  Grid->SetDefaultCellFont( Grid->GetFont() );
  Grid->SetDefaultCellTextColour( Grid->GetForegroundColour() );
}

void dataDialog::OnButton1Click3(wxCommandEvent& event)
{TimePickerCtrl1->GetTime(&gData.hour, &gData.minutes, &gData.sec);
 /*   int hour_predsk;
  int min_predsk;
  int sec_predsk;
  TimePickerCtrl1->GetTime(&hour_predsk, &min_predsk, &sec_predsk);
  gData.hour = hour_predsk;
  gData.minutes= min_predsk;
  gData.sec = sec_predsk;/*int year_predsk;
  int month_predsk;
  int day_predsk;
  wxDateTime T;
  T = DatePickerCtrl1->GetValue();
  day_predsk = T.GetDay(); //для скачивания файла
  month_predsk = T.GetMonth()+1; // тк 1 месяц равен 0;
  year_predsk = T.GetYear();

  aa.day= day_predsk;
  aa.month = month_predsk;
  aa.year = year_predsk;*/
  //g.Create(parent, wxID_ANY, _("Grid"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("wxID_ANY"));
/*	Create(parent, wxID_ANY, _("Grid"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("wxID_ANY"));
	SetClientSize(wxSize(679,551));
	SetMinSize(wxSize(-1,-1));
	SetMaxSize(wxSize(-1,-1));
	SashWindow1 = new wxSashWindow(this, ID_SASHWINDOW1, wxPoint(80,112), wxSize(288,328), wxSW_3D|wxCLIP_CHILDREN, _T("ID_SASHWINDOW1"));
	Button1 = new wxButton(SashWindow1, ID_BUTTON1, _("Label"), wxPoint(197,47), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
	SashWindow1->SetSashVisible(wxSASH_TOP,    true);
	SashWindow1->SetSashVisible(wxSASH_BOTTOM, true);
	SashWindow1->SetSashVisible(wxSASH_LEFT,   true);
	SashWindow1->SetSashVisible(wxSASH_RIGHT,  true);
	Center();

	Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&GridDialog::OnButton1Click);
	//*)*/
GridDialog *g;
g = new GridDialog(this, wxID_ANY, wxDefaultPosition,wxDefaultSize);
g->Show(true);

}

dataDialog::~dataDialog()
{
  //(*Destroy(dataDialog)
  //*)
}

void dataDialog::OnQuit(wxCommandEvent& event)
{
  Close();
}

void dataDialog::OnInit(wxInitDialogEvent& event) {};

void dataDialog::OnAbout(wxCommandEvent& event)
{
  wxString msg = wxbuildinfo(long_f);
  wxMessageBox(msg, _("Welcome to..."));
}

void dataDialog::OnSashWindow1SashDragged(wxSashEvent& event)
{

}

/*
void parseDate(const char* File1, const char* file,
               string text5,string text2,string text3,
               string text4, string textYear)
{
  // Зависиомть от системы, на входе система - на выходе название файла с расширением.
  string text1;
  string text0;
  //gps
  int z =type;
  text1 = text5+text2+text3+text4;
  text0 =   "/MCC/ALMANAC/"+ textYear +"/"+text1;
  switch (z)
  {
  case 0:
    text1 +=".agp"s;

    // f<< " day_down="<< day_down<<endl;
    //  f<< " text4="<< text4<<endl;
    //  const char* File1 ;
    //  const char* file ;
    File1 = text0.c_str();//"/MCC/ALMANAC/2015/MCCJ_150307.agp"//перевод строки с строку Си
    file = text1.c_str();
    //! добавить если файла нет, искать ближайший!
//   f<< "const char* File1"<< File1<<endl;
//   f<< " file"<< file<<endl;
    break;
  case 1:
    //glonass
    text1 += ".agl"s;

    //  f<< " day_down="<< day_down<<endl;
    //  f<< " text4="<< text4<<endl;
    //const char* File1 ;
    //  const char* file ;
    File1 = text0.c_str();//"/MCC/ALMANAC/2015/MCCJ_150307.agl"//перевод строки с строку Си
    file = text1.c_str();
    //  f<< "const char* File1"<< File1<<endl;
//   f<< " file"<< file<<endl;
    //  break;
  }
  text0 =   "/MCC/ALMANAC/"+ textYear +"/"+text1;
}
*/
void dataDialog::OnButton2Click(wxCommandEvent& event)
{

  wxString s;
  const char* File1 ;
  const char* file ;
  /*
  switch (typeSys())
  {
  case 0:
    File1 = "/MCC/PRODUCTS/LATEST/MERMS-GSC_C.ete";
    file = "MERMS-GSC_C.ete";
    wxTextFile file11(wxT("MERMS-GSC_C.ete"));
    if (file11.Exists())
    {
      wxRemoveFile(file);
    }
    break;
  case 1:
    File1 = "/MCC/PRODUCTS/LATEST/MERMS-RSC_C.ete";
    file = "MERMS-RSC_C.ete";
    wxTextFile file11(wxT("MERMS-RSC_C.ete"));
    if (file11.Exists())
    {
      wxRemoveFile(file);
    }
    break;
    case 2:
       File1 = "/MCC/PRODUCTS/LATEST/MERMS-ESC_C.ete";
    file = "MERMS-ESC_C.ete";
    wxTextFile file11(wxT("MERMS-ESC_C.ete"));
    if (file11.Exists())
    {
      wxRemoveFile(file);
    }
    break;
    case 3:
       File1 = "/MCC/PRODUCTS/LATEST/MERMS-CSC_C.ete";
    file = "MERMS-CSC_C.ete";
    wxTextFile file11(wxT("MERMS-CSC_C.ete"));
    if (file11.Exists())
    {
      wxRemoveFile(file);
    }
    break;
    case 4:
       File1 = "/MCC/PRODUCTS/LATEST/MERMS-JSC_C.ete";
    file = "MERMS-JSC_C.ete";
    wxTextFile file11(wxT("MERMS-JSC_C.ete"));
    if (file11.Exists())
    {
      wxRemoveFile(file);
    }
    break;
  }

  }
  */
  //wxMessageBox(Choice1->GetString(Choice1->GetSelection()), _(""));
//  wxString s;
  if ((Choice1->GetString(Choice1->GetSelection()))== "GPS"s)
  {
    File1 = "/MCC/PRODUCTS/LATEST/MERMS-GSC_C.ete";
    file = "MERMS-GSC_C.ete";
    wxTextFile file11(wxT("MERMS-GSC_C.ete"));
     parseEph_GPS(file);
    if (file11.Exists())
    {
      wxRemoveFile(file);
    }
  }
  if ((Choice1->GetString(Choice1->GetSelection()))== "Glonass"s)
  {
    File1 = "/MCC/PRODUCTS/LATEST/MERMS-RSC_C.ete";
    file = "MERMS-RSC_C.ete";
    wxTextFile file11(wxT("MERMS-RSC_C.ete"));
     parseEph_GLNS(file);
    if (file11.Exists())
    {
      wxRemoveFile(file);
    }
  }

  if ((Choice1->GetString(Choice1->GetSelection()))== "Galileo"s)
  {
    File1 = "/MCC/PRODUCTS/LATEST/MERMS-ESC_C.ete";
    file = "MERMS-ESC_C.ete";
    wxTextFile file11(wxT("MERMS-ESC_C.ete"));
    parseEph_Gal(file);
    if (file11.Exists())
    {
      wxRemoveFile(file);
    }
  }
  if ((Choice1->GetString(Choice1->GetSelection()))== "Beidou"s)
  {
    File1 = "/MCC/PRODUCTS/LATEST/MERMS-CSC_C.ete";
    file = "MERMS-CSC_C.ete";
    wxTextFile file11(wxT("MERMS-CSC_C.ete"));
    // parse(file);
    if (file11.Exists())
    {
      wxRemoveFile(file);
    }

  }

  if ((Choice1->GetString(Choice1->GetSelection()))== "QZSS"s)
  {
    File1 = "/MCC/PRODUCTS/LATEST/MERMS-JSC_C.ete";
    file = "MERMS-JSC_C.ete";
    wxTextFile file11(wxT("MERMS-JSC_C.ete"));
    if (file11.Exists())
    {
      wxRemoveFile(file);
    }
  }

  bool down = download( "ftp.glonass-iac.ru", NULL, NULL, File1, file);
  if (!down)
  {
    wxMessageBox(_("Error"), _("Error"));
    return;
  }
  Gridd(file);
}

void dataDialog::Gridd(const char* file)
{
  int k=0;
  int sizeY;
  if (Grid != NULL)
  {
    delete Grid;
  }
  memset(&SISerr,0, sizeof(SISerr));
  int max_sats = parse(file);
  sizeY=490;
  Grid = new wxGrid(SashWindow1, ID_GRID, wxPoint(33,60), wxSize(244,sizeY), 0, _T("ID_GRID"));
  wxString s;
  Grid->CreateGrid(max_sats,2);
  Grid->SetColLabelValue(0, _("SISRE, m"));
  Grid->SetColLabelValue(1, _("SISVE, mm/s"));
  Grid->SetDefaultCellFont( Grid->GetFont() );
  Grid->SetDefaultCellTextColour( Grid->GetForegroundColour() );
  for (k=0; k<max_sats; k++ )
  {
    Grid->SetCellValue((k), 0,  wxString::Format("%.3f", SISerr[k].SISRE));
    Grid->SetCellValue((k), 1,  wxString::Format("%.3f", SISerr[k].SISVE));
  }
}



void dataDialog::OnTextCtrl1Text1(wxCommandEvent& event)
{TextCtrlH->GetValue().ToDouble(&gData.H);
}

void dataDialog::OnSpinCtrl1Change(wxSpinEvent& event)
{

}


void dataDialog::OnButton1Click1(wxCommandEvent& event)
{
  //доп прорвекра
 /* int index;
  gData.typeGnss = Choice1->GetSelection();
  wxDateTime T;
  T = DatePickerCtrl1->GetValue();
  gData.day = T.GetDay(); //для скачивания файла
  gData.month = T.GetMonth()+1; // тк 1 месяц равен 0;
  gData.year = T.GetYear();
  TimePickerCtrl1->GetTime(&gData.hour, &gData.minutes, &gData.sec);
 */ StaticText4 ->ClearBackground();
// Вводим значения h,B,L
  double h;
  double Bgrad;
  double Lgrad;
  TextCtrlH->GetValue().ToDouble(&h);
  TextCtrlB->GetValue().ToDouble(&Bgrad);
  TextCtrlL->GetValue().ToDouble(&Lgrad);
  double PI = M_PI;
  double B; //Latitude
  double L; //Longitude
  B=Bgrad*M_PI/180.0;
  L=Lgrad*M_PI/180.0;
  double N;
  double e=0;
  double a=6378136; // радиус З

// Получение координат потребителя
  N=a/sqrt(1-(e*e)*(sin(B))*(sin(B)));


  double Coord_x;
  double Coord_y;
  double Coord_z;
  Coord_x = (N+h)*cos(B)*cos(L);
  Coord_y = (N+h)*cos(B)*sin(L);
  Coord_z = ((1-e*e)*N+h)*sin(B);
  double Coord_user[3];
  Coord_user[0]=(N+h)*cos(B)*cos(L);
  Coord_user[1]= (N+h)*cos(B)*sin(L);
  Coord_user[2]= ((1-e*e)*N+h)*sin(B);

  double Coord_sput[3];
  double alpha;
//передаем в класс определения времени
//Т.е получили время на которое необходимо предсказать
//Далее "найдем" файл от которого будет высчитывать само предсказание
//если от сегодн. дня, то день -1; тк файл загружается ~ в 18 00;

// Считаем сегодняшн. дату
  int year_predsk = gData.year;
  int month_predsk = gData.month;
  int day_predsk = gData.day;
  int hour_predsk;
  int min_predsk;
  int sec_predsk;
//время от которого скачиваем
  int year_down;
  int month_down;
  int day_down;
//int hour_down;
//int min_down;
//int sec_down ;
 /*  wxDateTime T;
  T = DatePickerCtrl1->GetValue();
 day_predsk = T.GetDay(); //для скачивания файла
  month_predsk = T.GetMonth()+1; // тк 1 месяц равен 0;
  year_predsk = T.GetYear();*/

//получаем дату и время
// Дата и время от которой предсказывать:
  TimePickerCtrl1->GetTime(&hour_predsk, &min_predsk, &sec_predsk);

 // mydata aa;
  time_t nowsec = time(0);
  tm *ltm = localtime(&nowsec);
  int yeartoday = 1900+ltm->tm_year;
  int monthtoday = 1 + ltm->tm_mon;
  int daytoday = ltm->tm_mday;
  int hourrtoday = ltm->tm_hour;
  int mintoday = 1 + ltm->tm_min;
  int sectoday = 1 + ltm->tm_sec;
// Если предсказание  в прошлом, то год ии месяц предсказания остется тот же, но день - прошлый
  day_down = day_predsk-1;
  year_down = year_predsk;
  month_down = month_predsk;
  ofstream f;
  f.open("test\\test2.txt");
  f<< "year_predsk="<< year_predsk<<endl;
  f<< "month_predsk="<< month_predsk<<endl;
  f<< "day_predsk="<< day_predsk<<endl;
  f<< "hour_predsk="<< hour_predsk<<endl;
  f<< "min_predsk="<< min_predsk<<endl;
  f<< "sec_predsk="<< sec_predsk<<endl;



//если предсказание уже на будущее, то год,месяц остается сегодняшний, а день минус 1
//если год = году сейчас, но день больше или равен, то день минус 1
// по сути можно облегчить и сделать 1 цикл через "или"
  if (year_predsk>yeartoday)
  {
    day_down = daytoday -1;
    year_down = yeartoday;
    month_down = monthtoday;
  }
  if (year_predsk == yeartoday)
  {
    if ( day_predsk >= daytoday)
    {
      day_down = daytoday -1;
      year_down = yeartoday;
      month_down = monthtoday;
    }
  }
  f<< "day_download="<< day_down<<endl;
  f<< "month_download="<< month_down<<endl;
  f<< "year_download="<< year_down<<endl;
  timeCalc calc(day_predsk,month_predsk,year_predsk,hour_predsk,min_predsk,sec_predsk,00);

//
//преобразование в слово для скачивания
  string textYear = to_string(year_down); //2021
  string text5 = "MCCJ_";
  string text2 = to_string(year_down -2000); //year itog текущий -1
  string text3 ;
  if (month_down<10)
  {
    text3 = "0"s + to_string(month_down); //month текущий -1
  }
  else
  {
    text3 = to_string(month_down);
  }
  string text4;

  if (day_down<10)
  {
    text4 = "0"s +to_string(day_down); //day текущий -1
  }
  else
  {
    text4 = to_string(day_down);
  }
  string text1; //day download
  string text0;
  f<< " text2="<< text2<<endl;
  f<< " text3="<< text3<<endl;
  f<< " text4="<< text4<<endl;
  mat sko;
  //
  double skoo[5];
  if ((Choice1->GetString(Choice1->GetSelection()))== "GPS")
  {
    downlGPS(&text1, //file alm
                       text2,
                       text3,
                       text4,
                       text5,
                       textYear);
  timeCalc calc(day_predsk,month_predsk,year_predsk,hour_predsk,min_predsk,sec_predsk,00);
  const char* file; // для файла с алм
  file = (text1).c_str();
  calccGPS(file,
          skoo,
          calc,
          B,L,h);

  }
  else if ((Choice1->GetString(Choice1->GetSelection()))== "Glonass")
  {

    downlGlonass(&text1, //file alm
                       text2,
                       text3,
                       text4,
                       text5,
                       textYear);
     timeCalc calcGln(gData.day,gData.month,gData.year ,gData.hour ,gData.minutes ,gData.sec ,00);

     const char* file; // для файла с алм
     file = (text1).c_str();
    calccGlonass(file,
          skoo,
          calcGln,
          B,L,h);
    //для ион
    /*   text1 = "BRDC1510.21n"s;

       text_0 = "/MCC/BRDC/" +textYear +"/" + text_1";

       const char* File11 ;
       const char* file1 ;
       File11 = text0.c_str();//""//перевод строки с строку Си
       file1 = text1.c_str();
       bool down = download( "glonass-iac.ru", NULL, NULL, File11, file1);
      */


  }
  else if ((Choice1->GetString(Choice1->GetSelection()))== "Galileo"s)
  {
      timeCalc calcGalileo(day_down, month_down, year_down, 0,0,0,0);
      const char* file; // для файла с алм
    downGalileo( year_down, &day_down, &text0,
       &text1,
       text2,
        text3,
        text4);
      file = (text1).c_str(); //ссылка на файл
      /*  if (day_down <= 0)
        {
          wxMessageBox(_("Альманах не удалось скачать !"), _("Error"));
          break;
        }*/
    calccGalileo(file,
                  skoo,
                  calc,
                  calcGalileo,
                   B, L,  h );

  }


  //int k =   Downloadhttp("http://www.gsc-europa.eu/sites/default/files/sites/all/files/2021-09-24.xml",
  //"file1.txt"); //_ _ _


  else
  {
    wxMessageBox(_("Выберите другую ГНСС"), _("Error"));
  }
  //double sss = sko(0,0);
  wxString s;
/* s.Printf("Значение СКО:\nСКО для x: %.3f м\nСКО для y: %.3f м\nСКО для z: %.3f м\nСКО для D: %.3f, м СКО: %.3f м",
           sko(0,0), sko(1,1), sko(2,2), sko(3,3), sqrt (pow(sko(0,0),2)+pow(sko(1,1),2)+pow(sko(2,2),2) ));

*/s.Printf("Значение СКО:\nСКО для x: %.3f м\nСКО для y: %.3f м\nСКО для z: %.3f м\nСКО для D: %.3f, м СКО: %.3f м",
  skoo[0], skoo[1], skoo[2], skoo[3], skoo[4]);
  StaticText4->SetLabel(s);
  f.close();
// delete[] calc;
}




void dataDialog::OnDatePickerCtrl1Changed(wxDateEvent& event)
{ wxDateTime T;
  T = DatePickerCtrl1->GetValue();
   gData.day = T.GetDay(); //для скачивания файла
   gData.month = T.GetMonth()+1; // тк 1 месяц равен 0;
   gData.year = T.GetYear();

}
void dataDialog::OnTimePickerCtrl1Changed(wxDateEvent& event)
{
  TimePickerCtrl1->GetTime(&gData.hour, &gData.minutes, &gData.sec);
}
void dataDialog::OnButton3Click1(wxCommandEvent& event)
{
  /*int *hour;
  int *minn;
  int *sec;

  TimePickerCtrl1->GetTime(hour, minn, sec);
  wxString s;
  s.Printf("Значение max_sats: %f\nЗначение PRN: %f\nЗначение t_almanax: %f\nЗначение v0m0:", hour, minn,sec);
  StaticText5->SetLabel(s);
  */
}

void dataDialog::OnButton3Click2(wxCommandEvent& event)
{
   TimePickerCtrl1->GetTime(&gData.hour, &gData.minutes, &gData.sec);
  /*
  int hour;
  int minn;
  int sec;
  wxDateTime T;
  T = DatePickerCtrl1->GetValue();
  int D = T.GetDay();
  int Month = T.GetMonth()+1; // тк 1 месяц равен 0;
  int Year = T.GetYear();
  TimePickerCtrl1->GetTime(&hour, &minn, &sec);
  timeCalc calc(D ,Month,Year ,hour,minn,sec,00);
  calc.timeGPS();
  //отладочные данные/
  ofstream f;
  f.open("test.txt");
  f<< "hour"<< hour<<endl;
  f<< "minn"<< minn<<endl;
  f<<"sec"<<sec<<endl;
  f<<"D"<<D<<endl;
  f<<"Month"<<Month<<endl;
  f<<"Year"<<Year<<endl;
  //f <<"timeGLNS\n"<<"gps.sec_after_week" <<calc.day_after_vis_year<<endl;
    f <<"sec_since_week" <<calc.sec_since_week<<endl;
    f <<"week" <<calc.week<<endl;
    f <<"dT" <<calc.dT<<endl;
    f <<"timeSec" <<calc.timeSec<<endl;
    f <<"c_date" <<calc.c_date<<endl;
    f <<"c_month" <<calc.c_month<<endl;
    f <<"c_date" <<calc.c_date<<endl;
    f <<"c_year" <<calc.c_year<<endl;
    f <<"c_hour" <<calc.c_hour<<endl;
    f <<"c_minutes" <<calc.c_minutes<<endl;
    calc.timeGLL();
  f <<"Galileo\n"<<"sec_since_week" <<calc.sec_since_week<<endl;
  f <<"week" <<calc.week<<endl;
  f <<"dT" <<calc.dT<<endl;
  calc.timeGLNS();
  f <<"-----------------\nGLonass \n"<<"GLNS_day_after_vis_year" <<calc.GLNS_day_after_vis_year<<endl;
  f <<"numb_fouryear_period" <<calc.GLNS_numb_fouryear_period<<endl;
  f <<"GLNS_sec_since_week" <<calc.GLNS_sec_since_week<<endl;

  // Получение коорд спутников
  //ephemerids(double toe,int t_almanax, double M0, double sqrtA, double E, double I, double Om0, double time_week ))

  //my coord

  Coordinates Coord_sp = ephemerids(44271.777,
                                  61440,
                                  0.84951556,
                                  0.51536460*pow(10,4),
                                  0.11027813*pow(10, -1),
                                  0.30822450,
                                  -0.47967029,
                                  1835);

  f <<"-----------------\ncoord \n"<<"Coord_sp.X=" <<Coord_sp.X<<endl;
  f <<"Coord_sp.Y" <<Coord_sp.Y<<endl;
    f <<"Coord_sp.Z" <<Coord_sp.Z<<endl;
  f.close();
  */
}


/*

void dFiTableFrame::MainProcess(void)
{
  const char *input_fname;
  wxString ofname, ifname;
  FILE *ifd;
  size_t sz;
  int status;

  ifname = FilePickerCtrl1->GetPath();
  input_fname = ifname.mb_str().data();
  if (input_fname[0]==0)
  {
    MessageDialog1->SetMessage("Файл не выбран");
    MessageDialog1->ShowModal();
    return;
  }

  ifd = fopen(input_fname, "rb");
  if (ifd == NULL)
  {
    MessageDialog1->SetMessage("Ошибка открытия файла");
    MessageDialog1->ShowModal();
    return ;
  }

  if (TextCtrl1->IsEnabled())
  {
      ofname = TextCtrl1->GetLineText(1);
      ofd = fopen(ofname.mb_str().data(), "w");
      if (ofd == NULL)
      {
        MessageDialog1->SetMessage("Ошибка открытия отладочного файла");
        MessageDialog1->ShowModal();
        return ;
      }
  }

  //know file size
  fseek(ifd, 0L, SEEK_END);
  sz = ftell(ifd);
  rewind(ifd);
  Gauge1->SetRange(sz + (int)(0.05*sz));
  wxg = Gauge1;

  Button1->SetLabel("Обработка...");
  Button1->Enable(false);

  status = Parser(ifd);

  fclose(ifd);
  if (ofd)
    fclose(ofd);

  if (status!=0 && status!=1 && status!=3 && status!=4)
  {
    MessageDialog1->SetMessage( wxString::Format("Ошибка обработки %d", status) );
    MessageDialog1->ShowModal();https://yadi.sk/d/9ZiGgoHS85p8ag
  }
  else
  {
    CalTable();
    Gauge1->SetValue(Gauge1->GetRange());
    MessageDialog1->SetMessage("Калибровочная таблица создана");
    MessageDialog1->SetTitle("OK");
    MessageDialog1->ShowModal();
  }

  Button1->SetLabel("Обработать лог");
  Button1->Enable(true);

  return;
}

static long unsigned int dFiTableFrame::StaticMainProcess(void* Param)
{
  dFiTableFrame* This = (dFiTableFrame*)Param;
  This->MainProcess();
  return 0;  // обнуление функц.
}

void dFiTableFrame::OnButton1Click(wxCommandEvent& event)
{
 CreateThread(NULL, 4096, StaticMainProcess, (void*)this, 0, NULL);
}

*/


void dataDialog::OnChoice1Select6(wxCommandEvent& event)
{
gData.typeGnss = Choice1->GetSelection();
}

void dataDialog::OnTextCtrlBText(wxCommandEvent& event)
{  TextCtrlB->GetValue().ToDouble(&gData.B);
}

void dataDialog::OnTextCtrlLText1(wxCommandEvent& event)
{TextCtrlL->GetValue().ToDouble(&gData.L);
}
