
#include "ephemerids.h"

#define _USE_MATH_DEFINES
#include <math.h>

#include <windows.h>
#include <wininet.h>
#include <iostream>
#include <string>
#include <stdio.h>

#include <wx/msgdlg.h>
#include <wx/string.h>
#include <wx/textfile.h>
#include <wx/dialog.h>
#include <wx/msgdlg.h>
#include <wx/spinctrl.h>
#include <wx/intl.h>
#include <wx/settings.h>

GlonassCoordinates ephemerids(int n, int t)
{
  GlonassCoordinates Coordinates;
  double TETTA;
  double OMEGA;
  switch (n)
  {
    case 1:
        TETTA = 0;
        OMEGA = 0;
        break;
    case 2:
        TETTA = -45;
        OMEGA = 0;
        break;
    case 3:
        TETTA = -90;
        OMEGA = 0;
          break;
    case 4:
        TETTA = -135;
        OMEGA = 0;
          break;
    case 5:
        TETTA = -180;
        OMEGA = 0;
          break;
    case 6:
        TETTA = -225;
        OMEGA = 0;
          break;
    case 7:
        TETTA = -270;
        OMEGA = 0;
          break;
    case 8:
        TETTA = -315;
        OMEGA = 0;

          break;
    case 9:
        TETTA = 15;
        OMEGA = 120;
          break;
    case 10:
        TETTA = -30;
        OMEGA = 120;
          break;
    case 11:
        TETTA = -75;
        OMEGA = 120;
          break;
    case 12:
        TETTA = -120;
        OMEGA = 120;
          break;
    case 13:
        TETTA = -165;
        OMEGA = 120;
          break;
    case 14:
        TETTA = -210;
        OMEGA = 120;
          break;
    case 15:
        TETTA = -255;
        OMEGA = 120;
          break;
    case 16:
        TETTA = -300;
        OMEGA = 120;
          break;
    case 17:
        TETTA = 30;
        OMEGA = 240;
          break;
    case 18:
        TETTA = -15;
        OMEGA = 240;
          break;
    case 19:
        TETTA = -60;
        OMEGA = 240;
          break;
    case 20:
        TETTA = -105;
        OMEGA = 240;
          break;
    case 21:
        TETTA = -150;
        OMEGA = 240;
          break;
    case 22:
        TETTA = -195;
        OMEGA = 240;
          break;
    case 23:
        TETTA = -240;
        OMEGA = 240;
          break;
    case 24:
        TETTA = -285;
        OMEGA = 240;
          break;
  }
  double PI = M_PI;
TETTA = TETTA*PI/180;
OMEGA = OMEGA*PI/180;

double ci;
double si;

ci = cos((64.8*PI/180));
si = sin((64.8*PI/180));

double V_sat_glns = 1.5514*pow(10,-4);
double V_earth = 0; //7.292115*10^(-5);

double Tsat = t*V_sat_glns;
double Tear = -t*V_earth;

double e = 0;
double p = 19100000+6378136;
double r = p/(1+e*cos(TETTA));

Coordinates.X = r*(((cos(TETTA+Tsat))*(cos(OMEGA+Tear)))-((sin(TETTA+Tsat))*(sin(OMEGA+Tear)*ci)));
Coordinates.Y = r*(cos(TETTA+Tsat)*sin(OMEGA+Tear)+sin(TETTA+Tsat)*cos(OMEGA+Tear)*ci);
Coordinates.Z = r*(sin(TETTA+Tsat))*si;
/*wxString FoobarX;
FoobarX.Printf("X=%f", Coordinates.X);
wxMessageBox(FoobarX);

wxString FoobarY;
FoobarY.Printf("Y=%f", Coordinates.Y);
wxMessageBox(FoobarY);

wxString FoobarZ;
FoobarZ.Printf("Z=%f", Coordinates.Z);
wxMessageBox(FoobarZ);
*/
  return Coordinates;
}
