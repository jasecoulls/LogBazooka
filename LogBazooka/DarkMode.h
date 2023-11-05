#pragma once

#include <Windows.h>
#include <uxtheme.h>
#include <dwmapi.h>

#define DWMWA_USE_IMMERSIVE_DARK_MODE 19

void EnableDarkModeForApp(HWND hwnd);
bool ShouldAppsUseDarkMode();