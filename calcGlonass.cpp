#include <math.h>
#include <calcGlonass.h>

//
#include "FTPdownl.h"
#include "parser.h"
#include "angle.h"
#include "xyz2enu.h"
#include "parserGLNS.H"
#include "ephemeridsGLNS.h"

#include <wx/msgdlg.h>
#include <windows.h>
#include <wininet.h>
//
#include <armadillo>
using namespace std;
using namespace arma;


void calccGlonass(int flag, //нужно ли скачивать файл
              double (&skoo)[5],
              string text1,
              string text0,
              timeCalc calc,
              double B,double L, double h)
{
//
  double N;
  double e=0;
  double a=6378136; // радиус «
// ѕолучение координат потребител€
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
//
  double Coord_sput[3];
  double alpha;
  //  f<< " day_down="<< day_down<<endl;
  //  f<< " text4="<< text4<<endl;
    const char* File1 ;
    const char* file ;
    File1 = text0.c_str();//"/MCC/ALMANAC/2015/MCCJ_150307.agl"//перевод строки с строку —и
    file = text1.c_str();
  //  //! добавить если файла нет, искать ближайший!
   // f<< "const char* File1"<< File1<<endl;
  //  f<< " file"<< file<<endl;
  if (flag == 1)
  {
         bool down = download( "ftp.glonass-iac.ru", NULL, NULL, File1, file);
  }

    int max_sats = parseGLNS(file);


    int numberSput = 24;
    int vsb[numberSput] ;
    int sumvsb = 0;
    vector<int> Visibles; //вектор из кол-во элементов - visibles

   // f<< "Glns:"<<endl;
   // f<<"calc.GLNS_numb_fouryear_period (N4)=" << calc.GLNS_numb_fouryear_period<<endl;;
   // f <<"calc.GLNS_sec_since_week=" <<calc.GLNS_sec_since_week<<endl;;
    GlonassCoordinates Coord_sp;
    for (int i=1; i<=numberSput; i++)
    {
// ѕолучение коорд спутников
//ephemerids(double toe,int t_almanax, double M0, double sqrtA, double E, double I, double Om0, double time_week ))

      calc.timeGLNS();
      timeCalc GLNSephemTime( almanax_GLNS[i-1].date,almanax_GLNS[i-1].month, almanax_GLNS[i-1].year,0,0,0,0);
      Coord_sp = ephemeridsGLNS(calc.GLNS_numb_fouryear_period, //N4
                                calc.GLNS_day_after_vis_year,
                                calc.GLNS_sec_since_week,
                                GLNSephemTime.GLNS_numb_fouryear_period, //Na берем из расчета даты альманаха
                                almanax_GLNS[i-1].tLA,
                                almanax_GLNS[i-1].dT,
                                almanax_GLNS[i-1].dT,
                                almanax_GLNS[i-1].dTT,
                                almanax_GLNS[i-1].E,
                                almanax_GLNS[i-1].w,
                                almanax_GLNS[i-1].Lam);

     // f <<"i-1 (номер спутн) ="<<i-1<<endl;
    //  f << "GLNS_numb_fouryear_period (Na)"<<  GLNSephemTime.GLNS_numb_fouryear_period<<endl;
    //  f<<"Coord_sp.X="<<Coord_sp.X<<endl;
    //  f <<"Coord_sp.Y =" <<Coord_sp.Y<<endl;
    //  f <<"Coord_sp.Z =" <<Coord_sp.Z<<endl;

      Coord_sput[0] = Coord_sp.X;
      Coord_sput[1] = Coord_sp.Y;
      Coord_sput[2] = Coord_sp.Z;
// ќпределение угла

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
        timeCalc GLNSephemTime( almanax_GLNS[k-1].date,almanax_GLNS[k-1].month, almanax_GLNS[k-1].year,0,0,0,0);
        Coord_sp = ephemeridsGLNS(calc.GLNS_numb_fouryear_period, //N4
                                  calc.GLNS_day_after_vis_year,
                                  calc.GLNS_sec_since_week,
                                  GLNSephemTime.GLNS_numb_fouryear_period, //Na берем из расчета даты альманаха
                                  almanax_GLNS[k-1].tLA,
                                  almanax_GLNS[k-1].dT,
                                  almanax_GLNS[k-1].dT,
                                  almanax_GLNS[k-1].dTT,
                                  almanax_GLNS[k-1].E,
                                  almanax_GLNS[k-1].w,
                                  almanax_GLNS[k-1].Lam);
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
    mat Htr = H.t();
    mat sko = sqrt((inv(Htr*inv(Dn)*H)).t());
    sko.save("test\\skoGln.txt", raw_ascii);
    skoo[0]= sko(0,0);
    skoo[1]= sko(1,1);
    skoo[2]= sko(2,2);
    skoo[3]= sko(3,3);
    skoo[4] = sqrt (pow(sko(0,0),2)+pow(sko(1,1),2)+pow(sko(2,2),2) );
    }
