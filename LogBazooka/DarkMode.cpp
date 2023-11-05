#pragma once
#include "DarkMode.h"


// This class handles dark mode routines for the application.

bool ShouldAppsUseDarkMode() {

	// Check if the user has enabled dark mode.
	HKEY hKey;
	LSTATUS status = RegOpenKeyExW(HKEY_CURRENT_USER, L"Software\\Microsoft\\Windows\\CurrentVersion\\Themes\\Personalize", 0, KEY_READ, &hKey);
	if (status == ERROR_SUCCESS) {

		DWORD value;
		DWORD valueSize = sizeof(DWORD);
		status = RegQueryValueExW(hKey, L"AppsUseLightTheme", NULL, NULL, (LPBYTE)&value, &valueSize);
		RegCloseKey(hKey);
		if (status == ERROR_SUCCESS) {

			// If the user has enabled dark mode, return true.
			if (value == 0) {
				return true;
			}
		}
	}

	// If the user has not enabled dark mode, return false.
	return false;
}


void EnableDarkModeForApp(HWND hwnd) {
	// Set window to dark mode
	SetWindowTheme(hwnd, L"DarkMode_Explorer", NULL);
	//DwmSetWindowAttribute(hwnd, DWMWA_USE_IMMERSIVE_DARK_MODE, &(BOOL) {TRUE}, sizeof(BOOL));
}

