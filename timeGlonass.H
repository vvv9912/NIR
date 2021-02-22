#ifndef timeGlonass_H
#define timeGlonass_H


typedef struct
  {
    int Year_glonass;
    int day_after_vis_year_glonass;
    int sum_sec_glonass;

  } strtimeGlonass;

int timeGlonass();
#endif

