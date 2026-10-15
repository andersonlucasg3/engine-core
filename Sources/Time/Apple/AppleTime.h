#pragma once

#include "Time/Time.h"

class CAppleTime : public CTime
{
public:
    CORE_API ~CAppleTime() override = default;
    CORE_API Double GetTimeInSeconds() const override;
};

typedef CAppleTime CPlatformTime;