
/***************************************************************************//**
 * \file filename.�
 * \brief ������� ��������, ����������
 * \remarks �������������� ������, ��� ������������
 * \author �����
 *
 * \if use_svn_keywords
 *  ::                                    $: Revision of last commit
 *  ::                                        $: Date of last commit
 *  ::                                      $: Author of last commit
 * \endif
 *
 * \b LICENSE \b INFORMATION \n
 *  Copyright (c) Year, Company, City, Country
 ******************************************************************************/

/*******************************************************************************
 * Includes
 ******************************************************************************/
// ����������� ������������ �������� ������������ ������
// ������ ������ ������������ ������������ ���� ������
#include <stdio.h>
#include "parserGPS.H"

//#include "parserGPS.h"
/*******************************************************************************
 * Macro Definitions
 ******************************************************************************/
// ��������� ����������������

/*******************************************************************************
 * Extern Data
 ******************************************************************************/
// ���������� ����������� �������������� ������
data_almanax_GPS almanax_GPS[75];
/*******************************************************************************
 * Local Data
 ******************************************************************************/
// ��������� ���������� ����� � ������

/*******************************************************************************
 * Local Function Prototypes
 ******************************************************************************/
// ��������� ��������� ������� (��� ������������)

/*******************************************************************************
 * Function Pointers
 ******************************************************************************/
// ���������� ���������� �� ������� (��� ������������)

/*******************************************************************************
 * Function Definitions
 ******************************************************************************/
// ���������� �������
// ������� ���������� ������������ �������, ����� ���������� ��������� �������
// ��� ������� ������ ����� ��������

/*******************************************************************************
 * END OF FILE
 *****************************************************/


int parseGPS(const char* file)
{
  int i;
  int  Numbb;
  char systype;
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
    while ( !feof(fd) )                               // ���� �� ����� �����
    {
    //   almanax_GPS[i-1].systype = systype;

//������ 1
fscanf(fd, "%u", (int *)dummy); //1 - ����� ��������� ���������
fscanf(fd, "%u", (int *)dummy); //2 - ����� ��������� ���������
fscanf(fd, "%u", (int *)dummy); //3 - ��� ��������� ���������
fscanf(fd, "%u", &Numbb); //4 -


//������ 2
fscanf(fd, "%u", &(i));//1 - ����� PRN
almanax_GPS[i-1].PRN=i;
almanax_GPS[i-1].NN = Numbb;
fscanf(fd, "%u", (int *)dummy);//2 - ���������� ������� ��������
fscanf(fd, "%u", &( almanax_GPS[i-1].num_week));//3 - ������ GPS (���������)
fscanf(fd, "%u", &( almanax_GPS[i-1].time_week));//4 - ����� ������ GPS, � (���������)
fscanf(fd, "%u", (int *)dummy);//5 - �����
fscanf(fd, "%u", (int *)dummy);//6 - �����
fscanf(fd, "%u", (int *)dummy);//7 - ���
fscanf(fd, "%lf", &( almanax_GPS[i-1].t_almanax));//8 - ����� ���������, �
fscanf(fd, "%lf", (int *)dummy);//9 - �������� ������� �� GPS ������������ ���������� �������, �
fscanf(fd, "%lf", (int *)dummy);//10- �������� �������� ������� �� GPS ������������ ���������� �������, �/�
fscanf(fd, "%lf", &( almanax_GPS[i-1].vOm0));//11- Om0 - �������� ������� ����, ���������/c

//������ 3
fscanf(fd, "%lf", &( almanax_GPS[i-1].Om0));//1 - Om0 - ������� ����, ���������
fscanf(fd, "%lf", &( almanax_GPS[i-1].I));//2 - I - ����������, ���������
fscanf(fd, "%lf", &( almanax_GPS[i-1].w));//3 - w - �������� �������, ���������
fscanf(fd, "%lf", &( almanax_GPS[i-1].E));//4 - E - ��������������
fscanf(fd, "%lf", &( almanax_GPS[i-1].sqrtA));//5 - SQRT(A) - ������ �� ������� �������, �**0.5
fscanf(fd, "%lf", &( almanax_GPS[i-1].M0));//6 - M0 - ������� ��������, ���������

almanax_GPS[i-1].PRN=i;



   }
     int imax=i;
     almanax_GPS[0].mass = imax;
  fclose(fd);

   //printf("num_week = %d " , almanax_GPS[1].num_week);

  return imax;
}
