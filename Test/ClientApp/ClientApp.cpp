// ClientApp.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <future>
#include <vector>
#include <string>
#include <iostream>
#include <functional>

#import "..\Debug\ScannerApp.dll" rename_namespace("Test")

#define SCOPE_LOCK(LockVar)		\
    std::unique_lock<std::mutex> lock(LockVar);	\

template<typename T> class Queue
{
public:
	inline void push_back(const T& data)
	{
		SCOPE_LOCK(m_Lock);
		m_Data.push_back(data);

	}

	inline bool pop_front(T& data)
	{
		SCOPE_LOCK(m_Lock);
		
		bool success = false;
		if (!m_Data.empty())
		{
			data = m_Data[0];
			m_Data.erase(m_Data.begin());

			success = true;
		}

		return success;
	}

private:
	std::mutex     m_Lock;
	std::vector<T> m_Data;
};

class ClientApp
{
	using Files = Queue<std::wstring>;

public:
	ClientApp()
		: m_ThreadCount(0)
	{
		initThreadCount();

		CoInitialize(NULL);
		m_Scanner = Test::IScannerPtr(__uuidof(Test::Scanner));
	}

	virtual ~ClientApp()
	{
		m_Scanner.Release();
		CoUninitialize();
	}

	void run(const std::wstring& path)
	{
		if (!isDirectory(path))
		{
			scanFile(path);
		}
		else
		{
			scanDirectory(path);
		}
	}

private:
	void scanFile(const std::wstring& path)
	{
		GUID guid;

		std::wcout << L"Scanning: " << path << std::endl;
		if (m_Scanner->ScanFile(path.c_str(), &guid) == S_OK)
		{
			LPOLESTR uidstr;
			StringFromCLSID(guid, &uidstr);

			std::wcout << L"Matching found: " << uidstr << L" : " << path.c_str() << std::endl;
		}
	}

	void scanDirectory(const std::wstring& path)
	{
		Files files;

		enumDirectory(path, files);
		unleashThreads(files);
	}

	void enumDirectory(const std::wstring& path, Files& files)
	{
		WIN32_FIND_DATA ffd;
		HANDLE hFind = INVALID_HANDLE_VALUE;		

		std::wstring wildcard = path + L"\\*";

		hFind = FindFirstFile(wildcard.c_str(), &ffd);
		if (hFind != INVALID_HANDLE_VALUE) do
		{
			if (std::wstring(ffd.cFileName) == L".")
			{
				continue;
			}

			if (std::wstring(ffd.cFileName) == L"..")
			{
				continue;
			}

			if (ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			{
				enumDirectory(path + L"\\" + ffd.cFileName, files);
			}
			else
			{
				files.push_back(path + L"\\" + ffd.cFileName);
			}
		} 
		while (FindNextFile(hFind, &ffd) != 0);
	}

	void unleashThreads(Files& files)
	{
		std::function<void()> lambda = std::bind(&ClientApp::threadFunc, this, std::move(files));

		std::vector<std::future<void>> threads;
		for (size_t i = 0; i < m_ThreadCount; i++)
		{
			threads.push_back(std::async(std::launch::async, lambda));
		}
		for (size_t i = 0; i < m_ThreadCount; i++)
		{
			threads[i].wait();
		}
	}

	bool isDirectory(const std::wstring& path)
	{
		WIN32_FILE_ATTRIBUTE_DATA attr_data;
		GetFileAttributesEx(path.c_str(), GetFileExInfoStandard, &attr_data);

		return attr_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY;
	}

	void initThreadCount()
	{
		SYSTEM_INFO sys_info;
		GetSystemInfo(&sys_info);

		m_ThreadCount = sys_info.dwNumberOfProcessors;
	}

	void threadFunc(Files&& files)
	{
		std::wstring file;
		while (files.pop_front(file))
		{
			scanFile(file);
		}
	}

private:
	Test::IScannerPtr m_Scanner;
	size_t            m_ThreadCount;

};

void print_usage(const char* desc)
{
	std::cout << "\n\nUsage: " << desc << " <option(s)>\n"
		<< "\nOptions:\n"
		<< "\t-h,--help \t\t Show this help message.\n"
		<< "\t-p,--path <path> \t Scan file or directory.\n"
		<< std::endl;
}

int main(int argc, char* argv[])
{
	if (argc == 1)
	{
		print_usage(argv[0]);
		return 1;
	}

	// parse command line arguments
	std::string path;
	for (int i = 1; i < argc; i++)
	{
		std::string arg = argv[i];
		if ((arg == "-h") || (arg == "--help")) 
		{
			print_usage(argv[0]);
			return 0;
		}
		else if ((arg == "-p") || (arg == "--path")) 
		{
			if (i + 1 < argc) 
			{
				path = argv[++i];
				break;
			}
			else 
			{
				std::cerr << "--path option requires one argument." << std::endl;
				return 1;
			}
		}
	}

	// run client 
	ClientApp client;
	client.run( std::wstring(path.begin(), path.end()) );

    return 0;
}

