
#include "include/getENU.h"
#include "include/xyz2enu.h"
#define _USE_MATH_DEFINES
#include <math.h>

#define SQUARE(val) val * val

void getENU(double x,double y, double z, double B, double L, double Coor[3])
{
  double R[3];
  double C[9];
  R[0]= x; // вектор столбец
  R[1]= y;
  R[2]= z;

  xyz2enu(B, L, C); // получение матрицы ENU в -> C

  Coor[0]=C[0]*R[0]+C[1]*R[1]+C[2]*R[2]; //вектор столбец
  Coor[1]=C[3]*R[0]+C[4]*R[1]+C[5]*R[2];
  Coor[2]=C[6]*R[0]+C[7]*R[1]+C[8]*R[2];
}

