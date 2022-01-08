#include <iostream>
//#include <ifstream>
#include <fstream>
#include "include/parserBeidou.h"
#include <cstring>
#include <stdio.h>
using namespace std;

void parserstructB(char a[100], double *d);
int parserBeidou(const char* file1, almanaxBeidou *almanaxbeidou)
{
  char date[100];
  char dummy[50];
  char a[100];
  int chh = 0;
  int imax = 0;
  double _prn;
  int prn;
  ifstream F;
  F.open(file1);
  if (F)
  {
    while (!F.eof())
    {
        F >> date;
        parserstructB(date, &_prn);
        prn = static_cast<int>(_prn);
        memset(&date,0,sizeof(date));

        almanaxbeidou[prn].PRN = prn;
       F >> almanaxbeidou[prn].H;
       F >> almanaxbeidou[prn].e;
       F >> almanaxbeidou[prn].t;
       F >> almanaxbeidou[prn].di;
       F >> almanaxbeidou[prn].Omega;
       F >> almanaxbeidou[prn].sqrta;
       F >> almanaxbeidou[prn].Omega0;
       F >> almanaxbeidou[prn].w;
       F >> almanaxbeidou[prn].m;
       F >> almanaxbeidou[prn].af0;
       F >> almanaxbeidou[prn].af1;
       F >> almanaxbeidou[prn].week;
    }
  }

  F.close();
  return imax;
}

void parserstructB(char a[100], double *d)
{
  char z[100] = {0} ;
  int ch= 0;
  //for (int k = 0; k< (sizeof(&a)); k++)//зачем я умножал на 4
  for (int k = 0; k< (sizeof(a)); k++)
  {
    if ( a[k] != 'C')
    {
    z[ch] = a[k];
    ch++;
    }
  }
//sscanf(z, "%lf", &d ) ;
  *d = atof(z);
}
