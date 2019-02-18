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
void SmartPointerTest(std::vector<double> * allocTime, std::vector<double> * readTime, std::vector<double> * randomAccess, const unsigned int & testSize, const unsigned int & randomSeed);
void PreHeapPointerTest(std::vector<double> * allocTime, std::vector<double> * readTime, std::vector<double> * randomAccess, const unsigned int & testSize, const unsigned int & randomSeed);

void LinkedRawPointerTest(std::vector<double> * allocTime, std::vector<double> * readTime, std::vector<double> * randomAccess, const unsigned int & testSize, const unsigned int & randomSeed);
void LinkedSmartPointerTest(std::vector<double> * allocTime, std::vector<double> * readTime, std::vector<double> * randomAccess, const unsigned int & testSize, const unsigned int & randomSeed);

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

	RawPointerTest(&alloc, &read, &random, size, 420);
	OutputClass::Output("Smart.txt", alloc, read, random);

	alloc.clear();
	read.clear();
	random.clear();

	PreHeapPointerTest(&alloc, &read, &random, size, 420);
	OutputClass::Output("PreAlloc.txt", alloc, read, random);

	alloc.clear();
	read.clear();
	random.clear();
	
	LinkedRawPointerTest(&alloc, &read, &random, size, 420);
	OutputClass::Output("RawLinkedList.txt", alloc, read, random);

	//alloc.clear();
	//read.clear();
	//random.clear();

	//LinkedSmartPointerTest(&alloc, &read, &random, size, 420);
	//OutputClass::Output("SmartLinkedList.txt", alloc, read, random);

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
void SmartPointerTest(std::vector<double> * allocTime, std::vector<double> * readTime, std::vector<double> * randomAccess, const unsigned int & testSize, const unsigned int & randomSeed)
{
	srand(randomSeed);
	std::unique_ptr<std::unique_ptr<TestStruct>[]> allocTest = std::make_unique< std::unique_ptr<TestStruct>[] >(testSize);

	DeltaTimer timer;

	for (size_t i = 0; i < testSize; i++)
	{
		timer.Init();

		allocTest[i] = std::make_unique<TestStruct>();

		const double t = timer.GetDeltaTimeInSeconds();
		allocTime->push_back(t);
	}

	for (size_t i = 0; i < testSize; i++)
	{
		timer.Init();
		
		TestStruct * tmp = allocTest[i].get();
		TestTestStruct(tmp);

		const double t = timer.GetDeltaTimeInSeconds();
		readTime->push_back(t);
	}

	for (size_t i = 0; i < testSize; i++)
	{
		timer.Init();

		TestStruct * tmp = allocTest[rand() % testSize].get();
		TestTestStruct(tmp);

		const double t = timer.GetDeltaTimeInSeconds();
		randomAccess->push_back(t);
	}
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

void LinkedRawPointerTest(std::vector<double>* allocTime, std::vector<double>* readTime,
	std::vector<double>* randomAccess, const unsigned& testSize, const unsigned& randomSeed)
{
	srand(randomSeed);

	LinkedListRaw<TestStruct*> allocTest;

	DeltaTimer timer;

	for (size_t i = 0; i < testSize; i++)
	{
		timer.Init();

		allocTest.Insert(new TestStruct());

		const double t = timer.GetDeltaTimeInSeconds();
		allocTime->push_back(t);
	}

	for (size_t i = 0; i < testSize; i++)
	{
		timer.Init();

		TestStruct * tmp = allocTest.GetAt(i);
		TestTestStruct(tmp);

		const double t = timer.GetDeltaTimeInSeconds();
		readTime->push_back(t);
	}

	for (size_t i = 0; i < testSize; i++)
	{
		timer.Init();

		TestStruct * tmp = allocTest.GetAt(rand() % testSize);
		TestTestStruct(tmp);

		const double t = timer.GetDeltaTimeInSeconds();
		randomAccess->push_back(t);
	}

	for (size_t i = 0; i < testSize; i++)
	{
		delete allocTest.GetAt(i);
	}


}
void LinkedSmartPointerTest(std::vector<double>* allocTime, std::vector<double>* readTime,
	std::vector<double>* randomAccess, const unsigned& testSize, const unsigned& randomSeed)
{
	
}

void TestTestStruct(TestStruct* test)
{
	float x = test->x;
	float y = test->y;
	float z = test->z;
	float w = test->w;
}
