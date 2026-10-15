#include "AppleDirectoryReference.h"

#include "String/String.h"
#include "String/Apple/AppleStringConvertion.h"

#include "Filesystem/DirectoryReference.h"

#include "NSSharedPtr.hpp"
#include "NSFileManager.h"

#include <sys/_types/_filesec_t.h>

void CAppleDirectoryReference::UpdateExistance() 
{
    _bExists = NS::FileManager::defaultManager()->fileExistsAtPath(PathString());
}

CAppleDirectoryReference::CAppleDirectoryReference(const CString& InPath) : Super(InPath)
{
    _directoryURL = NS::RetainPtr(NS::URL::fileURLWithPath(CStringToNSString(_path)));

    UpdateExistance();
}

bool CAppleDirectoryReference::Create(bool InCreateIntermediates)
{
    NS::Error* Error = nullptr;
    if (!NS::FileManager::defaultManager()->createDirectoryAtURL(_directoryURL.get(), InCreateIntermediates, nullptr, &Error))
    {
        GLogger.Error("CAppleDirectoryReference::Create(InCreateIntermediates: {}) - Failed to create directory {}", 
            InCreateIntermediates, Error->debugDescription()->utf8String());
        return false;
    }

    UpdateExistance();
    return true;
}

bool CAppleDirectoryReference::Delete()
{
    NS::Error* Error = nullptr;
    if (!NS::FileManager::defaultManager()->removeItemAtURL(_directoryURL.get(), &Error))
    {
        GLogger.Error("CAppleDirectoryReference::Delete() - Failed to delete directory: {}", Error->debugDescription()->utf8String());
        return false;
    }

    UpdateExistance();
    return true;
}

NS::String* CAppleDirectoryReference::PathString() const
{
    return _directoryURL->path();
}

NS::URL* CAppleDirectoryReference::PathURL() const
{
    return _directoryURL.get();
}