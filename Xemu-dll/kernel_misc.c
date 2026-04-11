#include <windows.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "kernel.h"

// === Av (Audio/Video) ===

// 0x0001 - #1 AvGetSavedDataAddress
void* __stdcall stub_AvGetSavedDataAddress(void) { return 0; }

// 0x0002 - #2 AvSendTVEncoderOption
void __stdcall stub_AvSendTVEncoderOption(void* RegisterBase, uint32_t Option, uint32_t Param, uint32_t* Result) { }

// 0x0003 - #3 AvSetDisplayMode
uint32_t __stdcall stub_AvSetDisplayMode(void* RegisterBase, uint32_t Step, uint32_t Mode, uint32_t Format, uint32_t Pitch, void* FrameBuffer)
{
    printf("AvSetDisplayMode(Mode=%u)\n", Mode);
    return 0;
}

// 0x0004 - #4 AvSetSavedDataAddress
void __stdcall stub_AvSetSavedDataAddress(void* Address) { }

// === Dbg ===

// 0x0008 - #8 DbgPrint (NOTE: __cdecl, not __stdcall! Variadic function.)
uint32_t __cdecl stub_DbgPrint(char* Format, ...)
{
	printf("XBOX: %s\n", Format);
	return 0;
}

// === Ex ===

// 0x0018 - #24 ExQueryNonVolatileSetting
uint32_t __stdcall stub_ExQueryNonVolatileSetting(uint32_t ValueIndex, uint32_t* Type, void* Value, uint32_t ValueLength, void* ResultLength)
{
    printf("ExQueryNonVolatileSetting(index=0x%X)\n", ValueIndex);
    // Zero the output buffer so the game doesn't read uninitialized garbage
    if (Value) memset(Value, 0, ValueLength);
    if (Type) *Type = 0;
    if (ResultLength) *(uint32_t*)ResultLength = ValueLength;
    return 0;  // STATUS_SUCCESS
}

// === Hal ===

// 0x002C - #44 HalGetInterruptVector
uint32_t __stdcall stub_HalGetInterruptVector(uint32_t BusInterruptLevel, void* Irql)
{
    printf("HalGetInterruptVector(%u)\n", BusInterruptLevel);
    return 0;
}

// 0x002E - #46 HalReadWritePCISpace
void __stdcall stub_HalReadWritePCISpace(uint32_t BusNumber, uint32_t SlotNumber, uint32_t RegisterNumber, void* Buffer, uint32_t Length, uint32_t WritePCISpace)
{
    printf("HalReadWritePCISpace(bus=%u slot=%u reg=%u write=%u)\n", BusNumber, SlotNumber, RegisterNumber, WritePCISpace);
}

// 0x0031 - #49 HalReturnToFirmware
void __stdcall stub_HalReturnToFirmware(uint32_t Routine) { }

// === Interlocked (FASTCALL!) ===

// 0x0036 - #54 InterlockedExchange
uint32_t __fastcall stub_InterlockedExchange(void* Destination, uint32_t Value)
{
    uint32_t* dest = (uint32_t*)Destination;
    uint32_t old = *dest;
    *dest = Value;
    return old;
}

// === Io ===

// 0x0043 - #67 IoCreateSymbolicLink
uint32_t __stdcall stub_IoCreateSymbolicLink(void* SymbolicLinkName, void* DeviceName)
{
    printf("IoCreateSymbolicLink\n");
    return 0;
}

// 0x0045 - #69 IoDeleteSymbolicLink
uint32_t __stdcall stub_IoDeleteSymbolicLink(void* SymbolicLinkName)
{
    printf("IoDeleteSymbolicLink\n");
    return 0;
}

// === Ke ===

// 0x0062 - #98 KeConnectInterrupt
uint32_t __stdcall stub_KeConnectInterrupt(void* InterruptObject)
{
    printf("KeConnectInterrupt\n");
    return 0;
}

// 0x0063 - #99 KeDelayExecutionThread
uint32_t __stdcall stub_KeDelayExecutionThread(uint32_t WaitMode, uint32_t Alertable, void* Interval)
{
    printf("KeDelayExecutionThread\n");
    return 0;
}

// 0x0067 - #103 KeGetCurrentIrql
uint32_t __stdcall stub_KeGetCurrentIrql(void)
{
    printf("KeGetCurrentIrql\n");
    return 0;
}

// 0x0068 - #104 KeGetCurrentThread
void* __stdcall stub_KeGetCurrentThread(void)
{
    printf("KeGetCurrentThread\n");
    return 0;
}

// 0x006B - #107 KeInitializeDpc
void __stdcall stub_KeInitializeDpc(void* Dpc, void* DeferredRoutine, void* DeferredContext)
{
    printf("KeInitializeDpc\n");
}

// 0x006D - #109 KeInitializeInterrupt
void __stdcall stub_KeInitializeInterrupt(void* Interrupt, void* ServiceRoutine, void* ServiceContext, uint32_t Vector, uint32_t Irql, uint32_t InterruptMode, uint32_t ShareVector)
{
    printf("KeInitializeInterrupt\n");
}

// 0x0077 - #119 KeInsertQueueDpc
uint32_t __stdcall stub_KeInsertQueueDpc(void* Dpc, void* SystemArgument1, void* SystemArgument2) { return 0; }

// 0x0080 - #128 KeQuerySystemTime
void __stdcall stub_KeQuerySystemTime(void* CurrentTime)
{
    printf("KeQuerySystemTime\n");
}

