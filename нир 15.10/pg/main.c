
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
 ******************************************************************************/

/*******************************************************************************
 * Includes
 ******************************************************************************/
// ����������� ������������ �������� ������������ ������
// ������ ������ ������������ ������������ ���� ������
#include <stdio.h>
#include <trovloloMain.cpp>


/*******************************************************************************
 * Macro Definitions
 ******************************************************************************/
// ��������� ����������������

/*******************************************************************************
 * Extern Data
 ******************************************************************************/
// ���������� ����������� �������������� ������

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



typedef struct
{

  char systype;
  double SISRE;
  double SISVE;

} data_t;

  int i;
  int k;
  int a = 5 ;

data_t SISerr[75];
void mmm()
{


int main(int argc, char* argv[])

  //  unsigned char hr[37];
  // unsigned char min[37];
  //unsigned char sec[37];
fd = fopen("MERMS-ESC_C.ete");
  FILE* fd;
  char systype;
  char dummy[30];
  char hr[30];
  char min[30];
  char sec[30];
//char hr;
//char min;
//char sec;
  /*printf("Hello world\n");
  printf("Number of args: %d\n", argc);
  for (i=0; i< argc; i++)
    printf("%s\n", argv[i]); */




  while ( !feof(fd) )
  {
    fscanf(fd, "%c", &systype);
    fscanf(fd, "%c", &systype);
    if (systype !='E')
    {
      printf("Sync error\n");
      break;
    }
    fscanf(fd, "%d", &i); //01  123      - ����������� ���� ��� PRN (R01-R24 ��� �������, G01-G32 ��� GPS), ����

    SISerr[i-1].systype = systype;
    fscanf(fd, "%d", (int *)dummy); //02  1        - ���� �������� ����������� (0-������ ��������� �� �� ������ ������������� ���������,
    //           1 - �������� ������������� ����������� �� ������ ��������,
    //           2 - �������� ������������� ����������� �� ������ ����������,
    //           3 - �������� ������������� ����� ����������� ��������)
    fscanf(fd, "%u", (unsigned int *)dummy); //03  12       - �����
    fscanf(fd, "%c", dummy);
    fscanf(fd, "%u", (unsigned int *)dummy); //04  12       - �����
    fscanf(fd, "%c", dummy);
    fscanf(fd, "%u", (unsigned int *)dummy);//05  12       - ���
    fscanf(fd, "%u", (unsigned int *)dummy);//06  12       - ����     UTC
    fscanf(fd, "%c", dummy);
    fscanf(fd, "%u", (unsigned int *)dummy); //07  12       - ������   UTC
    fscanf(fd, "%c", dummy);
    fscanf(fd, "%u", (unsigned int *)dummy);  //08  12       - �������  UTC
    fscanf(fd, "%lf", (double *)dummy);  //09  123.123  - ������������ ��������� ������, �����
    fscanf(fd, "%u", (unsigned int *)dummy);  //10  123456   - ����� ����� ������������ �����
    fscanf(fd, "%u", (unsigned int *)dummy);  //11  123      - % �������� � ������ ����� R, N, B
    fscanf(fd, "%u", (unsigned int *)dummy);  //12  123      - % �������� � ������ ����� ����
    fscanf(fd, "%u", (unsigned int *)dummy);  //13  123      - % �������� � ������ ����� SISRE
    fscanf(fd, "%u", (unsigned int *)dummy);  //14  123      - % �������� � ������ ����� Vr, Vn, Vb
    fscanf(fd, "%u", (unsigned int *)dummy);  //15  123      - % �������� � ������ ����� �������
    fscanf(fd, "%u", (unsigned int *)dummy);  //16  123      - % �������� � ������ ����� SISVE
    fscanf(fd, "%lf", (double *)dummy);// 17  123.123  - �� ������ R, �           �IN ������ R, �           Med ������ ������ R, �
    fscanf(fd, "%lf", (double *)dummy);// 18  123.123  - �� ������ N, �           �IN ������ N, �           Med ������ ������ N, �
    fscanf(fd, "%lf", (double *)dummy);//19  123.123  - �� ������ B, �           �IN ������ B, �           Med ������ ������ B, �
    fscanf(fd, "%lf", (double *)dummy);//20  123.123  - �� ������ �����, ��      �IN ������ �����, ��      Med ������ ������ �����, ��
    fscanf(fd, "%lf", (double *)dummy);//21  123.123  - �� ������ SISRE, �       �IN ������ SISRE, �       Med ������ ������ SISRE, �
    fscanf(fd, "%lf", (double *)dummy);//22  123.123  - ��� R, �                 �AX ������ R, �           95% ������ ������ R, �
    fscanf(fd, "%lf", (double *)dummy);//23  123.123  - ��� N, �                 �AX ������ N, �           95% ������ ������ N, �
    fscanf(fd, "%lf", (double *)dummy);//24  123.123  - ��� B, �                 �AX ������ B, �           95% ������ ������ B, �
    fscanf(fd, "%lf", (double *)dummy);//25  123.123  - ��� �����, ��            �AX ������ �����, ��      95% ������ ������ �����, ��
    fscanf(fd, "%Lf", &(SISerr[i-1].SISRE));//26  123.123  - ��� SISRE, �             �AX ������ SISRE, �       95% ������ ������ SISRE, �
    fscanf(fd, "%lf", (double *)dummy);//27  123.123  - �� ������ VR, ��/�       �IN ������ VR, ��/�       Med ������ VR, ��/�
    fscanf(fd, "%lf", (double *)dummy);//28  123.123  - �� ������ VN, ��/�       �IN ������ VN, ��/�       Med ������ VN, ��/�
    fscanf(fd, "%lf", (double *)dummy);//29  123.123  - �� ������ VB, ��/�       �IN ������ VB, ��/�       Med ������ VB, ��/�
    fscanf(fd, "%lf", (double *)dummy);//30  123.123  - �� ������ �������, ��/�  �IN ������ �������, ��    Med ������ �������, ��
    fscanf(fd, "%lf", (double *)dummy);//31  123.123  - �� ������ SISVE, �       �IN ������ SISVE, �       Med ������ SISVE, ��/�
    fscanf(fd, "%lf", (double *)dummy);//32  123.123  - ��� VR, ��/�             �AX ������ VR, ��/�       95% ������ VR, ��/�
    fscanf(fd, "%lf", (double *)dummy);//33  123.123  - ��� VN, ��/�             �AX ������ VN, ��/�       95% ������ VN, ��/�
    fscanf(fd, "%lf", (double *)dummy);//34  123.123  - ��� VB, ��/�             �AX ������ VB, ��/�       95% ������ VB, ��/�
    fscanf(fd, "%lf", (double *)dummy);//35  123.123  - ��� �������, ��/�        �AX ������ �����, ��/c    95% ������ �����, ��/c
    fscanf(fd, "%Lf", &(SISerr[i-1].SISVE));//36  123.123  - ��� SISVE, ��/�          �AX ������ SISVE, ��/�    95% ������ SISVE, ��/�
   fscanf(fd, "%c", &systype);


  }

  int imax=i;

  for (i=0; i<=imax; i++)
  {  // printf("ssi", i, "=" ,SISerr[i-1].SISRE);
     if (SISerr[i].SISRE>0)
     {


   printf("PRN=%u\n",i+1);
   printf("SISRE=%lf\n" ,SISerr[i].SISRE);
   printf("SISVE=%lf\n\n" ,SISerr[i].SISVE);
     }
  }

 // printf("ii=%u\n",i);
//printf("ssi1=%lf\n",SISerr[i-1].SISRE);
// printf("min=%u\n",min[26]);
//printf("ii=%u\n",i);

/*
  printf("hr=%u\n",hr[3]);
printf("min=%u\n",min[26]);
printf("ssi1=%lf\n",SISerr[0].SISRE);
printf("ssi2=%lf\n",SISerr[1].SISRE);
printf("ssi3=%lf\n",SISerr[2].SISRE);
printf("ssi4=%lf\n",SISerr[3].SISRE);

printf("ssi5=%lf\n",SISerr[4].SISRE);
printf("ssi6=%lf\n",SISerr[5].SISRE);
printf("ssi7=%lf\n",SISerr[6].SISRE);
printf("ssi8=%lf\n",SISerr[7].SISRE);
printf("ssi9=%lf\n",SISerr[8].SISRE);
printf("ssi10=%lf\n",SISerr[9].SISRE);
printf("ssi11=%lf\n",SISerr[10].SISRE);
printf("ssi12=%lf\n",SISerr[11].SISRE);
printf("ssi13=%lf\n",SISerr[12].SISRE);
printf("ssi14=%lf\n",SISerr[13].SISRE);
printf("ssi15=%lf\n",SISerr[14].SISRE);
printf("ssi16=%lf\n",SISerr[15].SISRE);
printf("ssi17=%lf\n",SISerr[16].SISRE);
printf("ssi18=%lf\n",SISerr[17].SISRE);
printf("ssi19=%lf\n",SISerr[18].SISRE);  */

  fclose(fd);
  return 0;

}
/*int f_2()
{
    main();
}

*/

/*******************************************************************************
 * END OF FILE
 ******************************************************************************/

