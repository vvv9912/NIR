#include <iostream>
#include <fstream>
#include "parserion.H"
using namespace std;

ion  pars(const char* file)
{ //int i;
 char dummy[100];
double a0,a1,a2,a3;
  int i = 0;
  ion ion1;
  ifstream fin("BRDC0010.21N");
  if (!fin.is_open())
  cout << "don't open"<<endl;
  else
  {
  fin.getline(dummy, sizeof(dummy)); // 1 строка
  cout << dummy<<endl;
  fin.getline(dummy, sizeof(dummy)); // 2 строка
    cout << dummy<<endl;
  fin.getline(dummy, sizeof(dummy));  //3
    cout << dummy<<endl;

  fin >> ion1.a0 >>  ion1.a1 >>  ion1.a2 >> ion1.a3 ;
  cout << ion1.a0  << ion1.a1<<endl;
  fin.getline(dummy, sizeof(dummy));// дочитываем 4 строку
    cout << dummy<<endl;
  fin >> ion1.b0 >>ion1.b1>> ion1.b2>> ion1.b3;
  fin.close();

  }
  return ion1;
}
