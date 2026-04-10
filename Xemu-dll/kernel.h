#include <stdio.h>
#include <stdint.h>

extern void* kernel_table[512];

// === Nt functions (kernel_nt.c) ===
uint32_t __stdcall stub_NtAllocateVirtualMemory(void** BaseAddress, uint32_t ZeroBits, uint32_t* AllocationSize, uint32_t AllocationType, uint32_t Protect);
uint32_t __stdcall stub_NtClearEvent(uint32_t EventHandle);
uint32_t __stdcall stub_NtClose(uint32_t Handle);
uint32_t __stdcall stub_NtCreateEvent(void* EventHandle, void* ObjectAttributes, uint32_t EventType, uint32_t InitialState);
uint32_t __stdcall stub_NtCreateFile(void* FileHandle, uint32_t DesiredAccess, void* ObjectAttributes, void* IoStatusBlock, void* AllocationSize, uint32_t FileAttributes, uint32_t ShareAccess, uint32_t CreateDisposition, uint32_t CreateOptions);
uint32_t __stdcall stub_NtCreateMutant(void* MutantHandle, void* ObjectAttributes, uint32_t InitialOwner);
uint32_t __stdcall stub_NtCreateSemaphore(void* SemaphoreHandle, void* ObjectAttributes, uint32_t InitialCount, uint32_t MaximumCount);
uint32_t __stdcall stub_NtFreeVirtualMemory(void** BaseAddress, uint32_t* FreeSize, uint32_t FreeType);
uint32_t __stdcall stub_NtOpenDirectoryObject(void* DirectoryHandle, void* ObjectAttributes);
uint32_t __stdcall stub_NtOpenFile(void* FileHandle, uint32_t DesiredAccess, void* ObjectAttributes, void* IoStatusBlock, uint32_t ShareAccess, uint32_t OpenOptions);
uint32_t __stdcall stub_NtOpenSymbolicLinkObject(void* LinkHandle, void* ObjectAttributes);
uint32_t __stdcall stub_NtPulseEvent(uint32_t EventHandle, void* PreviousState);
uint32_t __stdcall stub_NtQueryDirectoryObject(uint32_t DirectoryHandle, void* Buffer, uint32_t Length, uint32_t RestartScan, uint32_t* Context, uint32_t* ReturnLength);
uint32_t __stdcall stub_NtQueryFullAttributesFile(void* ObjectAttributes, void* FileInformation);
uint32_t __stdcall stub_NtQueryInformationFile(uint32_t FileHandle, void* IoStatusBlock, void* FileInformation, uint32_t Length, uint32_t FileInformationClass);
uint32_t __stdcall stub_NtQueryVirtualMemory(void* BaseAddress, void* Buffer);
uint32_t __stdcall stub_NtQueryVolumeInformationFile(uint32_t FileHandle, void* IoStatusBlock, void* FileInformation, uint32_t Length, uint32_t FileInformationClass);
uint32_t __stdcall stub_NtReadFile(uint32_t FileHandle, uint32_t Event, void* ApcRoutine, void* ApcContext, void* IoStatusBlock, void* Buffer, uint32_t Length, void* ByteOffset);
uint32_t __stdcall stub_NtReleaseMutant(uint32_t MutantHandle, void* PreviousCount);
uint32_t __stdcall stub_NtReleaseSemaphore(uint32_t SemaphoreHandle, uint32_t ReleaseCount, uint32_t* PreviousCount);
uint32_t __stdcall stub_NtResumeThread(uint32_t ThreadHandle, uint32_t* PreviousSuspendCount);
uint32_t __stdcall stub_NtSetEvent(uint32_t EventHandle, void* PreviousState);
uint32_t __stdcall stub_NtSetInformationFile(uint32_t FileHandle, void* IoStatusBlock, void* FileInformation, uint32_t Length, uint32_t FileInformationClass);
uint32_t __stdcall stub_NtSuspendThread(uint32_t ThreadHandle, uint32_t* PreviousSuspendCount);
uint32_t __stdcall stub_NtWaitForSingleObject(uint32_t Handle, uint32_t Alertable, void* Timeout);
uint32_t __stdcall stub_NtWaitForSingleObjectEx(uint32_t Handle, uint32_t WaitMode, uint32_t Alertable, void* Timeout);
uint32_t __stdcall stub_NtWaitForMultipleObjectsEx(uint32_t Count, void* Handles, uint32_t WaitType, uint32_t WaitMode, uint32_t Alertable, void* Timeout);
uint32_t __stdcall stub_NtWriteFile(uint32_t FileHandle, uint32_t Event, void* ApcRoutine, void* ApcContext, void* IoStatusBlock, void* Buffer, uint32_t Length, void* ByteOffset);
void __stdcall stub_NtYieldExecution(void);

