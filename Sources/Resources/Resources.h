#pragma once

#include "Filesystem/FileReference.h"

class CResources
{
public:
	CORE_API virtual ~CResources() = default;
	CORE_API virtual SFileRef GetResource(const CString& InResourceName) const = 0;
};

extern const CResources& GResources;