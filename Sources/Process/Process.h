#pragma once

#include "Templates/Array.h"

#include "String/String.h"

class CProcess
{
protected:
    CORE_API CProcess();

public:
    CORE_API virtual ~CProcess() = default;

    CORE_API virtual void SetCommandLine(int argc, char* argv[]) = 0;
    CORE_API virtual const TArray<CString>& GetCommandLineArgs() const = 0;

    CORE_API virtual const CString& GetContainerPath() const = 0;
};

CORE_API extern CProcess& GProcess;