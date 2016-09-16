// GT_HelloWorldWin32.cpp
// compile with: /D_UNICODE /DUNICODE /DWIN32 /D_WINDOWS /c

#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <tchar.h>
#define IDC_MAIN_BUTTON 101

// Global variables

// The main window class name.
static TCHAR szWindowClass[] = _T("win32app");

// The string that appears in the application's title bar.
static TCHAR szTitle[] = _T("Calendar Testing");

//YearViewButton
HWND yearView;

HWND monthView;

HWND weekView;

HWND dayView;

HINSTANCE hInst;

// Forward declarations of functions included in this code module:
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_APPLICATION));
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_APPLICATION));

	if (!RegisterClassEx(&wcex))
	{
		MessageBox(NULL,
			_T("Call to RegisterClassEx failed!"),
			_T("Win32 Guided Tour"),
			NULL);

		return 1;
	}

	hInst = hInstance; // Store instance handle in our global variable

					   // The parameters to CreateWindow explained:
					   // szWindowClass: the name of the application
					   // szTitle: the text that appears in the title bar
					   // WS_OVERLAPPEDWINDOW: the type of window to create
					   // CW_USEDEFAULT, CW_USEDEFAULT: initial position (x, y)
					   // 500, 100: initial size (width, length)
					   // NULL: the parent of this window
					   // NULL: this application does not have a menu bar
					   // hInstance: the first parameter from WinMain
					   // NULL: not used in this application
	HWND hWnd = CreateWindow(
		szWindowClass,
		szTitle,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,
		700, 500,
		NULL,
		NULL,
		hInstance,
		NULL
	);

	if (!hWnd)
	{
		MessageBox(NULL,
			_T("Call to CreateWindow failed!"),
			_T("Win32 Guided Tour"),
			NULL);

		return 1;
	}

	// The parameters to ShowWindow explained:
	// hWnd: the value returned from CreateWindow
	// nCmdShow: the fourth parameter from WinMain
	ShowWindow(hWnd,
		nCmdShow);
	UpdateWindow(hWnd);

	// Main message loop:
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return (int)msg.wParam;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;
	//TCHAR greeting[] = _T("Hello, World!");
	TCHAR date[] = _T("22 AUG 2016");


	switch (message)
	{
	case WM_CREATE:
		yearView = CreateWindowEx(
			NULL,
			L"BUTTON", //Predefined class
			L"Year View", //Button Text
			WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, // Styles
			50, //x position
			50, //y position
			100, //Button Width
			25, //Button height
			hWnd, //Parent window
			(HMENU)IDC_MAIN_BUTTON, //menu
			GetModuleHandle(NULL),
			NULL);

		monthView = CreateWindowEx(
			NULL,
			L"BUTTON", //Predefined class
			L"Month View", //Button Text
			WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, // Styles
			200, //x position
			50, //y position
			100, //Button Width
			25, //Button height
			hWnd, //Parent window
			(HMENU)IDC_MAIN_BUTTON, //menu
			GetModuleHandle(NULL),
			NULL);

		weekView = CreateWindowEx(
			NULL,
			L"BUTTON", //Predefined class
			L"Week View", //Button Text
			WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, // Styles
			350, //x position
			50, //y position
			100, //Button Width
			25, //Button height
			hWnd, //Parent window
			(HMENU)IDC_MAIN_BUTTON, //menu
			GetModuleHandle(NULL),
			NULL);

		dayView = CreateWindowEx(
			NULL,
			L"BUTTON", //Predefined class
			L"Day View", //Button Text
			WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, // Styles
			500, //x position
			50, //y position
			100, //Button Width
			25, //Button height
			hWnd, //Parent window
			(HMENU)IDC_MAIN_BUTTON, //menu
			GetModuleHandle(NULL),
			NULL);


	case WM_COMMAND:
		switch (wParam)
		{
		case BN_CLICKED:
			hdc = BeginPaint(hWnd, &ps);
			if ((HWND)lParam == yearView) {
				TextOut(hdc, 110, 110, date, _tcslen(date));
				UpdateWindow(hWnd);
			}
			EndPaint(hWnd, &ps);
			break;
		}
		break;
	case WM_PAINT:
	{
		hdc = BeginPaint(hWnd, &ps);

		// Here your application is laid out.
		// For this introduction, we just print out "Hello, World!"
		// in the top left corner.
		/*TextOut(hdc,
		5, 5,
		greeting, _tcslen(greeting));*/
		// End application-specific layout section.

		//PaintRectangle
		Rectangle(hdc, 100, 100, 450, 450);

		//PrintDate
		//TextOut(hdc, 110, 110, date, _tcslen(date));


		EndPaint(hWnd, &ps);
		break;
	}
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
		break;
	}

	return 0;
}