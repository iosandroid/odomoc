// Scanner.cpp : Implementation of CScanner

#include "stdafx.h"
#include "Scanner.h"

#include "Intsafe.h"
#include "atlfile.h"

#include <map>
#include <vector>
#include <string>
#include <fstream>
#include <psapi.h>
#include <iostream>
#include <algorithm>

// CScanner

STDMETHODIMP CScanner::ScanFile(BSTR filename, GUID* guid)
{
	ATLASSERT(guid);
		
	// Create a file.
	CAtlFile file;
	HRESULT hres = file.Create(filename, GENERIC_READ, FILE_SHARE_READ, OPEN_ALWAYS);
	if (hres != S_OK)
	{
		std::cout << "Error: unable to open file: " << filename << std::endl;
		return S_FALSE;
	}
	
	ULONGLONG size;
	file.GetSize(size);

	SIZE_T processed = 0;
	while (processed < size)
	{
		CAtlFileMappingBase file_map;

		hres = file_map.MapFile((HANDLE)file, m_MapSize > size ? 0 : m_MapSize, processed, PAGE_READONLY, FILE_MAP_READ);
		if (hres != S_OK) break;
	
		SIZE_T mapped = file_map.GetMappingSize();

		hres = ScanMemBlock(static_cast<CHAR*>(file_map.GetData()), mapped, guid);
		if (hres == S_OK) return S_OK;

		processed += mapped;
	}

	file.Close();	
	return S_FALSE;
}

STDMETHODIMP CScanner::ScanMemBlock(CHAR* mem, LONG size, GUID* guid)
{
	ATLASSERT(guid);

	for (auto it : m_SigData)
	{
		const char* pattern = it.first.data();
		char* found = std::search(mem, mem + size, pattern, pattern + it.first.size());

		if (found != (mem + size))
		{
			*guid = it.second;
			return S_OK;
		}
	}

	return S_FALSE;
}

void CScanner::LoadSigData()
{
	std::wifstream fs(L"signatures.dat");
	std::wstring line;

	while (getline(fs, line) && (line != L""))
	{
		size_t dotpos = line.find_first_of('.');

		std::wstring hexstr = line.substr(0, dotpos);
		std::wstring uidstr = line.substr(dotpos + 1, std::wstring::npos);

		GUID   guid;
		HEXARR hexarr;

		CLSIDFromString(uidstr.c_str(), &guid);

		size_t count = hexstr.size() >> 1;
		hexarr.resize(count);

		for (size_t i = 0; i < count; i++)
		{
			swscanf_s(&hexstr[2 * i], L"%2hhx", &hexarr[i]);
		}

		m_SigData.insert(std::make_pair(hexarr, guid));
	}
}


void CScanner::LoadSysInfo()
{
	SYSTEM_INFO sys_info;
	GetSystemInfo(&sys_info);	
	
	m_MapSize = sys_info.dwAllocationGranularity;
}
