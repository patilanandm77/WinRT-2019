#include<windows.h>

#include <tchar.h>
#include <stdio.h>
#include <strsafe.h>
#include<fileapi.h>



#include "ClassFactoryDLLServerWithRegFile.h"


class CSumSubtract : public ISum, ISubtract
{
private:
	long m_cRef;
public:
	CSumSubtract(void);
	~CSumSubtract(void);


	HRESULT __stdcall QueryInterface(REFIID, void **);
	ULONG __stdcall AddRef(void);
	ULONG __stdcall Release(void);
	HRESULT __stdcall SumOfTwoIntegers(int, int, int*);
	HRESULT __stdcall SubtractionOfTwoIntegers(int, int, int*);

};


class CSumSbtractClassFactory : public IClassFactory
{
private:
	long m_cRef;
public:
	CSumSbtractClassFactory(void);
	~CSumSbtractClassFactory(void);

	HRESULT __stdcall QueryInterface(REFIID, void **);
	ULONG __stdcall AddRef(void);
	ULONG __stdcall Release(void);

	HRESULT __stdcall CreateInstance(IUnknown *, REFIID, void **);
	HRESULT __stdcall LockServer(BOOL);

};


long glNumberOfActiveComponents = 0;
long glNumberOfServerLocks = 0;


BOOL WINAPI DllMain(HINSTANCE hDll, DWORD dwReason, LPVOID Reserved)
{
	MessageBox(NULL, TEXT("Inside Dll main "), TEXT("dll"), MB_OK);

	switch (dwReason)
	{
	case DLL_PROCESS_ATTACH:
		MessageBox(NULL, TEXT("Dll Process Attach"), TEXT("dll"), MB_OK);
		break;
	case DLL_THREAD_ATTACH:
		MessageBox(NULL, TEXT("Dll Thread attach"), TEXT("dll"), MB_OK);
		break;
	case DLL_THREAD_DETACH:
		MessageBox(NULL, TEXT("Dll Thread Detach"), TEXT("dll"), MB_OK);
		break;
	case DLL_PROCESS_DETACH:
		MessageBox(NULL, TEXT("Dll Process Detach"), TEXT("dll"), MB_OK);
		break;
	}


	return TRUE;
}



CSumSubtract::CSumSubtract(void)
{
	MessageBox(NULL, TEXT("CSumSubtract Constructor"), TEXT("dll"), MB_OK);
	m_cRef = 1;
	InterlockedIncrement(&glNumberOfActiveComponents);
}

CSumSubtract ::~CSumSubtract(void)
{
	MessageBox(NULL, TEXT("CSumSubtract Desructor"), TEXT("dll"), MB_OK);
	InterlockedDecrement(&glNumberOfActiveComponents);
}


HRESULT CSumSubtract::QueryInterface(REFIID riid, void **ppv)
{

	MessageBox(NULL, TEXT("QI CSumSubtract"), TEXT("dll"), MB_OK);
	if (riid == IID_IUnknown)
	{
		*ppv = static_cast<ISum*>(this);
	}
	else if (riid == IID_ISum)
	{
		*ppv = static_cast<ISum*>(this);
	}
	else if (riid == IID_ISubtract)
	{
		*ppv = static_cast<ISubtract*>(this);
	}
	else
	{
		*ppv = NULL;
	}

	reinterpret_cast<IUnknown*>(*ppv)->AddRef();
	return (S_OK);
}

ULONG CSumSubtract::AddRef(void)
{
	MessageBox(NULL, TEXT("AddRef CSumSubtract"), TEXT("dll"), MB_OK);
	InterlockedIncrement(&m_cRef);
	return (m_cRef);
}

ULONG CSumSubtract::Release(void)
{
	MessageBox(NULL, TEXT("Release -> CSumSubtract"), TEXT("dll"), MB_OK);
	InterlockedDecrement(&m_cRef);
	if (m_cRef == 0)
	{
		delete(this);
		return (0);
	}
	return (m_cRef);
}


HRESULT CSumSubtract::SumOfTwoIntegers(int num1, int num2, int* pSum)
{
	MessageBox(NULL, TEXT("SumOfTwoIntegers() "), TEXT("dll"), MB_OK);
	*pSum = num1 + num2;
	return(S_OK);
}

