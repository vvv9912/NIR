#ifndef PARSERGALILEO_H
#define PARSERGALILEO_H

#include <urlmon.h>
struct parseralmanaxGalileo
{
  char svid[100];
  char aSqroot[100];
  char ecc[100];
  char deltai[100];
  char omega0[100];
  char omegaDot[100];
  char w[100];
  char m0[100];
  char af0[100];
  char af1[100];
  char iod[100];
  char t0a[100];
  char wna[100];

};
struct almanaxGalileo
{
  double svid;
  double aSqroot;
  double ecc;
  double deltai;
  double omega0;
  double omegaDot;
  double w;
  double m0;
  double af0;
  double af1;
  double iod;
  double t0a;
  double wna;

};
int parserGalileo(const char* file1, almanaxGalileo *almanaxgalileo);

void parserstruct(char a[100],
                  double *d);


void Downloadhttp(const char* url, const char* file2);




#endif
