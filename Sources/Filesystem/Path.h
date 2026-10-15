#pragma once

#include "String/String.h"

class CPath 
{
public:
    CORE_API virtual ~CPath() = default;

    CORE_API virtual char PathSeparator() const = 0;

    CORE_API virtual CString GetFullPath(const CString& InPath) const = 0;
    CORE_API virtual CString GetPathRoot(const CString& InPath) const = 0;

    CORE_API virtual CString Combine(const TArray<CString>& PathComponents) const;

    CORE_API virtual CString LastPathComponent(const CString& Path) const;
    CORE_API virtual CString RemoveLastPathComponent(const CString& Path) const;
    
    CORE_API virtual const CString& CachesPath() const = 0;
};

CORE_API extern const CPath& GPath;