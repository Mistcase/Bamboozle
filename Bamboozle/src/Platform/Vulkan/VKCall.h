#pragma once

#include "Bamboozle/Assert.h"

#define VK_CALL(call) call

//#define VK_CALL(call)\
//do\
//{\
//    const auto result = call;\
//	if (result != VK_SUCCESS)\
//    {\
//	    ASSERT_FAIL_NO_MSG();\
//    }\
//} while (false)
