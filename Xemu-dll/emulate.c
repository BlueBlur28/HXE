//This acts as the "main.c" of the emulator

#include <windows.h>
#include "memory.h"
#include "xbe.h"
#include "cpu.h"
#include "kernel.h"

__declspec(dllexport) void Emulate(void)
{
    InitVirtualMem();

    AddVectoredExceptionHandler(1, ExceptionHandler);

    LoadXBE("SonicWorld.xbe");
    ReadByte(0x00010000);
    ReadByte(0x00010001);
    ReadByte(0x00010002);
    ReadByte(0x00010003);

    LoadSectionHeaders();

    thunktable_decode(1);
    LoadThunkTable();

    uint32_t entry = entry_decode(1);
    run_cpu(entry);

    ExitProcess(0);
}
