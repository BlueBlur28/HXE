#include <windows.h>
#include <stdio.h>
#include <stdint.h>

// MainMem is the .exe image base. The .exe occupies 64 MB at 0x10000
// so addresses 0x10000-0x4010000 are valid memory inside the .exe image.
void* MainMem;
void* ShadowTheHedgehogRam; //Just to clear i'm just being funny, this is the Xbox's "Shadow Ram"


//ToDo: Fix Shadow Ram It's a mirror right now but if MainMem gets written shadow ram gets written too


void InitVirtualMem(void) //Inits the Xbox's memory by allocating virtual space
{
    // The .exe image is at 0x10000 with read+execute. Make it writable so
    // we can load XBE bytes directly into it.
    DWORD oldProtect;
    if (!VirtualProtect((LPVOID)0x00010000, 0x04000000, PAGE_EXECUTE_READWRITE, &oldProtect)) {
        printf("VirtualProtect failed: %lu\n", GetLastError());
        return;
    }

    MainMem = (void*)0x00010000;
    printf("MainMemory OK! at %p\n", MainMem);


    //Shadow Ram - disabled in 32-bit mode (0xF0000000 is in kernel space)
    /*
    ShadowTheHedgehogRam = VirtualAlloc(
        (LPVOID)0xF0000000,
        0x04000000,
        MEM_RESERVE | MEM_COMMIT,
        PAGE_EXECUTE_READWRITE
    );

    if (ShadowTheHedgehogRam == NULL) {
        printf("failed: %lu\n", GetLastError());
    }
    else {
        printf("Shadow RAM OK! at %p\n", ShadowTheHedgehogRam);
    }
    */


}

void LoadXBE(const char* XBE)
{
    FILE* f = fopen(XBE, "rb");      // "rb" = read binary
    fseek(f, 0, SEEK_END);                  // jump to end
    long size = ftell(f);                   // get position = file size
    fseek(f, 0, SEEK_SET);                  // jump back to start
    fread(MainMem, 1, size, f);              // read `size` bytes into buffer
    fclose(f);
    printf("Xbe Loaded!\n");
}

uint8_t ReadByte(uint32_t addr)
{
    uint8_t value = *(uint8_t*)addr;
    printf("ReadByte(0x%08X) = 0x%02X\n", addr, value);
    return value;
}