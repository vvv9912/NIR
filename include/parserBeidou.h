#ifndef PARSERBEIDOU_H
#define PARSERBEIDOU_H


struct almanaxBeidou
{
  int PRN=0;
  double H;
  double e;
  double t;
  double di;
  double Omega;
    double Omega0;
  double sqrta;
  double w;
  double m;
  double af0;
  double af1;
  double week;
};
//void parserstructB(char a[100], double *d);
int parserBeidou(const char* file1, almanaxBeidou *almanaxbeidou);

#endif
