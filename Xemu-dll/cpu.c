#include <stdio.h>
#include <stdint.h>
#include <windows.h>



uint32_t entry_decode(int type)
{
    uint32_t encoded = *(uint32_t*)(0x00010000 + 0x0128);
    uint32_t key = (type == 0) ? 0x94859D4B : 0xA8FC57AB;
    uint32_t entry = encoded ^ key;

    printf("Entry point: 0x%08X\n", entry);
    return entry;
}


void run_cpu(uint32_t entry)
{
    printf("Jumping to entry point 0x%08X...\n", entry);
    void (*game)(void) = (void (*)(void))entry;
    game();
    printf("Game returned (this probably won't print).\n");
}


LONG CALLBACK ExceptionHandler(EXCEPTION_POINTERS* ep)
{
    if (ep->ExceptionRecord->ExceptionCode == 0xC0000096)  // EXCEPTION_PRIV_INSTRUCTION
    {
        uint8_t* inst = (uint8_t*)ep->ContextRecord->Eip;  // what instruction crashed

        printf("Privileged instruction at 0x%08X: opcode 0x%02X 0x%02X\n",
            ep->ContextRecord->Eip, inst[0], inst[1]);

        if (*inst == 0xFA || *inst == 0xFB)  // cli or sti — just skip
        {
            ep->ContextRecord->Eip += 1;
            return EXCEPTION_CONTINUE_EXECUTION;
        }

        if (inst[0] == 0x0F && inst[1] == 0x32)  // rdmsr — return 0 in EDX:EAX
        {
            ep->ContextRecord->Eax = 0;
            ep->ContextRecord->Edx = 0;
            ep->ContextRecord->Eip += 2;
            return EXCEPTION_CONTINUE_EXECUTION;
        }

        if (*inst == 0xF4)  // hlt — game is idle-waiting for an interrupt
        {
            Sleep(1);
            ep->ContextRecord->Eip += 1;  // just skip hlt, let jmp loop back
            return EXCEPTION_CONTINUE_EXECUTION;
        }
    }

    return EXCEPTION_CONTINUE_SEARCH;  // not ours, let Windows handle it
}


