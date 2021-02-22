/***************************************************************
 * Name:      dataMain.cpp
 * Purpose:   Code for Application Frame
 * Author:    aaa ()
 * Created:   2019-08-14
 * Copyright: aaa ()
 * License:
 **************************************************************/

#include "dataMain.h"
#include "parser.h"
#include "angle.h"
#include "ephemerids.h"
#include "xyz2enu.h"
#include "timeGlonass.H"
#include "TimeGPS.H"
#include <wx/msgdlg.h>
#include <windows.h>
#include <wininet.h>
#include <iostream>
#include <string>
#include <stdio.h>
#include <armadillo>

#include <fstream>

#include <wx/string.h>
#include <wx/textfile.h>
#include <wx/dialog.h>
#include <wx/msgdlg.h>
#include <wx/spinctrl.h>
#include <wx/intl.h>
#include <wx/settings.h>

#define SQUARE(val) val * val

using namespace std;
using namespace arma;

//(*InternalHeaders(dataDialog)
#include <wx/intl.h>
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
const long dataDialog::ID_SASHWINDOW1 = wxNewId();
//*)

const long dataDialog::ID_GRID = wxNewId();
BEGIN_EVENT_TABLE(dataDialog,wxDialog)
  //(*EventTable(dataDialog)
  //*)
END_EVENT_TABLE()

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



