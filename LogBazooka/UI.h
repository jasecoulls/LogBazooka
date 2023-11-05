#pragma once

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files
#include <windows.h>

void				CreateUI(HWND hWnd, HINSTANCE hInst, HFONT hUIFont, HFONT hLogFont, HWND &hLogLabel, HWND &hLogEdit);
HFONT				GetSystemFont();
