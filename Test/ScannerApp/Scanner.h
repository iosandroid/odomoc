// Scanner.h : Declaration of the CScanner

#pragma once
#include <map>
#include <vector>

#include "resource.h"       // main symbols



#include "ScannerApp_i.h"



#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Single-threaded COM objects are not properly supported on Windows CE platform, such as the Windows Mobile platforms that do not include full DCOM support. Define _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA to force ATL to support creating single-thread COM object's and allow use of it's single-threaded COM object implementations. The threading model in your rgs file was set to 'Free' as that is the only threading model supported in non DCOM Windows CE platforms."
#endif

using namespace ATL;


// CScanner

class ATL_NO_VTABLE CScanner :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CScanner, &CLSID_Scanner>,
	public IDispatchImpl<IScanner, &IID_IScanner, &LIBID_ScannerAppLib, /*wMajor =*/ 1, /*wMinor =*/ 0>
{
public:
	CScanner()
	{
		load_signatures();
	}

DECLARE_REGISTRY_RESOURCEID(IDR_SCANNER)


BEGIN_COM_MAP(CScanner)
	COM_INTERFACE_ENTRY(IScanner)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()



	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		return S_OK;
	}

	void FinalRelease()
	{
	}

public:
	STDMETHOD(Scan)();

private:
	char m_Path[1024];

	using Buffer     = std::vector<unsigned char>;
	using Signatures = std::map<Buffer, CLSID>;

	Signatures m_Signatures;

public:
	STDMETHOD(ScanPath)(BSTR path);

private:
	void load_signatures();
};

OBJECT_ENTRY_AUTO(__uuidof(Scanner), CScanner)
