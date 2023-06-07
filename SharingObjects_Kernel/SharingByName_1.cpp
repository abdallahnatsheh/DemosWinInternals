#include "SharingByName_1.h"
#include <Windows.h>
#include <stdio.h>

//make it main to run it
int func(){
	HANDLE hEvent = CreateEvent(nullptr, TRUE, FALSE, L"ShutdownEvent");
	if (!hEvent) {
		printf("Error: %u\n", GetLastError());
		return 1;
	}
	printf("hEvent: 0x%p\n", hEvent);
	
	if(GetLastError() == ERROR_ALREADY_EXISTS){
		printf("Worker process: %u. Waiting for shutdown...\n",GetCurrentProcessId());
		WaitForSingleObject(hEvent, INFINITE);
		printf("Shutting down....\n");
	}
	else {
		printf("Controller process %u. Press ENTER to send shutdown notification...",
			GetCurrentProcessId());
		char dummy[3];
		gets_s(dummy);

		SetEvent(hEvent);
		printf("Notification sent!\n");
	}
	CloseHandle(hEvent);
	return 0;
}