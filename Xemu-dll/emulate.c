#define _CRT_SECURE_NO_WARNINGS
//This acts as the "main.c" of the emulator

#include <windows.h>
#include "memory.h"
#include "xbe.h"
#include "cpu.h"
#include "kernel.h"
#include "gpu.h"

__declspec(dllexport) void Emulate(HWND hWnd, HDC hDC)
{
    setbuf(stdout, NULL);
    InitVirtualMem();

    AddVectoredExceptionHandler(1, ExceptionHandler);

    gpu_set_window(hWnd, hDC);

    LoadXBE("hello.xbe"); //LoadXBE("C:/Projects/XboxRoms/Shadow/default.xbe");
    ReadByte(0x00010000);
    ReadByte(0x00010001);
    ReadByte(0x00010002);
    ReadByte(0x00010003);

    LoadSectionHeaders();

    thunktable_decode(1);
    LoadThunkTable();

    gpu_dump_pbkit_patterns();
    gpu_patch_pbkit();
   

    uint32_t entry = entry_decode(1);
    run_cpu(entry);

    ExitProcess(0);
}
