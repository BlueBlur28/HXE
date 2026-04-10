//This acts as the "main.c" of the emulator



#include <windows.h>
#include "memory.h"
#include "xbe.h"
#include "cpu.h"
#include "kernel.h"

__declspec(dllexport) void Emulate(void)
{
    InitVirtualMem();
    // Add LoadXBE / LoadSectionHeaders / etc. calls here as you wire them up.

    LoadXBE("hello.xbe");
    ReadByte(0x00010000);
    ReadByte(0x00010001);
    ReadByte(0x00010002);
    ReadByte(0x00010003);

    LoadSectionHeaders();    // split XBE sections to their virtual addresses
    entry_decode(1);          // decode entry point (prints it)

    thunktable_decode(1);

    LoadThunkTable();         // walk thunks and patch using kernel_table

    AddVectoredExceptionHandler(1, ExceptionHandler); //Tell Windows to use our Exception Handler

    
    
    uint32_t entry = entry_decode(1);
    run_cpu(entry);
    

    // Don't return — the .exe's loader code has been overwritten by XBE bytes
    ExitProcess(0);
}
