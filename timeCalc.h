#ifndef TIMECALC_H
#define TIMECALC_H

struct timee{
double sec;
double week;
double sec_after_week;
double day_after_vis_year;
double delta_day_after_vis_year ;
double sum_sec;
double numb_fouryear_period;
double sec_after_week_plus_delta;
};
class timeCalc
{
public:
  timeCalc(int date,
     int month,
     int year,
     int hour,
     int minutes,
     int sec,
     int m_sec ); // msec пока не используется.
  ~timeCalc(); // дописать
  int dT; // поправки ко времени
  int sec_since_week; //GPS,GALILEO
  int week;//GPS,GALILEO
  int GLNS_sec_since_week;
  int GLNS_numb_fouryear_period; //N4 -for GLONASS ;
  int GLNS_day_after_vis_year;//NT - for GLONASS

  void timeGLNS();
  void timeGPS();
  void timeGLL();
  double timeSec;
  int c_date;
  int c_month;
  int c_year; //в формате 2015
  int c_hour;
  int c_minutes;
  int c_sec;
  int c_m_sec;
protected:
  /*double timeSec;
  int c_date;
  int c_month;
  int c_year; //в формате 2015
  int c_hour;
  int c_minutes;
  int c_sec;
  int c_m_sec;*/
};

#endif
