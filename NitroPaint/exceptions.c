#include "exceptions.h"

#include <DbgHelp.h>
#include <winternl.h>
#include <stdio.h>

DWORD __stdcall GetModuleBaseRoutine(HANDLE hProcess, DWORD address) {
	return (DWORD) GetModuleHandle(NULL);
}

PVOID __stdcall FunctionTableAccessRoutine(HANDLE hProcess, DWORD base) {
	return NULL;
}

LPWSTR GetModuleFromAddress(DWORD address, PVOID *ModuleBase) {
	ULONG_PTR Peb = __readfsdword(0x30);
	PPEB_LDR_DATA LdrData = *(PPEB_LDR_DATA *) (Peb + 0xC);

	PLIST_ENTRY ModuleList = &LdrData->InMemoryOrderModuleList;
	PLIST_ENTRY CurrentModule = ModuleList;
	ULONG_PTR LargestBaseAddress = 0;

	LPWSTR ModuleName = NULL;

	while (1) {
		PLDR_DATA_TABLE_ENTRY Entry = (PLDR_DATA_TABLE_ENTRY) (((ULONG_PTR) CurrentModule) - 0x8);
		CurrentModule = CurrentModule->Flink;
		if (CurrentModule == ModuleList) break;

		ULONG_PTR Base = (ULONG_PTR) Entry->DllBase;
		if (Base > LargestBaseAddress && Base < address) {
			LargestBaseAddress = Base;
			ModuleName = Entry->FullDllName.Buffer;
		}
	}

	int lastIndex = -1;

	int index = 0;
	LPWSTR nameCopy = ModuleName;
	while (*nameCopy) {
		WCHAR wc = *nameCopy;
		if (wc == L'\\') lastIndex = index;
		index++;
		nameCopy++;
	}

	if(ModuleBase) *ModuleBase = (PVOID) LargestBaseAddress;

	LPWSTR name = ModuleName + lastIndex + 1;
	return name;
}

BOOL __stdcall ReadProcessMemoryRoutine(HANDLE hProcess, DWORD lpBaseAddress, LPVOID lpBuffer, DWORD nSize, LPDWORD lpBytesRead) {
	BOOL b =  ReadProcessMemory(hProcess, (LPCVOID) lpBaseAddress, lpBuffer, (SIZE_T) nSize, (SIZE_T *) lpBytesRead);
	return b;
}

void printStackTrace(CONTEXT *context, EXCEPTION_RECORD *record) {

	SymInitialize(GetCurrentProcess(), NULL, TRUE);

	STACKFRAME frame = { 0 };
	HANDLE thread = GetCurrentThread();
	//GetThreadContext(thread, &context);
	context->ContextFlags = CONTEXT_ALL;

	frame.AddrPC.Offset = context->Eip;
	frame.AddrPC.Segment = (WORD) context->SegCs;
	frame.AddrPC.Mode = AddrModeFlat;
	frame.AddrFrame.Offset = context->Ebp;
	frame.AddrFrame.Segment = (WORD) context->SegSs;
	frame.AddrFrame.Mode = AddrModeFlat;
	frame.AddrStack.Offset = context->Esp;
	frame.AddrStack.Segment = (WORD) context->SegSs;
	frame.AddrStack.Mode = AddrModeFlat;
}

EXCEPTION_DISPOSITION __cdecl ExceptionHandler(EXCEPTION_RECORD *exceptionRecord, void *establisherFrame, CONTEXT *contextRecord, void *dispatcherContext){
	//uh oh, an exception occurred. There's really no good way to recover from
	//these, so we just tell the user something went wrong and peacefully exit.
	
	printStackTrace(contextRecord, exceptionRecord);
	ExitProcess(exceptionRecord->ExceptionCode);
	return ExceptionContinueSearch;
}

void entry(PVOID Peb) {
	_asm {
		//install SEH handler
		//int 3
		push offset ExceptionHandler
		xor eax, eax
		push fs:[eax]
		mov fs:[eax], esp
	}
	ExitProcess(WinMain(GetModuleHandle(NULL), NULL, NULL, 0));
}