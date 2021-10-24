#ifndef calcGlonass_H
#define calcGlonass_H
#include <fstream>
#include <iostream>
#include <string>
#include "timeCalc.h"

using namespace std;

void calccGlonass(int flag,//нужно ли скачивать файл
              double (&skoo)[5],
              string text1,
              string text0, //если файл уже скачен оставить нулевой
              timeCalc calc,
              double B,double L, double h);
#endif //

