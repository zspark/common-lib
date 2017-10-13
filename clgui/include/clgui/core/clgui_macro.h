#pragma once

#define GLFW_DLL
#include "GLFW\glfw3.h"
#undef GLFW_DLL

#ifdef CLGUI_API_IMPORTS
#define CLGUI_API __declspec(dllimport)
#else
#define CLGUI_API __declspec(dllexport)
#endif

#define DEPRECATED

#define CLGUI_NAMESPACE_START namespace clgui{
#define CLGUI_NAMESPACE_END }

#define M_1_255 (1.0f/255.0f)

#if __CLGUI_DEBUG__
#include <iostream>
#endif
