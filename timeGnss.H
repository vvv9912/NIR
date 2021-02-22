#ifndef timeGnss_H
#define timeGnss_H


typedef struct
  {
    int Year_glonass;
    int day_after_vis_year_glonass;
    int sum_sec_glonass;
    int week_GPS;
    int sec_afterweek_GPS;
    int week_galileo;
    int sec_afterweek_galileo;
  } TimeGNSS;

double timme(int numb_GNSS);
#endif
