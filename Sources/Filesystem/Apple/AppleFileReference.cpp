#include "AppleFileReference.h"

#include "String/Apple/AppleStringConvertion.h"

#include "NSFileManager.h"

void CAppleFileReference::UpdateExistance()
{
    _bExists = NS::FileManager::defaultManager()->fileExistsAtPath(PathString());
}

CAppleFileReference::CAppleFileReference(const CString& InPath) : Super(InPath)
{
    _fileURL = NS::RetainPtr(NS::URL::fileURLWithPath(CStringToNSString(_path)));
    UpdateExistance();
}

NS::String* CAppleFileReference::PathString() const
{
    return _fileURL->path();
}

NS::URL* CAppleFileReference::PathURL() const
{
    return _fileURL.get();
}