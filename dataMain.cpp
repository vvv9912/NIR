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

using std::cout;
using std::cin;
using std::endl;
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
const long dataDialog::ID_TEXTCTRL4 = wxNewId();
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
  SetClientSize(wxSize(582,579));
  SashWindow1 = new wxSashWindow(this, ID_SASHWINDOW1, wxPoint(56,40), wxSize(416,520), wxSW_3D|wxCLIP_CHILDREN, _T("ID_SASHWINDOW1"));
  Choice1 = new wxChoice(SashWindow1, ID_CHOICE1, wxPoint(29,16), wxSize(193,96), 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE1"));
  Choice1->SetSelection( Choice1->Append(_("Glonass")) );
  Choice1->Append(_("GPS"));
  Choice1->Append(_("Galileo"));
  Choice1->Append(_("Beidou"));
  Choice1->Append(_("QZSS"));
  Button2 = new wxButton(SashWindow1, ID_BUTTON2, _("���������"), wxPoint(258,16), wxSize(127,23), 0, wxDefaultValidator, _T("ID_BUTTON2"));
  Notebook1 = new wxNotebook(SashWindow1, ID_NOTEBOOK1, wxPoint(124,214), wxDefaultSize, 0, _T("ID_NOTEBOOK1"));
  Button1 = new wxButton(SashWindow1, ID_BUTTON1, _("Label"), wxPoint(293,216), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
  TextCtrlH = new wxTextCtrl(SashWindow1, ID_TEXTCTRL1, _("200"), wxPoint(302,95), wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL1"));
  TextCtrlB = new wxTextCtrl(SashWindow1, ID_TEXTCTRL2, _("55.716367"), wxPoint(300,131), wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL2"));
  TextCtrlL = new wxTextCtrl(SashWindow1, ID_TEXTCTRL3, _("37.554003"), wxPoint(300,172), wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL3"));
  TextCtrlTEST1 = new wxTextCtrl(SashWindow1, ID_TEXTCTRL4, wxEmptyString, wxPoint(316,308), wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL4"));
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
  if ((Choice1->GetString(Choice1->GetSelection()))== "GPS")
  {
    File1 = "/MCC/PRODUCTS/LATEST/MERMS-GSC_C.ete";
    file = "MERMS-GSC_C.ete";
        wxTextFile file11(wxT("MERMS-GSC_C.ete"));
        if (file11.Exists())
        {wxRemoveFile(file);
        }
  }
  if ((Choice1->GetString(Choice1->GetSelection()))== "Glonass")
  {
    File1 = "/MCC/PRODUCTS/LATEST/MERMS-RSC_C.ete";
    file = "MERMS-RSC_C.ete";
        wxTextFile file11(wxT("MERMS-RSC_C.ete"));
        if (file11.Exists())
        {wxRemoveFile(file);
        }
  }
  if ((Choice1->GetString(Choice1->GetSelection()))== "Galileo")
  {
    File1 = "/MCC/PRODUCTS/LATEST/MERMS-ESC_C.ete";
    file = "MERMS-ESC_C.ete";
        wxTextFile file11(wxT("MERMS-ESC_C.ete"));
        if (file11.Exists())
        {wxRemoveFile(file);
        }
  }
  if ((Choice1->GetString(Choice1->GetSelection()))== "Beidou")
  {
    File1 = "/MCC/PRODUCTS/LATEST/MERMS-CSC_C.ete";
    file = "MERMS-CSC_C.ete";
        wxTextFile file11(wxT("MERMS-CSC_C.ete"));
        if (file11.Exists())
        {wxRemoveFile(file);
        }

  }
  if ((Choice1->GetString(Choice1->GetSelection()))== "QZSS")
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
  // ��������� �����.
/*for (k=0; k<max_sats; k++ )
  {
     SISerr[k].SISRE=0;
    SISerr[k].SISVE=0;
  }
  */
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

void dataDialog::OnButton1Click1(wxCommandEvent& event)
{
//wxString s;
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
double a=6378136; // ������ �

// ��������� ��������� �����������
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
//GlonassCoordinates Coord_sp = ephemerids(5,1);

using namespace std;
setlocale(LC_ALL, "RUS");
ofstream f;
f.open("angle.txt", ios::out);

f<< "Coord user"<<" x = "<< Coord_x <<"\t"<< "y = "<< Coord_y<<"\t" << "z = "<< Coord_z<<"\n";
/*
int vsb = 0 ;
int sumvsb = 0;
for (int i=1; i<=24; i++)
{ = dy/Ri;
H(2, numsput) = dz/Ri;
H(3, numsput) = 1;

  f<<"Hn["<<numsput<<"] = "<<H(0, numsput)<< "\t"<< H(1, numsput)<< "\t"<< H(2, numsput) << "\t"<<H(3 , numsput) <<"\n";
}
mat Dn1(24,24);
Dn1 = inv (Dn,-1);
for (int z=0; z<=23; z++)
{
   f<<"Dn^-1["<<z<<"] = "<< Dn1(z,z)<<"\n";
}
// ��������� ����� ���������
GlonassCoordinates Coord_sp = ephemerids(i,10000);


Coord_user[0]=a;
Coord_user[1]=0;
Coord_user[2]=0;

Coord_sput[0] = a;
Coord_sput[1] = a;
Coord_sput[2] = 0;

// ����������� ����
alpha = 90 - (angle(Coord_sput, Coord_user, B, L)*180/PI);
// ����������� ��������� ��������
if (abs(alpha) >5)
  {
    vsb = 1;
  }
  else
  {
    vsb = 0;
  }
sumvsb = sumvsb+ vsb;
// �����  � txt
f<<"N="<<i<< "\t alpha = " <<alpha<< "\t"<< vsb <<"\t"<< "[ " <<Coord_sp.X<<" ; "<<Coord_sp.Y<<" ; "<<Coord_sp.Z<<" ]"<<"\n";
}
f<<"number of visible spt = "<< sumvsb;
f.close();

*/

int vsb = 0 ;
int sumvsb = 0;
vector<int> Visibles;

for (int i=1; i<=24; i++)
{
// ��������� ����� ���������
GlonassCoordinates Coord_sp = ephemerids(i,10000);
Coord_sput[0] = Coord_sp.X;
Coord_sput[1] = Coord_sp.Y;
Coord_sput[2] = Coord_sp.Z;
// ����������� ����
alpha = 90 - (angle(Coord_sput, Coord_user, B, L)*180/PI);
// ����������� ��������� ��������

if ((alpha) >5)
  {
    sumvsb++;
    Visibles.push_back(i);
  }

// �����  � txt
f<<"N="<<i<< "\t alpha = " <<alpha<< "\t"<< vsb <<"\t"<< "[ " <<Coord_sp.X<<" ; "<<Coord_sp.Y<<" ; "<<Coord_sp.Z<<" ]"<<"\n";
}

f<<"number of visible spt = "<< sumvsb<<"\n";
f<<"number of visible spt = "<< Visibles.size() <<"\n";

int inum = 24;

// mat Dn(inum, inum);
  //Dn.zeros(); // ��-�� ���� ������� �� �������� ������� inv

  mat Dn;
  Dn.zeros(inum, inum);

  for (int k=0; k<=23; k++)
  {
  Dn(k,k) = SISerr[k].SISRE;
  }

 // Test
 //  mat Dn(inum, inum, fill::randu);

  /*mat Dn2;
  Dn2.zeros(inum, inum);
 for (int i=0 ; i<inum; i++)
 {
   Dn2(i, i) = 1+i;
 }

Dn2(5,5) = 0; Dn2(10,10)= 0;
f<< "Dn \n"<< Dn<<"\n";
*/
  mat Dn2 =  Dn;
/*  mat Dntest;
  Dntest.zeros(inum, inum);
  Dntest(1,1) = Dn2(1,1);
  for (int i=1 ; i<inum; i++)
  {
      if (Dn2(i,i) == 0)
      {
        Dntest(i,i) = Dn2(i+1, i+1);
        Dn2(i+1,i+1)=0;
      }
      else
      {
        Dntest(i,i)= Dn2(i,i);
      }
  }
*/

f<< "Dn \n"<< Dn<<"\n";
f<< "Dn2 \n"<< Dn2<<"\n";
//f<< "Dntest \n"<< Dntest<<"\n";

double dx;
double dy;
double dz;
double Ri;
// ������ �����

mat H(inum, 4);
H.zeros();

for (int numsput=0; numsput<=23; numsput++)
{
GlonassCoordinates Coord_sp = ephemerids((numsput+1),10000);
  dx=(Coord_sp.X-Coord_x);
  dy=(Coord_sp.Y-Coord_y);
  dz=(Coord_sp.Z- Coord_z);
 // Ri = sqrt (SQUARE(dx)+SQUARE(dy)+SQUARE(dz));
Ri = sqrt (pow(dx,2)+pow(dy,2)+pow(dz,2));
H(numsput,0 ) = dx/Ri;
H(numsput, 1) = dy/Ri;
H(numsput, 2) = dz/Ri;
H(numsput, 3) = 1;
}
f<<"H \n" <<H<<"\n";
// ������� Dn - ���������� : Sisre 0 0 0... ; 0 Sisre 0 0 ...; 0 0 Sisre 0...
/*mat A(5, 5, fill::randu);
mat CC = inv(A);
*/
/*
mat Dn1 = inv(Dn);

f<<"Dn1 \n" <<Dn1<<"\n";

mat sko = Dn1*H;
f<<"Sko \n" <<sko<<"\n";
*/
 f.close();

 /*
wxString FoobarX;
FoobarX.Printf("Coord_x=%f", Coord_x);
wxMessageBox(FoobarX);

wxString FoobarY;
FoobarY.Printf("Coord_y=%f", Coord_y);
wxMessageBox(FoobarY);

wxString FoobarZ;
FoobarZ.Printf("Coord_z=%f", Coord_z);
wxMessageBox(FoobarZ);


wxString Foobaralpha;
Foobaralpha.Printf("���� %f", alpha);
wxMessageBox(Foobaralpha);
*/
//std::cout << "My X = " << myCoord.x;
//double Zy=5;
//TextCtrlTEST1->SetValue(&Zy);
/*
wxString Foobar;
Foobar.Printf("���� ����� �� Y %f", myCoord.Y);
wxMessageBox(Foobar);
*/
//wxMessageBox( _("This is the message."), wxT("This is the title"), wxICON_INFORMATION);


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
    MessageDialog1->SetMessage("���� �� ������");
    MessageDialog1->ShowModal();
    return;
  }

  ifd = fopen(input_fname, "rb");
  if (ifd == NULL)
  {
    MessageDialog1->SetMessage("������ �������� �����");
    MessageDialog1->ShowModal();
    return ;
  }

  if (TextCtrl1->IsEnabled())
  {
      ofname = TextCtrl1->GetLineText(1);
      ofd = fopen(ofname.mb_str().data(), "w");
      if (ofd == NULL)
      {
        MessageDialog1->SetMessage("������ �������� ����������� �����");
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

  Button1->SetLabel("���������...");
  Button1->Enable(false);

  status = Parser(ifd);

  fclose(ifd);
  if (ofd)
    fclose(ofd);

  if (status!=0 && status!=1 && status!=3 && status!=4)
  {
    MessageDialog1->SetMessage( wxString::Format("������ ��������� %d", status) );
    MessageDialog1->ShowModal();https://yadi.sk/d/9ZiGgoHS85p8ag
  }
  else
  {
    CalTable();
    Gauge1->SetValue(Gauge1->GetRange());
    MessageDialog1->SetMessage("������������� ������� �������");
    MessageDialog1->SetTitle("OK");
    MessageDialog1->ShowModal();
  }

  Button1->SetLabel("���������� ���");
  Button1->Enable(true);

  return;
}

static long unsigned int dFiTableFrame::StaticMainProcess(void* Param)
{
  dFiTableFrame* This = (dFiTableFrame*)Param;
  This->MainProcess();
  return 0;
}

void dFiTableFrame::OnButton1Click(wxCommandEvent& event)
{
 CreateThread(NULL, 4096, StaticMainProcess, (void*)this, 0, NULL);
}

*/





