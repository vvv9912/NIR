#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>
#include <ctime>
//#include <chrono>
using namespace std;
void rashetcoord(double N4 ,
                              double N,
                              double ti,
                              double N_A,
                              double tlymbda_A,
                              double dT,
                              double dI,
                              double dTT,
                              double Ee,
                              double omegaA,
                              double Lam );
int main()
{
rashetcoord(5,789,54000,
788, 0.452390625e+4,-0.2656127e+4,0.1220703e-2, //0.6758690E-02
0.1220703E-02,0.5750656E-03,  0.3695374E+00, 0.5243139E+00 );
return 0;
}



void rashetcoord(double N4 ,
                              double N,
                              double ti,
                              double N_A,
                              double tlymbda_A,
                              double dT,
                              double dI,
                              double dTT,
                              double Ee,
                              double omegaA,
                              double Lam )
{//1. Определяется интервал прогноза пр Δtпр в секундах:
double dN_A;
double Tsr = 43200; //номинальное значение периода обращения НКА, в секундах (Tср определено в nинтерфейсе соответствующего сигнала)
double isr = 63; // Из указаний
if (N4 == 27)
  dN_A= N-N_A-(floor((N-N_A)/1461)*1460); //() вычисление целого, ближайшего к x
else
  dN_A= N-N_A-(floor((N-N_A)/1461)*1461);

double dtpr = dN_A*86400+(ti-tlymbda_A);
 printf("dtpr = %0.3f c\n", dtpr );
//2.Рассчитывается количество целых витков W на интервале прогноза:
double W = floor(dtpr/(Tsr+dT)); // dTa = dT ? поправка к среднему значению драконического периода обращения.
cout << "W"<<W<<endl;
//3 Определяется текущее наклонение:
double i = ((isr/180)+dI)*M_PI; //ΔiA = dI ? – поправка к среднему значению наклонения орбиты.
 printf("i = %0.3f c\n", i );
//4 Определяются средний драконический период на витке W+1 и среднее движение:
double Tdr = Tsr+dT+(2*W+1)*dTT; //dT'a = dTT; половинная скорость изменения драконического периода.
 printf("Tdr = %0.3f c\n", Tdr);
double n = 2*M_PI/Tdr;
 printf("n = %0.3f c\n", n);
//5.Методом последовательных приближений m = 0, 1, 2… рассчитывается большая полуось орбиты a:

double GM = 398600441.8e6; //геоцентрическая константа гравитационного поля Земли с учетом атмосферы,
double ae = 6378136; // большая (экваториальная) полуось общеземного эллипсоида ПЗ-90
double J02 = 1082.62575e-6; //зональный гармонический коэффициент второй степени
double Tosk;
double p;
double a;
double epsA = Ee;
//стартовые значения
double a_old = 0;
a = 1;
Tosk = Tdr;
p = 0;

/*
while (abs(a-a_old)>1e-2)
{a_old = a;
a = pow((pow((Tosk/(2*M_PI)),2)*GM),1/3); //Tock = Tdr;
p = a*(1-pow(epsA,2));
Tosk = Tdr/((1-(3/2)*J02*pow((ae/p),2))*((2-(5/2)*pow(sin(i),2))*((pow(1-
pow(epsA,2),3/2))/(1+epsA*pow(cos(omegaA*M_PI),2)))+
(1+epsA*pow(cos(omegaA*M_PI),3))/(1-pow(epsA,2))));
cout << "----"<<ksh<<endl;
 printf("a = %0.3f c\n", a);
  printf("p = %0.3f c\n", p);
    printf("Tosk  = %0.3f c\n", Tosk );
    ksh++;
}*/

double eq1 = 2 - (5/2)*pow(sin(i),2);
double eq2 = 1 - pow(epsA,2);
double eq3 = 1 + epsA*cos(omegaA*M_PI);
double eq4 = pow(eq2,3/2);
double eq5 = pow(eq3,2);
double eq6 = eq4 / eq5;
double eq7 = pow(eq3,3);
double eq8 = eq7 / eq2;
double Big_div = eq1 * eq6 + eq8;
double eq9;
printf("J02  = %0.9f c\n", J02 );
printf("a = %0.9f c\n", a);
printf("p = %0.9f c\n", p);
printf("Tosk  = %0.9f c\n", Tosk );

int ksh = 1;
while (abs(a - a_old) > 1e-5)
{a_old = a;
a = pow((pow((Tosk/(2*M_PI)),2)*GM),1/3);
p = a*eq2;
eq9 = 1 - (3/2)*J02*(pow((ae/p),2));
Tosk = Tdr/(eq9*Big_div);
cout << "----"<<ksh<<endl;
printf("a = %0.9f c\n", a);
printf("p = %0.9f c\n", p);
printf("Tosk  = %0.20 c\n", Tosk );
ksh++;
}

//6Определяются текущие значения долготы восходящего узла орбиты и аргумента
//перигея с учетом их векового движения под влиянием сжатия Земли:
double omegaZ = 7.2921150e-5; //угловая скорость вращения Земли

double lymbda = Lam*M_PI-(omegaZ+(3/2)*J02*n*pow((ae/p),2)*cos(i))*dtpr;
double omega =  omegaA*M_PI-(3/4)*J02*n*pow((ae/p),2)*(1-5*pow(cos(i),2))*dtpr;

//7Рассчитывается значение средней долготы на момент прохождения текущего
//восходящего узла:
double E0 = -2*a*atan((sqrt((1-epsA)/(1+epsA)))*tan(omega/2));
double L1 =omega + E0 - epsA*sin(E0);
//8Определяется текущее значение средней долготы НКА:
double L = L1+n*(dtpr-(Tsr+dT)*W-dTT*pow(W,2));
//10Определяется эксцентрическая аномалия путем решения уравнения Кеплера
double E = L - omega;
double Eold = 0;
while (abs(E-Eold)>1e-9)
  {
  Eold = E;
  ////////////////////////////////////////
  E = L-omega+ epsA*sin(E); // eps ?! !! стра 81, п10 икд
  ////////////////////////////////////////
  }
//11Вычисляются истинная аномалия  и аргумент широты НКА u:
double v = 2*atan((sqrt((1-epsA)/(1+epsA)))*tan(E/2));
double u = v + omega;
//12Рассчитываются координаты центра масс НКА в геоцентрической
//прямоугольной пространственной системе координат:
double r = p/(1+epsA*cos(v));

double x = r*(cos(lymbda)*cos(u)-sin(lymbda)*sin(u)*cos(i));
double y = r*(sin(lymbda)*cos(u)+cos(lymbda)*sin(u)*cos(i));
double z = r*sin(u)*sin(i);
cout <<x <<endl;
cout <<y <<endl;
cout <<z <<endl;

}

