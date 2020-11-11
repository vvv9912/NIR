#ifndef PARSER_H
#define PARSER_H

#ifdef __cplusplus
extern "C" {
#endif
typedef struct
{

  char systype;
  double SISRE;
  double SISVE;
 // double imax;
} data_t;

extern data_t SISerr[75];//
int parse(const char* file);


#ifdef __cplusplus
}
#endif
#endif
