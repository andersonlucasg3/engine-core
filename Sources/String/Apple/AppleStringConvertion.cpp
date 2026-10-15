#include "AppleStringConvertion.h"

CString NSStringToCString(NS::String* InString)
{
    return CString(InString->utf8String(), InString->length());
}

NS::String* CStringToNSString(const CString& InString)
{
    return NS::String::string(*InString, NS::UTF8StringEncoding);
}
