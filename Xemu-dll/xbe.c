#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "kernel.h"

uint32_t ThunkTableAddr;

void LoadSectionHeaders(void) {
    uint32_t numSections = *(uint32_t*)(0x00010000 + 0x011C);
    uint32_t headersAddr = *(uint32_t*)(0x00010000 + 0x0120);

    printf("Number of sections: %u\n", numSections);

    for (uint32_t i = 0; i < numSections; i++) {
        uint32_t header = headersAddr + (i * 0x38);

        // read the 3 fields we care about
        uint32_t virtAddr = *(uint32_t*)(header + 0x04);
        uint32_t rawAddr = *(uint32_t*)(header + 0x0C) + 0x00010000;
        uint32_t rawSize = *(uint32_t*)(header + 0x10);

        printf("Section %u: copying %u bytes from 0x%08X to 0x%08X\n",
            i, rawSize, rawAddr, virtAddr);

        // copy the bytes from where they are in the loaded XBE
        // to where the section wants to live
        memcpy((void*)virtAddr, (void*)rawAddr , rawSize);
    }
}


void thunktable_decode(int type)
{
    uint32_t encoded = *(uint32_t*)(0x00010000 + 0x0158);
    uint32_t key = (type == 0) ? 0xEFB1F152 : 0x5B6D40B6;
    uint32_t entry = encoded ^ key;

    ThunkTableAddr = encoded ^ key;

    printf("Kernel Thunk Table At: 0x%08X\n", entry);
}


void LoadThunkTable(void)
{
    uint32_t* thunk = (uint32_t*)ThunkTableAddr;
    while (*thunk != 0) {
        uint32_t importNum = *thunk & 0x1FF;

        if (kernel_table[importNum] != NULL) {
            *thunk = (uint32_t)kernel_table[importNum];
            printf("Patched #%u\n", importNum);
        } else {
            printf("UNSTUBBED #%u (left as placeholder)\n", importNum);
        }

        thunk++;
    }
}