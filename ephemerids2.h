#ifndef EPHEMERIDS2_H
#define EPHEMERIDS2_H

typedef struct
{
  double X;
  double Y;
  double Z;

} Coordinatess;
Coordinatess CoordGPS(double t, //у меня toe
                     double toe, //t_almanax
                     double M0,
                    double  sqrtA,
                     double  e, //E
                    double I,
                     double  Omega0 );

#endif

