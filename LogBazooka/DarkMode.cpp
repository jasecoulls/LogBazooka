#pragma once
#include "DarkMode.h"


// This class handles dark mode routines for the application.

bool ShouldAppsUseDarkMode() {
    // Check if the user has enabled dark mode.
    HKEY hKey;
    LSTATUS status = RegOpenKeyExW(HKEY_CURRENT_USER, L"Software\\Microsoft\\Windows\\CurrentVersion\\Themes\\Personalize", 0, KEY_READ, &hKey);
    if (status == ERROR_SUCCESS) {
        DWORD value = 0;  // Initialize value
        DWORD valueSize = sizeof(DWORD);
        status = RegQueryValueExW(hKey, L"AppsUseLightTheme", NULL, NULL, (LPBYTE)&value, &valueSize);
        RegCloseKey(hKey);
        if (status == ERROR_SUCCESS) {
            // If the registry value for light theme is 0, dark mode is enabled, so return true.
            return value == 0;
        }
    }

    // If the user has not enabled dark mode or there was an error reading the registry, return false.
    return false;
}


void EnableDarkModeForApp(HWND hwnd) {
	// Set window to dark mode
	SetWindowTheme(hwnd, L"DarkMode_Explorer", NULL);
	BOOL isDarkMode = TRUE;
	DwmSetWindowAttribute(hwnd, DWMWA_USE_IMMERSIVE_DARK_MODE, &isDarkMode, sizeof(isDarkMode));
}

