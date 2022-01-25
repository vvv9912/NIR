#include <include/calcBeidou.h>
#include <math.h>
//
#include "include/parserBeidou.H"
#include "include/parserEphB.h"
#include "include/angle.h"
#include "include/ephemerids.h"
#include "include/xyz2enu.h"
//
//#include "ephemerids2.h"
//#include "Kepler.h"
//
#include <wx/msgdlg.h>
#include <windows.h>
#include <wininet.h>
//
#include <armadillo>
//
#include <iostream>
#include <string>
#include <stdio.h>
//#include <fstream>

using namespace std;
using namespace arma;


void calccBeidou(const char* file,
              double (&skoo)[5],
              timeCalc calc,
              double B,double L, double h)
 { //double skoo[4];
/*  double N;
  double e=0; //
  double a=6378136; // радиус З
// Получение координат потребителя
  N=a/sqrt(1-(e*e)*(sin(B))*(sin(B)));
*/
double a = 6378137.0; //большая полуось
double b = 6356752.3142; // малая полуосб
double f = (a-b)/a; //сжатие
//double e = (sqrt(pow(a,2)+pow(b,2)))/a; //эксцентриситет
double epow2 = f*(2-f);
double e2; // второй эксцентриситет
e2 = epow2/(1-epow2);
double N = a/sqrt(1-epow2*pow(sin(B),2));
  double Coord_x;
  double Coord_y;
  double Coord_z;
  Coord_x = (N+h)*cos(B)*cos(L);
  Coord_y = (N+h)*cos(B)*sin(L);
  Coord_z = ((1-epow2)*N+h)*sin(B);
  double Coord_user[3];
  Coord_user[0]=(N+h)*cos(B)*cos(L);
  Coord_user[1]= (N+h)*cos(B)*sin(L);
  Coord_user[2]= ((1-epow2)*N+h)*sin(B);

  double Coord_sput[3];
  double alpha;
    almanaxBeidou alm_b[31];
    parserBeidou(file, alm_b);
// Расчет матрицы Dn, Hn, SKO
    int numberSput = 30;
    int vsb[numberSput] ;
    int sumvsb = 0;
    vector<int> Visibles; //вектор из кол-во элементов - visibles
    calc.timeB();
    double toe=calc.sec_since_week;
//ofstream f;
//f.open("test\\cor_be1.txt", ios::app);
 Coordinates Coord_sp; // можно потом заменить в 482 строке и ниже.
 //Coordinatess Coord_sp2;

    for (int i=1; i<=numberSput; i++)
    {
// Получение коорд спутников
//ephemerids(double toe,int t_almanax, double M0, double sqrtA, double E, double I, double Om0, double time_week ))
      if (alm_b[i].PRN !=0 )
      {
        Coord_sp = ephemerids(toe,
                            alm_b[i].t,
                            (alm_b[i].m)/M_PI, // в рад -> полуцик
                            alm_b[i].sqrta,
                            alm_b[i].e,
                            (alm_b[i].di)/M_PI, //в рад -> полуцикл
                            (alm_b[i].Omega0)/M_PI, //в рад -> полуцик
                            alm_b[i].week);


    /* Coord_sp2 = CoordGPS(toe,
                            alm_b[i].t,
                            (alm_b[i].m), // в рад -> полуцик
                            alm_b[i].sqrta,
                            alm_b[i].e,
                            (alm_b[i].di), //в рад -> полуцикл
                            (alm_b[i].Omega0));*/
      Coord_sput[0] = Coord_sp.X;
      Coord_sput[1] = Coord_sp.Y;
      Coord_sput[2] = Coord_sp.Z;

  //  f<<alm_b[i].PRN<<endl;
  //   f<<toe<<endl;
  //  f<<alm_b[i].t<<endl;
  //  f<<(alm_b[i].m)<<endl;
  //  f<< alm_b[i].sqrta<<endl;
 //     f<<  alm_b[i].e<<endl;
 // f<<  (alm_b[i].di)<<endl;
 // f<<  (alm_b[i].di)/M_PI<<endl;
 //// f<<  (alm_b[i].Omega0)/M_PI<<endl;
 // f<<  (alm_b[i].Omega0)<<endl;
 // f<<  alm_b[i].week<<endl;

  //   f<<"Coord_sp.X="<<Coord_sp.X<<endl;
  //   f <<"Coord_sp.Y =" <<Coord_sp.Y<<endl;
  //  f <<"Coord_sp.Z =" <<Coord_sp.Z<<endl;
  //  f<< "coord---------"<<endl;/*
    // f<<"Coord_sp.X="<<Coord_sp2.X<<endl;
  //   f <<"Coord_sp.Y =" <<Coord_sp2.Y<<endl;
  //  f <<"Coord_sp.Z =" <<Coord_sp2.Z<<endl;*/
// Определение угла
      alpha = 90 - (angle(Coord_sput, Coord_user, B, L)*180/M_PI);
 // f<<"alpha"<<alpha<<endl;
// определение видимости спутника
      vsb[i]=0;
      if ((alpha) >5)
      {
        vsb[i]=1;
        sumvsb++;
        Visibles.push_back(i);  // добавление элемента в конец вектора
      }
     // f<<vsb[i]<<endl;
    }
    }
//    f<<sumvsb<<endl;
     // f<<sumvsb<<endl;
//ofstream f;
//f.open("test\\coord_beidou2.txt");
//f.close();
  if (sumvsb < 4)
  {
  skoo[0]= -10;
  skoo[1]= -10;
  skoo[2]= -10;
  skoo[3]= -10;
  skoo[4] = -10;
  }
  else
  {
// получение матрицы Dn
    int i = 0;
    mat Dn;
    Dn.zeros(sumvsb, sumvsb);
    for (int k=1; k<=numberSput; k++)
    {
      if ((vsb[k]) == 1)
      {
        Dn(i,i) = pow(((SISerr_Beidou[k-1].SISRE) + (SISerr_Beidou[k-1].M0_SRE/3.0)),2);
        i++;
      }
    }

    // Dn.save("test\\Dn_B.txt", raw_ascii);
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
//ofstream f2;
//f2.open("test\\cor_be12.txt");
    int numsput = 0;
    for (int k=1; k<=numberSput; k++)
    {
      if ((vsb[k]) == 1)
      {
       Coord_sp = ephemerids(toe,
                            alm_b[k].t,
                            alm_b[k].m/M_PI, // в рад -> полуцик
                            alm_b[k].sqrta,
                            alm_b[k].e,
                            alm_b[k].di/M_PI, //в рад -> полуцикл
                            alm_b[k].Omega0/M_PI, //в рад -> полуцик
                            alm_b[k].week);
        /*   Coord_sp2 = CoordGPS(toe,
                            alm_b[k].t,
                            (alm_b[k].m), // в рад -> полуцик
                            alm_b[k].sqrta,
                            alm_b[k].e,
                            (alm_b[k].di), //в рад -> полуцикл
                            (alm_b[k].Omega0));*/
        dx=(Coord_sp.X-Coord_x);
        dy=(Coord_sp.Y-Coord_y);
        dz=(Coord_sp.Z- Coord_z);
        Ri = sqrt (pow(dx,2)+pow(dy,2)+pow(dz,2));
        H(numsput, 0 ) = dx/Ri;
        H(numsput, 1) = dy/Ri;
        H(numsput, 2) = dz/Ri;
        H(numsput, 3) = 1;
        numsput++ ;
    /*       f2<<alm_b[k].PRN<<endl;
             f2<<"Coord_sp.X="<<Coord_sp.X<<endl;
     f2 <<"Coord_sp.Y =" <<Coord_sp.Y<<endl;
    f2 <<"Coord_sp.Z =" <<Coord_sp.Z<<endl;
    f2<< "coord2---------"<<endl;
     f2<<"Coord_sp.X="<<Coord_sp2.X<<endl;
     f2 <<"Coord_sp.Y =" <<Coord_sp2.Y<<endl;
    f2 <<"Coord_sp.Z =" <<Coord_sp2.Z<<endl;*/
      }
    }
//f2.close();
 //  H.save("test\\H_B.txt", raw_ascii);
    mat Htr = H.t();
  //  Htr.save("test\\Htr_B.txt", raw_ascii);
    mat u = Htr*inv(Dn)*H;
    mat sko ;
  //  f<< det(u)<<endl;
 /*   if (det(u) < 0.000000000000001)
    {
    skoo[0]= -1;
    skoo[1]= -1;
    skoo[2]= -1;
    skoo[3]= -1;
    skoo[4] = -1;
    }
    else
    {*/
    sko = sqrt((inv(u)).t());
    skoo[0]= sko(0,0);
    skoo[1]= sko(1,1);
    skoo[2]= sko(2,2);
    skoo[3]= sko(3,3);
    skoo[4] = sqrt (pow(sko(0,0),2)+pow(sko(1,1),2)+pow(sko(2,2),2) );
   // }
  }
//  f.close();
}

