#include <math.h>
#include <downlGalileo.h>
#include <string>
#include "FTPdownl.h"
#include "parserGalileo.h"
#include <wx/msgdlg.h>
using namespace std;

void downGalileo(int year_down,int *day_download, string *text0,
       string *text1,
       string text2,
       string text3,
       string text4)

{ int day_down = *day_download;
   text2 = to_string(year_down);
//2021-06-08
    const char* File1 ;
    const char* file ;
    *text1 = text2 + "-"s + text3 + "-"s + text4 + ".xml"s;
    *text0 = "http://www.gsc-europa.eu/sites/default/files/sites/all/files/"s+*text1;
//    f<< " *text1="<< *text1<<endl;

    file = (*text1).c_str(); //ссылка на файл
    File1 = (*text0).c_str();
 //   f<< " file"<< file<<endl;
    int ok = Downloadhttp(File1,file);
    if (ok == 0)
    {
      *text1 = text2 + "_"s + text3 + "_"s + text4 + ".xml"s;
      *text0 = "http://www.gsc-europa.eu/sites/default/files/sites/all/files/"s+*text1;
      file = (*text1).c_str(); //ссылка на файл
      File1 = (*text0).c_str();
      ok = Downloadhttp(File1,file);
  //    f<< "ok = "<<ok <<endl;
 //     f<< " file"<< file<<endl;
  //    f<< "file1 = "<< File1 <<endl;


    }
    while (ok == 0)
    {
      day_down = day_down - 1;
      if (day_down<10)
      {
        text4 = "0"s +to_string(day_down); //day текущий -1
      }
      else
      {
        text4 = to_string(day_down);
      }
      *text1 = text2 + "_"s + text3 + "_"s + text4 + ".xml"s;
      *text0 = "http://www.gsc-europa.eu/sites/default/files/sites/all/files/"s+*text1;
      file = (*text1).c_str(); //ссылка на файл
      File1 = (*text0).c_str();
      ok = Downloadhttp(File1,file);
   //   f<< "ok = "<<ok <<endl;
  //    f<< " file"<< file<<endl;
  //    f<< "file1 = "<< File1 <<endl;
      if (ok == 0)
      {
        *text1 = text2 + "-"s + text3 + "-"s + text4 + ".xml"s;
        *text0 = "http://www.gsc-europa.eu/sites/default/files/sites/all/files/"s+*text1;
        file = (*text1).c_str(); //ссылка на файл
        File1 = (*text0).c_str();
        ok = Downloadhttp(File1,file);
   //     f<< "ok = "<<ok <<endl;
    //    f<< " file = "<< file<<endl;
    //    f<< "file1 = "<< File1 <<endl;

      }
      if (day_down <= 0)
        {
          wxMessageBox(_("Альманах не удалось скачать !"), _("Error")); //доделать уменьш месяца
          break;
        }
    }
*day_download = day_down;
}
