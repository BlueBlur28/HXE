#include <windows.h>
#include <stdio.h>
#include <stdint.h>
#include "kernel.h"

// 0x00B8 - #184 NtAllocateVirtualMemory
uint32_t __stdcall stub_NtAllocateVirtualMemory(void** BaseAddress, uint32_t ZeroBits, uint32_t* AllocationSize, uint32_t AllocationType, uint32_t Protect)
{
    uint32_t size = *AllocationSize;
    void* ptr = VirtualAlloc(NULL, size, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
    printf("NtAllocateVirtualMemory(%u) = %p\n", size, ptr);
    if (ptr) {
        *BaseAddress = ptr;
        return 0;
    }
    return 0xC0000017;  // STATUS_NO_MEMORY
}

// 0x00BA - #186 NtClearEvent
uint32_t __stdcall stub_NtClearEvent(uint32_t EventHandle) { return 0; }

// 0x00BB - #187 NtClose
uint32_t __stdcall stub_NtClose(uint32_t Handle) { return 0; }

// 0x00BD - #189 NtCreateEvent
uint32_t __stdcall stub_NtCreateEvent(void* EventHandle, void* ObjectAttributes, uint32_t EventType, uint32_t InitialState)
{
    static uint32_t fake_handle = 0x2000;
    printf("NtCreateEvent -> handle 0x%X\n", fake_handle);
    *(uint32_t*)EventHandle = fake_handle++;
    return 0;
}

// 0x00BE - #190 NtCreateFile
uint32_t __stdcall stub_NtCreateFile(void* FileHandle, uint32_t DesiredAccess, void* ObjectAttributes, void* IoStatusBlock, void* AllocationSize, uint32_t FileAttributes, uint32_t ShareAccess, uint32_t CreateDisposition, uint32_t CreateOptions)
{
    printf("NtCreateFile\n");
    return 0;
}

// 0x00C0 - #192 NtCreateMutant
uint32_t __stdcall stub_NtCreateMutant(void* MutantHandle, void* ObjectAttributes, uint32_t InitialOwner)
{
    static uint32_t fake_handle = 0x1000;
    printf("NtCreateMutant -> handle 0x%X\n", fake_handle);
    *(uint32_t*)MutantHandle = fake_handle++;
    return 0;
}

// 0x00C1 - #193 NtCreateSemaphore
uint32_t __stdcall stub_NtCreateSemaphore(void* SemaphoreHandle, void* ObjectAttributes, uint32_t InitialCount, uint32_t MaximumCount)
{
    static uint32_t fake_handle = 0x3000;
    printf("NtCreateSemaphore -> handle 0x%X\n", fake_handle);
    *(uint32_t*)SemaphoreHandle = fake_handle++;
    return 0;
}

// 0x00C7 - #199 NtFreeVirtualMemory
uint32_t __stdcall stub_NtFreeVirtualMemory(void** BaseAddress, uint32_t* FreeSize, uint32_t FreeType) { return 0; }

// 0x00C9 - #201 NtOpenDirectoryObject
uint32_t __stdcall stub_NtOpenDirectoryObject(void* DirectoryHandle, void* ObjectAttributes) { return 0; }

// 0x00CA - #202 NtOpenFile
uint32_t __stdcall stub_NtOpenFile(void* FileHandle, uint32_t DesiredAccess, void* ObjectAttributes, void* IoStatusBlock, uint32_t ShareAccess, uint32_t OpenOptions) { return 0; }

// 0x00CB - #203 NtOpenSymbolicLinkObject
uint32_t __stdcall stub_NtOpenSymbolicLinkObject(void* LinkHandle, void* ObjectAttributes) { return 0; }

// 0x00CD - #205 NtPulseEvent
uint32_t __stdcall stub_NtPulseEvent(uint32_t EventHandle, void* PreviousState) { return 0; }

// 0x00D0 - #208 NtQueryDirectoryObject
uint32_t __stdcall stub_NtQueryDirectoryObject(uint32_t DirectoryHandle, void* Buffer, uint32_t Length, uint32_t RestartScan, uint32_t* Context, uint32_t* ReturnLength) { return 0; }

// 0x00D2 - #210 NtQueryFullAttributesFile
uint32_t __stdcall stub_NtQueryFullAttributesFile(void* ObjectAttributes, void* FileInformation) { return 0; }

// 0x00D3 - #211 NtQueryInformationFile
uint32_t __stdcall stub_NtQueryInformationFile(uint32_t FileHandle, void* IoStatusBlock, void* FileInformation, uint32_t Length, uint32_t FileInformationClass) { return 0; }

// 0x00D9 - #217 NtQueryVirtualMemory
uint32_t __stdcall stub_NtQueryVirtualMemory(void* BaseAddress, void* Buffer) { return 0; }

// 0x00DA - #218 NtQueryVolumeInformationFile
uint32_t __stdcall stub_NtQueryVolumeInformationFile(uint32_t FileHandle, void* IoStatusBlock, void* FileInformation, uint32_t Length, uint32_t FileInformationClass) { return 0; }

// 0x00DB - #219 NtReadFile
uint32_t __stdcall stub_NtReadFile(uint32_t FileHandle, uint32_t Event, void* ApcRoutine, void* ApcContext, void* IoStatusBlock, void* Buffer, uint32_t Length, void* ByteOffset) { return 0; }

// 0x00DD - #221 NtReleaseMutant
uint32_t __stdcall stub_NtReleaseMutant(uint32_t MutantHandle, void* PreviousCount) { return 0; }

// 0x00DE - #222 NtReleaseSemaphore
uint32_t __stdcall stub_NtReleaseSemaphore(uint32_t SemaphoreHandle, uint32_t ReleaseCount, uint32_t* PreviousCount) { return 0; }

// 0x00E0 - #224 NtResumeThread
uint32_t __stdcall stub_NtResumeThread(uint32_t ThreadHandle, uint32_t* PreviousSuspendCount) { return 0; }

// 0x00E1 - #225 NtSetEvent
uint32_t __stdcall stub_NtSetEvent(uint32_t EventHandle, void* PreviousState) { return 0; }

// 0x00E2 - #226 NtSetInformationFile
uint32_t __stdcall stub_NtSetInformationFile(uint32_t FileHandle, void* IoStatusBlock, void* FileInformation, uint32_t Length, uint32_t FileInformationClass) { return 0; }

// 0x00E7 - #231 NtSuspendThread
uint32_t __stdcall stub_NtSuspendThread(uint32_t ThreadHandle, uint32_t* PreviousSuspendCount) { return 0; }

// 0x00E9 - #233 NtWaitForSingleObject
uint32_t __stdcall stub_NtWaitForSingleObject(uint32_t Handle, uint32_t Alertable, void* Timeout) { return 0; }

// 0x00EA - #234 NtWaitForSingleObjectEx
uint32_t __stdcall stub_NtWaitForSingleObjectEx(uint32_t Handle, uint32_t WaitMode, uint32_t Alertable, void* Timeout) { return 0; }

// 0x00EB - #235 NtWaitForMultipleObjectsEx
uint32_t __stdcall stub_NtWaitForMultipleObjectsEx(uint32_t Count, void* Handles, uint32_t WaitType, uint32_t WaitMode, uint32_t Alertable, void* Timeout) { return 0; }

// 0x00EC - #236 NtWriteFile
uint32_t __stdcall stub_NtWriteFile(uint32_t FileHandle, uint32_t Event, void* ApcRoutine, void* ApcContext, void* IoStatusBlock, void* Buffer, uint32_t Length, void* ByteOffset) { return 0; }

// 0x00EE - #238 NtYieldExecution
void __stdcall stub_NtYieldExecution(void) { }
