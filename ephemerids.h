#ifndef EPHEMERIDS_H
#define EPHEMERIDS_H

typedef struct
{
      double X;
      double Y;
      double Z;

} GlonassCoordinates;

GlonassCoordinates ephemerids(double toe,
                              double t_almanax,
                               double almanax_M0,
                              double sqrtA,
                                double E,
                                double I,
                                double Om0,
                                double time_week );

#endif

