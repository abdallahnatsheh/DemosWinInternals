#include <Windows.h>
#include <stdio.h>
#include <string>

int main() {
	int processId = 0;
	HANDLE hEvent = CreateEvent(nullptr, FALSE, FALSE, nullptr);

	HANDLE hProcess = OpenProcess(PROCESS_DUP_HANDLE, FALSE, processId);
	if (hProcess) {
		HANDLE hTarget;
		if (DuplicateHandle(GetCurrentProcess(), hEvent, hProcess, &hTarget,
			SYNCHRONIZE, FALSE, 0)) {
			printf("Success! 0x%p\n", hTarget);
		}
		CloseHandle(hProcess);
	}
	CloseHandle(hEvent);
	return 0;
}