#ifndef PARSEREPHB_H
#define PARSEREPHB_H

#ifdef __cplusplus
extern "C" {
#endif
typedef struct
{

  char systype;
  double SISRE;
  double SISVE;
  double M0_SRE;
} data_t_Beidou;

extern data_t_Beidou SISerr_Beidou[75];
int parseEph_B(const char* file);


#ifdef __cplusplus
}
#endif
#endif
