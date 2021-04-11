#ifndef PARSERGPS_H
#define PARSERGPS_H

#ifdef __cplusplus
extern "C" {
#endif


typedef struct
{
  int NN;
  char systype;
  int num_week;
  int time_week;
  double t_almanax;

  //  double dt;
 // double vt;
  unsigned int PRN;
  double vOm0;
  double Om0;
  double I;
  double w;
  double E;
  double sqrtA;
  double M0;
  int mass;
} data_almanax;



extern data_almanax almanax_GPS[75];
int parseGPS(const char* file);


#ifdef __cplusplus
}
#endif
#endif
