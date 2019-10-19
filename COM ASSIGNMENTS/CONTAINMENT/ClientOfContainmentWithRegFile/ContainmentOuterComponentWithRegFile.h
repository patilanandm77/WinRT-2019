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


// {30BFD0B9-3D46-44C6-8776-370905F67A63}
const CLSID CLSID_SumSubtract = { 0x30bfd0b9, 0x3d46, 0x44c6, 0x87, 0x76, 0x37, 0x9, 0x5, 0xf6, 0x7a, 0x63 };



// {7A0833D5-11C9-4AF4-8537-C4DECFE8680D}
const IID IID_ISubtract = { 0x7a0833d5, 0x11c9, 0x4af4, 0x85, 0x37, 0xc4, 0xde, 0xcf, 0xe8, 0x68, 0xd };


// {1CC65686-7AAA-4FA2-AF89-97E1CF11D59C}
const IID IID_ISum = { 0x1cc65686, 0x7aaa, 0x4fa2, 0xaf, 0x89, 0x97, 0xe1, 0xcf, 0x11, 0xd5, 0x9c };






