#include <stdio.h>
#include <stdint.h>



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