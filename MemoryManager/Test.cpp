#include <iostream>
#include <memory>
#include "MemoryStack.h"

#include "DeltaTimer.h"
#include <vector>
#include <thread>
#include "LinkedList.h"
#include "OutputClass.h"
#include <cstdlib>
#include <string>

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

void RawPointerTest(std::vector<double> * allocTime, std::vector<double> * readTime, std::vector<double> * randomAccess, const unsigned int & testSize, const unsigned int & randomSeed);
void TestTestStruct(TestStruct* test);

int main(int commands, char * arr[])
{
	if (commands <= 1)
	{
		int commands = 3;
		const char * arr[] = { "test", "2", "output.txt" };

		std::vector<double> alloc;
		std::vector<double> read;
		std::vector<double> random;

		const int size = std::atoi(arr[1]);
		RawPointerTest(&alloc, &read, &random, size, 420);

		OutputClass::Output(arr[2], alloc, read, random);
	}
	else
	{
		std::vector<double> alloc;
		std::vector<double> read;
		std::vector<double> random;

		const int size = std::atoi(arr[1]);
		RawPointerTest(&alloc, &read, &random, size, 420);

		OutputClass::Output(arr[2], alloc, read, random);
	}
	

	
}

void RawPointerTest(std::vector<double> * allocTime, std::vector<double> * readTime, std::vector<double> * randomAccess, const unsigned int & testSize, const unsigned int & randomSeed)
{
	srand(randomSeed);
	TestStruct ** allocTest = new TestStruct*[testSize];

	DeltaTimer timer;
	
	for (size_t i = 0; i < testSize; i++)
	{
		timer.Init();

		allocTest[i] = new TestStruct();

		const double t = timer.GetDeltaTimeInSeconds();
		allocTime->push_back(t);
	}

	for (size_t i = 0; i < testSize; i++)
	{
		timer.Init();

		TestStruct * tmp = allocTest[i];
		TestTestStruct(tmp);

		const double t = timer.GetDeltaTimeInSeconds();
		readTime->push_back(t);
	}

	for (size_t i = 0; i < testSize; i++)
	{
		timer.Init();

		TestStruct * tmp = allocTest[rand() % testSize];
		TestTestStruct(tmp);

		const double t = timer.GetDeltaTimeInSeconds();
		randomAccess->push_back(t);
	}

	for (size_t i = 0; i < testSize; i++)
	{
		delete allocTest[i];
	}

	delete[] allocTest;
}

void TestTestStruct(TestStruct* test)
{
	float x = test->x;
	float y = test->y;
	float z = test->z;
	float w = test->w;
}


//int main(int commands, char * arr[])
//{
//	const size_t testSize = 0xfffffff;
//	SetDbgFlag();
//
//
//	DeltaTimer timer;
//
//	std::cout << "Default Alloc " << testSize << " Objects " << " Start" << std::endl;
//
//	TestStruct ** test = new TestStruct*[testSize];
//
//
//	timer.Init();
//	for (size_t i = 0; i < testSize; i++)
//	{
//		test[i] = new TestStruct();
//	}
//	for (size_t i = 0; i < testSize; i++)
//	{
//		delete test[i];
//	}
//
//	const double DefaultTime = timer.GetDeltaTimeInSeconds();
//	
//	std::cout << "Default: " << DefaultTime << " Sec" << std::endl;
//
//	std::cout << "Pre Alloc " << testSize << " Objects " << " Start" << std::endl;
//
//	MemoryStack::Init(testSize * sizeof(TestStruct));
//
//	timer.Init();
//	for (size_t i = 0; i < testSize; i++)
//	{
//		test[i] = MemoryStack::AllocData<TestStruct>();
//		test[i]->x = static_cast<float>(i);
//		test[i]->y = static_cast<float>(i);
//		test[i]->z = static_cast<float>(i);
//		test[i]->w = static_cast<float>(i);
//	}
//	for (size_t i = 0; i < testSize; i++)
//	{
//		MemoryStack::Free(test[i]);
//	}
//	const double MemTime = timer.GetDeltaTimeInSeconds();
//
//	delete[] test;
//
//	std::cout << "MemoryAllocator: " << MemTime << " Sec" << std::endl;
//	MemoryStack::Release();
//	std::cin.get();
//	return 0;
//}