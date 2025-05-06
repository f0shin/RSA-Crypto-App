#ifndef FILE_UTILS_H
#define FILE_UTILS_H

#include <windows.h>

// file_utils.h : 파일 선택 & 폴더 생성 정의

BOOL OpenFileDialog(HWND hwnd, char *filename);
void create_folder_if_not_exists();

#endif // FILE_UTILS_H
