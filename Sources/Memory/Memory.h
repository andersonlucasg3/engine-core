#pragma once

#include "Defines/Types.h"

using namespace Core::Types;

class CMemory
{
protected:
	CORE_API CMemory() = default;
	CORE_API virtual ~CMemory() = default;

public:
	CORE_API virtual void* Alloc(SizeT InSize) const = 0;
	CORE_API virtual void Free(void* InPtr) const = 0;
	CORE_API virtual void* Copy(const void* From, void* To, SizeT Size) const = 0;
	CORE_API virtual void* Set(void* Ptr, int Val, SizeT Size) const = 0;
	CORE_API virtual bool Equal(const void* Ptr1, SizeT Ptr1Size, const void* Ptr2, SizeT Ptr2Size) const = 0;

	template<typename TPtr>
	TPtr* Alloc()
	{
		return (TPtr*)Alloc(sizeof(TPtr));
	}
};

CORE_API extern const CMemory& GMemory;