#include "FTPdownl.h"
#include <windows.h>
#include <wininet.h>
#include <iostream>
#include <stdio.h>



bool download(LPCSTR server, LPCSTR login, LPCSTR pass, LPCSTR local_file, LPCSTR remote_file)
{
  bool status;
  HINTERNET hOpen, hConnection;

  hOpen = InternetOpen(NULL, INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);
  if (hOpen == NULL)
   return false;

  hConnection = InternetConnectA(hOpen, server, 21, login, pass, INTERNET_SERVICE_FTP, INTERNET_FLAG_PASSIVE, 0 );
  if (hConnection == NULL)
 {
   InternetCloseHandle(hOpen);
  return false;
 }

  status=FtpGetFileA(hConnection, local_file, remote_file, true, 0, FTP_TRANSFER_TYPE_UNKNOWN, 0);
  InternetCloseHandle(hConnection);
  InternetCloseHandle(hOpen);
  return status;
}
