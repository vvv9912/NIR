#include "angle.h"
#include "xyz2enu.h"

#define _USE_MATH_DEFINES
#include <math.h>

#define SQUARE(val) val * val

double angle(double Coord_sput[3],double Coord[3], double B, double L)
{
  double ES[3];
  double Renu[3];
  double R[3];
  double lengthES;
  double C[9];
  double a;

  ES[0]=(Coord_sput[0]-Coord[0]);
  ES[1]=(Coord_sput[1]-Coord[1]);
  ES[2]=(Coord_sput[2]- Coord[2]);

  lengthES =  sqrt (pow((Coord_sput[0]- Coord[0]),2)+pow((Coord_sput[1]-Coord[1]),2)+pow((Coord_sput[2]- Coord[2]),2));
//lengthES =  sqrt (SQUARE(Coord_sput[0]- Coord[0])+SQUARE(Coord_sput[1]-Coord[1])+SQUARE(Coord_sput[2]- Coord[2]));
  R[0]= ES[0]/lengthES; // вектор столбец
  R[1]= ES[1]/lengthES;
  R[2]= ES[2]/lengthES;

  xyz2enu(B, L, C); // получение матрицы ENU в -> C

  Renu[0]=C[0]*R[0]+C[1]*R[1]+C[2]*R[2]; //вектор столбец
  Renu[1]=C[3]*R[0]+C[4]*R[1]+C[5]*R[2];
  Renu[2]=C[6]*R[0]+C[7]*R[1]+C[8]*R[2];

  a = acos (Renu[2]); // rad
  return  a;
}
