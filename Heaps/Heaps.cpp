#include <Windows.h>
#include <Stdio.h>
#include "MyData.h"

int main(){
	MyData* p = new MyData(1,3);
	p->DoWork();
	MyData* p2 = new MyData(2, 7);
	p2->DoWork();
	MyData* p3 = new MyData(9, 0);
	p3->DoWork();	
	delete p;
	delete p2;
	delete p3;

	return 0;
}