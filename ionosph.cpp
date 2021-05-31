
struct alpha {
double a0,a1,a2,a3;
};
struct betta {
double b0,b1,b2,b3;
};
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

void pars(const char* file)
{ //int i;
  char dummy[50];
    FILE *fd;
   // string file = "MCCJ_150306.AGP";
    fd = fopen(file, "r");
   //fd = fopen("test.txt", "r");
    if (fd == NULL)
    {
         printf("ERORR");
    }
    else{ printf("OK"); }

    //   almanax_GPS[i-1].systype = systype;

//Строка 1
fscanf(fd, "%u", (int *)dummy); // 2.10
fscanf(fd, "%s", (int *)dummy); // N: GPS NAV DATA  2
fscanf(fd, "%s", (int *)dummy); // RINEX VERSION / TYPE
//2
fscanf(fd, "%s", (int *)dummy); //EPHEMCHECK 2.10
fscanf(fd, "%s", (int *)dummy); //MCC D.ZALETAEV
fscanf(fd, "%s", (int *)dummy); //15-Jan-21 18:00
fscanf(fd, "%s", (int *)dummy); //PGM / RUN BY / DATE
//3
fscanf(fd, "%s", (int *)dummy); //A new version of accumulating navigation files by IANC
fscanf(fd, "%", (int *)dummy); //COMMENT
//4
fscanf(fd, "%lf", &( alpha.a0));//
fscanf(fd, "%lf", &( alpha.a1));//
fscanf(fd, "%lf", &( alpha.a2));//
fscanf(fd, "%lf", &( alpha.a3));//

fscanf(fd, "%lf", &( betta.b0));//
fscanf(fd, "%lf", &( betta.b1));//
fscanf(fd, "%lf", &( betta.b2));//
fscanf(fd, "%lf", &( betta.b3));//



  fclose(fd);
   //printf("num_week = %d " , almanax_GPS[1].num_week);
  //return imax;
}
