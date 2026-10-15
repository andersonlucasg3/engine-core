#include "AppleMemory.h"

#include <memory.h>
#include <cstdlib>

void* CAppleMemory::Alloc(SizeT InSize) const
{
	return malloc(InSize);
}

void CAppleMemory::Free(void* InPtr) const
{
	free(InPtr);
}

void* CAppleMemory::Copy(const void* From, void* To, SizeT Size) const
{
	return memcpy(To, From, Size);
}

void* CAppleMemory::Set(void* Ptr, int Val, SizeT Size) const
{
	return memset(Ptr, Val, Size);
}

bool CAppleMemory::Equal(const void* Ptr1, SizeT Ptr1Size, const void* Ptr2, SizeT Ptr2Size) const
{
	if (Ptr1Size != Ptr2Size) return false;

	return memcmp(Ptr1, Ptr2, Ptr1Size) == 0; // equal
}