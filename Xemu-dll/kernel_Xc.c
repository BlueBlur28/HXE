#include <stdio.h>
#include <stdint.h>
#include "kernel.h"

// 0x014F - #335 XcSHAInit
uint32_t __stdcall stub_XcSHAInit(void* pbSHAContext) { return 0; }

// 0x0150 - #336 XcSHAUpdate
void __stdcall stub_XcSHAUpdate(void* pbSHAContext, void* pbInput, uint32_t dwInputLength) { }

// 0x0151 - #337 XcSHAFinal
void __stdcall stub_XcSHAFinal(void* pbSHAContext, void* pbDigest) { }
