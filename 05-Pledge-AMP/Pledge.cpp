
#include<windows.h>

//global callback declarations
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

//winmain()

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow)
{
	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;
	TCHAR szAppName[] = TEXT("Pledge");





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
		TEXT("My App : Pledge"),
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
	PAINTSTRUCT ps;
	RECT rc;
	unsigned int x = 350;
	unsigned int y = 40;
	TCHAR str1[255] = TEXT("India is my country.");
	TCHAR str2[255] = TEXT("All Indians are my brothers and sisters.");
	TCHAR str3[255] = TEXT("I love my country, and I am proud of its rich and varied heritage.");
	TCHAR str4[255] = TEXT("I shall always strive to be worthy of it.");
	TCHAR str5[255] = TEXT("I shall respect my parents,teachers");
	TCHAR str6[255] = TEXT("and all elders and treat everyone with courtesy.");
	TCHAR str7[255] = TEXT("To my country and my people,");
	TCHAR str8[255] = TEXT("I pledge my devotion.");
	TCHAR str9[255] = TEXT("In their well being and prosperity lies my happiness.");
	switch (iMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_PAINT:
		GetClientRect(hwnd, &rc);
		hdc = BeginPaint(hwnd, &ps);

		SetTextColor(hdc, RGB(255, 128, 0));
		SetBkColor(hdc, RGB(0, 0, 0));
		//DrawText(hdc, str, -1, &rc, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
		TextOut(hdc,x,y,str1,sizeof(str1));
		TextOut(hdc,x,y*2,str2,sizeof(str2));
		TextOut(hdc,x,y*3,str3,sizeof(str3));
		
		
		SetTextColor(hdc, RGB(255, 255,255));
		SetBkColor(hdc, RGB(0, 0, 0));
		//DrawText(hdc, str, -1, &rc, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
		TextOut(hdc, x, y*4, str4, sizeof(str4));
		TextOut(hdc, x, y*5, str5, sizeof(str5));
		TextOut(hdc, x, y*6, str6, sizeof(str6));
		
		SetTextColor(hdc, RGB(0, 255, 0));
		SetBkColor(hdc, RGB(0, 0, 0));
		//DrawText(hdc, str, -1, &rc, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
		TextOut(hdc, x, y*7, str7, sizeof(str7));
		TextOut(hdc, x, y*8, str8, sizeof(str8));
		TextOut(hdc, x, y*9, str9, sizeof(str9));
		
		EndPaint(hwnd, &ps);

		break;

	}

	return (DefWindowProc(hwnd, iMsg, wParam, lParam));

}