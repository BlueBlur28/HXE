#include <stdio.h>
#include <stdint.h>

extern void* kernel_table[400];

uint32_t __stdcall stdcall_NtCreateMutant(void* MutantHandle, void* ObjectAttributes, uint32_t InitialOwner); //#192

uint32_t __stdcall stdcall_XcSHAInit(void* pbSHAContext);
