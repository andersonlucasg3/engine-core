#pragma once

#include "Deleter.h"

#include "Defines/Types.h"

using namespace Core::Types;

struct SRefCounter final
{
	inline SRefCounter() :
		_refCount(0),
		_weakCount(0)
	{
		//
	}

	inline ~SRefCounter() = default;

	inline UInt32 RefCount()
	{
		return _refCount;
	}

	inline UInt32 WeakCount()
	{
		return _weakCount;
	}

	inline bool IsValid()
	{
		return _refCount > 0;
	}

	inline bool IsPendingDelete()
	{
		return _refCount == 0 && _weakCount == 0;
	}

	inline SRefCounter* RetainStrong()
	{ 
		++_refCount;

		return this;
	}

	inline void ReleaseStrong()
	{
		--_refCount;
	}

	inline SRefCounter* RetainWeak()
	{
		++_weakCount;

		return this;
	}

	inline void ReleaseWeak()
	{
		--_weakCount;
	}

private:
	UInt32 _refCount;
	UInt32 _weakCount;
};