// === Xc functions (kernel_Xc.c) ===
uint32_t __stdcall stub_XcSHAInit(void* pbSHAContext);
void __stdcall stub_XcSHAUpdate(void* pbSHAContext, void* pbInput, uint32_t dwInputLength);
void __stdcall stub_XcSHAFinal(void* pbSHAContext, void* pbDigest);

// === Misc functions (kernel_misc.c) ===
void* __stdcall stub_AvGetSavedDataAddress(void);
void __stdcall stub_AvSendTVEncoderOption(void* RegisterBase, uint32_t Option, uint32_t Param, uint32_t* Result);
uint32_t __stdcall stub_AvSetDisplayMode(void* RegisterBase, uint32_t Step, uint32_t Mode, uint32_t Format, uint32_t Pitch, void* FrameBuffer);
void __stdcall stub_AvSetSavedDataAddress(void* Address);
uint32_t __cdecl stub_DbgPrint(char* Format, ...);
uint32_t __stdcall stub_ExQueryNonVolatileSetting(uint32_t ValueIndex, uint32_t* Type, void* Value, uint32_t ValueLength, void* ResultLength);
uint32_t __stdcall stub_HalGetInterruptVector(uint32_t BusInterruptLevel, void* Irql);
void __stdcall stub_HalReadWritePCISpace(uint32_t BusNumber, uint32_t SlotNumber, uint32_t RegisterNumber, void* Buffer, uint32_t Length, uint32_t WritePCISpace);
void __stdcall stub_HalReturnToFirmware(uint32_t Routine);
uint32_t __fastcall stub_InterlockedExchange(void* Destination, uint32_t Value);
uint32_t __stdcall stub_IoCreateSymbolicLink(void* SymbolicLinkName, void* DeviceName);
uint32_t __stdcall stub_IoDeleteSymbolicLink(void* SymbolicLinkName);
uint32_t __stdcall stub_KeConnectInterrupt(void* InterruptObject);
uint32_t __stdcall stub_KeDelayExecutionThread(uint32_t WaitMode, uint32_t Alertable, void* Interval);
uint32_t __stdcall stub_KeGetCurrentIrql(void);
void* __stdcall stub_KeGetCurrentThread(void);
void __stdcall stub_KeInitializeDpc(void* Dpc, void* DeferredRoutine, void* DeferredContext);
void __stdcall stub_KeInitializeInterrupt(void* Interrupt, void* ServiceRoutine, void* ServiceContext, uint32_t Vector, uint32_t Irql, uint32_t InterruptMode, uint32_t ShareVector);
uint32_t __stdcall stub_KeInsertQueueDpc(void* Dpc, void* SystemArgument1, void* SystemArgument2);
void __stdcall stub_KeQuerySystemTime(void* CurrentTime);
uint32_t __stdcall stub_KeSetBasePriorityThread(void* Thread, uint32_t Priority);
void* __stdcall stub_MmAllocateContiguousMemory(uint32_t NumberOfBytes);
void* __stdcall stub_MmAllocateContiguousMemoryEx(uint32_t NumberOfBytes, uint32_t LowestAddr, uint32_t HighestAddr, uint32_t Alignment, uint32_t ProtectionType);
void __stdcall stub_MmFreeContiguousMemory(void* BaseAddress);
void __stdcall stub_MmPersistContiguousMemory(void* BaseAddress, uint32_t NumberOfBytes, uint32_t Persist);
uint32_t __stdcall stub_MmQueryAllocationSize(void* BaseAddress);
uint32_t __stdcall stub_ObReferenceObjectByHandle(uint32_t Handle, void* ObjectType, void** ReturnedObject);
void __fastcall stub_ObfDereferenceObject(void* Object);
uint32_t __stdcall stub_PsCreateSystemThreadEx(void* ThreadHandle, uint32_t ThreadExtensionSize, uint32_t KernelStackSize, uint32_t TlsDataSize, void* ThreadId, void* StartRoutine, void* StartContext, uint32_t CreateSuspended, uint32_t DebugStack, void* SystemRoutine);
void __stdcall stub_PsTerminateSystemThread(uint32_t ExitStatus);
void __stdcall stub_RtlEnterCriticalSection(void* CriticalSection);
void __stdcall stub_RtlInitAnsiString(void* DestinationString, void* SourceString);
void __stdcall stub_RtlInitializeCriticalSection(void* CriticalSection);
void __stdcall stub_RtlLeaveCriticalSection(void* CriticalSection);
uint32_t __stdcall stub_RtlNtStatusToDosError(uint32_t Status);
void __stdcall stub_RtlRaiseException(void* ExceptionRecord);
uint32_t __stdcall stub_RtlTryEnterCriticalSection(void* CriticalSection);

// Data exports (addresses of static buffers)
extern uint8_t stub_LaunchDataPage[];
extern uint8_t stub_PsThreadObjectType[];
extern uint8_t stub_XeImageFileName[];
