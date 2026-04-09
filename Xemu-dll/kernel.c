#include <stdio.h>
#include <stdint.h>
#include "kernel.h"



// 0x00C0 - NtCreateMutant 
uint32_t __stdcall stdcall_NtCreateMutant(void* MutantHandle, void* ObjectAttributes, uint32_t InitialOwner) //#192
{
	return 0;
}


//0x014F - XcSHAInit
uint32_t __stdcall stdcall_XcSHAInit(void* pbSHAContext)
{
	return 0;
}

// Lookup table indexed by import number. NULL = not stubbed.
void* kernel_table[400] = {
	[192] = stdcall_NtCreateMutant,
	[335] = stdcall_XcSHAInit,
	// add one line per stub as you write them
};