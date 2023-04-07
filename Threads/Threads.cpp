#include <Windows.h>
#include <stdio.h>
//just a program that creates two threads and waits for both of them to complete
//every thread return multiple of the input number it takes

DWORD CALLBACK DoWork(PVOID param) {
	int data = *(int*)param;
	printf("Worker Thread:%u\n", GetCurrentThreadId());
	Sleep(GetCurrentThreadId()/5);
	return data * data;
}

int main(){
	int x = 20 , y =10;
	HANDLE hThread = CreateThread(nullptr, 0, DoWork,&x, 0, nullptr);
	HANDLE hThread2 = CreateThread(nullptr, 0, DoWork, &y, 0, nullptr);

	printf("Main thread: %u\n", GetCurrentThreadId());

	HANDLE h[] = { hThread,hThread2 };
	WaitForMultipleObjects(_countof(h), h, TRUE, INFINITE);
	
	DWORD sum = 0;
	for (int i = 0; i < _countof(h); i++) {
		DWORD code;
		GetExitCodeThread(h[i],&code);
		printf("Thread %u is done. Result =%u\n",GetThreadId(h[i]),code);
		sum += code;
		CloseHandle(h[i]);
	}
	printf("Work done. Total=%u\n",sum);

	return 0;

}