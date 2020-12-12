#pragma once

#ifdef NC_PLATFORM_WINDOWS
	#ifdef NC_BUILD_DLL
		#define NUTCRACKER_API _declspec(dllexport)
	#else
		#define NUTCRACKER_API _declspec(dllimport)
	#endif

#else
	#error Hazel only support Windows!
#endif