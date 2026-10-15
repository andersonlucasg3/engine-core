#include "Process.h"

#include "Logger/Logger.h"

#include <exception>

CProcess::CProcess()
{
    std::set_terminate([] 
    {
        GLogger.LogException();
    });
}