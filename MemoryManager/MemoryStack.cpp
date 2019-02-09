#include "MemoryStack.h"

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
	char* addressStartPoint = reinterpret_cast<char*>(address);
	for (char* i = addressStartPoint; i < addressStartPoint + size; i += ALIGNMENT)
	{
		const unsigned ad = reinterpret_cast<unsigned>(i);
		if (ad)
			return false;
	}
	return true;
}



