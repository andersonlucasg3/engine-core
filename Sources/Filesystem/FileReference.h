#pragma once

#include "SmartPointer/SharedPointer.h"

#include "Filesystem/FilesystemReference.h"

class CFileReference;

struct SFileRef final : public TSharedPtr<CFileReference>
{
    using Super = TSharedPtr<CFileReference>;

    CORE_API SFileRef() = default;
    CORE_API SFileRef(const char* InCStr);
    CORE_API SFileRef(const CString& InPath);
    CORE_API SFileRef(const TArray<CString>& InComponents);
    CORE_API ~SFileRef() = default;

    CORE_API SFileRef& operator=(const char* InCStr);
    CORE_API SFileRef& operator=(const CString& InPath);
    CORE_API SFileRef& operator=(const TArray<CString>& InComponents);

private:
    void operator=(const TSharedPtr<CFileReference>& Other);
};

class CFileReference : public TFilesystemReference<CFileReference>
{
    using Super = TFilesystemReference<CFileReference>;

protected:
    CORE_API explicit CFileReference(const CString& InPath);
    CORE_API ~CFileReference() override = default;

public:
    CORE_API bool Delete() override;
};