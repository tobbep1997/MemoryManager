#include <iostream>
#include <memory>
#include "MemoryStack.h"

#include "DeltaTimer.h"
#include <vector>
#include <thread>
#include "LinkedList.h"

void SetDbgFlag()
{
#ifdef _DEBUG
	_CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_DEBUG);
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif
}

struct TestStruct
{
	union
	{
		struct
		{
			float x, y, z, w;
		};
		struct
		{
			float r, g, b, a;
		};
	};

	TestStruct()
	{
		x = 0, y = 0, z = 0, w = 0;
	}
};

void MemoryAllocatorTest();
const size_t testSize = 20000000;
const int loop = 5;
int counter = 0;

std::vector<double> timeSmart;
std::vector<double> timeRaw;

void threadCounter()
{
	while (counter < loop)
	{
		std::cout << "\r" << ((float)counter / (float)loop) * 100 << "%";
		Sleep(100);
	}
	system("cls");
}

int main()
{
	//const size_t testSize = 0xfffffff;
	

	LinkedListSmart list;
	for (size_t i = 0; i < 50; i++)
	{
		list.Insert(i);
	}
	list.PrintAllData();

	SetDbgFlag();
	std::thread te = std::thread(threadCounter);
	for (size_t i = 0; i < loop; i++)
	{
		MemoryAllocatorTest();
		counter++;
	}
	te.join();

	double sum = 0.0f;
	for (int i = 0; i < timeSmart.size(); ++i)
	{
		sum += timeSmart.at(i);
	}
	sum /= timeSmart.size();
	std::cout << "SmartPointer avr: " << sum << std::endl;

	sum = 0.0f;
	for (int i = 0; i < timeRaw.size(); ++i)
	{
		sum += timeRaw.at(i);
	}
	sum /= timeRaw.size();
	std::cout << "RawPointer avr: " << sum << std::endl;

	std::cin.get();
	return 0;

	DeltaTimer timer;

	std::cout << "Default Alloc " << testSize << " Objects " << " Start" << std::endl;

	TestStruct ** test = new TestStruct*[testSize];


	timer.Init();
	for (size_t i = 0; i < testSize; i++)
	{
		test[i] = new TestStruct();
	}
	for (size_t i = 0; i < testSize; i++)
	{
		delete test[i];
	}

	const double DefaultTime = timer.GetDeltaTimeInSeconds();
	
	std::cout << "Default: " << DefaultTime << " Sec" << std::endl;

	std::cout << "Pre Alloc " << testSize << " Objects " << " Start" << std::endl;

	MemoryStack::Init(testSize * sizeof(TestStruct));

	timer.Init();
	for (size_t i = 0; i < testSize; i++)
	{
		test[i] = MemoryStack::AllocData<TestStruct>();
		test[i]->x = static_cast<float>(i);
		test[i]->y = static_cast<float>(i);
		test[i]->z = static_cast<float>(i);
		test[i]->w = static_cast<float>(i);
	}
	for (size_t i = 0; i < testSize; i++)
	{
		MemoryStack::Free(test[i]);
	}
	const double MemTime = timer.GetDeltaTimeInSeconds();

	delete[] test;

	std::cout << "MemoryAllocator: " << MemTime << " Sec" << std::endl;




	MemoryStack::Release();
	std::cin.get();
	return 0;
}

void MemoryAllocatorTest()
{
	DeltaTimer timer;

	double smart;
	double raw;

	timer.Init();
	std::unique_ptr<std::unique_ptr<TestStruct>[]> smartArray;
	smartArray = std::make_unique< std::unique_ptr<TestStruct>[] >(testSize);
	for (int i = 0; i < testSize; i++)
	{
		smartArray[i] = std::make_unique<TestStruct>();
	}
	smart = timer.GetDeltaTimeInSeconds();
	timeSmart.push_back(smart);

	timer.Init();
	TestStruct ** test = new TestStruct*[testSize];
	for (size_t i = 0; i < testSize; i++)
	{
		test[i] = new TestStruct();
	}
	raw = timer.GetDeltaTimeInSeconds();
	timeRaw.push_back(raw);

	

	for (size_t i = 0; i < testSize; i++)
	{
		delete test[i];
	}
	delete[] test;
	

}