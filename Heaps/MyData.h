#pragma once
class MyData{
public:
	MyData(int x, int y);

	void* operator new(size_t size);
	void operator delete(void* p);
	void DoWork();
private:
	int m_X, m_Y;

	inline static HANDLE s_hHeap;
	inline static unsigned s_Objects;
};

