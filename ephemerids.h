#ifndef EPHEMERIDS_H
#define EPHEMERIDS_H

typedef struct
{
  double X;
  double Y;
  double Z;

} Coordinates;
Coordinates CoordGPS(double t, //у меня toe
                     double toe, //t_almanax
                     double M0,
                    double  sqrtA,
                     double  e, //E
                    double I,
                     double  Omega0 );

#endif

