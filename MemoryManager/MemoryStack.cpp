#include "MemoryStack.h"
#include <iostream>

size_t MemoryStack::m_allocatorOffset = 0;
size_t MemoryStack::m_heapSize = 0;

void MemoryStack::Init(const size_t & size)
{
	m_heapSize = size;
	MemoryAllocator::Init(size);
}


void MemoryStack::Release()
{
	MemoryAllocator::Release();
}

bool MemoryStack::SafeData(void* address, const size_t& size)
{
	if (reinterpret_cast<char*>(address) + size >
		reinterpret_cast<char*>(MemoryAllocator::Data) + m_heapSize)
		return false;

	const char value = *reinterpret_cast<char *>(address);
	for (unsigned int i = 0; i < size; i++)
	{
		if ((value >> i & 1))
			return false;
	}
	return true;
}



