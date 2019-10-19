#include<windows.h>

#include"ContainmentInnerComponentWithRegFile.h"
class CMultiplicationDivision : public IMultiplication, IDivision
{
	private :
		long m_cRef;
	public:

		CMultiplicationDivision(void);
		~CMultiplicationDivision(void);

		HRESULT __stdcall QueryInterface(REFIID, void**);

		ULONG _stdcall AddRef(void);

		ULONG __stdcall Release(void);

		HRESULT __stdcall MultiplicationOfTwoNumbers(int, int, int*);
		HRESULT __stdcall DivisionOfTwoNumbers(int, int, int*);
 	
};


class CMultiplicationDivisionClassFactory :public IClassFactory
{
	private:
		long m_cRef;
	
	public :
	
		CMultiplicationDivisionClassFactory(void);
		~CMultiplicationDivisionClassFactory(void);

		HRESULT __stdcall QueryInterface(REFIID, void**);

		ULONG _stdcall AddRef(void);

		ULONG __stdcall Release(void);

		HRESULT __stdcall CreateInstance(IUnknown*, REFIID, void**);
		HRESULT __stdcall LockServer(BOOL);

};



long glNumberOfActiveComponents = 0;
long glNumberOfServerLocks = 0;




BOOL WINAPI DllMain(HINSTANCE hDll,DWORD dwReason,LPVOID Reserved)
{

	MessageBox(NULL, TEXT("Inside dll main(); "), TEXT("dll inner comp"),MB_OK);
	switch (dwReason)
	{
	case DLL_PROCESS_ATTACH:
		MessageBox(NULL, TEXT("DLL proc att"), TEXT("Inner DLL"), MB_OK);
		break;
	case DLL_THREAD_ATTACH:
		MessageBox(NULL, TEXT("DLL Thread att"), TEXT("Inner DLL"), MB_OK);
		break;
	case DLL_THREAD_DETACH:
		MessageBox(NULL, TEXT("DLL thread detach"), TEXT("Inner DLL"), MB_OK);
		break;
	case DLL_PROCESS_DETACH:
		MessageBox(NULL, TEXT("DLL proc detach"), TEXT("Inner DLL"), MB_OK);
		break;

	}
	return TRUE;
}

CMultiplicationDivision::CMultiplicationDivision(void)
{

	m_cRef = 1;
	InterlockedIncrement(&glNumberOfActiveComponents);
}

CMultiplicationDivision::~CMultiplicationDivision(void)
{
	InterlockedDecrement(&glNumberOfActiveComponents);	
}

HRESULT CMultiplicationDivision::QueryInterface(REFIID riid, void **ppv)
{
	MessageBox(NULL, TEXT("Co class QI"), TEXT("Inner DLL"), MB_OK);
	if (riid == IID_IUnknown)
	{
		*ppv = static_cast<IMultiplication*>(this);
	}
	else if (riid == IID_IMultiplication)
	{
		*ppv = static_cast <IMultiplication*>(this);
	}
	else if (riid == IID_IDivision)
	{
		*ppv = static_cast <IDivision*>(this);

	}
	else
	{
		*ppv = NULL;
		return E_NOINTERFACE;
	}

	reinterpret_cast<IUnknown*>(*ppv)->AddRef();
	return S_OK;
}


ULONG CMultiplicationDivision :: AddRef()
{
	MessageBox(NULL, TEXT("co class AddRef"), TEXT("Inner DLL"), MB_OK);
	InterlockedIncrement(&m_cRef);
	return m_cRef;
}

ULONG CMultiplicationDivision::Release()
{
	MessageBox(NULL, TEXT("co class Release"), TEXT("Inner DLL"), MB_OK);
	InterlockedDecrement(&m_cRef);
	if (m_cRef == 0)
	{
		delete(this);
		return 0;
	}
	return m_cRef;
}


HRESULT CMultiplicationDivision::MultiplicationOfTwoNumbers(int num1, int num2, int *pMultiplication)
{
	MessageBox(NULL, TEXT("Mul of thw num"), TEXT("Inner DLL"), MB_OK);
	*pMultiplication = num1 * num2;

	return S_OK;
}

