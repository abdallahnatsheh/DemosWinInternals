#include <Windows.h>
#include "MyData.h"
#include <stdio.h>

MyData::MyData(int x, int y) : m_X(x), m_Y(y) {

}

void* MyData::operator new(size_t size){
	if (s_Objects++ == 0)
		s_hHeap = HeapCreate(0, 1 << 16, 0);
	return HeapAlloc(s_hHeap, 0 , size);
}

void MyData::operator delete(void* p){
	HeapFree(s_hHeap, 0, p);
	if (--s_Objects == 0)
		HeapDestroy(s_hHeap);
}

void MyData::DoWork()
{
	printf("X=%d Y=%d\n", m_X, m_Y);
}
