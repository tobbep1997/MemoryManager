#pragma once

#define ALIGNMENT sizeof(nullptr)

class MemoryAllocator
{
public:

	static void * Data;

	static void Init(const size_t & size = 65536);
	static void Release();

};