// 0x008F - #143 KeSetBasePriorityThread
uint32_t __stdcall stub_KeSetBasePriorityThread(void* Thread, uint32_t Priority)
{
    printf("KeSetBasePriorityThread\n");
    return 0;
}

// === Mm ===

// 0x00A4 - #164 LaunchDataPage (DATA EXPORT - global variable)
uint8_t stub_LaunchDataPage[0x1000] = { 0 };

// 0x00A5 - #165 MmAllocateContiguousMemory
void* __stdcall stub_MmAllocateContiguousMemory(uint32_t NumberOfBytes)
{
    void* ptr = VirtualAlloc(NULL, NumberOfBytes, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
    printf("MmAllocateContiguousMemory(%u) = %p\n", NumberOfBytes, ptr);
    return ptr;
}

// 0x00A6 - #166 MmAllocateContiguousMemoryEx
void* __stdcall stub_MmAllocateContiguousMemoryEx(uint32_t NumberOfBytes, uint32_t LowestAddr, uint32_t HighestAddr, uint32_t Alignment, uint32_t ProtectionType)
{
    void* ptr = VirtualAlloc(NULL, NumberOfBytes, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
    printf("MmAllocateContiguousMemoryEx(%u) = %p\n", NumberOfBytes, ptr);
    return ptr;
}

// 0x00AB - #171 MmFreeContiguousMemory
void __stdcall stub_MmFreeContiguousMemory(void* BaseAddress) { }

// 0x00B2 - #178 MmPersistContiguousMemory
void __stdcall stub_MmPersistContiguousMemory(void* BaseAddress, uint32_t NumberOfBytes, uint32_t Persist) { }

// 0x00B4 - #180 MmQueryAllocationSize
uint32_t __stdcall stub_MmQueryAllocationSize(void* BaseAddress) { return 0; }

// === Ob ===

// 0x00F6 - #246 ObReferenceObjectByHandle
uint32_t __stdcall stub_ObReferenceObjectByHandle(uint32_t Handle, void* ObjectType, void** ReturnedObject)
{
    printf("ObReferenceObjectByHandle(%u)\n", Handle);
    return 0;
}

// 0x00FA - #250 ObfDereferenceObject (FASTCALL!)
void __fastcall stub_ObfDereferenceObject(void* Object) { }

// === Ps ===

// 0x00FF - #255 PsCreateSystemThreadEx
uint32_t __stdcall stub_PsCreateSystemThreadEx(void* ThreadHandle, uint32_t ThreadExtensionSize, uint32_t KernelStackSize, uint32_t TlsDataSize, void* ThreadId, void* StartRoutine, void* StartContext, uint32_t CreateSuspended, uint32_t DebugStack, void* SystemRoutine)
{
    static uint32_t fake_handle = 0x4000;
    printf("PsCreateSystemThreadEx -> calling StartRoutine at %p\n", StartRoutine);
    if (ThreadHandle) *(uint32_t*)ThreadHandle = fake_handle++;

    // Call the thread function synchronously (we're single-threaded)
    if (StartRoutine) {
        void (__stdcall *start)(void*) = (void (__stdcall *)(void*))StartRoutine;
        start(StartContext);
    }

    return 0;
}

// 0x0102 - #258 PsTerminateSystemThread
void __stdcall stub_PsTerminateSystemThread(uint32_t ExitStatus) { }

// 0x0103 - #259 PsThreadObjectType (DATA EXPORT)
uint8_t stub_PsThreadObjectType[64] = { 0 };

// === Rtl ===

// 0x0115 - #277 RtlEnterCriticalSection
void __stdcall stub_RtlEnterCriticalSection(void* CriticalSection)
{
    EnterCriticalSection((CRITICAL_SECTION*)CriticalSection);
}

// 0x0121 - #289 RtlInitAnsiString
// Xbox ANSI_STRING struct: { uint16_t Length; uint16_t MaxLength; char* Buffer; }
void __stdcall stub_RtlInitAnsiString(void* DestinationString, void* SourceString)
{
    uint16_t* dest = (uint16_t*)DestinationString;
    if (SourceString) {
        uint16_t len = (uint16_t)strlen((char*)SourceString);
        dest[0] = len;            // Length
        dest[1] = len + 1;        // MaxLength (includes null terminator)
        *(char**)(dest + 2) = (char*)SourceString;  // Buffer pointer
    } else {
        dest[0] = 0;
        dest[1] = 0;
        *(char**)(dest + 2) = 0;
    }
}

// 0x0123 - #291 RtlInitializeCriticalSection
void __stdcall stub_RtlInitializeCriticalSection(void* CriticalSection)
{
    InitializeCriticalSection((CRITICAL_SECTION*)CriticalSection);
}

// 0x0126 - #294 RtlLeaveCriticalSection
void __stdcall stub_RtlLeaveCriticalSection(void* CriticalSection)
{
    LeaveCriticalSection((CRITICAL_SECTION*)CriticalSection);
}

// 0x012D - #301 RtlNtStatusToDosError
uint32_t __stdcall stub_RtlNtStatusToDosError(uint32_t Status) { return 0; }

// 0x012E - #302 RtlRaiseException
void __stdcall stub_RtlRaiseException(void* ExceptionRecord) { }

// 0x0132 - #306 RtlTryEnterCriticalSection
uint32_t __stdcall stub_RtlTryEnterCriticalSection(void* CriticalSection) { return 1; }

// === Xe ===

// 0x0146 - #326 XeImageFileName (DATA EXPORT)
uint8_t stub_XeImageFileName[64] = { 0 };
