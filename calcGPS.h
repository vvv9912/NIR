#ifndef calcGPS_H
#define calcGPS_H
#include <fstream>
#include <iostream>
#include <string>
#include "timeCalc.h"

using namespace std;

void calccGPS(int flag,//����� �� ��������� ����
              double (&skoo)[5],
              string text1,
              string text0, //���� ���� ��� ������ �������� �������
              timeCalc calc,
              double B,double L, double h);
#endif //
