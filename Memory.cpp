#include "Memory.h"

Memory::Process::Process(const wchar_t* name)
{
	this->name = name;
}

Memory::Process::~Process(){ }


DWORD 
Memory::Process::GetProcessID() {
	DWORD procID = 0;
	HANDLE snapProcess = (CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0));
	if (snapProcess != INVALID_HANDLE_VALUE) {
		PROCESSENTRY32 procEntry;
		procEntry.dwSize = sizeof(procEntry);

		if (Process32First(snapProcess, &procEntry)) {

			do {
				if (!_wcsicmp(procEntry.szExeFile, this->name)) {
					procID = procEntry.th32ProcessID;
					break;
				}
			} while (Process32Next(snapProcess, &procEntry));
		}
	}
	CloseHandle(snapProcess);
	return procID;
}

const wchar_t* 
Memory::Process::GetName(){
	return this->name;
}

void 
Memory::Process::SetName(const wchar_t* newName) {
	this->name = newName;
}

uintptr_t 
Memory::Process::GetModuleBaseAddress() {
	uintptr_t modBaseAddr = 0;
	HANDLE snapProcess = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, this->GetProcessID());

	if (snapProcess != INVALID_HANDLE_VALUE){
		MODULEENTRY32 modEntry;
		modEntry.dwSize = sizeof(modEntry);
		if (Module32First(snapProcess, &modEntry)) {
			do {
				if (!_wcsicmp(modEntry.szModule, this->GetName())) {
					modBaseAddr = (uintptr_t)modEntry.modBaseAddr;
					break;
				}
			} while (Module32Next(snapProcess, &modEntry));
		}
	}
	CloseHandle(snapProcess);
	return modBaseAddr;
}


uintptr_t
FindDMAAddy(HANDLE handleProcess, uintptr_t ptr, std::vector<unsigned int> offsets) {
	uintptr_t addr = ptr;
	for (unsigned int i = 0; i < offsets.size(); i++) {
		ReadProcessMemory(handleProcess, (BYTE*)addr, &addr, sizeof(addr), 0);
		addr += offsets[i];
	}
	return addr;
}