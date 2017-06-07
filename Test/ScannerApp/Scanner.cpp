// Scanner.cpp : Implementation of CScanner

#include "stdafx.h"
#include "Scanner.h"

#include "Intsafe.h"
#include "atlfile.h"

#include <map>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <algorithm>

// CScanner



STDMETHODIMP CScanner::Scan()
{
	// TODO: Add your implementation code here

	std::cout << "Scanner : start scan.\n";
	return S_OK;
}


STDMETHODIMP CScanner::ScanPath(BSTR path)
{
	CAtlFileMappingBase fileMap;

	// Create a file.
	CAtlFile file;
	file.Create(path, GENERIC_READ, FILE_SHARE_READ, OPEN_ALWAYS);

	ULONGLONG uLongSize;
	file.GetSize(uLongSize);

	size_t size;
	ULongLongToSizeT(uLongSize, &size);

	if (fileMap.MapFile((HANDLE)file, size, 0, PAGE_READONLY, FILE_MAP_READ) != S_OK)
	{
		return S_FALSE;
	}

	char* buffer = static_cast<char*>(fileMap.GetData());
	std::string search_string = std::string(buffer, buffer + size);
	
	for (auto sign : m_Signatures)
	{
		auto it = std::search(std::begin(search_string), std::end(search_string), std::begin(sign.first), std::end(sign.first));

		if (it != std::end(search_string))
		{
			int a = 1;
		}
	}

	return S_OK;
}

void CScanner::load_signatures()
{
	std::wifstream fs(L"signatures.dat");
	std::wstring line;

	while (getline(fs, line) && (line != L""))
	{
		size_t dotpos = line.find_first_of('.');

		std::wstring hexstr = line.substr(0, dotpos);
		std::wstring uidstr = line.substr(dotpos + 1, std::wstring::npos);
		
		GUID   guid;
		Buffer buffer;

		CLSIDFromString(uidstr.c_str(), &guid);

		size_t count = hexstr.size() >> 1;
		buffer.resize(count);
		for (size_t i = 0; i < count; i++)
		{			
			swscanf_s(&hexstr[2*i], L"%2hhx", &buffer[i]);
		}

		m_Signatures.insert(std::make_pair(buffer, guid));
	}

}
