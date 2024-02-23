#include <iostream>
#include "Memory.h"
#include "Handle.h"


int main()
{
    Memory::Process mem = Memory::Process(L"re4.exe");
    Attach::Handle currentProcess = Attach::Handle(mem.GetProcessID());
    currentProcess.HandleProcess();
    uintptr_t ammoValue = 0x5C893294;
    int value = 0;
    int lastReadValue = -1; // Inicialize com um valor que nunca será lido
    while (true) {
        int readedValue = currentProcess.ReadValueFromMemoryAddress(ammoValue, &value);
        if (readedValue != lastReadValue)
        {
            std::cout << "Leon ammo value: " << readedValue << std::endl;
            lastReadValue = readedValue;
        }
        if (readedValue < 10) {
            int newAmmo = 10;
            currentProcess.WriteValueFromMemoryAddress(ammoValue, &newAmmo);
        }
    }
    currentProcess.CloseHandleProcess();
}
