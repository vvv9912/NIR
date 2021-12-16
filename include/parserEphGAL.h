#ifndef parserEphGAL_H
#define parserEphGAL_H

#ifdef __cplusplus
extern "C" {
#endif
typedef struct
{

  char systype;
  double SISRE;
  double SISVE;
  double M0_SRE;
} data_t_Gal;

extern data_t_Gal SISerr_Gal[75];
int parseEph_Gal(const char* file);


#ifdef __cplusplus
}
#endif
#endif
