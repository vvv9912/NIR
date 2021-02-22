#include "TimeGPS.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include <ctime>
//#include <time.h>

double timeGPS()
{
  struct strTimeGPS;
  tm tm;
  tm.tm_year=114;
  tm.tm_mon = 1; // мес€ц года (€нварь = 0) [0,11]
  tm.tm_mday = 28;// день мес€ца [1,31]
  tm.tm_hour = 12;
  tm.tm_min=0; //0 ... 59
  tm.tm_sec=0; // 0...61
  time_t time2 = mktime(&tm);

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




return strTimeGPS;

}

