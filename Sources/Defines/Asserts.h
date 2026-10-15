#pragma once

#include "Logger/Logger.h"

#define assertm(a, message) 																\
	if (!(a)) 																				\
	{																						\
		GLogger.Fatal("Error at file: {}:{}\n{}: {}", __FILE__, __LINE__, message, #a);	\
	}

#ifndef assert
#define assert(a) assertm(a, "failed to evaluate expression")
#endif // assert

#define assert_equal(a, b) assertm(a == b, *CString("{}", __FUNCTION__))
#define assert_lesser(a, b)	assertm(a < b, *CString("{}", __FUNCTION__))
#define assert_greater(a, b) assertm(a > b, *CString("{}", __FUNCTION__))