

void ionospheric(double E,double A, double phi_u, double lymbda_u, double GPStime,const char* file)
{
  pars(file);
  //E;GpsTime;
  if (GPStime >=86400)
  GPStime -= 86400;
  if (GPStime <0)
  GPStime += 86400;
  double phim, phi_i,  Y, A,t;
  double lymbda_i;
  t = 4.32*1e4*lymbda_i+GPStime;
  Y = (0.0137/(E+0.11))-0.022;
  phi_i = phi_u + Y*cos(A);
  if (phi_i > 0.416)
    phi_i+=0.416;
  if (phi_i < 0.416)
    phi_i-=0.416;

  lymbda_i =lymbda_u + (Y*sin(A))/cos(phi_i);

  phim = phi_i+0.064*cos(lymbda_i-13617);
  double AMP;
  //AMP = sum()..; phi_m^n; n -?
  if (AMP< 0)
    AMP=0;
  //per
  double PER;
  //PER =
  if (PER < 72.000)
    PER = 72.000;
  //F
  double F = 1.0+16.0*pow((0.53-E),3);
  //x
  double x = (2*M_PI*(t-50400)/PER);
  //T
  double Tiono;
  if (fabs(x)<1.57)
  {
    Tiono= F*(5.0e-9+(AMP)*(1-(pow(x,2)/2)+(pow(x,4)/24)));
  }
  else
  {
    Tiono= F*(5.0e-9);
  }

}


