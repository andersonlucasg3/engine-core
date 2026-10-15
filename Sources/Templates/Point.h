#pragma once

#include "String/String.h"

template<typename TElement>
struct TPoint
{
	TElement X;
	TElement Y;

	TPoint() :
		X(), 
		Y()
	{

	}

	TPoint(TElement X, TElement Y) :
		X(X), 
		Y(Y)
	{

	}

	virtual ~TPoint() = default;

	bool operator==(const TPoint& Other)
	{
		return	X == Other.X &&
				Y == Other.Y;
	}

	CString ToString() const
	{
		return CString("{{ X: {}, Y: {} }}", X, Y);
	}
};