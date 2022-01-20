#include <iostream>
//#include <ifstream>
#include <fstream>
#include "include/parserGalileo.h"

using namespace std;


int parserGalileo(const char* file1, almanaxGalileo *almanaxgalileo)
{
  char date[100];
  char dummy[50];
  char a[100];
  int chh = 0;
  int imax = 0;
  char c[100] = "<svAlmanac>";
  ifstream F;
  F.open(file1);
  if (F)
  {
    while (!F.eof())
    {

      F >> a;
      //while (!"<svAlmanac>")
      if (strcmp(a,c) == 0)
      {
        F >> date;
        parserstruct(date, &almanaxgalileo[chh].svid);
        memset(&date,0,sizeof(date));
        F >> dummy;
        //  cout <<"almanaxgalileo[chh]->svid = "<<almanaxgalileo[chh]->svid<<endl;
        F >> date;
        parserstruct(date, &almanaxgalileo[chh].aSqroot);
        memset(&date,0,sizeof(date));
        //  cout <<"&almanaxgalileo[chh]->aSqroot = "<<almanaxgalileo[chh]->aSqroot<<endl;
        F >> date;
        parserstruct(date, &almanaxgalileo[chh].ecc);
        memset(&date,0,sizeof(date));
        F >> date;
        parserstruct(date, &almanaxgalileo[chh].deltai);
        memset(&date,0,sizeof(date));
        F >> date;
        parserstruct(date, &almanaxgalileo[chh].omega0);
        memset(&date,0,sizeof(date));
        F >> date;
        parserstruct(date, &almanaxgalileo[chh].omegaDot);
        memset(&date,0,sizeof(date));
        F >> date;
        parserstruct(date, &almanaxgalileo[chh].w);
        memset(&date,0,sizeof(date));
        F >> date;
        parserstruct(date, &almanaxgalileo[chh].m0);
        memset(&date,0,sizeof(date));
        F >> date;
        parserstruct(date, &almanaxgalileo[chh].af0);
        memset(&date,0,sizeof(date));
        F >> date;
        parserstruct(date, &almanaxgalileo[chh].af1);
        memset(&date,0,sizeof(date));
        F >> date;
        parserstruct(date, &almanaxgalileo[chh].iod);
        memset(&date,0,sizeof(date));
        F >> date;
        parserstruct(date, &almanaxgalileo[chh].t0a);
        memset(&date,0,sizeof(date));
        F >> date;
        parserstruct(date, &almanaxgalileo[chh].wna);
        memset(&date,0,sizeof(date));
        /*  memset(&alm.svid,0,sizeof(alm.svid));
          memset(&alm.aSqroot,0,sizeof(alm.aSqroot));
          memset(&alm.ecc,0,sizeof(alm.ecc));
          memset(&alm.deltai,0,sizeof(alm.deltai));
          memset(&alm.omega0,0,sizeof(alm.omega0));
          memset(&alm.omegaDot,0,sizeof(alm.omegaDot));
          memset(&alm.w,0,sizeof(alm.w));
          memset(&alm.m0,0,sizeof(alm.m0));
          memset(&alm.af0,0,sizeof(alm.af0));
          memset(&alm.af1,0,sizeof(alm.af1));
          memset(&alm.iod,0,sizeof(alm.iod));
          memset(&alm.t0a,0,sizeof(alm.t0a));
          memset(&alm.wna,0,sizeof(alm.wna));*/
        imax = chh;
        chh++;

      }
      memset(&a[0], 0, sizeof(a));
    }
  }
  F.close();
  //перенос массива
/*  for (int i = 0; i<=imax; i++ )
  {

  }
  */
  return imax;
}

void parserstruct(char a[100], double *d)
{
  char z[100] = {0} ;
  int ch= 0;
  //for (int k = 0; k< (sizeof(&a)); k++)//зачем я умножал на 4
  for (int k = 0; k< (sizeof(a))*4; k++)
  {
    if ( a[k] == '>'  )
    {
      k++;
      while (a[k] != '<')
      {
        z[ch] = a[k];
        k++;
        ch++;
      }
      break;
    }
  }
//sscanf(z, "%lf", &d ) ;
  *d = atof(z);

}

int Downloadhttp(const char* url, const char* file2)
{
  /* URLDownloadToFileA(NULL, "http://www.gsc-europa.eu/sites/default/files/sites/all/files/2021_09_28.xml",
                    "b111.txt", 0,NULL);*/
  if (URLDownloadToFileA(NULL,url,file2, 0,NULL) == S_OK)
    return 1;
    else return 0;
                    // return k;
}
