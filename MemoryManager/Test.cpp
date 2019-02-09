#include <iostream>
#include "MemoryStack.h"

#include "DeltaTimer.h"

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

int main()
{
	const size_t testSize = 0xfffffff;
	MemoryStack::Init(testSize * sizeof(TestStruct));
	SetDbgFlag();


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
	delete[] test;

	test = new TestStruct*[testSize];
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