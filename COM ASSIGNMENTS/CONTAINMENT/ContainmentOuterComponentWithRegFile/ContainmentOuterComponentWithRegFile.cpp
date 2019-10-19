#include<windows.h>

#include <tchar.h>
#include <stdio.h>
#include <strsafe.h>
#include<fileapi.h>


//#include "ContainmentInnerComponentWithRegFile.h"
//#include "ContainmentOuterComponentWithRegFile.h"
#include "Header.h"


class CSumSubtract : public ISum, ISubtract,IMultiplication,IDivision
{
private:
	long m_cRef;
	
	IMultiplication *m_pIMultiplication;
	IDivision *m_pIDivision;
public:
	

	CSumSubtract(void);
	~CSumSubtract(void);


	HRESULT __stdcall QueryInterface(REFIID, void **);
	ULONG __stdcall AddRef(void);
	ULONG __stdcall Release(void);
	HRESULT __stdcall SumOfTwoIntegers(int, int, int*);
	HRESULT __stdcall SubtractionOfTwoIntegers(int, int, int*);


	HRESULT __stdcall MultiplicationOfTwoNumbers(int, int, int*);
	HRESULT __stdcall DivisionOfTwoNumbers(int, int, int*);

	HRESULT __stdcall InitializeInnerComponent(void);

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
	MessageBox(NULL, TEXT("CSumSubtract Constructor"), TEXT("Outer DLL"), MB_OK);
	
	m_pIMultiplication = NULL;
	m_pIDivision = NULL;
	m_cRef = 1;
	InterlockedIncrement(&glNumberOfActiveComponents);
}

CSumSubtract ::~CSumSubtract(void)
{
	MessageBox(NULL, TEXT("CSumSubtract Desructor"), TEXT("Outer DLL"), MB_OK);
	if (m_pIMultiplication)
	{
		m_pIMultiplication->Release();
		m_pIMultiplication = NULL;
	}
	if (m_pIDivision)
	{
		m_pIDivision->Release();
		m_pIDivision = NULL;
	}
	InterlockedDecrement(&glNumberOfActiveComponents);
}


HRESULT CSumSubtract::QueryInterface(REFIID riid, void **ppv)
{

	MessageBox(NULL, TEXT("QI CSumSubtract"), TEXT("Outer DLL"), MB_OK);
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
	else if (riid == IID_IMultiplication)
	{
		*ppv = static_cast<IMultiplication*>(this);
	}
	else if (riid == IID_IDivision)
	{
		*ppv = static_cast<IDivision*>(this);
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
	MessageBox(NULL, TEXT("AddRef CSumSubtract"), TEXT("Outer DLL"), MB_OK);
	InterlockedIncrement(&m_cRef);
	return (m_cRef);
}

ULONG CSumSubtract::Release(void)
{
	MessageBox(NULL, TEXT("Release -> CSumSubtract"), TEXT("Outer DLL"), MB_OK);
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
	MessageBox(NULL, TEXT("SumOfTwoIntegers() "), TEXT("Outer DLL"), MB_OK);
	*pSum = num1 + num2;
	return(S_OK);
}

HRESULT CSumSubtract::SubtractionOfTwoIntegers(int num1, int num2, int* pSub)
{
	MessageBox(NULL, TEXT("SubtractionOfTwoIntegers() "), TEXT("Outer DLL"), MB_OK);
	*pSub = num1 - num2;
	return (S_OK);
}

HRESULT CSumSubtract::MultiplicationOfTwoNumbers(int num1,int num2, int *pIMultiplication)
{
	m_pIMultiplication->MultiplicationOfTwoNumbers(num1,num2, pIMultiplication);
	
	return S_OK;
}


HRESULT CSumSubtract::DivisionOfTwoNumbers(int num1, int num2, int *pIDivision)
{
	m_pIDivision->DivisionOfTwoNumbers(num1, num2, pIDivision);
	return S_OK;
}

HRESULT  CSumSubtract::InitializeInnerComponent(void)
{

	MessageBox(NULL,TEXT("Initialize inner comp"),TEXT("outer dll"),MB_OK);
	HRESULT hr;
	hr = CoCreateInstance(CLSID_MultiplicationDivision, NULL, CLSCTX_INPROC_SERVER, IID_IMultiplication, (void**)&m_pIMultiplication);
	if (FAILED(hr))
	{
		MessageBox(NULL, TEXT("IMultipliation Interface can not be Obtained :"), TEXT("Outer DLL"), MB_OK);
		return E_FAIL;
	}
	MessageBox(NULL, TEXT("CoCreateInstance"), TEXT("outer dll"), MB_OK);
	hr = m_pIMultiplication->QueryInterface(IID_IDivision, (void**)&m_pIDivision);
	if (FAILED(hr))
	{
		MessageBox(NULL, TEXT("IDivision Interface can not be Obtained :"), TEXT("Outer DLL"), MB_OK);
		return E_FAIL;
	}
	MessageBox(NULL, TEXT(" Init inner comp done"), TEXT("Outer DLL"), MB_OK);
	return S_OK;

}

CSumSbtractClassFactory::CSumSbtractClassFactory(void)
{
	MessageBox(NULL, TEXT("Contructor of CSumSubtarctClassFactory"), TEXT("Outer DLL"), MB_OK);
	m_cRef = 1;
}
CSumSbtractClassFactory::~CSumSbtractClassFactory(void)
{
	MessageBox(NULL, TEXT("Distructor of CSumSubtarctClassFactory"), TEXT("Outer DLL"), MB_OK);
}

HRESULT CSumSbtractClassFactory::QueryInterface(REFIID riid, void **ppv)
{



	MessageBox(NULL, TEXT("QI ClassFactory"), TEXT("Outer DLL"), MB_OK);
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
	MessageBox(NULL, TEXT("AddRef ClassFactory"), TEXT("Outer DLL"), MB_OK);
	InterlockedIncrement(&m_cRef);
	return m_cRef;
}
ULONG CSumSbtractClassFactory::Release(void)
{
	MessageBox(NULL, TEXT("Release ClassFactory"), TEXT("Outer DLL"), MB_OK);
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
	MessageBox(NULL, TEXT("CreateInstance ClassFactory"), TEXT("Outer DLL"), MB_OK);
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
	hr = pCSumSubtract->InitializeInnerComponent();
	if (FAILED(hr))
	{
		MessageBox(NULL, TEXT("Failed to Initialize Inner component :"), TEXT("Outer DLL"), MB_OK);
		return E_FAIL;
	}
	hr = pCSumSubtract->QueryInterface(riid, ppv);

	pCSumSubtract->Release();
	return hr;


}

HRESULT CSumSbtractClassFactory::LockServer(BOOL fLock)
{
	MessageBox(NULL, TEXT("LockServer ClassFactory"), TEXT("Outer DLL"), MB_OK);
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

	MessageBox(NULL, TEXT("DllGetClassObject"), TEXT("Outer DLL"), MB_OK);
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
	MessageBox(NULL, TEXT("DllCanUnloadNow"), TEXT("Outer DLL"), MB_OK);
	if ((glNumberOfActiveComponents == 0) && (glNumberOfServerLocks == 0))
	{
		return S_OK;
	}
	return S_FALSE;
}





