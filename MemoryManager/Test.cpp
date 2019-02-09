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
	const size_t testSize = 65536;
	SetDbgFlag();

	MemoryStack::Init();

	DeltaTimer timer;

	timer.Init();

	for (size_t i = 0; i < testSize; i++)
	{
		TestStruct * Test = new TestStruct();
		delete Test;
	}

	double time = timer.GetDeltaTimeInSeconds();

	std::cout << "Standard: " << time << std::endl;

	timer.Init();
	for (size_t i = 0; i < testSize; i++)
	{
		TestStruct * Test = nullptr;
		Test = MemoryStack::AllocData<TestStruct>();
	}

	time = timer.GetDeltaTimeInSeconds();

	std::cout << "MemoryAllocator: " << time << std::endl;

	MemoryStack::Release();

	std::cin.get();
	return 0;
}