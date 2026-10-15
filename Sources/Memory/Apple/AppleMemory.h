#pragma once

#include "Memory/Memory.h"

class CAppleMemory : public CMemory
{
public:
    CAppleMemory() = default;
    ~CAppleMemory() override = default;

    CORE_API void* Alloc(SizeT InSize) const override;
	CORE_API void Free(void* InPtr) const override;
	CORE_API void* Copy(const void* From, void* To, SizeT Size) const override;
	CORE_API void* Set(void* Ptr, int Val, SizeT Size) const override;
	CORE_API bool Equal(const void* Ptr1, SizeT Ptr1Size, const void* Ptr2, SizeT Ptr2Size) const override;
};

typedef CAppleMemory CPlatformMemory;