#include "Handle.h"


Attach::Handle::Handle(DWORD handler)
	: handler(handler), handleProcess(NULL)
{
}


Attach::Handle::~Handle() {}

void Attach::Handle::HandleProcess() {
	this->handleProcess = OpenProcess(PROCESS_ALL_ACCESS, 0, this->handler);
}

HANDLE Attach::Handle::getHandle() {
	return this->handleProcess;
}


int 
Attach::Handle::ReadValueFromMemoryAddress(uintptr_t address, int *buffer) {
	if (ReadProcessMemory(this->getHandle(), (BYTE*)address, buffer, sizeof(*buffer), nullptr)) {
		return *buffer;
	}
	return -1;
}

int
Attach::Handle::WriteValueFromMemoryAddress(uintptr_t address, int* buffer) {
	if (WriteProcessMemory(this->getHandle(), (BYTE*)address, buffer, sizeof(*buffer), nullptr)) {
		return 1;
	}
	return -1;
}

int
Attach::Handle::CloseHandleProcess() {
	if (CloseHandle(this->getHandle())) return 0;
	return -1;
}