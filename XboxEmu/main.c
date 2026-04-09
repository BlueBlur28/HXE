#include <windows.h>

extern unsigned char xbox_memory_blob[];

typedef void (*EmulateFn)(void);

DWORD CALLBACK rawMain(void)
{
    // Keep the placeholder alive so the linker doesn't strip it
    (void)xbox_memory_blob;

    HMODULE dll = LoadLibraryA("Xemu-dll.dll");
    if (!dll) {
        OutputDebugStringA("HXE: Failed to load Xemu-dll.dll\n");
        return 1;
    }

    EmulateFn Emulate = (EmulateFn)GetProcAddress(dll, "Emulate");
    if (!Emulate) {
        OutputDebugStringA("HXE: Failed to find Emulate in DLL\n");
        return 1;
    }

    Emulate();
    return 0;
}
