#include <math.h>
#include "include/geoc2geod.h"
void geoc2geod(double x,double y,double z, double* B, double* L, double* H)
{
double a = 6378137.0; //большая полуось
double b = 6356752.3142; // малая полуосб
double f = (a-b)/a; //сжатие
//double e = (sqrt(pow(a,2)+pow(b,2)))/a; //эксцентриситет
double epow2 = f*(2-f);
double e2; // второй эксцентриситет
e2 = epow2/(1-epow2);
//
double p = sqrt(pow(x,2)+pow(y,2)); //расстояние от оси вращения эллипсоида
double r = sqrt(pow(x,2)+pow(y,2)+pow(z,2));//геоцентрический радиус-вектор
//
double tgL = y/x;
double tgB =(z/p)*(1+e2*b/r);
double tgthetta = (1-f)*tgB; //приведенная широта
double thetta = atan(tgthetta); // рад
tgB = (z+e2*b*pow(sin(thetta),3))/(p-epow2*a*pow(cos(thetta),3));
 *B = atan(tgB); //рад
 *L = atan(tgL); //рад
double N = a/sqrt(1-epow2*pow(sin(*B),2));
//double c = a/(1-f);
//double N = c/sqrt(1+e2*pow(sin(*B),2));
 *H = (p/cos(*B))-N;
if (fabs(*H) <= 1.0)
{ *H = (z/sin(*B))-N*(1-epow2);
}
*B = *B*180.0/M_PI; //град
*L = *L*180.0/M_PI; //град
*H = *H/1000; // km
}
