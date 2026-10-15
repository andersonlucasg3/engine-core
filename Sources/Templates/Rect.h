#pragma once

#include "String/String.h"
#include "Point.h"
#include "Size.h"

template<
	typename TElement,
	typename TPoint = TPoint<TElement>,
	typename TSize = TSize<TElement>
>
struct TRect
{
	TPoint Origin;
	TSize Size;

	TRect() :
		Origin(), 
		Size()
	{

	}

	TRect(const TPoint& Origin, const TSize& Size) :
		Origin(Origin), 
		Size(Size)
	{

	}

	TRect(TElement X, TElement Y, TElement Width, TElement Height) :
		Origin(X, Y), 
		Size(Width, Height)
	{

	}

	TElement X() const
	{
		return Origin.X;
	}

	TElement Y() const
	{
		return Origin.Y;
	}

	TElement Width() const
	{
		return Size.Width;
	}

	TElement Height() const
	{
		return Size.Height;
	}

	bool operator==(const TRect& Other)
	{
		return	Origin == Other.Origin &&
				Size == Other.Size;
	}

	CString ToString() const
	{
		return CString("{{ Origin: {}, Size: {} }}", *Origin.ToString(), *Size.ToString());
	}
};