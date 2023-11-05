#include "UI.h"

/// <summary>
/// Creates the UI and sets the appropriate fonts.
/// </summary>
void CreateUI(HWND hWnd, HINSTANCE hInst, HFONT hUIFont, HFONT hLogFont, HWND& hLogLabel, HWND& hLogEdit)
{

	// Add the "Log:" label.
	hLogLabel = CreateWindowEx(
		0, L"STATIC", L"Log:",
		WS_CHILD | WS_VISIBLE | SS_LEFT,
		10, 10, 100, 30,
		hWnd, NULL, hInst, NULL);
	SendMessage(hLogLabel, WM_SETFONT, (WPARAM)hUIFont, TRUE);

	// Add the log textbox.
	hLogEdit = CreateWindowEx(
		WS_EX_CLIENTEDGE, L"EDIT", L"",
		WS_CHILD | WS_VISIBLE | WS_VSCROLL | ES_MULTILINE | ES_READONLY | ES_AUTOVSCROLL,
		10, 40, 500, 500,
		hWnd, NULL, hInst, NULL);
	SendMessage(hLogEdit, WM_SETFONT, (WPARAM)hLogFont, TRUE);

}


HFONT GetSystemFont() {
	NONCLIENTMETRICS ncm{};
	ncm.cbSize = sizeof(NONCLIENTMETRICS);
	SystemParametersInfo(SPI_GETNONCLIENTMETRICS, sizeof(NONCLIENTMETRICS), &ncm, 0);
	HFONT hUIFont = CreateFontIndirect(&ncm.lfMessageFont);
	return hUIFont;
}