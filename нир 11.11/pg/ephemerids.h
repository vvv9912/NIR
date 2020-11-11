#ifndef EPHEMERIDS_H
#define EPHEMERIDS_H

typedef struct
{
      double X;
      double Y;
      double Z;

} GlonassCoordinates;

GlonassCoordinates ephemerids(int n, int t);

#endif

