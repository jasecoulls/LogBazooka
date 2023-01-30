// LogBazooka.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "LogBazooka.h"
#include "LogRoutines.h"
#include <string>
#include <iostream>


#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

HWND hThisWnd;                                  // The main window hWnd.
HWND hLogLabel;                                 // The Log: label.
HWND hLogEdit;                                  // The log edit box.

HFONT hUIFont;                                  // This is the font we use for the UI.
HFONT hLogFont;                                 // This is the font we use for the log.

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
void                ResizeLogWindowToFitMainWindow();
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
void                AddStringToLog(std::wstring str);
void                CreateUI();
void                MakeHighDPIAware();


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_LOGBAZOOKA, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);
    MakeHighDPIAware();

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_LOGBAZOOKA));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}


/// <summary>
/// Sets the application to be high DPI aware (no fuzzy text)
/// </summary>
void MakeHighDPIAware() {
	typedef BOOL(WINAPI* SetProcessDPIAwareFunc)();
	SetProcessDPIAwareFunc setProcessDPIAwareFunc = (SetProcessDPIAwareFunc)GetProcAddress(GetModuleHandle(TEXT("user32.dll")), "SetProcessDPIAware");
	if (setProcessDPIAwareFunc) {
		setProcessDPIAwareFunc();
	}
}

/// <summary>
/// Creates the UI and sets the appropriate fonts.
/// </summary>
void CreateUI() 
{
    // Add the log: label.
	hLogLabel = CreateWindowEx(
		0, L"STATIC", L"Log:",
		WS_CHILD | WS_VISIBLE | SS_LEFT,
		10, 10, 100, 30,
		hThisWnd, NULL, hInst, NULL);
	SendMessage(hLogLabel, WM_SETFONT, (WPARAM)hUIFont, TRUE);
    
	// Add the log edit box.
	hLogEdit = CreateWindowEx(
		WS_EX_CLIENTEDGE, L"EDIT", L"",
		WS_CHILD | WS_VISIBLE | WS_VSCROLL | ES_MULTILINE | ES_AUTOVSCROLL,
		10, 40, 500, 500,
		hThisWnd, NULL, hInst, NULL);
	SendMessage(hLogEdit, WM_SETFONT, (WPARAM)hLogFont, TRUE);
	ClearLog(hLogEdit);
}

//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex{};

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_LOGBAZOOKA));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_LOGBAZOOKA);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }
   
   // Store the hWnd for later.
   hThisWnd = hWnd;
   
   // Set hUIFont to whatever the system font currently is.
   NONCLIENTMETRICS ncm{};
   ncm.cbSize = sizeof(NONCLIENTMETRICS);
   SystemParametersInfo(SPI_GETNONCLIENTMETRICS, sizeof(NONCLIENTMETRICS), &ncm, 0);
   hUIFont = CreateFontIndirect(&ncm.lfMessageFont);
   
   // Set hLogFont to Consolas.
   hLogFont = CreateFont(16, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, L"Consolas");
   
   CreateUI();
   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

/// <summary>
/// Resizes the hLogEdit window to fit the main window with a 10 pixel margin.
/// </summary>
void ResizeLogWindowToFitMainWindow() 
{
    const int TOP_OFFSET = 40;
    const int MARGIN = 10;

	// Get the size of the main window.
    RECT rect;
    if (GetClientRect(hThisWnd, &rect))
    {
        int width = rect.right - rect.left;
        int height = rect.bottom - rect.top - TOP_OFFSET;

        // Subtract off the margin
        width = width - (MARGIN * 2);
        height = height - (MARGIN * 2);

        // Get the position of the current hLogEdit window.
		RECT logEditRect;
		if (GetWindowRect(hLogEdit, &logEditRect))
		{
			// Move the hLogEdit window to the new position.
			MoveWindow(hLogEdit, MARGIN, TOP_OFFSET, width, height, TRUE);
		}
        

    }
    
}

void AddStringToLog(std::wstring str)
{
	// Get the current text length.
	int length = GetWindowTextLength(hLogEdit);

	// Put the selection at the end of text.
	SendMessage(hLogEdit, EM_SETSEL, (WPARAM)length, (LPARAM)length);

	// prepend a newline.
    std::wstring newstr = L"\r\n" + str;
    
	// Replace the selection.
	SendMessage(hLogEdit, EM_REPLACESEL, FALSE, (LPARAM)newstr.c_str());
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
        case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            case IDM_SAVE:
                SaveLog(hLogEdit, hThisWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
        
        case WM_COPYDATA:
        {
            // Extract the WM_COPYDATA to a logitem.
            COPYDATASTRUCT* pcds = (COPYDATASTRUCT*)lParam;

            // Work out what we're about to show.
            if (pcds->dwData == LOGTYPE_INT) {
                // Create an int from the value in cbData.
                int newNumber = pcds->cbData;
                // Convert the int to a string
                std::wstring newNumberString = std::to_wstring(newNumber);
                AddStringToLog(newNumberString);
            }
            else if (pcds->dwData == LOGTYPE_STRING) {
                // Get the string length.
                int stringLength = pcds->cbData;
                const char* str = (const char*)(pcds->lpData);
                // Convert to a wstring and add to log.
				std::wstring wstr = std::wstring(str, str + stringLength);
				AddStringToLog(wstr);
            }
			else if (pcds->dwData == LOGTYPE_HEX) {
				// Get the number value.
				int newNumber = pcds->cbData;
				// Convert to a hex string.
				std::string hexValue = int_to_hex(newNumber);
				std::wstring wstr = std::wstring(hexValue.begin(), hexValue.end());
				AddStringToLog(wstr);
            }
        }
        break;

        case WM_CTLCOLORSTATIC:
        {
            HDC hdcStatic = (HDC)wParam;
            SetBkMode(hdcStatic, TRANSPARENT);
            return (INT_PTR)(HBRUSH)GetStockObject(NULL_BRUSH);
        }
        break;
        

        case WM_SIZE:
        {
            ResizeLogWindowToFitMainWindow();
        }
        break;

        case WM_DESTROY:
        {
            PostQuitMessage(0);
        }
        break;

		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
            
    }
    return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
