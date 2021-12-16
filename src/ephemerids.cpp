
#include "include/ephemerids.h"

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

Coordinates ephemerids(double toe,
                              double t_almanax,
                              double almanax_M0,
                              double sqrtA,
                              double E,
                              double I,
                              double Om0,
                              double time_week )
{//toe - время на которое нуэно расчитать;
 Coordinates Coordinates;

 double M0 = almanax_M0*M_PI;
 double A0 = pow((sqrtA),2);
 double en = E;
 double omegan = 0.16578805*M_PI;
 double i0n = I*M_PI;
 double Omega0n = Om0*M_PI;
 double nu = 3.986005*pow(10,14); //из икд
 double OMEGA_REF=(-2.6*pow(10,-9))*M_PI;//из икд
 double OMEGA_e=7.2921151467*pow(10,-5);//из икд
 int week_almanax = time_week;
 double t_sec_almanax = t_almanax;
 double tk = toe- t_sec_almanax;
 if (tk > 302400)
 {
 tk = 604800-tk;
 }
 else if (tk<-302400)
 {
 tk = 604800+tk;
 }
 double n0 = sqrt(nu/pow(A0,3));
 double nA = n0;
 double Mk = M0 + nA*tk;
 double Ek;
 double Ekold = 0;
Ek = en*sin(0)+Mk;
while (abs(Ek- Ekold)>0.000000001 )
{ Ekold = Ek;
 Ek = en*sin(Ek)+Mk;
}

double vk = atan2(sqrt(1-(pow(en,2)))*sin(Ek), (cos(Ek)-en) );
double Ak = A0;
double rk = Ak*(1-en*cos(Ek));
double Fk = vk + omegan;
double uk = Fk;
double xkk = rk*cos(uk);
double ykk = rk*sin(uk);
double OMEGA = OMEGA_REF;
double OMEGAk = Omega0n+(OMEGA-OMEGA_e)*tk-OMEGA_e*t_sec_almanax;
double ik = i0n;
double xk = xkk*cos(OMEGAk)-ykk*cos(ik)*sin(OMEGAk);
double yk = xkk*sin(OMEGAk)+ykk*cos(ik)*cos(OMEGAk);
double zk = ykk*sin(ik);

Coordinates.X =  xkk*cos(OMEGAk)-ykk*cos(ik)*sin(OMEGAk);
Coordinates.Y = xkk*sin(OMEGAk)+ykk*cos(ik)*cos(OMEGAk);
Coordinates.Z = ykk*sin(ik);
  return Coordinates;
}
