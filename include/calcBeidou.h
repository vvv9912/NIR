#ifndef calcBeidou_H
#define calcBeidou_H
#include <fstream>
#include <iostream>
#include <string>
#include "timeCalc.h"

using namespace std;

void calccBeidou(const char* file,
              double (&skoo)[5],
              timeCalc calc,
              double B,double L, double h);
#endif //

