#ifndef PARSERGLNS_H
#define PARSERGLNS_H

#ifdef __cplusplus
extern "C" {
#endif


typedef struct
{
  int NN;
  char systype;
  int date;
  int month;
  int year;
  double t_almanax;

  //  double dt;
 // double vt;
  unsigned int PRN;
  double tLA; // строка 2 -п.7
  double Lam ;
  double dI;
  double w;
  double E;
  double dT;
  double dTT;

  int mass;
} data_almanax_GLNS;



extern data_almanax_GLNS almanax_GLNS[75];
int parseGLNS(const char* file);


#ifdef __cplusplus
}
#endif
#endif
