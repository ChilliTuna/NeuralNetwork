#pragma once

#ifdef DLL_EXPORT
	#define API __declspec(dllexport)
#else
	#define API __declspec(dllimport)
#endif // DLL_EXPORT