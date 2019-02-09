#pragma once
#include "MemoryAllocator.h"


class MemoryStack
{
public:
	static void Init(const size_t & size = 65536);
	static void Release();

	template <typename T>
	static T* AllocData();

	template <typename T>
	static void Free(T* ptr);

	static bool SafeData(void * address, const size_t & size);

private:
	static size_t m_allocatorOffset;
	static size_t m_heapSize;

};

template <typename T>
T* MemoryStack::AllocData()
{
	const size_t alignedSize = (sizeof(T) + ALIGNMENT) & ~ALIGNMENT;

	void * returnAddress = reinterpret_cast<char*>(MemoryAllocator::Data) + m_allocatorOffset;
	if (SafeData(returnAddress, alignedSize))
	{
		m_allocatorOffset = (m_allocatorOffset + alignedSize) % m_heapSize;
		return reinterpret_cast<T*>(returnAddress);
	}

	return nullptr;
}

template <typename T>
void MemoryStack::Free(T* ptr)
{
	ZeroMemory(ptr, sizeof(T));
}

