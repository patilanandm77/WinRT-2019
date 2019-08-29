
#include<windows.h>

//global callback declarations
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
DWORD WINAPI IncreamentingThread(LPVOID param);
DWORD WINAPI DecreamentingThread(LPVOID param);
//winmain()

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow)
{
	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;
	TCHAR szAppName[] = TEXT("MultiThreadingApp");





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
		TEXT("My App : MultiThreading"),
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
	//HDC hdc;
	//PAINTSTRUCT ps;
	//RECT rc;
	//TCHAR str[255];

	HANDLE hThreadOne = NULL;
	HANDLE hThreadTwo = NULL;
	switch (iMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_CREATE:
		hThreadOne = CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)IncreamentingThread,(LPVOID)hwnd,0,NULL);
		hThreadTwo = CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)DecreamentingThread,(LPVOID)hwnd,0,NULL);
		break;
	/*
	case WM_PAINT:
		GetClientRect(hwnd, &rc);
		hdc = BeginPaint(hwnd, &ps);
		SetTextColor(hdc, RGB(0, 255, 0));
		SetBkColor(hdc, RGB(0, 0, 0));
		//DrawText(hdc, str, -1, &rc, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
		EndPaint(hwnd, &ps);
		
		break;
	*/
	}

	return (DefWindowProc(hwnd, iMsg, wParam, lParam));

}


DWORD WINAPI IncreamentingThread(LPVOID param)
{
	HDC hdc;
	unsigned long int i;
	TCHAR str[255];
	hdc = GetDC((HWND) param);
	SetTextColor(hdc, RGB(0, 255, 0));
	SetBkColor(hdc,RGB(0,0,0));
	

	for (i=0;i< 4294967295;i++)
	{
		wsprintf(str,TEXT("ThreadOne -> Increamenting Order : %lu"),i);
		TextOut(hdc, 5, 5, str, wcslen(str));
	}

	ReleaseDC((HWND)param,hdc);
	return 0;

}

DWORD WINAPI DecreamentingThread(LPVOID param)
{
	HDC hdc;
	unsigned long int i;
	TCHAR str[255];
	hdc = GetDC((HWND)param);
	SetTextColor(hdc, RGB(0, 255, 0));
	SetBkColor(hdc, RGB(0, 0, 0));
	
	for (i = 4294967295;i>0 ;i--)
	{
		wsprintf(str, TEXT("ThreadTwo -> Decreamenting Order : %lu "),i);
		
		TextOut(hdc, 5, 20, str, wcslen(str));
	}

	ReleaseDC((HWND)param, hdc);
	return 0;

}




