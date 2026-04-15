#include <windows.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
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

// Bump allocator for contiguous memory (KSEG0 at 0x80000000)
static uint32_t contig_ptr = 0x80100000;

// 0x00A5 - #165 MmAllocateContiguousMemory
void* __stdcall stub_MmAllocateContiguousMemory(uint32_t NumberOfBytes)
{
    uint32_t size = (NumberOfBytes + 0xFFF) & ~0xFFF;
    void* ptr = (void*)contig_ptr;
    contig_ptr += size;
    printf("MmAllocateContiguousMemory(%u) = %p\n", NumberOfBytes, ptr);
    return ptr;
}

// 0x00A6 - #166 MmAllocateContiguousMemoryEx
void* __stdcall stub_MmAllocateContiguousMemoryEx(uint32_t NumberOfBytes, uint32_t LowestAddr, uint32_t HighestAddr, uint32_t Alignment, uint32_t ProtectionType)
{
    uint32_t size = (NumberOfBytes + 0xFFF) & ~0xFFF;
    void* ptr = (void*)contig_ptr;
    contig_ptr += size;
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

// === Additional stubs for top unstubbed imports ===

void* __stdcall stub_ExAllocatePool(uint32_t NumberOfBytes) { return malloc(NumberOfBytes); }
void __stdcall stub_ExFreePool(void* P) { free(P); }

uint32_t __stdcall stub_IoCreateFile(void* FileHandle, uint32_t a, void* b, void* c, void* d, uint32_t e, uint32_t f, uint32_t g, uint32_t h, uint32_t i)
{
    if (FileHandle) *(uint32_t*)FileHandle = 0;
    return 0xC0000034;
}

uint8_t stub_IoDeviceObjectType[64] = { 0 };

uint32_t __stdcall stub_IoSetIoCompletion(void* a, void* b, void* c, uint32_t d, uint32_t e) { return 0; }
uint32_t __stdcall stub_IoSetShareAccess(uint32_t a, uint32_t b, void* c, void* d) { return 0; }
void __stdcall stub_KeBugCheck(uint32_t Code) { printf("KeBugCheck: 0x%08X\n", Code); }
uint32_t __stdcall stub_KeInsertQueue(void* Queue, void* Entry) { return 0; }

void __stdcall stub_KeQueryPerformanceCounter(void* out)
{
    if (out) { LARGE_INTEGER li; QueryPerformanceCounter(&li); *(LARGE_INTEGER*)out = li; }
}

uint32_t __stdcall stub_KeReleaseMutant(void* m, uint32_t a, uint32_t b, uint32_t c) { return 0; }
uint32_t __stdcall stub_KeRemoveQueueDpc(void* Dpc) { return 0; }
uint32_t __stdcall stub_KeRestoreFloatingPointState(void* Save) { return 0; }
uint32_t stub_KeTickCount = 0;
uint32_t __stdcall stub_NtFlushBuffersFile(void* a, void* b) { return 0; }
uint32_t __stdcall stub_PsQueryStatistics(void* Stats) { return 0; }
uint32_t __stdcall stub_RtlAnsiStringToUnicodeString(void* a, void* b, uint32_t c) { return 0; }
void __stdcall stub_RtlCopyString(void* a, void* b) { }
uint32_t __stdcall stub_RtlIntegerToChar(uint32_t a, uint32_t b, uint32_t c, void* d) { return 0; }
uint32_t __stdcall stub_HalIsResetOrShutdownPending(void) { return 0; }

// Ex
void __stdcall stub_ExAcquireReadWriteLockExclusive(void* Lock) { }
void __stdcall stub_ExAcquireReadWriteLockShared(void* Lock) { }
uint8_t stub_ExEventObjectType[64] = { 0 };
uint8_t stub_ExMutantObjectType[64] = { 0 };
uint8_t stub_ExSemaphoreObjectType[64] = { 0 };
uint8_t stub_ExTimerObjectType[64] = { 0 };
void __stdcall stub_ExInterlockedAddLargeInteger(void* a, uint32_t b, uint32_t c) { }
void __stdcall stub_ExInterlockedAddLargeStatistic(void* a, uint32_t b) { }
uint64_t __stdcall stub_ExInterlockedCompareExchange64(void* a, void* b, void* c) { return 0; }
void __stdcall stub_ExReleaseReadWriteLock(void* Lock) { }
void __stdcall stub_ExfInterlockedInsertHeadList(void* a, void* b) { }
void __stdcall stub_ExfInterlockedInsertTailList(void* a, void* b) { }
void* __stdcall stub_ExfInterlockedRemoveHeadList(void* a) { return 0; }

// Interlocked (fastcall)
uint32_t __fastcall stub_InterlockedCompareExchange(void* Dest, uint32_t Exch, uint32_t Comp) { return 0; }
uint32_t __fastcall stub_InterlockedIncrement(uint32_t* v) { return v ? ++*v : 0; }
uint32_t __fastcall stub_InterlockedDecrement(uint32_t* v) { return v ? --*v : 0; }
void* __fastcall stub_InterlockedPopEntrySList(void* Head) { return 0; }
void* __fastcall stub_InterlockedPushEntrySList(void* Head, void* Entry) { return 0; }

// Io
void* __stdcall stub_IoAllocateIrp(uint32_t Size, uint32_t ChargeQuota) { return 0; }
uint32_t __stdcall stub_IoCreateDevice(void* a, uint32_t b, void* c, uint32_t d, uint32_t e, uint32_t f, void** g) { return 0; }
uint32_t __stdcall stub_IoDeleteDevice(void* a) { return 0; }
uint8_t stub_IoFileObjectType[64] = { 0 };
uint8_t stub_IoCompletionObjectType[64] = { 0 };
void __stdcall stub_IoFreeIrp(void* Irp) { }
uint32_t __stdcall stub_IoQueueThreadIrp(void* Irp) { return 0; }
uint32_t __stdcall stub_IoSynchronousFsdRequest(uint32_t a, void* b, void* c, uint32_t d, void* e, void* f, uint32_t g) { return 0; }
uint32_t __fastcall stub_IofCallDriver(void* Dev, void* Irp) { return 0; }
void __fastcall stub_IofCompleteRequest(void* Irp, uint32_t Boost) { }

// Kd
uint32_t stub_KdDebuggerEnabled = 0;
uint32_t stub_KdDebuggerNotPresent = 1;

// Ke
void __stdcall stub_KeBoostPriorityThread(void* Thread, uint32_t Inc) { }
void __stdcall stub_KeEnterCriticalRegion(void) { }
void __stdcall stub_KeLeaveCriticalRegion(void) { }
uint8_t stub_MmGlobalData[64] = { 0 };
void __stdcall stub_KeInitializeMutant(void* M, uint32_t Owner) { }
void __stdcall stub_KeInitializeQueue(void* Q, uint32_t Count) { }
void __stdcall stub_KeInitializeTimerEx(void* T, uint32_t Type) { }
uint32_t __stdcall stub_KeInsertDeviceQueue(void* Q, void* E) { return 0; }
uint32_t __stdcall stub_KeInsertByKeyDeviceQueue(void* Q, void* E, uint32_t K) { return 0; }
uint32_t __stdcall stub_KeInsertHeadQueue(void* Q, void* E) { return 0; }
uint64_t stub_KeInterruptTime = 0;
void __stdcall stub_KePulseEvent(void* E, uint32_t Inc, uint32_t Wait) { }
uint64_t __stdcall stub_KeQueryInterruptTime(void) { return 0; }
uint32_t __stdcall stub_KeRaiseIrqlToDpcLevel(void) { return 0; }
uint32_t __stdcall stub_KeReleaseSemaphore(void* S, uint32_t Inc, uint32_t Adj, uint32_t Wait) { return 0; }
void* __stdcall stub_KeRemoveDeviceQueue(void* Q) { return 0; }
void* __stdcall stub_KeRemoveByKeyDeviceQueue(void* Q, uint32_t K) { return 0; }
uint32_t __stdcall stub_KeRemoveEntryDeviceQueue(void* Q, void* E) { return 0; }
uint32_t __stdcall stub_KeResetEvent(void* E) { return 0; }
void __stdcall stub_KeRundownQueue(void* Q) { }
uint32_t __stdcall stub_KeSetTimer(void* T, uint64_t DueTime, void* Dpc) { return 0; }
uint32_t __stdcall stub_KeSetTimerEx(void* T, uint64_t DueTime, uint32_t Period, void* Dpc) { return 0; }
uint32_t __stdcall stub_KeTestAlertThread(uint32_t Mode) { return 0; }
uint32_t __stdcall stub_KeWaitForSingleObject(void* O, uint32_t Reason, uint32_t Mode, uint32_t Alert, void* Timeout) { return 0; }
uint32_t __stdcall stub_KeWaitForMultipleObjects(uint32_t Count, void* Objs, uint32_t Type, uint32_t Reason, uint32_t Mode, uint32_t Alert, void* Timeout, void* Wait) { return 0; }
uint32_t __fastcall stub_KfLowerIrql(uint32_t Irql) { return 0; }
uint32_t __fastcall stub_KfRaiseIrql(uint32_t Irql) { return 0; }

// Mm
void __stdcall stub_MmUnmapIoSpace(void* a, uint32_t b) { }

// Nt
uint32_t __stdcall stub_NtCreateTimer(void* H, void* OA, uint32_t Type) { if (H) *(uint32_t*)H = 0; return 0; }
uint32_t __stdcall stub_NtDeviceIoControlFile(uint32_t H, uint32_t E, void* A, void* AC, void* IOSB, uint32_t Code, void* In, uint32_t InLen, void* Out, uint32_t OutLen) { return 0; }
uint32_t __stdcall stub_NtFsControlFile(uint32_t H, uint32_t E, void* A, void* AC, void* IOSB, uint32_t Code, void* In, uint32_t InLen, void* Out, uint32_t OutLen) { return 0; }
uint32_t __stdcall stub_NtProtectVirtualMemory(void** BA, uint32_t* Size, uint32_t Prot, uint32_t* Old) { return 0; }
uint32_t __stdcall stub_NtQueueApcThread(uint32_t Th, void* R, void* Ctx, void* A1, void* A2) { return 0; }
uint32_t __stdcall stub_NtQueryTimer(uint32_t H, uint32_t Cls, void* Info) { return 0; }
uint32_t __stdcall stub_NtUserIoApcDispatcher(void* Ctx, void* IOSB, uint32_t Rsv) { return 0; }

// Ob
uint8_t stub_ObDirectoryObjectType[64] = { 0 };
uint8_t stub_ObSymbolicLinkObjectType[64] = { 0 };
uint32_t __stdcall stub_ObReferenceObjectByPointer(void* O, void* T) { return 0; }
void __fastcall stub_ObfReferenceObject(void* O) { }

// Phy
uint32_t __stdcall stub_PhyGetLinkState(uint32_t Flags) { return 0; }

// Ps
uint32_t __stdcall stub_PsCreateSystemThread(void* H, void* OA, void* SR, void* SC, uint32_t Dbg) { if (H) *(uint32_t*)H = 0; return 0; }

// Rtl
uint32_t __stdcall stub_RtlAppendUnicodeStringToString(void* D, void* S) { return 0; }
uint32_t __stdcall stub_RtlAppendUnicodeToString(void* D, void* S) { return 0; }
uint32_t __stdcall stub_RtlCharToInteger(char* S, uint32_t Base, uint32_t* V) { if (V) *V = 0; return 0; }
uint32_t __stdcall stub_RtlCompareMemory(void* a, void* b, uint32_t Len) { return Len; }
uint32_t __stdcall stub_RtlCompareString(void* a, void* b, uint32_t Case) { return 0; }
uint32_t __stdcall stub_RtlCompareUnicodeString(void* a, void* b, uint32_t Case) { return 0; }
void __stdcall stub_RtlCopyUnicodeString(void* D, void* S) { }
void __stdcall stub_RtlCreateUnicodeString(void* D, void* S) { }
uint32_t __stdcall stub_RtlEqualString(void* a, void* b, uint32_t Case) { return 1; }
uint32_t __stdcall stub_RtlEqualUnicodeString(void* a, void* b, uint32_t Case) { return 1; }
void __stdcall stub_RtlFreeAnsiString(void* S) { }
void __stdcall stub_RtlFreeUnicodeString(void* S) { }
void __stdcall stub_RtlGetCallersAddress(void** Caller, void** Parent) { if (Caller) *Caller = 0; if (Parent) *Parent = 0; }
uint32_t __stdcall stub_RtlIntegerToUnicodeString(uint32_t V, uint32_t Base, void* S) { return 0; }
uint32_t __stdcall stub_RtlMultiByteToUnicodeN(void* U, uint32_t UMax, uint32_t* URet, void* M, uint32_t MLen) { return 0; }
uint32_t __stdcall stub_RtlMultiByteToUnicodeSize(uint32_t* Sz, void* M, uint32_t MLen) { return 0; }
uint32_t __stdcall stub_RtlUlongByteSwap(uint32_t V) { return _byteswap_ulong(V); }
uint32_t __stdcall stub_RtlUnicodeStringToAnsiString(void* D, void* S, uint32_t Alloc) { return 0; }
uint16_t __stdcall stub_RtlUpcaseUnicodeChar(uint16_t C) { return (C >= 'a' && C <= 'z') ? C - 32 : C; }
uint32_t __stdcall stub_RtlUpcaseUnicodeString(void* D, void* S, uint32_t Alloc) { return 0; }
uint32_t __stdcall stub_RtlUpcaseUnicodeToMultiByteN(void* M, uint32_t MMax, uint32_t* MRet, void* U, uint32_t ULen) { return 0; }

// Xbox data exports
uint8_t stub_XboxEEPROMKey[16] = { 0 };
uint8_t stub_XboxHDKey[16] = { 0 };
uint8_t stub_XboxSignatureKey[16] = { 0 };
uint8_t stub_KiBugCheckData[20] = { 0 };
