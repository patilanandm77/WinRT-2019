#pragma once
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

// {87206F99-95B5-4E38-88E7-C32346C32EA4}
const CLSID CLSID_SumSubtract = { 0x87206f99, 0x95b5, 0x4e38, 0x88, 0xe7, 0xc3, 0x23, 0x46, 0xc3, 0x2e, 0xa4 };

// {FCCD21D1-50E5-4DAC-9C35-877D94F360CB}
const IID IID_ISum = { 0xfccd21d1, 0x50e5, 0x4dac, 0x9c, 0x35, 0x87, 0x7d, 0x94, 0xf3, 0x60, 0xcb };

// {B9AAF842-CEEF-4F87-862D-7B8C59BFCA33}
const IID IID_ISubtract = { 0xb9aaf842, 0xceef, 0x4f87, 0x86, 0x2d, 0x7b, 0x8c, 0x59, 0xbf, 0xca, 0x33 };









	
