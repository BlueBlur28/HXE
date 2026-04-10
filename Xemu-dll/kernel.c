#include <stdio.h>
#include <stdint.h>
#include "kernel.h"

// Lookup table indexed by import number. NULL = not stubbed.
void* kernel_table[512] = {
	// Av
	[1]   = stub_AvGetSavedDataAddress,
	[2]   = stub_AvSendTVEncoderOption,
	[3]   = stub_AvSetDisplayMode,
	[4]   = stub_AvSetSavedDataAddress,
	// Dbg
	[8]   = stub_DbgPrint,
	// Ex
	[24]  = stub_ExQueryNonVolatileSetting,
	// Hal
	[44]  = stub_HalGetInterruptVector,
	[46]  = stub_HalReadWritePCISpace,
	[49]  = stub_HalReturnToFirmware,
	// Interlocked
	[54]  = stub_InterlockedExchange,
	// Io
	[67]  = stub_IoCreateSymbolicLink,
	[69]  = stub_IoDeleteSymbolicLink,
	// Ke
	[98]  = stub_KeConnectInterrupt,
	[99]  = stub_KeDelayExecutionThread,
	[103] = stub_KeGetCurrentIrql,
	[104] = stub_KeGetCurrentThread,
	[107] = stub_KeInitializeDpc,
	[109] = stub_KeInitializeInterrupt,
	[119] = stub_KeInsertQueueDpc,
	[128] = stub_KeQuerySystemTime,
	[143] = stub_KeSetBasePriorityThread,
	// Mm
	[164] = stub_LaunchDataPage,
	[165] = stub_MmAllocateContiguousMemory,
	[166] = stub_MmAllocateContiguousMemoryEx,
	[171] = stub_MmFreeContiguousMemory,
	[178] = stub_MmPersistContiguousMemory,
	[180] = stub_MmQueryAllocationSize,
	// Nt
	[184] = stub_NtAllocateVirtualMemory,
	[186] = stub_NtClearEvent,
	[187] = stub_NtClose,
	[189] = stub_NtCreateEvent,
	[190] = stub_NtCreateFile,
	[192] = stub_NtCreateMutant,
	[193] = stub_NtCreateSemaphore,
	[199] = stub_NtFreeVirtualMemory,
	[201] = stub_NtOpenDirectoryObject,
	[202] = stub_NtOpenFile,
	[203] = stub_NtOpenSymbolicLinkObject,
	[205] = stub_NtPulseEvent,
	[208] = stub_NtQueryDirectoryObject,
	[210] = stub_NtQueryFullAttributesFile,
	[211] = stub_NtQueryInformationFile,
	[217] = stub_NtQueryVirtualMemory,
	[218] = stub_NtQueryVolumeInformationFile,
	[219] = stub_NtReadFile,
	[221] = stub_NtReleaseMutant,
	[222] = stub_NtReleaseSemaphore,
	[224] = stub_NtResumeThread,
	[225] = stub_NtSetEvent,
	[226] = stub_NtSetInformationFile,
	[231] = stub_NtSuspendThread,
	[233] = stub_NtWaitForSingleObject,
	[234] = stub_NtWaitForSingleObjectEx,
	[235] = stub_NtWaitForMultipleObjectsEx,
	[236] = stub_NtWriteFile,
	[238] = stub_NtYieldExecution,
	// Ob
	[246] = stub_ObReferenceObjectByHandle,
	[250] = stub_ObfDereferenceObject,
	// Ps
	[255] = stub_PsCreateSystemThreadEx,
	[258] = stub_PsTerminateSystemThread,
	[259] = stub_PsThreadObjectType,
	// Rtl
	[277] = stub_RtlEnterCriticalSection,
	[289] = stub_RtlInitAnsiString,
	[291] = stub_RtlInitializeCriticalSection,
	[294] = stub_RtlLeaveCriticalSection,
	[301] = stub_RtlNtStatusToDosError,
	[302] = stub_RtlRaiseException,
	[306] = stub_RtlTryEnterCriticalSection,
	// Xc
	[335] = stub_XcSHAInit,
	[336] = stub_XcSHAUpdate,
	[337] = stub_XcSHAFinal,
	// Xe
	[326] = stub_XeImageFileName,
};
