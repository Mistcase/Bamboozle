#pragma once

#include "Bamboozle/Assert.h"

#define VK_CALL(call)\
do\
{\
	if (call != VK_SUCCESS)\
    {\
	    ASSERT_FAIL_NO_MSG();\
    }\
} while (false)
