#include <iostream>
#include <Windows.h>
#include <stdio.h>
//####this project is about creating maximum number of kernel objects ####


//first test is to create infinite number of kernel object here is mutex
void Test1(int type) {
	//if type is 1 create mutex
	//if type is 2 create job 
	int count = 0;
	HANDLE hMutex = nullptr;
	for (;;) {
		if (type == 1){
			hMutex = CreateMutex(nullptr, FALSE, nullptr);
		}else if (type ==2)
			hMutex = CreateJobObject(nullptr, nullptr);

		if (!hMutex) {
			break;
		}
		count++;
	}
	printf("Total: %d\n", count);
}


void Test2() {
	int count = 0;
	HANDLE hMutex = CreateMutex(nullptr, FALSE, nullptr);
	for (;;) {
		HANDLE hTarget;
		if (!DuplicateHandle(GetCurrentProcess(), hMutex, GetCurrentProcess(), &hTarget, 0, FALSE, DUPLICATE_SAME_ACCESS))
			break;
		count++;
	}
	printf("Total: %d\n", count);
}


int main(){
	Test1(2);
	char dummy[3];
	gets_s(dummy);

	return 0;
}

