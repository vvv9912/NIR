// Начнем с директив препроцессора. ADD_H – это произвольное уникальное имя (обычно используется имя заголовочного файла)
#include <windows.h>

#ifndef FTPdonwl_H
#define FTPdonwl_H

bool download(LPCSTR server, LPCSTR login, LPCSTR pass, LPCSTR local_file, LPCSTR remote_file);

#endif


