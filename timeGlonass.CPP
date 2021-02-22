#include "timeGlonass.H"
#define _USE_MATH_DEFINES
#include <math.h>
#include <ctime>


int timeGlonass()
{
  struct strtimeGlonass;
 /* {
    int Year_glonass;
    int day_after_vis_year_glonass;
    int sum_sec_glonass;
  };*/


  tm tm;
  tm.tm_year=114;
  tm.tm_mon = 1; // мес€ц года (€нварь = 0) [0,11]
  tm.tm_mday = 28;// день мес€ца [1,31]
  tm.tm_hour = 12;
  tm.tm_min=0; //0 ... 59
  tm.tm_sec=0; // 0...61
  time_t time2 = mktime(&tm);
  tm tmGlonass;
  tmGlonass.tm_year=96;//год (1900 год = 0)
  tmGlonass.tm_mon = 0; // мес€ц года (€нварь = 0) [0,11]
  tmGlonass.tm_mday = 1;// день мес€ца [1,31]
  tmGlonass.tm_hour = 0; // часы после полуночи [0,23]
  tmGlonass.tm_min=0; //минуты после часов [0,59]
  tmGlonass.tm_sec=0;  // секунды после минут [0,59]
  time_t timebaseGlonass = mktime(&tmGlonass);
  double timeGlonass = time2 - timebaseGlonass;
  double yearGl =  (static_cast<double>(tm.tm_year) - static_cast<double>(tmGlonass.tm_year))/4;
  int deltayear = tm.tm_year%4;
  tm GlonassVis;
  GlonassVis.tm_year = tm.tm_year - deltayear;
  GlonassVis.tm_mon = 0; // мес€ц года (€нварь = 0) [0,11]
  GlonassVis.tm_mday = 1;// день мес€ца [1,31]
  GlonassVis.tm_hour = 0; // часы после полуночи [0,23]
  GlonassVis.tm_min=0; //минуты после часов [0,59]
  GlonassVis.tm_sec=0;  // секунды после минут [0,59]
  time_t time_aftet_vis_year = mktime(&GlonassVis);
  int delta_day_after_vis_year = time2 - time_aftet_vis_year;
  strtimeGlonass.day_after_vis_year_glonass =delta_day_after_vis_year/(60*60*24); //дней после висок года
  double yearGlonass = timeGlonass/(60*60*24/365);
  double wekGlonass = timeGlonass/(60*60*24*7);
  int sec_afterweek_Glonass  = static_cast<int>(timeGlonass)%(60*60*24*7);
  strtimeGlonass.sum_sec_glonass = tm.tm_hour*60*60 + tm.tm_min*60 + tm.tm_sec;
  strtimeGlonass.Year_glonass = round(yearGl);

  return strtimeGlonass;

}

