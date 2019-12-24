#pragma once
#ifdef LV_BUILD_DLL
	#define LV_API __declspec(dllexport)
#else
	#define LV_API __declspec(dllimport)
#endif
