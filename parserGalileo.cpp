#include <iostream>
//#include <ifstream>
#include <fstream>
#include "parserGalileo.h"

using namespace std;


int parserGalileo(const char* file1, almanaxGalileo *almanaxgalileo)
{

  char dummy[50];
  parseralmanaxGalileo alm;
 // almanaxGalileo almanaxgalileo[40];
  char a[100];
  //int ch=1;
  int chh = 0;
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
     F >> alm.svid;
     parserstruct(alm.svid, &almanaxgalileo[chh].svid);
     F >> dummy;
   //  cout <<"almanaxgalileo[chh]->svid = "<<almanaxgalileo[chh]->svid<<endl;
     F >> alm.aSqroot;
     parserstruct(alm.aSqroot, &almanaxgalileo[chh].aSqroot);
    //  cout <<"&almanaxgalileo[chh]->aSqroot = "<<almanaxgalileo[chh]->aSqroot<<endl;
     F >> alm.ecc;
      parserstruct(alm.ecc, &almanaxgalileo[chh].ecc);
     F >> alm.deltai;
      parserstruct(alm.deltai, &almanaxgalileo[chh].deltai);
     F >> alm.omega0;
      parserstruct(alm.omega0, &almanaxgalileo[chh].omega0);
     F >> alm.omegaDot;
      parserstruct(alm.omegaDot, &almanaxgalileo[chh].omegaDot);
     F >> alm.w;
      parserstruct(alm.w, &almanaxgalileo[chh].w);
     F >> alm.m0;
      parserstruct(alm.m0, &almanaxgalileo[chh].m0);
     F >> alm.af0;
      parserstruct(alm.af0, &almanaxgalileo[chh].af0);
     F >> alm.af1;
      parserstruct(alm.af1, &almanaxgalileo[chh].af1);
     F >> alm.iod;
      parserstruct(alm.iod, &almanaxgalileo[chh].iod);
     F >> alm.t0a;
      parserstruct(alm.t0a, &almanaxgalileo[chh].t0a);
     F >> alm.wna;
      parserstruct(alm.wna, &almanaxgalileo[chh].wna);

    memset(&alm.svid,0,sizeof(alm.svid));
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
    memset(&alm.wna,0,sizeof(alm.wna));
    chh++;
    }
   // ch++;
// cout <<"&almanaxgalileo[chh]->aSqroot = "<<almanaxgalileo[10]->aSqroot<<endl;
    //cout << a<< endl;
    memset(&a[0], 0, sizeof(a));
  //  a[100] = {0};
  }
}
return 0;
}

void parserstruct(char a[100],
                  double *d)
{
 char z[100] = {0} ;
 int ch= 0;
//for (int k = 0; k< (sizeof(a))*4; k++)
for (int k = 0; k< 20; k++)
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
//d = 1;
//double k;
//sscanf(z,"%d",d);
/*sscanf(z,"%lf",&k);
d = 0;
sscanf(z,"%f",&d);
cout << "\t\n\t\n = " <<d<<endl ;*/
}

void Downloadhttp(const char* url, const char* file2)
{
   /* URLDownloadToFileA(NULL, "http://www.gsc-europa.eu/sites/default/files/sites/all/files/2021_09_28.xml",
                     "b111.txt", 0,NULL);*/

URLDownloadToFileA(NULL,
                    url,
                    file2,
                    0,
                    NULL);

}
