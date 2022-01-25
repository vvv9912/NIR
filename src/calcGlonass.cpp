#include <math.h>
#include <include/calcGlonass.h>

//
#include "include/FTPdownl.h"
//#include "parser.h"
#include <include/parserEphGLNS.h>
#include "include/angle.h"
#include "include/xyz2enu.h"
#include "include/parserGLNS.H"
#include "include/ephemeridsGLNS.h"

#include <wx/msgdlg.h>
#include <windows.h>
#include <wininet.h>
//
#include <armadillo>
#include <fstream>
using namespace std;
using namespace arma;


void calccGlonass(const char* file,
              double (&skoo)[5],
              timeCalc calc,
              double B,double L, double h)
{
//
 /* double N;
  double e=0;
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
//
  double Coord_sput[3];
  double alpha;
  //  f<< " day_down="<< day_down<<endl;
  //  f<< " text4="<< text4<<endl;
  //  //! добавить если файла нет, искать ближайший!
   // f<< "const char* File1"<< File1<<endl;
  //  f<< " file"<< file<<endl;
    int max_sats = parseGLNS(file); //max_sats не нужен, только обрабочтик


    int numberSput = 24;
    int vsb[numberSput] ;
    int sumvsb = 0;
    vector<int> Visibles; //вектор из кол-во элементов - visibles

   // f<< "Glns:"<<endl;
   // f<<"calc.GLNS_numb_fouryear_period (N4)=" << calc.GLNS_numb_fouryear_period<<endl;;
   // f <<"calc.GLNS_sec_since_week=" <<calc.GLNS_sec_since_week<<endl;;
    GlonassCoordinates Coord_sp;
    calc.timeGLNS();

   // ofstream f;
   // f.open("test\\GLNS_COORD.txt",ios::out | ios::app);
   // f<<"iteratinon\n";
    for (int i=1; i<=numberSput; i++)
    {
// Получение коорд спутников
//ephemerids(double toe,int t_almanax, double M0, double sqrtA, double E, double I, double Om0, double time_week ))

      timeCalc GLNSephemTime( almanax_GLNS[i-1].date,almanax_GLNS[i-1].month, almanax_GLNS[i-1].year,0,0,0,0);
      GLNSephemTime.timeGLNS();
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

  //  f <<"i-1 (номер спутн) ="<<i-1<<endl;
    //  f << "GLNS_numb_fouryear_period (Na)"<<  GLNSephemTime.GLNS_numb_fouryear_period<<endl;
   // f<<"Coord_sp.X="<<Coord_sp.X<<endl;
  //  f <<"Coord_sp.Y =" <<Coord_sp.Y<<endl;
  //  f <<"Coord_sp.Z =" <<Coord_sp.Z<<endl;

      Coord_sput[0] = Coord_sp.X;
      Coord_sput[1] = Coord_sp.Y;
      Coord_sput[2] = Coord_sp.Z;
// Определение угла

      alpha = 90 - (angle(Coord_sput, Coord_user, B, L)*180/M_PI);
// определение видимости спутника
      vsb[i]=0;
      if ((alpha) >5)
      {
    // f <<"i (номер спутн) ="<<i<<endl;
    // f<<"Coord_sp.X="<<Coord_sp.X<<endl;
    //  f <<"Coord_sp.Y =" <<Coord_sp.Y<<endl;
    // f <<"Coord_sp.Z =" <<Coord_sp.Z<<endl;
        vsb[i]=1;
        sumvsb++;
      //  Visibles.push_back(i);  // добавление элемента в конец вектора
      }
    }
   //  ofstream fsumvsbGl;
    // fsumvsbGl.open("test\\sumvsbGl.txt",ios::app);
    // fsumvsbGl<<sumvsb<<"\n";
    // fsumvsbGl.close();
// получение матрицы Dn
    int i = 0;
    mat Dn;
    Dn.zeros(sumvsb, sumvsb);
    for (int k=1; k<=numberSput; k++)
    {
      if ((vsb[k]) == 1)
      {
        Dn(i,i) = pow(((SISerr_GLNS[k-1].SISRE)+ (SISerr_GLNS[k-1].M0_SRE/3.0)),2);
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
 // Dn.save("test\\DnGl.txt", raw_ascii);
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
   // H.save("test\\HGl.txt", raw_ascii);
    mat Htr = H.t();
    mat u = Htr*inv(Dn)*H;
    mat sko ;

  if (sumvsb > 4)
  {
  if (det(u) < 0.000000001)
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
  }
  else
  {
  skoo[0]= -10;
  skoo[1]= -10;
  skoo[2]= -10;
  skoo[3]= -10;
  skoo[4] = -10;
  }
//  sko.save("test\\skoGl.txt", raw_ascii);
//f<<skoo[0]<<"\t"<<skoo[1]<<"\t"<<skoo[2]<<"\t"<<skoo[3]<<"\t"<<skoo[4]<<endl;
//f<<"B = "<<B*180.0/M_PI<<"\t L ="<<L*180.0/M_PI<<"\t h ="<<h<<endl;
//f<<"date = "<<calc.c_date << "\t month = "<<calc.c_month<< "\t year = "<<calc.c_year<<endl;
//f<<"hour = "<<calc.c_hour<<"\t min = "<<calc.c_minutes<< "\t sec = "<<calc.c_sec<<endl;
//f.close();
}

void downlGlonass(   string *text1, //file alm
                      string text2,
                      string text3,
                      string text4,
                      string text5,
                      string textYear)
  {

    *text1 = text5+text2+text3+text4+".agl"s;
    string text0 =   "/MCC/ALMANAC/"+ textYear +"/"+(*text1);
    const char* File1 ;
    const char* file ;
    File1 = text0.c_str();//"/MCC/ALMANAC/2015/MCCJ_150307.agl"//перевод строки с строку Си
    file = (*text1).c_str();
  //  //! добавить если файла нет, искать ближайший!
   // f<< "const char* File1"<< File1<<endl;
  //  f<< " file"<< file<<endl;
    bool down = download( "ftp.glonass-iac.ru", NULL, NULL, File1, file);

  }
