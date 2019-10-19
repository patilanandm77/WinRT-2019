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
	virtual HRESULT __stdcall DivisionOfTwoNumbers(int,int,int*) = 0;
};


// {ABEB648C-2B68-405B-B577-2C8FD1EB401C}
const CLSID CLSID_MultiplicationDivision = { 0xabeb648c, 0x2b68, 0x405b, 0xb5, 0x77, 0x2c, 0x8f, 0xd1, 0xeb, 0x40, 0x1c };

// {CC1F954D-1447-429C-B65D-D33C85C405EF}
const IID IID_IMultiplication = { 0xcc1f954d, 0x1447, 0x429c, 0xb6, 0x5d, 0xd3, 0x3c, 0x85, 0xc4, 0x5, 0xef };

// {CCDBE5CA-4825-43FA-A588-2A26614A2EAC}
const IID IID_IDivision = { 0xccdbe5ca, 0x4825, 0x43fa, 0xa5, 0x88, 0x2a, 0x26, 0x61, 0x4a, 0x2e, 0xac };



