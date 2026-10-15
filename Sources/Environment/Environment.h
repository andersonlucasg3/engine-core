#pragma once

class CEnvironment
{
public:
	CORE_API virtual ~CEnvironment() = default;

	CORE_API virtual const char* NewLine() const = 0;
};

extern const CEnvironment& GEnvironment;