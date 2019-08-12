
#include<windows.h>
#define MY_TIMER 300
#define BOTTOM_TIMER 301
//global callback declarations
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
TIMERPROC CALLBACK BottomTimerProc(HWND, UINT, UINT, DWORD);
static int time = 2000;
static int BottomTimer = 0;
static int iPaintFlag = 0;
//winmain()

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow)
{
	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;
	TCHAR szAppName[] = TEXT("My App : ANAND PATIL");


	//initialization of WNDCLASSEX

	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.lpfnWndProc = WndProc;
	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndclass.lpszClassName = szAppName;
	wndclass.lpszMenuName = NULL;
	wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);


	RegisterClassEx(&wndclass);

	//create window

	hwnd = CreateWindow(szAppName,
		TEXT("My App : Anand Patil"),
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

	//sTCHAR str[255];
	HDC hdc;

	HBRUSH hBrush;
	PAINTSTRUCT ps;
	RECT rc;
	static int i;
	static LONG BottomSize;

	static LONG Left, Right, Top, Bottom;
	switch (iMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_CREATE:
		SetTimer(hwnd, MY_TIMER, 1000, NULL);
		GetClientRect(hwnd, &rc);


		break;

	case WM_CHAR:
		switch (LOWORD(wParam))
		{
		case 'R':
		case 'r':
			iPaintFlag = 1;

			InvalidateRect(hwnd, NULL, true);
			break;
		case 'G':
		case 'g':
			iPaintFlag = 2;
			InvalidateRect(hwnd, NULL, true);
			break;
		case 'B':
		case 'b':
			iPaintFlag = 3;
			InvalidateRect(hwnd, NULL, true);
			break;
		case 'C':
		case 'c':
			iPaintFlag = 4;
			InvalidateRect(hwnd, NULL, true);
			break;
		case 'M':
		case 'm':
			iPaintFlag = 5;
			InvalidateRect(hwnd, NULL, true);
			break;
		case 'Y':
		case 'y':
			iPaintFlag = 6;
			InvalidateRect(hwnd, NULL, true);
			break;
		case 'W':
		case 'w':
			iPaintFlag = 7;
			InvalidateRect(hwnd, NULL, true);
			break;
		case '-':
			time += 200;
			break;
		case '+':
			time -= 200;
			break;
			/*
			default :
				//iPaintFlag = 0;
				InvalidateRect(hwnd, NULL, true);
				break;
				*/
		}

		break;
	case WM_TIMER:

		KillTimer(hwnd, MY_TIMER);

		if (iPaintFlag > 7)
		{
			iPaintFlag = 0;
			InvalidateRect(hwnd, NULL, true);
		}
		if (time < 200)
		{
			time = 200;
		}
		if (time > 2000)
		{
			time = 2000;
		}


		SetTimer(hwnd, MY_TIMER, time, NULL);
		iPaintFlag++;
		InvalidateRect(hwnd, NULL, false);
		break;
	case WM_PAINT:
		GetClientRect(hwnd, &rc);

		Left = rc.left;
		Right = rc.right;
		Top = rc.top;
		Bottom = rc.bottom;

		hdc = BeginPaint(hwnd, &ps);
		switch (iPaintFlag)
		{
		case 1:
			hBrush = CreateSolidBrush(RGB(255, 0, 0));//green
			SelectObject(hdc, hBrush);
			rc.right = (Right / 8);
			rc.left = 0;
			//rc.bottom = (Bottom / 8) *2;
			FillRect(hdc, &rc, hBrush);
			break;

		case 2:
			hBrush = CreateSolidBrush(RGB(0, 255, 0));//green
			SelectObject(hdc, hBrush);
			rc.right = (Right / 8) * 2;
			rc.left = Right / 8;
			//rc.bottom = (Bottom / 8) *2;
			FillRect(hdc, &rc, hBrush);
			break;
		case 3:
			hBrush = CreateSolidBrush(RGB(0, 0, 255));//blue
			SelectObject(hdc, hBrush);
			rc.right = (Right / 8) * 3;
			rc.left = (Right / 8) * 2;
			//rc.bottom = (Bottom / 8)*3;
			FillRect(hdc, &rc, hBrush);
			break;
		case 4:
			hBrush = CreateSolidBrush(RGB(0, 255, 255));//cyan
			SelectObject(hdc, hBrush);
			rc.right = (Right / 8) * 4;
			rc.left = (Right / 8) * 3;
			//rc.bottom = (Bottom / 8)*4;
			FillRect(hdc, &rc, hBrush);
			break;
		case 5:
			hBrush = CreateSolidBrush(RGB(255, 0, 255));//magenta
			SelectObject(hdc, hBrush);
			rc.right = (Right / 8) * 5;
			rc.left = (Right / 8) * 4;
			//rc.bottom = (Bottom / 8) * 5;
			FillRect(hdc, &rc, hBrush);
			break;
		case 6:
			hBrush = CreateSolidBrush(RGB(255, 255, 0));//yellow
			SelectObject(hdc, hBrush);
			rc.right = (Right / 8) * 6;
			rc.left = (Right / 8) * 5;
			//rc.bottom = (Bottom / 8) * 6;
			FillRect(hdc, &rc, hBrush);
			break;
		case 7:
			hBrush = CreateSolidBrush(RGB(255, 255, 255));//
			SelectObject(hdc, hBrush);
			rc.right = (Right / 8) * 7;
			rc.left = (Right / 8) * 6;
			//rc.bottom = (Bottom / 8) * 7;
			FillRect(hdc, &rc, hBrush);
			break;
		default:
			hBrush = CreateSolidBrush(RGB(0, 0, 0));
			SelectObject(hdc, hBrush);
			rc.right = (Right / 8) * 8;
			rc.left = (Right / 8) * 7;
			FillRect(hdc, &rc, hBrush);
			break;

		}
		EndPaint(hwnd, &ps);
		break;
	}

	return (DefWindowProc(hwnd, iMsg, wParam, lParam));

}
