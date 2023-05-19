#include <stdio.h>
#include <Windows.h>

int cellx = 1024, celly = 1024;
int cell_size = 1024;

int FixMemory(DWORD code, void* p) {
	if (code != EXCEPTION_ACCESS_VIOLATION)
		return EXCEPTION_CONTINUE_SEARCH;
	VirtualAlloc(p, cell_size, MEM_COMMIT, PAGE_READWRITE);
	return EXCEPTION_CONTINUE_EXECUTION;
}

int main(){
	//malloc creates commited memory even if not all the memory used 
	//if i used 100k the rest 900k will still be wasted
	//void* buffer = malloc(cellx * celly * cell_size);
	//with virtual alloc we can create reserve memory what can be used when ever i want
	//so if i used 100kb i will not have to waste 900kb

	//in this virtuall alloc is commited not reserved
	//char* buffer = (char*)VirtualAlloc(nullptr,cellx * celly * cell_size,MEM_COMMIT | MEM_RESERVE,PAGE_READWRITE);
	//this is reserved memory 
	//this memory is not useable because its only reserved
	char* buffer = (char*)VirtualAlloc(nullptr, cellx * celly * cell_size, MEM_RESERVE, PAGE_READWRITE);
	//to make it usable , it must be commited and to save memory lets commit it
	//with the size we want
	//VirtualAlloc(buffer, cell_size, MEM_COMMIT, PAGE_READWRITE);
	__try {
		char text[] = "hello memory !";
		strcpy_s(buffer, sizeof(text), text);
	}
	__except (FixMemory(GetExceptionCode(), buffer)) {
	}
	printf("Read: %s\n", buffer);
	return 0;
}