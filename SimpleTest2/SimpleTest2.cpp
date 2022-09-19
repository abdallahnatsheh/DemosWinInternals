// SimpleTest2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <Windows.h>
#include <stdio.h>
#include "../SimpleLibrary/SimpleLibrary.h"

int main()
{
	HINSTANCE hInstDll = LoadLibrary(L"SimpleLibrary.dll");
	if (!hInstDll) {
		printf("Error: %u\n",GetLastError());
		return 1;
	}
	//typedef int (*PAdd)(int, int);
	auto add = (decltype(Add)*)GetProcAddress(hInstDll, "Add");

		if (add) {
		int result = add(1, 5);
		printf("result is : %d \n", result);
	}
		return 0;
}
