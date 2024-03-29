#include "ephemerids2.h"
#include "Kepler.h"
#include <armadillo>
//
#include <fstream>
#include <iostream>
#include <string>
#include <stdio.h>
using namespace arma;
using namespace std;
Coordinatess CoordGPS(double t, //� ���� toe
                     double toe, //t_almanax
                     double M0,
                    double  sqrtA,
                     double  e, //E
                    double I,
                     double  Omega0 )

{
  Coordinatess CoordinatesGps;
  double  a =  pow((sqrtA),2);
  double n = 3.986005*pow(10,14); //�� ���
  double i0 = I;
     double  w = 0.16578805*M_PI;
  double  OmegaDot =(-2.6*pow(10,-9))*M_PI;//�� ���
  double omegaE = 7.2921151467*pow(10,-5);
  double tk = t-toe;
  if (tk > 302400)
  {
    tk = 604800-tk;
  }
  else if (tk<-302400)
  {
    tk = 604800+tk;
  }
  double  Mk = M0+( (sqrt(n/(pow(a,3)))))*tk;
  //double Ek = kepler(e,Mk);
  double Ek = e*sin(0)+Mk;
  double Ekold = 0;
  while (fabs(Ek- Ekold)>0.000000001 )
  {
    Ekold = Ek;
    Ek = e*sin(Ek)+Mk;
  }
 // ofstream f;
//f.open("test\\ephem2.txt", ios::app);
  double vk = atan2(sqrt(1-(pow(e,2)))*sin(Ek), (cos(Ek)-e) );
  double uk = w+ vk;
  double rk = (a*(1-e*cos(Ek)));
  double ik = i0;
  double lymbdak_ECEF = Omega0 + (OmegaDot - omegaE)*tk-omegaE*toe;
 /* f<<"---ephem2---"<<endl;
  f<<"vk = " <<vk<<endl;
  f<<"uk = " <<uk<<endl;
  f<<"rk = " <<rk<<endl;
  f<<"ik = " <<ik<<endl;
  f<<"OMEGAk (lymbdak_ECEF) = " <<lymbdak_ECEF<<endl;
f.close();*/
  dmat R1(3,3);
  R1(0,0) = 1;
  R1(0,1) = 0;
  R1(0,2) = 0;
  R1(1,0) = 0;
  R1(1,1) =  cos(-ik);
  R1(1,2) = sin(-ik);
  R1(2,0) = 0;
  R1(2,1)=-sin(-ik);
  R1(2,2) = cos(-ik);
//R1 =[1 0 0;
//   0 cos(-ik) sin(-ik);
//   0 -sin(-ik) cos(-ik)];
  dmat R3l_ECEF(3,3);
  R3l_ECEF(0,0) = cos(-lymbdak_ECEF);
  R3l_ECEF(0,1) = sin(-lymbdak_ECEF);
  R3l_ECEF(0,2) = 0;
  R3l_ECEF(1,0) = -sin(-lymbdak_ECEF);
  R3l_ECEF(1,1) =  cos(-lymbdak_ECEF);
  R3l_ECEF(1,2) = 0;
  R3l_ECEF(2,0) = 0;
  R3l_ECEF(2,1) = 0;
  R3l_ECEF(2,2) = 1;
//[cos(-lymbdak_ECEF) sin(-lymbdak_ECEF) 0;
//   -sin(-lymbdak_ECEF) cos(-lymbdak_ECEF) 0;
  // 0 0 1];

  dmat R3uk(3,3) ;
//[cos(-uk) sin(-uk) 0;
  //  -sin(-uk) cos(-uk) 0;
  //  0 0 1];
  R3uk(0,0) = cos(-uk);
  R3uk(0,1) = sin(-uk);
  R3uk(0,2) = 0;
  R3uk(1,0) = -sin(-uk);
  R3uk(1,1) =  cos(-uk);
  R3uk(1,2) = 0;
  R3uk(2,0) = 0;
  R3uk(2,1)=0;
  R3uk(2,2) = 1;

  dmat rkk(3,1);
  rkk(0,0) = rk;
  rkk(1,0) = 0;
  rkk(2,0) = 0;

  dmat coord = R3l_ECEF*R1*R3uk*rkk;
  CoordinatesGps.X =  coord(0,0);
  CoordinatesGps.Y = coord(1,0);
  CoordinatesGps.Z = coord(2,0);
  return CoordinatesGps;
}





















