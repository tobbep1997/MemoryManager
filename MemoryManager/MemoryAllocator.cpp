#include "MemoryAllocator.h"
#include <cstdlib>


void * MemoryAllocator::Data = nullptr;

void MemoryAllocator::Init(const size_t& size)
{
	if (Data)
		Release();
	
	Data = _aligned_malloc(size, ALIGNMENT);
}

void MemoryAllocator::Release()
{
	_aligned_free(Data);
}

