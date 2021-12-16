#ifndef calcGlonass_H
#define calcGlonass_H
#include <fstream>
#include <iostream>
#include <string>
#include "timeCalc.h"

using namespace std;

void calccGlonass(const char* file,
                  double (&skoo)[5],
                  timeCalc calc,
                   double B,double L, double h);

void downlGlonass(   string *text1, //file alm
                      string text2,
                      string text3,
                      string text4,
                      string text5,
                      string textYear);
#endif //

