#pragma once

#include "Defines/Types.h"

using namespace Core::Types;

class CTime
{
public:
	CORE_API virtual ~CTime() = default;

	CORE_API virtual Double GetTimeInSeconds() const = 0;
};

extern const CTime& GTime;
