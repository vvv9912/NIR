#ifndef parserEphGPS_H
#define parserEphGPS_H

#ifdef __cplusplus
extern "C" {
#endif
typedef struct
{

  char systype;
  double SISRE;
  double SISVE;
} data_t_GPS;

extern data_t_GPS SISerr_GPS[75];
int parseEph_GPS(const char* file);


#ifdef __cplusplus
}
#endif
#endif
