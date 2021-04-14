#include "timeCalc.h"
#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>
#include <ctime>

timeCalc::timeCalc(int date,
     int month,
     int year,
     int hour,
     int minutes,
     int sec,
     int m_sec)
{
c_date = date;
c_month= month;
c_year = year;
c_hour = hour;
c_minutes = minutes;
c_sec = sec;
c_m_sec = m_sec;
tm tm;
tm.tm_year=year-1900;
tm.tm_mon = month-1;
tm.tm_mday = date;
tm.tm_hour = hour;
tm.tm_min=minutes;
tm.tm_sec=sec;
time_t time = mktime(&tm);
timeSec =time;
int dt=0;
  if ((tm.tm_year) > 81)
  dt++;
  if ((tm.tm_year) > 82)
  dt++;
  if ((tm.tm_year) > 83)
  dt++;
  if ((tm.tm_year) > 85)
  dt++;
  if ((tm.tm_year) > 87)
  dt++;
  if ((tm.tm_year) > 89)
  dt++;
  if ((tm.tm_year) > 90)
  dt++;
  if ((tm.tm_year) > 92)
  dt++;
  if ((tm.tm_year) > 93)
  dt++;
  if ((tm.tm_year) > 94)
  dt++;
  if ((tm.tm_year) > 95)
  dt++;
  if ((tm.tm_year) > 97)
  dt++;
  if ((tm.tm_year) > 98)
  dt++;
  if ((tm.tm_year) > 105)
  dt++;
  if ((tm.tm_year) > 108)
  dt++;
  if ((tm.tm_year) > 112)
  dt++;
   if ((tm.tm_year) > 115)
  dt++;
   if ((tm.tm_year) > 116)
  dt++;
dT = dt;
}
timeCalc::~timeCalc()
{

}
void timeCalc::timeGLNS()
{
tm tmm;
tmm.tm_year=c_year-1900;
tmm.tm_mon = c_month-1;
tmm.tm_mday = c_date;
tmm.tm_hour = c_hour;
tmm.tm_min=c_minutes;
tmm.tm_sec=c_sec;
tm GlonassVis;
tm tmGlonass;
tmGlonass.tm_year=96;//год (1900 год = 0)
tmGlonass.tm_mon = 0; // месяц года (январь = 0) [0,11]
tmGlonass.tm_mday = 1;// день месяца [1,31]
tmGlonass.tm_hour = 0; // часы после полуночи [0,23]
tmGlonass.tm_min=0; //минуты после часов [0,59]
tmGlonass.tm_sec=0;  // секунды после минут [0,59]
timee glonass;
tmm.tm_hour = tmm.tm_hour+3;
time_t time22 = mktime(&tmm);;
time_t timebaseGlonass = mktime(&tmGlonass);
double timeGlonass = time22 - timebaseGlonass;
glonass.numb_fouryear_period = (static_cast<double>(tmm.tm_year) - static_cast<double>(tmGlonass.tm_year))/4;
int deltayear = tmm.tm_year%4;

GlonassVis.tm_year = tmm.tm_year - deltayear;
GlonassVis.tm_mon = 0; // месяц года (январь = 0) [0,11]
GlonassVis.tm_mday = 1;// день месяца [1,31]
GlonassVis.tm_hour = 0; // часы после полуночи [0,23]
GlonassVis.tm_min=0; //минуты после часов [0,59]
GlonassVis.tm_sec=0;  // секунды после минут [0,59]
time_t time_aftet_vis_year = mktime(&GlonassVis);
glonass.delta_day_after_vis_year = time22 - time_aftet_vis_year;
glonass.day_after_vis_year =glonass.delta_day_after_vis_year/(60*60*24); //дней после висок года .. учесть 1 дей.
glonass.week = timeGlonass/(60*60*24*7);
glonass.sec_after_week=fmod(timeGlonass,(60*60*24*7));
glonass.sum_sec = tmm.tm_hour*60*60 + tmm.tm_min*60 + tmm.tm_sec;
GLNS_sec_since_week = glonass.sum_sec;
GLNS_numb_fouryear_period = ceil(glonass.numb_fouryear_period); //N4 -for GLONASS ;
GLNS_day_after_vis_year = ceil(glonass.day_after_vis_year) ;
}

void timeCalc::timeGPS()
{
tm tmgps;
tmgps.tm_year=80;//год (1900 год = 0)
tmgps.tm_mon = 0; // месяц года (январь = 0) [0,11]
tmgps.tm_mday = 6;// день месяца [1,31]
tmgps.tm_hour = 0; // часы после полуночи [0,23]
tmgps.tm_min=0; //минуты после часов [0,59]
tmgps.tm_sec=0;  // секунды после минут [0,59]
time_t timebase = mktime(&tmgps);
timee gps;
double time2 = timeSec;
gps.sec = (time2 - timebase)+dT;
gps.week = gps.sec/(60*60*24*7);
//gps.sec_after_week = static_cast<int>(round(gps.sec))%(60*60*24*7);
gps.sec_after_week=fmod(gps.sec,(60*60*24*7));

sec_since_week = (gps.sec_after_week);
week = static_cast<int>(gps.week);
}
void timeCalc::timeGLL()
{
tm tmgalileo;
tmgalileo.tm_year=99;//год (1900 год = 0)
tmgalileo.tm_mon = 7; // месяц года (январь = 0) [0,11]
tmgalileo.tm_mday = 22;// день месяца [1,31]
tmgalileo.tm_hour = 0; // часы после полуночи [0,23]
tmgalileo.tm_min=0; //минуты после часов [0,59]
tmgalileo.tm_sec=0;  // секунды после минут [0,59]
timee galileo;
time_t timebasegalileo = mktime(&tmgalileo);
double time2 = timeSec;
galileo.sec =  (time2 - timebasegalileo)+dT;
galileo.week = galileo.sec/(60*60*24*7);
galileo.sec_after_week = fmod(galileo.sec,(60*60*24*7));
week = static_cast<int>(galileo.week);
sec_since_week = galileo.sec_after_week;
}
