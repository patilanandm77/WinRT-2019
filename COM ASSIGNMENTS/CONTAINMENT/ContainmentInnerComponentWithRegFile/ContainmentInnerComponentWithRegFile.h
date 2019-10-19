#pragma once
#include<windows.h>

class IMultiplication :public IUnknown
{
public:
	virtual HRESULT  __stdcall MultiplicationOfTwoNumbers(int, int, int*) = 0;
};

class IDivision :public IUnknown
{
public:
	virtual HRESULT __stdcall DivisionOfTwoNumbers(int, int, int*) = 0;
};


// {71B63D4A-3414-4C06-8B1D-156C9717EF37}
const CLSID CLSID_MultiplicationDivision = { 0x71b63d4a, 0x3414, 0x4c06, 0x8b, 0x1d, 0x15, 0x6c, 0x97, 0x17, 0xef, 0x37 };

// {2498E0FB-DB51-4DCA-A1D8-F1D10C1D7E80}

const IID IID_IMultiplication = { 0x2498e0fb, 0xdb51, 0x4dca, 0xa1, 0xd8, 0xf1, 0xd1, 0xc, 0x1d, 0x7e, 0x80 };


// {5154BB81-A73D-4F78-B03E-D50DCD4D9C0C}
const IID IID_IDivision = { 0x5154bb81, 0xa73d, 0x4f78, 0xb0, 0x3e, 0xd5, 0xd, 0xcd, 0x4d, 0x9c, 0xc };



