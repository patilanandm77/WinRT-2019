#include<windows.h>



#include"ClassFactoryDllServerWithRegFile.h"


LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

ISum * pISum = NULL;
ISubtract * pISubtract = NULL;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int iCmdShow)
{
	WNDCLASSEX wndclass;
	HWND hwnd;
	TCHAR AppName[] = TEXT("Class Factory Client");
	MSG msg;
	HRESULT hr;

	hr = CoInitialize(NULL);

	if (FAILED(hr))
	{
		MessageBox(NULL, TEXT("COM library can not be initialized . program will now exit"), TEXT("ERROR"), MB_OK);

		exit(0);
	}


	wndclass.cbSize = sizeof(wndclass);
	wndclass.cbClsExtra = 0;
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.cbWndExtra = 0;
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.lpfnWndProc = WndProc;
	wndclass.lpszMenuName = NULL;
	wndclass.hInstance = hInstance;
	wndclass.lpszClassName = AppName;



	RegisterClassEx(&wndclass);

	hwnd = CreateWindow(AppName,
		TEXT("Client of COM Dll server"),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL,
		NULL,
		hInstance,
		NULL
	);

	ShowWindow(hwnd, WS_MAXIMIZE);

	UpdateWindow(hwnd);

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	CoUninitialize();

	return (int)msg.wParam;


}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{

	HRESULT hr;
	int iNum1, iNum2, iSum;
	TCHAR str[255];

	switch (iMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_CREATE:
		hr = CoCreateInstance(CLSID_SumSubtract, NULL, CLSCTX_INPROC_SERVER, IID_ISum, (void**)&pISum);
		if (FAILED(hr))
		{
			MessageBox(hwnd, TEXT("ISum interface can not be obtained"), TEXT("ERROR"), MB_OK);
			DestroyWindow(hwnd);
		}

		iNum1 = 20;
		iNum2 = 30;



		pISum->SumOfTwoIntegers(iNum1, iNum2, &iSum);
		wsprintf(str, TEXT("Sum of %d and %d = %d"), iNum1, iNum2, iSum);
		MessageBox(hwnd, str, TEXT("result"), MB_OK);

		hr = pISum->QueryInterface(IID_ISubtract, (void**)&pISubtract);

		if (FAILED(hr))
		{
			MessageBox(hwnd, TEXT("ISum interface can not be obtained"), TEXT("ERROR"), MB_OK);
			DestroyWindow(hwnd);
		}
		pISum->Release();
		pISum = NULL;

		iNum1 = 400;
		iNum2 = 200;

		pISubtract->SubtractionOfTwoIntegers(iNum1, iNum2, &iSum);

		pISubtract->Release();
		pISubtract = NULL;

		wsprintf(str, TEXT("Subtraction of %d and %d = %d"), iNum1, iNum2, iSum);
		MessageBox(hwnd, str, TEXT("result"), MB_OK);
		DestroyWindow(hwnd);
		break;
	}
	return DefWindowProc(hwnd, iMsg, wParam, lParam);
}