dataDialog::dataDialog(wxWindow* parent,wxWindowID id)
{
  //(*Initialize(dataDialog)
  Create(parent, wxID_ANY, _("Data app"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("wxID_ANY"));
  SetClientSize(wxSize(715,571));
  SashWindow1 = new wxSashWindow(this, ID_SASHWINDOW1, wxPoint(56,40), wxSize(592,520), wxSW_3D|wxCLIP_CHILDREN, _T("ID_SASHWINDOW1"));
  Choice1 = new wxChoice(SashWindow1, ID_CHOICE1, wxPoint(33,16), wxSize(244,21), 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE1"));
  Choice1->SetSelection( Choice1->Append(_("Glonass")) );
  Choice1->Append(_("GPS"));
  Choice1->Append(_("Galileo"));
  Choice1->Append(_("Beidou"));
  Choice1->Append(_("QZSS"));
  Button2 = new wxButton(SashWindow1, ID_BUTTON2, _("Загрузить"), wxPoint(305,16), wxSize(127,23), 0, wxDefaultValidator, _T("ID_BUTTON2"));
  Notebook1 = new wxNotebook(SashWindow1, ID_NOTEBOOK1, wxPoint(124,214), wxDefaultSize, 0, _T("ID_NOTEBOOK1"));
  Down = new wxButton(SashWindow1, ID_BUTTON1, _("Обработка "), wxPoint(305,216), wxSize(127,23), 0, wxDefaultValidator, _T("ID_BUTTON1"));
  TextCtrlH = new wxTextCtrl(SashWindow1, ID_TEXTCTRL1, _("0"), wxPoint(305,95), wxSize(127,-1), 0, wxDefaultValidator, _T("ID_TEXTCTRL1"));
  TextCtrlB = new wxTextCtrl(SashWindow1, ID_TEXTCTRL2, _("0"), wxPoint(305,140), wxSize(127,-1), 0, wxDefaultValidator, _T("ID_TEXTCTRL2"));
  TextCtrlL = new wxTextCtrl(SashWindow1, ID_TEXTCTRL3, _("0"), wxPoint(305,185), wxSize(127,-1), 0, wxDefaultValidator, _T("ID_TEXTCTRL3"));
  StaticText1 = new wxStaticText(SashWindow1, ID_STATICTEXT1, _("Введите значение высоты:"), wxPoint(305,77), wxDefaultSize, 0, _T("ID_STATICTEXT1"));
  StaticText2 = new wxStaticText(SashWindow1, ID_STATICTEXT2, _("Введите значение B:"), wxPoint(305,122), wxDefaultSize, 0, _T("ID_STATICTEXT2"));
  StaticText3 = new wxStaticText(SashWindow1, ID_STATICTEXT3, _("Введите значение L:"), wxPoint(305,167), wxDefaultSize, 0, _T("ID_STATICTEXT3"));
  StaticText4 = new wxStaticText(SashWindow1, ID_STATICTEXT4, _("Значения СКО:"), wxPoint(306,244), wxDefaultSize, 0, _T("ID_STATICTEXT4"));
  SashWindow1->SetSashVisible(wxSASH_TOP,    true);
  SashWindow1->SetSashVisible(wxSASH_BOTTOM, true);
  SashWindow1->SetSashVisible(wxSASH_LEFT,   true);
  SashWindow1->SetSashVisible(wxSASH_RIGHT,  true);

  Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&dataDialog::OnButton2Click);
  Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&dataDialog::OnButton1Click1);
  Connect(ID_TEXTCTRL1,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&dataDialog::OnTextCtrl1Text1);
  Connect(ID_SASHWINDOW1,wxEVT_SASH_DRAGGED,(wxObjectEventFunction)&dataDialog::OnSashWindow1SashDragged);
  Connect(wxID_ANY,wxEVT_INIT_DIALOG,(wxObjectEventFunction)&dataDialog::OnInit);
  //*)

Grid = new wxGrid(SashWindow1, ID_GRID, wxPoint(33,72), wxSize(244,490), 0, _T("ID_GRID"));

Grid->CreateGrid(24,2);
Grid->SetColLabelValue(0, _("SISRE, m"));
Grid->SetColLabelValue(1, _("SISVE, mm/s"));
Grid->SetDefaultCellFont( Grid->GetFont() );
Grid->SetDefaultCellTextColour( Grid->GetForegroundColour() );
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

void dataDialog::OnChoice1Select(wxCommandEvent& event)
{

}


void dataDialog::OnSashWindow1SashDragged(wxSashEvent& event)
{

}

void dataDialog::OnButton2Click(wxCommandEvent& event)
{

  wxString s;
  const char* File1 ;
  const char* file ;
  //wxMessageBox(Choice1->GetString(Choice1->GetSelection()), _(""));
  if ((Choice1->GetString(Choice1->GetSelection()))== "GPS"s)
  {
    File1 = "/MCC/PRODUCTS/LATEST/MERMS-GSC_C.ete";
    file = "MERMS-GSC_C.ete";
        wxTextFile file11(wxT("MERMS-GSC_C.ete"));
        if (file11.Exists())
        {wxRemoveFile(file);
        }
  }
  if ((Choice1->GetString(Choice1->GetSelection()))== "Glonass"s)
  {
    File1 = "/MCC/PRODUCTS/LATEST/MERMS-RSC_C.ete";
    file = "MERMS-RSC_C.ete";
        wxTextFile file11(wxT("MERMS-RSC_C.ete"));
        if (file11.Exists())
        {wxRemoveFile(file);
        }
  }
  if ((Choice1->GetString(Choice1->GetSelection()))== "Galileo"s)
  {
    File1 = "/MCC/PRODUCTS/LATEST/MERMS-ESC_C.ete";
    file = "MERMS-ESC_C.ete";
        wxTextFile file11(wxT("MERMS-ESC_C.ete"));
        if (file11.Exists())
        {wxRemoveFile(file);
        }
  }
  if ((Choice1->GetString(Choice1->GetSelection()))== "Beidou"s)
  {
    File1 = "/MCC/PRODUCTS/LATEST/MERMS-CSC_C.ete";
    file = "MERMS-CSC_C.ete";
        wxTextFile file11(wxT("MERMS-CSC_C.ete"));
        if (file11.Exists())
        {wxRemoveFile(file);
        }

  }
  if ((Choice1->GetString(Choice1->GetSelection()))== "QZSS"s)
  {
    File1 = "/MCC/PRODUCTS/LATEST/MERMS-JSC_C.ete";
    file = "MERMS-JSC_C.ete";
        wxTextFile file11(wxT("MERMS-JSC_C.ete"));
        if (file11.Exists())
        {wxRemoveFile(file);
        }
  }
  bool down = download( "glonass-iac.ru", NULL, NULL, File1, file);
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
Grid = new wxGrid(SashWindow1, ID_GRID, wxPoint(33,72), wxSize(244,sizeY), 0, _T("ID_GRID"));
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


void dataDialog::OnChoice1Select3(wxCommandEvent& event)
{
}

void dataDialog::OnTextCtrl1Text1(wxCommandEvent& event)
{
}

void dataDialog::OnSpinCtrl1Change(wxSpinEvent& event)
{

}
void dataDialog::OnChoice1Select4(wxCommandEvent& event)
{

}
void dataDialog::OnButton1Click1(wxCommandEvent& event)
{
StaticText4 ->ClearBackground();
if ((Choice1->GetString(Choice1->GetSelection()))== "Glonass")
{
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
B=Bgrad*PI/180;
L=Lgrad*PI/180;
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
Coord_user[0]=Coord_x;
Coord_user[1]= Coord_y;
Coord_user[2]= Coord_z;

double Coord_sput[3];
double alpha;
// Расчет матрицы Dn, Hn, SKO

int numberSput = 24;
int vsb[numberSput] ;
int sumvsb = 0;
vector<int> Visibles; //вектор из кол-во элементов - visibles

for (int i=1; i<=numberSput; i++)
{
// Получение коорд спутников
GlonassCoordinates Coord_sp = ephemerids(i,10000);
Coord_sput[0] = Coord_sp.X;
Coord_sput[1] = Coord_sp.Y;
Coord_sput[2] = Coord_sp.Z;
// Определение угла
alpha = 90 - (angle(Coord_sput, Coord_user, B, L)*180/PI);
// определение видимости спутника
vsb[i]=0;
if ((alpha) >5)
  {
    vsb[i]=1;
    sumvsb++;
    Visibles.push_back(i);  // добавление элемента в конец вектора
  }
}

// получение матрицы Dn
int i = 0;
  mat Dn;
  Dn.zeros(sumvsb, sumvsb);
  for (int k=1; k<=numberSput; k++)
  {
   if ((vsb[k]) == 1)
     {
      Dn(i,i) = SISerr[i].SISRE;
      i++;
     }
  }
  double max_val_Dn = Dn.max();
for (int i= 0; i<sumvsb; i++)
{
  if ( Dn(i,i) == 0)
  {
    Dn(i,i) = max_val_Dn;
  }
}

// получение матрицы H
double dx;
double dy;
double dz;
double Ri;

mat H(sumvsb, 4);
H.zeros();

int numsput = 0;

for (int k=1; k<=numberSput; k++)
{
     if ((vsb[k]) == 1)
    {
    GlonassCoordinates Coord_sp = ephemerids((k),10000);
    dx=(Coord_sp.X-Coord_x);
    dy=(Coord_sp.Y-Coord_y);
    dz=(Coord_sp.Z- Coord_z);
 // Ri = sqrt (SQUARE(dx)+SQUARE(dy)+SQUARE(dz));
    Ri = sqrt (pow(dx,2)+pow(dy,2)+pow(dz,2));

    H(numsput, 0 ) = dx/Ri;
    H(numsput, 1) = dy/Ri;
    H(numsput, 2) = dz/Ri;
    H(numsput, 3) = 1;
    numsput++ ;
    }
}
 timeGlonass();

mat Htr = H.t();
mat sko = sqrt((inv(Htr*inv(Dn)*H)).t());
// вывод значения в стат. текст
wxString s;
s.Printf("Значение СКО:\nСКО для x: %.3f м\nСКО для y: %.3f м\nСКО для z: %.3f м\nСКО для D: %.3f" ,sko(0,0), sko(1,1), sko(2,2), sko(3,3) );
StaticText4->SetLabel(s);
}
else
{
    wxMessageBox(_("Выберите другую ГНСС"), _("Error"));
}
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





