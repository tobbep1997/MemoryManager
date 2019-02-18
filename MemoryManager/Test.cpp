#include <iostream>
#include "MemoryStack.h"

#include "DeltaTimer.h"
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
};

void RawPointerTest(std::vector<double> * allocTime, std::vector<double> * readTime, std::vector<double> * randomAccess, const unsigned int & testSize, const unsigned int & randomSeed);
void PreHeapPointerTest(std::vector<double> * allocTime, std::vector<double> * readTime, std::vector<double> * randomAccess, const unsigned int & testSize, const unsigned int & randomSeed);
void TestTestStruct(TestStruct* test);

int main(int commands, char * arr[])
{
	std::vector<double> alloc;
	std::vector<double> read;
	std::vector<double> random;

	int size = 1024;
	if (commands > 1)
	size = std::atoi(arr[1]);

	RawPointerTest(&alloc, &read, &random, size, 420);
	OutputClass::Output("Raw.txt", alloc, read, random);

	alloc.clear();
	read.clear();
	random.clear();

	PreHeapPointerTest(&alloc, &read, &random, size, 420);
	OutputClass::Output("PreAlloc.txt", alloc, read, random);
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
void PreHeapPointerTest(std::vector<double> * allocTime, std::vector<double> * readTime, std::vector<double> * randomAccess, const unsigned int & testSize, const unsigned int & randomSeed)
{
	srand(randomSeed);
	TestStruct ** allocTest = new TestStruct*[testSize];

	DeltaTimer timer;

	MemoryStack::Init(sizeof(TestStruct) * testSize);
	for (size_t i = 0; i < testSize; i++)
	{

		timer.Init();
		allocTest[i] = MemoryStack::AllocData<TestStruct>();

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
	   
	delete[] allocTest;
	MemoryStack::Release();
	
}

void TestTestStruct(TestStruct* test)
{
	float x = test->x;
	float y = test->y;
	float z = test->z;
	float w = test->w;
}
