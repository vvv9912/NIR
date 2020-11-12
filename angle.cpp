#include "angle.h"
#include "xyz2enu.h"

#define _USE_MATH_DEFINES
#include <math.h>

double angle(double xsput, double ysput, double zsput,double Coord_x,double Coord_y, double Coord_z, double B, double L)
{
  double ES[3];
  double Renu[3];
  double R[3];
  double lengthES;
  double C[9];
  double a;
  ES[0]=(xsput-Coord_x);
  ES[1]=(ysput-Coord_y);
  ES[2]=(zsput-Coord_z);

  lengthES =  sqrt (pow((xsput-Coord_x),2)+pow((ysput-Coord_y),2)+pow((zsput-Coord_z),2));

  R[0]= ES[0]/lengthES; // вектор столбец
  R[1]= ES[1]/lengthES;
  R[2]= ES[2]/lengthES;

  xyz2enu(B, L, C); // получение матрицы ENU в -> C

  Renu[0]=C[0]*R[0]+C[1]*R[1]+C[2]*R[2]; //вектор столбец
  Renu[1]=C[3]*R[0]+C[4]*R[1]+C[5]*R[2];
  Renu[2]=C[6]*R[0]+C[7]*R[1]+C[8]*R[2];

  a = acos (Renu[3]);
  return  a;
}
