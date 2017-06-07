// ClientApp.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#import "d:\dev\Comodo\Test\Debug\ScannerApp.dll" rename_namespace("COM")

int main()
{
	::CoInitialize(NULL);

	COM::IScannerPtr scanner(__uuidof(COM::Scanner));
	scanner->Scan();
	
	::CoUninitialize();

    return 0;
}

