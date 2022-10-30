#pragma once

#ifdef BUBBLE_PLATFORM_WINDOWS
	#ifdef BUBBLE_BUILD_DLL
		#define BUBBLE_API __declspec(dllexport)
	#else
		#define BUBBLE_API __declspec(dllimport)
	#endif
#else
	#error Build platform is not supported!
#endif