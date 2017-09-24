#pragma once
#include "GLFW\glfw3.h"
#include "cl_types.h"
#include "core/clgui_macro.h"

CLGUI_NAMESPACE_START

class clguiComponent;

CLGUI_API void clguiInit(GLFWwindow* wnd);
CLGUI_API void clguiExec();
CLGUI_API void clguiExit();
CLGUI_API void clguiAddToStage(clguiComponent* com);
CLGUI_API void clguiRemoveFromStage(clguiComponent* com);
CLGUI_API void clguiSetStageColor(cluint r,cluint g,cluint b);

CLGUI_NAMESPACE_END

