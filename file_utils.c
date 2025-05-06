#include "file_utils.h"
#include <commdlg.h>
#include <stdio.h>

#define SAVE_PATH "C:\\crypt\\"

// file_utils.c : 파일 선택 & 폴더 생성 구현

BOOL OpenFileDialog(HWND hwnd, char *filename) {
    OPENFILENAME ofn;
    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = hwnd;
    ofn.lpstrFilter = "Text Files\0*.txt\0Key Files\0*.pem\0All Files\0*.*\0";
    ofn.lpstrFile = filename;
    ofn.nMaxFile = MAX_PATH;
    ofn.Flags = OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST;
    return GetOpenFileName(&ofn);
}

void create_folder_if_not_exists() {
    DWORD attributes = GetFileAttributes(SAVE_PATH);
    if (attributes == INVALID_FILE_ATTRIBUTES || !(attributes & FILE_ATTRIBUTE_DIRECTORY)) {
        CreateDirectoryA(SAVE_PATH, NULL);
    }
}