HRESULT CSumSubtract::SubtractionOfTwoIntegers(int num1, int num2, int* pSub)
{
	MessageBox(NULL, TEXT("SubtractionOfTwoIntegers() "), TEXT("dll"), MB_OK);
	*pSub = num1 - num2;
	return (S_OK);
}


CSumSbtractClassFactory::CSumSbtractClassFactory(void)
{
	MessageBox(NULL, TEXT("Contructor of CSumSubtarctClassFactory"), TEXT("dll"), MB_OK);
	m_cRef = 1;
}
CSumSbtractClassFactory::~CSumSbtractClassFactory(void)
{
	MessageBox(NULL, TEXT("Distructor of CSumSubtarctClassFactory"), TEXT("dll"), MB_OK);
}

HRESULT CSumSbtractClassFactory::QueryInterface(REFIID riid, void **ppv)
{



	MessageBox(NULL, TEXT("QI ClassFactory"), TEXT("dll"), MB_OK);
	if (riid == IID_IUnknown)
	{
		*ppv = static_cast<IClassFactory*>(this);
	}
	else if (riid == IID_IClassFactory)
	{
		*ppv = static_cast<IClassFactory*>(this);
	}
	else
	{
		*ppv = NULL;
		return (E_NOINTERFACE);
	}
	reinterpret_cast<IUnknown*>(*ppv)->AddRef();
	return (S_OK);
}

ULONG CSumSbtractClassFactory::AddRef(void)
{
	MessageBox(NULL, TEXT("AddRef ClassFactory"), TEXT("dll"), MB_OK);
	InterlockedIncrement(&m_cRef);
	return m_cRef;
}
ULONG CSumSbtractClassFactory::Release(void)
{
	MessageBox(NULL, TEXT("Release ClassFactory"), TEXT("dll"), MB_OK);
	InterlockedDecrement(&m_cRef);
	if (m_cRef == 0)
	{
		delete(this);
		return 0;
	}
	return m_cRef;
}


HRESULT CSumSbtractClassFactory::CreateInstance(IUnknown *pUnkOuter, REFIID riid, void **ppv)
{
	MessageBox(NULL, TEXT("CreateInstance ClassFactory"), TEXT("dll"), MB_OK);
	CSumSubtract *pCSumSubtract = NULL;
	HRESULT hr;

	if (pUnkOuter != NULL)
	{
		return (CLASS_E_NOAGGREGATION);
	}

	pCSumSubtract = new CSumSubtract;

	if (pCSumSubtract == NULL)
	{
		return (E_OUTOFMEMORY);
	}

	hr = pCSumSubtract->QueryInterface(riid, ppv);

	pCSumSubtract->Release();
	return hr;


}

HRESULT CSumSbtractClassFactory::LockServer(BOOL fLock)
{
	MessageBox(NULL, TEXT("LockServer ClassFactory"), TEXT("dll"), MB_OK);
	if (fLock)
	{
		InterlockedIncrement(&glNumberOfServerLocks);
	}
	else
	{
		InterlockedDecrement(&glNumberOfServerLocks);
	}
	return S_OK;
}




HRESULT __stdcall DllGetClassObject(REFCLSID rclsid, REFIID riid, void **ppv)
{

	MessageBox(NULL, TEXT("DllGetClassObject"), TEXT("dll"), MB_OK);
	CSumSbtractClassFactory *pCSumSubtractClassFactory = NULL;
	HRESULT hr;

	if (rclsid != CLSID_SumSubtract)
	{
		return CLASS_E_CLASSNOTAVAILABLE;
	}


	pCSumSubtractClassFactory = new CSumSbtractClassFactory;


	if (pCSumSubtractClassFactory == NULL)
	{
		return E_OUTOFMEMORY;
	}

	hr = pCSumSubtractClassFactory->QueryInterface(riid, ppv);
	pCSumSubtractClassFactory->Release();
	return hr;

}

HRESULT __stdcall DllCanUnloadNow(void)
{
	MessageBox(NULL, TEXT("DllCanUnloadNow"), TEXT("dll"), MB_OK);
	if ((glNumberOfActiveComponents == 0) && (glNumberOfServerLocks == 0))
	{
		return S_OK;
	}
	return S_FALSE;
}





