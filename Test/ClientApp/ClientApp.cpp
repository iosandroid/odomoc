// ClientApp.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#import "..\Debug\ScannerApp.dll" rename_namespace("COM")

int main()
{
	::CoInitialize(NULL);

	COM::IScannerPtr scanner(__uuidof(COM::Scanner));
	scanner->ScanPath(L"d:\\en.iso");
	
	::CoUninitialize();
    return 0;
}

