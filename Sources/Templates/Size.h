#pragma once

#include "String/String.h"
#include "Defines/Types.h"

template<typename TElement>
struct TSize
{
	TElement Width;
	TElement Height;

	TSize() :
		Width(), 
		Height()
	{

	}

	TSize(TElement Width, TElement Height) :
		Width(Width), 
		Height(Height)
	{

	}

	virtual ~TSize() = default;

	bool operator==(const TSize& Other)
	{
		return	Width == Other.Width &&
				Height == Other.Height;
	}

	CString ToString() const
	{
		return CString("{{ Width: {}, Height: {} }}", Width, Height);
	}
};