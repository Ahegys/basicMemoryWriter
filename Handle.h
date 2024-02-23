#pragma once
#include <windows.h>


namespace Attach
{
	class Handle
	{
	private:
		DWORD handler;
		HANDLE handleProcess;
	public:
		Handle(DWORD);
		~Handle();
		void HandleProcess();
		void setHandle(DWORD newHandle);
		HANDLE getHandle();
		int ReadValueFromMemoryAddress(uintptr_t, int*);
		int WriteValueFromMemoryAddress(uintptr_t, int*);
		int CloseHandleProcess();
	};
}


