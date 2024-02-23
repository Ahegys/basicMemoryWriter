#pragma once
#include <windows.h>
#include <TlHelp32.h>
#include <iostream>
#include <tchar.h>
#include <stdio.h>
#include <stdlib.h>
#include <vector>

namespace Memory {
	class Process
	{
	private:
		const wchar_t* name;

	public:
		Process(const wchar_t*);
		~Process();
		DWORD GetProcessID();
		const wchar_t* GetName();
		void SetName(const wchar_t*);
		uintptr_t GetModuleBaseAddress();
		uintptr_t FindDMAAddy(HANDLE, uintptr_t, std::vector<unsigned int>);
	};

}

