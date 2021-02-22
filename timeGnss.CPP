#include "timeGnss.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include <ctime>
//#include <time.h>

double timeGnss(int numb_GNSS)
{
  tm tmGlonass;
  struct TimeGNSS;
  tm tm;
  tm.tm_year=114;
  tm.tm_mon = 1; // мес€ц года (€нварь = 0) [0,11]
  tm.tm_mday = 28;// день мес€ца [1,31]
  tm.tm_hour = 12;
  tm.tm_min=0; //0 ... 59
  tm.tm_sec=0; // 0...61
  time_t time2 = mktime(&tm);

  switch (numb_GNSS)
  {
  case 0: //Glonass

  {
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
  day_after_vis_year_glonass =delta_day_after_vis_year/(60*60*24); //дней после висок года
  double yearGlonass = timeGlonass/(60*60*24/365);
  double wekGlonass = timeGlonass/(60*60*24*7);
  int sec_afterweek_Glonass  = static_cast<int>(timeGlonass)%(60*60*24*7);
  sum_sec_glonass = tm.tm_hour*60*60 + tm.tm_min*60 + tm.tm_sec;
  Year_glonass = round(yearGl);
 } break;

  case 1: //GPS

 {

  tm tmgps;
  tmgps.tm_year=80;//год (1900 год = 0)
  tmgps.tm_mon = 0; // мес€ц года (€нварь = 0) [0,11]
  tmgps.tm_mday = 6;// день мес€ца [1,31]
  tmgps.tm_hour = 0; // часы после полуночи [0,23]
  tmgps.tm_min=0; //минуты после часов [0,59]
  tmgps.tm_sec=0;  // секунды после минут [0,59]
  time_t timebase = mktime(&tmgps);
  double deltatime = time2 - timebase;
  double wek= deltatime/ (60*60*24*7);
  sec_afterweek_GPS = static_cast<int>(deltatime)%(60*60*24*7);
  week_GPS = static_cast<int>(wek);
 } break;

  case 2: //Galileo
{ tm tmgalileo;
  tmgalileo.tm_year=99;//год (1900 год = 0)
  tmgalileo.tm_mon = 7; // мес€ц года (€нварь = 0) [0,11]
  tmgalileo.tm_mday = 22;// день мес€ца [1,31]
  tmgalileo.tm_hour = 0; // часы после полуночи [0,23]
  tmgalileo.tm_min=0; //минуты после часов [0,59]
  tmgalileo.tm_sec=0;  // секунды после минут [0,59]
  time_t timebasegalileo = mktime(&tmgalileo);
  double timegalileo = time2 - timebasegalileo;
  double wekgalileo = timegalileo/((60*60*24*7));
  int sec_afterweek_galileo = static_cast<int>(timegalileo)%(60*60*24*7);
  week_galileo = static_cast<int>(wekgalileo);
}

  break;
  }

return TimeGNSS;

}
