#pragma once

#include "Process/Process.h"

class CDesktopProcess : public CProcess
{
    using Super = CProcess;

protected:
    CORE_API CDesktopProcess() = default;

public:
    CORE_API virtual ~CDesktopProcess() override = default;

    CORE_API virtual const CString& GetExecutablePath() const = 0;
};

CORE_API extern CDesktopProcess& GDesktopProcess;