#include <math.h>
#include <include/calcGalileo.h>

//
#include "include/FTPdownl.h"
//#include "parser.h"
#include <include/parserEphGAL.h>
#include "include/parserGalileo.h"
#include "include/angle.h"
#include "include/ephemerids.h"
#include "include/xyz2enu.h"

#include <wx/msgdlg.h>
#include <windows.h>
#include <wininet.h>
//
#include <armadillo>
using namespace std;
using namespace arma;

void calccGalileo(const char* file,
                  double (&skoo)[5],
                  timeCalc calc,
                  timeCalc calcGalileo,
                  double B,double L, double h )


{  /*  double N;
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
 /* double Coord_x;
  double Coord_y;
  double Coord_z;
  Coord_x = (N+h)*cos(B)*cos(L);
  Coord_y = (N+h)*cos(B)*sin(L);
  Coord_z = ((1-epow2)*N+h)*sin(B);*/
  double Coord_user[3];
  Coord_user[0]=(N+h)*cos(B)*cos(L);
  Coord_user[1]= (N+h)*cos(B)*sin(L);
  Coord_user[2]= ((1-epow2)*N+h)*sin(B);

  double Coord_sput[3];
  double alpha;

    calcGalileo.timeGLL();
   // f<<"day_down ="<<day_down<<endl;
  //  f<<" month_down ="<<month_down<<endl;
  //  f<<" year_down="<<year_down<<endl;
  //  f<< "week = " <<calcGalileo.week<<endl;
    //int weekGalileo = calcGalileo.week % 4;
//    f<< " file = "<< file<<endl;
   // f<< "file1 = "<< File1 <<endl;
    //файл с альманахом скачен
    almanaxGalileo almm[26];
    int max_sats = parserGalileo(file, almm);
    //расчет матрицы Dn
    int numberSput = 24;
    int vsb[numberSput];
    int sumvsb = 0;
    calc.timeGLL();
    double toe = calc.sec_since_week;
 //   f<< "Galileo:"<<endl;
 //   f<<"toe()calc.sec_since_week="<<toe<<endl;
 //   f<<"week="<<calc.week<<endl;
//    aSqroot = sqrt(A)-sqrt(Anom)
    double Anom = 29600000; //м
    //sqrt(A) = aSqroot + sqrt(Anom);
   Coordinates Coord_sp;
    for (int i=1; i<=numberSput; i++)
    {
      Coord_sp = ephemerids(toe,
                            almm[i-1].t0a,
                            almm[i-1].m0,
                            (almm[i-1].aSqroot)+sqrt(Anom), //проверить
                            almm[i-1].ecc, // проверить
                            almm[i-1].iod/M_PI,
                            almm[i-1].omega0,
                            calc.week); //Термин WNa представляет
      // собой двоичное представление по модулю
      //4 номера недели времени системы Galileo.
   //   f <<"i-1 (номер спут)"<<i-1<<endl;
   //   f<< "numb sp = "<<almm[i-1].svid<<endl;
  //    f<<"Coord_sp.X="<<Coord_sp.X<<endl;
  //   f <<"Coord_sp.Y =" <<Coord_sp.Y<<endl;
  //    f <<"Coord_sp.Z =" <<Coord_sp.Z<<endl;

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
//        Visibles.push_back(i);  // добавление элемента в конец вектора
      }
    }
  //    ofstream fsumvsbGal;
   //  fsumvsbGal.open("test\\sumvsbGal.txt",ios::app);
  //   fsumvsbGal<<sumvsb<<"\n";
  //   fsumvsbGal.close();
//    f <<"sumvsb =" <<sumvsb<<endl;
    // получение матрицы Dn
    int i = 0;
    mat Dn;
    Dn.zeros(sumvsb, sumvsb);
    for (int k=1; k<=numberSput; k++)
    {
      if ((vsb[k]) == 1)
      {

        Dn(i,i) = pow((SISerr_Gal[k-1].SISRE+ (SISerr_Gal[k-1].M0_SRE/3.0)),2);
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
                              almm[k-1].t0a,
                              almm[k-1].m0,
                              (almm[k-1].aSqroot)+sqrt(Anom), //проверить
                              almm[k-1].ecc, // проверить
                              almm[k-1].iod/M_PI,
                              almm[k-1].omega0,
                              calc.week); //Термин WNa представляет
        // собой двоичное представление по модулю
        //4 номера недели времени системы Galileo.
        dx=(Coord_sp.X- Coord_user[0]);
        dy=(Coord_sp.Y-Coord_user[1]);
        dz=(Coord_sp.Z- Coord_user[2]);
    //    f<<"Coord_sp.X = "<<Coord_sp.X<<endl;
    //    f<<"Coord_sp.Y = "<<Coord_sp.Y<<endl;
    //    f<<"Coord_sp.Z = "<<Coord_sp.Z<<endl;

// Ri = sqrt (SQUARE(dx)+SQUARE(dy)+SQUARE(dz));
        Ri = sqrt (pow(dx,2)+pow(dy,2)+pow(dz,2));
//        f<< "Ri"<< Ri<<endl;
        H(numsput, 0 ) = dx/Ri;
      //  double k =  H(numsput, 0 );
        H(numsput, 1) = dy/Ri;
        H(numsput, 2) = dz/Ri;
        H(numsput, 3) = 1;
        numsput++ ;
      }
    }
    //f <<  mat Htr <<endl;
    mat Htr = H.t();
    mat u = Htr*inv(Dn)*H;
    mat sko ;
  if (sumvsb >= 4)
  {
  if (det(u) < 0.000000001)
  {
  skoo[0]= 0;
  skoo[1]= 0;
  skoo[2]= 0;
  skoo[3]= 0;
  skoo[4] = 0;
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
  skoo[0]= 0;
  skoo[1]= 0;
  skoo[2]= 0;
  skoo[3]= 0;
  skoo[4] = 0;
  }
 // sko.save("test\\skoGal.txt", raw_ascii);

}
