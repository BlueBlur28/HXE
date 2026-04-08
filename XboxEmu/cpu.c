#include <stdio.h>
#include <stdint.h>



void cpu_init(int type)
{
    uint32_t encoded = *(uint32_t*)(0x00010000 + 0x0128);
    uint32_t key = (type == 0) ? 0x94859D4B : 0xA8FC57AB;
    uint32_t entry = encoded ^ key;

    printf("Entry point: 0x%08X\n", entry);
}


void run_cpu(uint32_t entry)
{
    printf("Jumping to entry point 0x%08X...\n", entry);
    void (*game)(void) = (void (*)(void))entry;
    game();
    printf("Game returned (this probably won't print).\n");
}


