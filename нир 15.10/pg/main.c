
/***************************************************************************//**
 * \file filename.с
 * \brief Краткое описание, назначение
 * \remarks Необязательная секция, для комментариев
 * \author Автор
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
// Подключение необходимого минимума заголовочных файлов
// Первым должен подключаться интерфейсный файл модуля
#include <stdio.h>
#include <trovloloMain.cpp>


/*******************************************************************************
 * Macro Definitions
 ******************************************************************************/
// Локальные макроопределения

/*******************************************************************************
 * Extern Data
 ******************************************************************************/
// Объявления экземпляров экспортируемых данных

/*******************************************************************************
 * Local Data
 ******************************************************************************/
// Локальные объявления типов и данных

/*******************************************************************************
 * Local Function Prototypes
 ******************************************************************************/
// Прототипы локальных функций (без комментариев)

/*******************************************************************************
 * Function Pointers
 ******************************************************************************/
// Объявление указателей на функции (без комментариев)

/*******************************************************************************
 * Function Definitions
 ******************************************************************************/
// Реализация функций
// Сначала реализация интерфейсных функций, далее реализация локальных функций
// Все функции должны иметь описание



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
    fscanf(fd, "%d", &i); //01  123      - орбитальный слот или PRN (R01-R24 для ГЛОНАСС, G01-G32 для GPS), либо

    SISerr[i-1].systype = systype;
    fscanf(fd, "%d", (int *)dummy); //02  1        - учет признака пригодности (0-только пригодные КА по данным навигационных сообщений,
    //           1 - возможно использование непригодных по данным эфемерид,
    //           2 - возможно использование непригодных по данным альманахов,
    //           3 - возможно использование любых непригодных эфемерид)
    fscanf(fd, "%u", (unsigned int *)dummy); //03  12       - число
    fscanf(fd, "%c", dummy);
    fscanf(fd, "%u", (unsigned int *)dummy); //04  12       - месяц
    fscanf(fd, "%c", dummy);
    fscanf(fd, "%u", (unsigned int *)dummy);//05  12       - год
    fscanf(fd, "%u", (unsigned int *)dummy);//06  12       - часы     UTC
    fscanf(fd, "%c", dummy);
    fscanf(fd, "%u", (unsigned int *)dummy); //07  12       - минуты   UTC
    fscanf(fd, "%c", dummy);
    fscanf(fd, "%u", (unsigned int *)dummy);  //08  12       - секунды  UTC
    fscanf(fd, "%lf", (double *)dummy);  //09  123.123  - длительность интервала оценки, сутки
    fscanf(fd, "%u", (unsigned int *)dummy);  //10  123456   - общее число обработанных точек
    fscanf(fd, "%u", (unsigned int *)dummy);  //11  123      - % вошедших в оценку точек R, N, B
    fscanf(fd, "%u", (unsigned int *)dummy);  //12  123      - % вошедших в оценку точек часы
    fscanf(fd, "%u", (unsigned int *)dummy);  //13  123      - % вошедших в оценку точек SISRE
    fscanf(fd, "%u", (unsigned int *)dummy);  //14  123      - % вошедших в оценку точек Vr, Vn, Vb
    fscanf(fd, "%u", (unsigned int *)dummy);  //15  123      - % вошедших в оценку точек частота
    fscanf(fd, "%u", (unsigned int *)dummy);  //16  123      - % вошедших в оценку точек SISVE
    fscanf(fd, "%lf", (double *)dummy);// 17  123.123  - МО ошибки R, м           МIN ошибки R, м           Med модуля ошибки R, м
    fscanf(fd, "%lf", (double *)dummy);// 18  123.123  - МО ошибки N, м           МIN ошибки N, м           Med модуля ошибки N, м
    fscanf(fd, "%lf", (double *)dummy);//19  123.123  - МО ошибки B, м           МIN ошибки B, м           Med модуля ошибки B, м
    fscanf(fd, "%lf", (double *)dummy);//20  123.123  - МО ошибки часов, нс      МIN ошибки часов, нс      Med модуля ошибки часов, нс
    fscanf(fd, "%lf", (double *)dummy);//21  123.123  - МО ошибки SISRE, м       МIN ошибки SISRE, м       Med модуля ошибки SISRE, м
    fscanf(fd, "%lf", (double *)dummy);//22  123.123  - СКП R, м                 МAX ошибки R, м           95% модуля ошибки R, м
    fscanf(fd, "%lf", (double *)dummy);//23  123.123  - СКП N, м                 МAX ошибки N, м           95% модуля ошибки N, м
    fscanf(fd, "%lf", (double *)dummy);//24  123.123  - СКП B, м                 МAX ошибки B, м           95% модуля ошибки B, м
    fscanf(fd, "%lf", (double *)dummy);//25  123.123  - СКП часов, нс            МAX ошибки часов, нс      95% модуля ошибки часов, нс
    fscanf(fd, "%Lf", &(SISerr[i-1].SISRE));//26  123.123  - СКП SISRE, м             МAX ошибки SISRE, м       95% модуля ошибки SISRE, м
    fscanf(fd, "%lf", (double *)dummy);//27  123.123  - МО ошибки VR, мм/с       МIN ошибки VR, мм/с       Med ошибки VR, мм/с
    fscanf(fd, "%lf", (double *)dummy);//28  123.123  - МО ошибки VN, мм/с       МIN ошибки VN, мм/с       Med ошибки VN, мм/с
    fscanf(fd, "%lf", (double *)dummy);//29  123.123  - МО ошибки VB, мм/с       МIN ошибки VB, мм/с       Med ошибки VB, мм/с
    fscanf(fd, "%lf", (double *)dummy);//30  123.123  - МО ошибки частоты, нс/с  МIN ошибки частоты, нс    Med ошибки частоты, нс
    fscanf(fd, "%lf", (double *)dummy);//31  123.123  - МО ошибки SISVE, м       МIN ошибки SISVE, м       Med ошибки SISVE, мм/с
    fscanf(fd, "%lf", (double *)dummy);//32  123.123  - СКП VR, мм/с             МAX ошибки VR, мм/с       95% ошибки VR, мм/с
    fscanf(fd, "%lf", (double *)dummy);//33  123.123  - СКП VN, мм/с             МAX ошибки VN, мм/с       95% ошибки VN, мм/с
    fscanf(fd, "%lf", (double *)dummy);//34  123.123  - СКП VB, мм/с             МAX ошибки VB, мм/с       95% ошибки VB, мм/с
    fscanf(fd, "%lf", (double *)dummy);//35  123.123  - СКП частоты, нс/с        МAX ошибки часов, нс/c    95% ошибки часов, нс/c
    fscanf(fd, "%Lf", &(SISerr[i-1].SISVE));//36  123.123  - СКП SISVE, мм/с          МAX ошибки SISVE, мм/с    95% ошибки SISVE, мм/с
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

