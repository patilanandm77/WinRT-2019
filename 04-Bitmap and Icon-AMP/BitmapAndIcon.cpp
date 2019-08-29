
#include<windows.h>
#include "BitmapAndIcon.h"
//global callback declarations
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

//winmain()
HINSTANCE hInstance;
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow)
{
	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;
	TCHAR szAppName[] = TEXT("My App : Bitmap and Icon");


	//initialization of WNDCLASSEX

	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.lpfnWndProc = WndProc;
	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(MY_ICON));
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndclass.lpszClassName = szAppName;
	wndclass.lpszMenuName = NULL;
	wndclass.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(MY_ICON));


	RegisterClassEx(&wndclass);

	//create window

	hwnd = CreateWindow(szAppName,
		TEXT("My App : Bitmap and Icon"),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL,
		NULL,
		hInstance,
		NULL);


	ShowWindow(hwnd, iCmdShow);
	UpdateWindow(hwnd);

	//message loop

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{


	HDC hdc;
	HDC hMemdc;
	static HBITMAP hBitmap;
	static HINSTANCE hInst;
	BITMAP bitmap;
	PAINTSTRUCT ps;
	RECT rc;



	switch (iMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_CREATE:
		//GetModuleHandle(NULL);
		hInst = ((LPCREATESTRUCT)lParam)->hInstance;
		hBitmap = (HBITMAP)LoadBitmap(hInst, (LPCWSTR)MY_BITMAP);

		break;


	case WM_PAINT:
		GetClientRect(hwnd, &rc);
		hdc = BeginPaint(hwnd, &ps);
		hMemdc = CreateCompatibleDC(NULL);
		SelectObject(hMemdc,(HGDIOBJ)hBitmap);
		GetObject(hBitmap, sizeof(BITMAP), &bitmap);

		StretchBlt(hdc, 0, 0, rc.right, rc.bottom, hMemdc, 0, 0, bitmap.bmWidth, bitmap.bmHeight, SRCCOPY);
		DeleteObject(hMemdc);
		EndPaint(hwnd, &ps);
		break;
	}

	return (DefWindowProc(hwnd, iMsg, wParam, lParam));

}