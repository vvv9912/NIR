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
  if ((year) > 81)
  dt++;
  if ((year) > 82)
  dt++;
  if ((year) > 83)
  dt++;
  if ((year) > 85)
  dt++;
  if ((year) > 87)
  dt++;
  if ((year) > 89)
  dt++;
  if ((year) > 90)
  dt++;
  if ((year) > 92)
  dt++;
  if ((year) > 93)
  dt++;
  if ((year) > 94)
  dt++;
  if ((year) > 95)
  dt++;
  if ((year) > 97)
  dt++;
  if ((year) > 98)
  dt++;
  if ((year) > 105)
  dt++;
  if ((year) > 108)
  dt++;
  if ((year) > 112)
  dt++;
   if ((year) > 115)
  dt++;
   if ((year) > 116)
  dt++;
dT = dt;
}
timeCalc::~timeCalc()
{

}
void timeCalc::timeGLNS()
{
timee glonass;
tm GlonassVis;
tm tmGlonass;
tmGlonass.tm_year=96;//год (1900 год = 0)
tmGlonass.tm_mon = 0; // месяц года (январь = 0) [0,11]
tmGlonass.tm_mday = 1;// день месяца [1,31]
tmGlonass.tm_hour = 0; // часы после полуночи [0,23]
tmGlonass.tm_min=0; //минуты после часов [0,59]
tmGlonass.tm_sec=0;  // секунды после минут [0,59]
double time = timeSec + 3*60*60;
time_t timebaseGlonass = mktime(&tmGlonass);
double timeGlonass = time - timebaseGlonass;
glonass.numb_fouryear_period = (static_cast<double>(c_year) - static_cast<double>(c_year))/4;
int deltayear = c_year%4;
GlonassVis.tm_year = c_year - deltayear;
GlonassVis.tm_mon = 0; // месяц года (январь = 0) [0,11]
GlonassVis.tm_mday = 1;// день месяца [1,31]
GlonassVis.tm_hour = 0; // часы после полуночи [0,23]
GlonassVis.tm_min=0; //минуты после часов [0,59]
GlonassVis.tm_sec=0;  // секунды после минут [0,59]
time_t time_aftet_vis_year = mktime(&GlonassVis);
glonass.delta_day_after_vis_year = time - time_aftet_vis_year;
glonass.day_after_vis_year =glonass.delta_day_after_vis_year/(60*60*24); //дней после висок года .. учесть 1 дей.
//double yearGlonass = timeGlonass/(60*60*24/365);
glonass.week = timeGlonass/(60*60*24*7);
glonass.sec_after_week=fmod(timeGlonass,(60*60*24*7));
glonass.sum_sec = c_hour*60*60 + c_minutes *60 + c_minutes +c_m_sec;
numb_fouryear_period = glonass.numb_fouryear_period;
day_after_vis_year = ceil(glonass.day_after_vis_year);
sec_since_week = glonass.sum_sec ;
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
