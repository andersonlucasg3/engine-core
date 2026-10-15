#pragma once

#include "Filesystem/FilesystemReference.h"

#include "FileReference.h"

class CDirectoryReference;

struct SDirectoryRef final : public TSharedPtr<CDirectoryReference>
{
    using Super = TSharedPtr<CDirectoryReference>;

    CORE_API SDirectoryRef() = default;
    CORE_API SDirectoryRef(const char* InCStr);
    CORE_API SDirectoryRef(const CString& InPath);
    CORE_API SDirectoryRef(const TArray<CString>& InComponents);
    CORE_API ~SDirectoryRef() = default;

    CORE_API SDirectoryRef& operator=(const char* InCStr);
    CORE_API SDirectoryRef& operator=(const CString& InPath);
    CORE_API SDirectoryRef& operator=(const TArray<CString>& InComponents);

private:
    void operator=(const TSharedPtr<CDirectoryReference>& Other);
};

class CDirectoryReference : public TFilesystemReference<CDirectoryReference>
{
    using Super = TFilesystemReference<CDirectoryReference>;

protected:
    CORE_API explicit CDirectoryReference(const CString& InPath) : Super(InPath) { }
    CORE_API ~CDirectoryReference() override = default;

public:
    CORE_API virtual bool Create(bool InCreateIntermediates = false);
    CORE_API virtual bool Delete() override;

    CORE_API virtual SDirectoryRef Combine(const CString& InComponent) const;
    CORE_API virtual SDirectoryRef Combine(const TArray<CString>& InComponents) const;
    CORE_API virtual SFileRef CombineFile(const CString& InFilename) const;
    CORE_API virtual SFileRef CombineFile(const TArray<CString>& InComponents) const;
};