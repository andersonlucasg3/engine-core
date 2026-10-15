#pragma once

#include "Process/Desktop/DesktopProcess.h"

#include "Templates/Array.h"

#include "String/String.h"

class CMacProcess : public CDesktopProcess
{
    CString ExecutablePath;
    CString ExecutableContainerPath;
    TArray<CString> CommandLineArgs;
    
public:
    CORE_API CMacProcess() = default;
    CORE_API ~CMacProcess() override = default;

    CORE_API void SetCommandLine(int argc, char* argv[]) override;
    CORE_API const CString& GetExecutablePath() const override;
    CORE_API const CString& GetContainerPath() const override;
    CORE_API const TArray<CString>& GetCommandLineArgs() const override;
    
    CORE_API bool IsRunningInsideAppBundle() const;
};

typedef CMacProcess CPlatformProcess;

extern const CMacProcess& GAppleProcess;