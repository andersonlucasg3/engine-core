#pragma once

#include "String/String.h"

#include "NSString.h"

extern CString NSStringToCString(NS::String* InString);

extern NS::String* CStringToNSString(const CString& InString);