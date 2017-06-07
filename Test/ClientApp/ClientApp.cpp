// ClientApp.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#import "..\Debug\ScannerApp.dll" rename_namespace("COM")

int main()
{
	::CoInitialize(NULL);

	COM::IScannerPtr scanner(__uuidof(COM::Scanner));
	scanner->ScanPath(L"d:\\dev\\wowp\\wowp_ws0\\game\\bigworld\\build_client_vc120_win32\\client_win32.sdf");
	
	::CoUninitialize();
    return 0;
}

