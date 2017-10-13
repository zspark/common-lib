#pragma once

#include "cl/cl_types.h"
#include "core/clgui_macro.h"

CLGUI_NAMESPACE_START

class clguiObject;
class clguiComponent;
class clguiStage;
class clguiMenuBar;
class clguiMenu;
class clguiMenuItem;

CLGUI_API void clguiInit(GLFWwindow* wnd);
CLGUI_API void clguiExec();
CLGUI_API void clguiExit();
CLGUI_API void clguiAddToStage(clguiComponent* com);
CLGUI_API void clguiRemoveFromStage(clguiComponent* com);
DEPRECATED CLGUI_API void clguiDeleteObject(clguiObject* obj,clbool withChildren=false);
CLGUI_API void clguiDeleteObject(cluint objID,clbool withChildren=false);
CLGUI_API void clguiDeleteChildren(clguiObject* obj);
CLGUI_API clguiStage* clguiGetStage();


CLGUI_API clguiMenuBar* clguiConverToMenuBar(clguiObject* obj);
CLGUI_API clguiMenu* clguiConverToMenu(clguiObject* obj);
CLGUI_API clguiMenuItem* clguiConverToMenuItem(clguiObject* obj);

CLGUI_NAMESPACE_END

