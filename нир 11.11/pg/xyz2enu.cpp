#include <math.h>

void xyz2enu(const double lat, const double lon, double * xyz2enu)
{
	/*%*************************************************************************
	%*     Copyright c 2001 The board of trustees of the Leland Stanford     *
	%*                      Junior University. All rights reserved.          *
	%*     This script file may be distributed and used freely, provided     *
	%*     this copyright notice is always kept with it.                     *
	%*                                                                       *
	%*     Questions and comments should be directed to Todd Walter at:      *
	%*     twalter@stanford.edu                                              *
	%****************************************************33*********************
	%
	%FINDXYZ2ENU find the rotation matrix to go from XYZ ECEF coordinates
	%     to a local East North Up frame
	%   [xyz2enu] = FINDXYZ2ENU(LAT, LON)
	%  LAT, LON specify the coordinates of the center of the local frame in radians
	%  XYZ2ENU is the rotation matrix such that DELTA_ENU = XYZ2ENU*DELTA_XYZ */
	xyz2enu[0] = sin(lon);
	xyz2enu[1] = cos(lon);
	xyz2enu[2] = 0.0;

	xyz2enu[5] = cos(lat);
	xyz2enu[8] = sin(lat);

	xyz2enu[3] = -xyz2enu[1] * xyz2enu[8];
	xyz2enu[4] = -xyz2enu[0] * xyz2enu[8];

	xyz2enu[6] = xyz2enu[1] * xyz2enu[5];
	xyz2enu[7] = xyz2enu[0] * xyz2enu[5];

	xyz2enu[0] = -xyz2enu[0];
/*
  Renu[0]=xyz2enu[0]*R[0]+xyz2enu[1]*R[1]+xyz2enu[2]*R[2];
  Renu[1]=xyz2enu[3]*R[0]+xyz2enu[4]*R[1]+xyz2enu[5]*R[2];
  Renu[0]=xyz2enu[6]*R[0]+xyz2enu[7]*R[1]+xyz2enu[8]*R[2];
  */
}
