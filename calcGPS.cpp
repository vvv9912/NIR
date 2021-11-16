#include <math.h>
#include <calcGPS.h>

//
#include "FTPdownl.h"
//#include "parser.h"
#include "parserGPS.H"
#include <parserEphGPS.h>
#include "angle.h"
#include "ephemerids.h"
#include "xyz2enu.h"

#include <wx/msgdlg.h>
#include <windows.h>
#include <wininet.h>
//
#include <armadillo>
//
#include <iostream>
#include <string>
#include <stdio.h>
#include <fstream>
using namespace std;
using namespace arma;

void calccGPS(const char* file,
              double (&skoo)[5],
              timeCalc calc,
              double B,double L, double h)
 { //double skoo[4];
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

/*text1 = text5+text2+text3+text4+".agp"s;
 text0 =   "/MCC/ALMANAC/"+ textYear +"/"+text1;*/
   // f<< " day_down="<< day_down<<endl;
   // f<< " text4="<< text4<<endl;

    int max_sats = parseGPS(file);

// Расчет матрицы Dn, Hn, SKO
    int numberSput = 32;
    int vsb[numberSput] ;
    int sumvsb = 0;
    vector<int> Visibles; //вектор из кол-во элементов - visibles
    calc.timeGPS();
    double toe=calc.sec_since_week;

   // f<< "GPS:"<<endl;
   // f<<"toe()calc.sec_since_week="<<toe<<endl;
   // f<<"week="<<calc.week<<endl;
    Coordinates Coord_sp; // можно потом заменить в 482 строке и ниже.

    for (int i=1; i<=numberSput; i++)
    {
// Получение коорд спутников
//ephemerids(double toe,int t_almanax, double M0, double sqrtA, double E, double I, double Om0, double time_week ))
      Coord_sp = ephemerids(toe,
                            almanax_GPS[i-1].t_almanax,
                            almanax_GPS[i-1].M0,
                            almanax_GPS[i-1].sqrtA,
                            almanax_GPS[i-1].E,
                            almanax_GPS[i-1].I,
                            almanax_GPS[i-1].Om0,
                            almanax_GPS[i-1].time_week);
/*      f<< "I = "<<almanax_GPS[i-1].I<<endl;
      f<< "toe = "<<toe<<endl;
      f<< "almanax_GPS[i-1].t_almanax = "<<almanax_GPS[i-1].t_almanax<<endl;
      f<< "almanax_GPS[i-1].time_week = "<<almanax_GPS[i-1].time_week<<endl;
      f <<"i-1 (номер спут)"<<i-1<<endl;

      f<<"Coord_sp.X="<<Coord_sp.X<<endl;
      f <<"Coord_sp.Y =" <<Coord_sp.Y<<endl;
      f <<"Coord_sp.Z =" <<Coord_sp.Z<<endl;*/

      Coord_sput[0] = Coord_sp.X;
      Coord_sput[1] = Coord_sp.Y;
      Coord_sput[2] = Coord_sp.Z;
// Определение угла
      alpha = 90 - (angle(Coord_sput, Coord_user, B, L)*180/M_PI);
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
        Dn(i,i) = SISerr_GPS[i].SISRE;
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
        Coord_sp = ephemerids(toe,
                              almanax_GPS[k-1].t_almanax,
                              almanax_GPS[k-1].M0,
                              almanax_GPS[k-1].sqrtA,
                              almanax_GPS[k-1].E,
                              almanax_GPS[k-1].I,
                              almanax_GPS[k-1].Om0,
                              almanax_GPS[k-1].time_week);
        dx=(Coord_sp.X-Coord_x);
        dy=(Coord_sp.Y-Coord_y);
        dz=(Coord_sp.Z- Coord_z);
// Ri = sqrt (SQUARE(dx)+SQUARE(dy)+SQUARE(dz));
        Ri = sqrt (pow(dx,2)+pow(dy,2)+pow(dz,2));
 //f<< "Ri"<< Ri<<endl;
        H(numsput, 0 ) = dx/Ri;
        H(numsput, 1) = dy/Ri;
        H(numsput, 2) = dz/Ri;
        H(numsput, 3) = 1;
        numsput++ ;
      }
    }
    mat Htr = H.t();
    Htr.save("test\\Htr_GPS.txt", raw_ascii);
    Dn.save("test\\Dn.txt", raw_ascii);
    mat u = Htr*inv(Dn)*H;
    mat sko ;

 /*   double z = det(u);
     ofstream f;
  f.open("test\\det.txt",ios::out | ios::app);
  f<<z<<"\n";
  f.close();*/
   if (det(u) < 0.1)
  {
  skoo[0]= -1;
  skoo[1]= -1;
  skoo[2]= -1;
  skoo[3]= -1;
  skoo[4] = -1;
  }
  else
  {
  sko = sqrt((inv(u)).t());
  skoo[0]= sko(0,0);
  skoo[1]= sko(1,1);
  skoo[2]= sko(2,2);
  skoo[3]= sko(3,3);
  skoo[4] = sqrt (pow(sko(0,0),2)+pow(sko(1,1),2)+pow(sko(2,2),2) );
  }
  sko.save("test\\skoGal.txt", raw_ascii);

}
 void downlGPS(   string *text1, //file alm
                      string text2,
                      string text3,
                      string text4,
                      string text5,
                      string textYear)
  {

  *text1 = text5+text2+text3+text4+".agp"s; //назв файла
  string text0 =   "/MCC/ALMANAC/"+ textYear +"/"+(*text1); //путь к файлу
    const char* File1 ;
    const char* file ;
    File1 = text0.c_str();//"/MCC/ALMANAC/2015/MCCJ_150307.agl"//перевод строки с строку Си
    file = (*text1).c_str();
  //  //! добавить если файла нет, искать ближайший!
   // f<< "const char* File1"<< File1<<endl;
  //  f<< " file"<< file<<endl;
    bool down = download( "ftp.glonass-iac.ru", NULL, NULL, File1, file);

  }
