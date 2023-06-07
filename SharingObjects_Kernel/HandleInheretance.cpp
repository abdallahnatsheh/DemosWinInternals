#include <Windows.h>
#include <stdio.h>
#include <string>

int main() {
	PROCESS_INFORMATION pi;
	STARTUPINFO si = { sizeof(si) };
	
	std::wstring name = L"notepad";

	HANDLE hEvent = CreateEvent(nullptr, FALSE, FALSE, nullptr);
	SetHandleInformation(hEvent, HANDLE_FLAG_INHERIT, HANDLE_FLAG_INHERIT);

	name += std::to_wstring((ULONG_PTR)hEvent);

	CreateProcess(nullptr, name.data(), nullptr, nullptr, TRUE, 
		0, nullptr, nullptr, &si, &pi);

	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);
	return 0;
}