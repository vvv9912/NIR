#ifndef parserEphGLNS_H
#define parserEphGLNS_H

#ifdef __cplusplus
extern "C" {
#endif
typedef struct
{

  char systype;
  double SISRE;
  double SISVE;
} data_t_GLNS;

extern data_t_GLNS SISerr_GLNS[75];
int parseEph_GLNS(const char* file);


#ifdef __cplusplus
}
#endif
#endif
