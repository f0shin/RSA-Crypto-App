#include "rsa_crypto.h"
#include "file_utils.h"
#include <windows.h>
#include <stdio.h>
#include <openssl/applink.c>

#define ID_ENCRYPT 1
#define ID_DECRYPT 2
#define ID_FILE_SELECT 3
#define ID_KEY_SELECT 4

HWND hEditStatus, hEditFile, hEditKey;

LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    char filename[MAX_PATH] = "", keyfile[MAX_PATH] = "";

    switch (msg) {
        case WM_CREATE:
            CreateWindow("STATIC", "RSA File Crypt App", WS_CHILD | WS_VISIBLE | SS_CENTER, 50, 10, 400, 30, hwnd, NULL, NULL, NULL);
            CreateWindow("STATIC", "~ Please Choose File ~", WS_CHILD | WS_VISIBLE | SS_CENTER, 50, 40, 400, 20, hwnd, NULL, NULL, NULL);

            hEditFile = CreateWindow("EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER, 180, 70, 130, 25, hwnd, NULL, NULL, NULL);
            hEditKey = CreateWindow("EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER, 180, 100, 130, 25, hwnd, NULL, NULL, NULL);
            CreateWindow("STATIC", "enc: .txt, dec: .dat", WS_CHILD | WS_VISIBLE | SS_CENTER, 320, 70, 130, 25, hwnd, NULL, NULL, NULL);
            CreateWindow("STATIC", "dec: private.pem", WS_CHILD | WS_VISIBLE | SS_CENTER, 320, 100, 130, 25, hwnd, NULL, NULL, NULL);

            hEditStatus = CreateWindow("STATIC", "Ready...", WS_CHILD | WS_VISIBLE | SS_CENTER, 50, 180, 400, 30, hwnd, NULL, NULL, NULL);

            CreateWindow("BUTTON", "Target File : ", WS_CHILD | WS_VISIBLE, 50, 70, 120, 25, hwnd, (HMENU)ID_FILE_SELECT, NULL, NULL);
            CreateWindow("BUTTON", "Key File : ", WS_CHILD | WS_VISIBLE, 50, 100, 120, 25, hwnd, (HMENU)ID_KEY_SELECT, NULL, NULL);

            CreateWindow("BUTTON", "Encrypt", WS_CHILD | WS_VISIBLE, 120, 140, 120, 30, hwnd, (HMENU)ID_ENCRYPT, NULL, NULL);
            CreateWindow("BUTTON", "Decrypt", WS_CHILD | WS_VISIBLE, 250, 140, 120, 30, hwnd, (HMENU)ID_DECRYPT, NULL, NULL);
            break;

        case WM_COMMAND:
            if (LOWORD(wParam) == ID_FILE_SELECT && OpenFileDialog(hwnd, filename)) {
                SetWindowText(hEditFile, filename);

            } else if (LOWORD(wParam) == ID_KEY_SELECT && OpenFileDialog(hwnd, keyfile)) {
                SetWindowText(hEditKey, keyfile);

            } else if (LOWORD(wParam) == ID_ENCRYPT) {
                GetWindowText(hEditFile, filename, MAX_PATH);
                rsa_encrypt(filename);

            } else if (LOWORD(wParam) == ID_DECRYPT) {
                GetWindowText(hEditFile, filename, MAX_PATH);
                GetWindowText(hEditKey, keyfile, MAX_PATH);
                rsa_decrypt(filename, keyfile);
            }
            break;

        case WM_CLOSE:
            DestroyWindow(hwnd);
            break;

        case WM_DESTROY:
            PostQuitMessage(0);
            break;

        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    WNDCLASS wc = {0};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = "RSA_GUI";

    RegisterClass(&wc);

    HWND hwnd = CreateWindow("RSA_GUI", "RSA File Crypt App",
                             WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU,
                             CW_USEDEFAULT, CW_USEDEFAULT, 500, 250,
                             NULL, NULL, hInstance, NULL);

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    if(GetConsoleWindow()) ShowWindow(GetConsoleWindow(), SW_HIDE); // µÚ¿¡ ¶ß´Â cmdÃ¢ ¼û±â±â

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return 0;
}
