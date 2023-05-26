#include <Windows.h>
#include <stdio.h>

int Error(const char* text, DWORD error = GetLastError()) {
	printf("%s (%u)\n", text, error);
	return 1;
}

int wmain(int argc, const wchar_t* argv[]){
	if (argc < 3) {
		printf("Usage: injector <pid> <dllpath>\n");
		return 0;
	}

	HANDLE hprocess = OpenProcess(PROCESS_VM_WRITE | PROCESS_VM_OPERATION | PROCESS_CREATE_THREAD,
		FALSE, _wtoi(argv[1]));
	if (!hprocess)
		return Error("Error in opening process");
	
	void* buffer = VirtualAllocEx(hprocess, nullptr, 1 << 12, MEM_RESERVE | MEM_COMMIT,
		PAGE_READWRITE);
	if (!buffer)
		return Error("Failed to allocate memory!");
	if (!WriteProcessMemory(hprocess, buffer, argv[2], (wcslen(argv[2])+1)  * sizeof(WCHAR), nullptr))
		return Error("Failed to write to process");
	HANDLE hThread = CreateRemoteThread(hprocess, nullptr, 0,
		(LPTHREAD_START_ROUTINE)GetProcAddress(GetModuleHandle(L"kernel32"), "LoadLibraryW"), buffer, 0, nullptr);
	if (!hThread)
		return Error("failed to create thread");
	WaitForSingleObject(hThread, INFINITE);
	CloseHandle(hThread);
	CloseHandle(hprocess);

	return 0;
}