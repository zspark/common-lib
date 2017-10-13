#pragma once

#ifdef DLL_VERSION
#ifdef CL3DM_API_IMPORTS
#define CL3DM_API __declspec(dllimport)
#else
#define CL3DM_API __declspec(dllexport)
#endif
#else
#define CL3DM_API
#endif

#define CL3DM_NAMESPACE_START namespace cl3dm{
#define CL3DM_NAMESPACE_END }

#if __CL3DM_INTERNAL_DEBUG__
#include <iostream>
#endif
