#include "AppleTime.h"

#include <mach/mach_time.h> 

CORE_API Double CAppleTime::GetTimeInSeconds() const
{
    UInt64 timeBase = mach_absolute_time();
    mach_timebase_info_data_t timebaseInfo;
    mach_timebase_info(&timebaseInfo);
    UInt64 nanoseconds = timeBase * timebaseInfo.numer / timebaseInfo.denom;
    Double seconds = static_cast<Double>(nanoseconds) / 1e9;
    return seconds;
}