#include <windows.h>
#include <stdio.h>
#include <stdint.h>

void* MainMem;
void* ShadowTheHedgehogRam; //Just to clear i'm just being funny, this is the Xbox's "Shadow Ram"


//ToDo: Fix Shadow Ram It's a mirror right now but if MainMem gets written shadow ram gets written too


void InitVirtualMem(void) //Inits the Xbox's memory by allocating virtual space
{
    MainMem = VirtualAlloc( // Allocating Main Memory
        (LPVOID)0x00010000,  // Skiping first 64kb becuase windows won't let us have it
        0x03FF0000,          
        MEM_RESERVE | MEM_COMMIT,
        PAGE_EXECUTE_READWRITE
    );

    if (MainMem == NULL) {
        printf("failed: %lu\n", GetLastError());
    }
    else {
        printf("MainMemory OK! at %p\n", MainMem);
    }


    //Shadow Ram


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