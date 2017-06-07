// dllmain.h : Declaration of module class.

class CScannerAppModule : public ATL::CAtlDllModuleT< CScannerAppModule >
{
public :
	DECLARE_LIBID(LIBID_ScannerAppLib)
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_SCANNERAPP, "{0B3C0600-449C-4229-B789-6B3389F3B5DA}")
};

extern class CScannerAppModule _AtlModule;
