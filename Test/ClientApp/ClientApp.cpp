// ClientApp.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#import "..\Debug\ScannerApp.dll" rename_namespace("COM")

int main()
{
	::CoInitialize(NULL);
	COM::IScannerPtr scanner(__uuidof(COM::Scanner));

	GUID guid;
	scanner->ScanFile(L"d:\\en.iso", &guid);
	
	::CoUninitialize();
    return 0;
}