HRESULT CMultiplicationDivision::DivisionOfTwoNumbers(int num1, int num2, int *pDivision)
{
	MessageBox(NULL, TEXT("Div of thw num"), TEXT("Inner DLL"), MB_OK);
	*pDivision = num1 / num2;
	return S_OK;

}


CMultiplicationDivisionClassFactory::CMultiplicationDivisionClassFactory()
{
	MessageBox(NULL, TEXT("const class fact"), TEXT("Inner DLL"), MB_OK);
	m_cRef = 1;
	
}
CMultiplicationDivisionClassFactory ::~CMultiplicationDivisionClassFactory()
{
	MessageBox(NULL, TEXT("Class fact distr"), TEXT("Inner DLL"), MB_OK);
	//no code
}

HRESULT CMultiplicationDivisionClassFactory::QueryInterface(REFIID riid, void **ppv)
{
	MessageBox(NULL, TEXT("Q I"), TEXT("Inner DLL"), MB_OK);
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
		return E_NOINTERFACE;
	}

	reinterpret_cast<IUnknown*>(*ppv)->AddRef();

	return S_OK;

}


ULONG CMultiplicationDivisionClassFactory::AddRef()
{
	MessageBox(NULL, TEXT("AddRef"), TEXT("Inner DLL"), MB_OK);
	InterlockedIncrement(&m_cRef);
	return m_cRef;
}

ULONG CMultiplicationDivisionClassFactory::Release()
{
	MessageBox(NULL, TEXT("Release"), TEXT("Inner DLL"), MB_OK);
	InterlockedDecrement(&m_cRef);
	if (m_cRef==0)
	{
		delete(this);
		return 0;
	}
	return m_cRef;
}


HRESULT CMultiplicationDivisionClassFactory::CreateInstance(IUnknown *pUnkOuter, REFIID riid, void**ppv)
{
	MessageBox(NULL, TEXT("CreateInstance"), TEXT("Inner DLL"), MB_OK);
	CMultiplicationDivision * pCMultiplicationDivision = NULL;
	HRESULT hr;
	if (pUnkOuter !=NULL)
	{
		return CLASS_E_NOAGGREGATION;
	}

	pCMultiplicationDivision = new CMultiplicationDivision;

	if (pCMultiplicationDivision == NULL)
	{
		return E_OUTOFMEMORY;
	}

	hr = pCMultiplicationDivision->QueryInterface(riid,ppv);
	pCMultiplicationDivision->Release();
	return hr;
	
}

HRESULT CMultiplicationDivisionClassFactory::LockServer(BOOL fLock)
{
	MessageBox(NULL, TEXT("LockServer"), TEXT("Inner DLL"), MB_OK);
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
	MessageBox(NULL, TEXT("DllGetClassObject"), TEXT("Inner DLL"), MB_OK);
	CMultiplicationDivisionClassFactory *pCMultiplicationDivisionClassFactory = NULL;
	HRESULT hr;

	if (rclsid != CLSID_MultiplicationDivision)
	{
		return CLASS_E_CLASSNOTAVAILABLE;
	}

	pCMultiplicationDivisionClassFactory = new CMultiplicationDivisionClassFactory;
	if (pCMultiplicationDivisionClassFactory == NULL)
	{
		return E_OUTOFMEMORY;
	}

	hr = pCMultiplicationDivisionClassFactory->QueryInterface(riid, ppv);
	
	pCMultiplicationDivisionClassFactory->Release();
	return hr;
}


HRESULT __stdcall DllCanUnloadNow(void)
{

	MessageBox(NULL, TEXT("DllCanUnloadNow"), TEXT("Inner DLL"), MB_OK);
	if ((glNumberOfActiveComponents == 0) && (glNumberOfServerLocks == 0))
	{
		return S_OK;

	}
	else
	{
		return S_FALSE;
	}
}





























