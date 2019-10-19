#pragma once

#include<windows.h>
class ISum :public IUnknown
{
public:
	virtual HRESULT __stdcall SumOfTwoIntegers(int, int, int*) = 0;
};

class ISubtract : public IUnknown
{
public:
	virtual HRESULT __stdcall SubtractionOfTwoIntegers(int, int, int*) = 0;
};


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


// {21BCFBC6-DF7C-4600-A513-6C5907196D15}
const CLSID CLSID_SumSubtract = { 0x21bcfbc6, 0xdf7c, 0x4600, 0xa5, 0x13, 0x6c, 0x59, 0x7, 0x19, 0x6d, 0x15 };






// {19CFBCE4-FD71-48BE-84BE-A6FC562266FE}
const IID IID_ISubtract = { 0x19cfbce4, 0xfd71, 0x48be, 0x84, 0xbe, 0xa6, 0xfc, 0x56, 0x22, 0x66, 0xfe };





// {E2906917-5DC0-4157-BB50-CC3CBED6AA57}
const IID IID_ISum = { 0xe2906917, 0x5dc0, 0x4157, 0xbb, 0x50, 0xcc, 0x3c, 0xbe, 0xd6, 0xaa, 0x57 };










