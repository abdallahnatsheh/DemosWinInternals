#include <stdio.h>
#include <Windows.h>
#include <memory>

struct ThreadData{
	int first;
	int last;
	int count;
};

//check if number is prime or not 
bool isPrime(int n) {
	int limit = (int)sqrt(n);
	for (int i = 2; i < +limit; i++)
		if (n % i == 0)
			return false;
	return true;
}

//this function takes every threadData and returns number of prime numbers in its range
DWORD WINAPI CountPrimes(PVOID param) {
	auto data = (ThreadData*)param;
	int count = 0;
	for (int i = data->first; i <= data->last; i++) {
		if (isPrime(i))
			count++;
	}
	data->count = count;
	return 0;

}

//this function creates number of threads and every thread have its own range
//then it runs every thread with its range to return how many prime number in every thread range
//then it sum everything to gather and return the value
int CalcPrimes(int first, int last, int threads) {
	int chunk = (last - first + 1) / threads;
	//HANDLE* handles = (HANDLE*)malloc(sizeof(HANDLE)*threads);
	auto handles = std::make_unique<HANDLE[]>(threads);
	auto data = std::make_unique<ThreadData[]>(threads);
	 
	for (int i = 0; i < threads; i++) {
		data[i].first = first + i * chunk;
		data[i].last = i == threads - 1 ? last : data[i].first + chunk - 1;
		handles[i] = CreateThread(nullptr, 0, CountPrimes, &data[i], 0, nullptr);
	}
	WaitForMultipleObjects(threads, handles.get(), TRUE, INFINITE);
	//free(handles);

	int total = 0;
	for (int i = 0; i < threads; i++) {
		total += data[i].count;
		CloseHandle(handles[i]);
	}
	return total;
}

int main(int argc , const char* argv[]){
	int threads = 1;
	if (argc > 1) 
		threads = atoi(argv[1]);

	printf("Working with %d threads",threads);
	auto start = GetTickCount64();
	int count = CalcPrimes(3, 20000000, threads);
	auto end = GetTickCount64();
	printf("TotalL %d Elapsed: %d\n", count, (DWORD)(end - start));
	return 0;
}
