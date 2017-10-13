#pragma once

#include "clgui/core/clgui_macro.h"
#include "clgui/core\clgui_variable.h"
#include "clgui/core/clgui_object.h"

CLGUI_NAMESPACE_START

class clguiMenu;

class CLGUI_API clguiMenuBar:public clguiContainer{
public:
  clguiMenuBar();

public:
  void AddChild(clguiMenu* menu);
  void RemoveChild(clguiMenu* menu);
  //bool BuildLayoutComponentsByJson(Json::Value json)override;


protected:
  clbool PreRender()override;
  void Render()override;

private:
  ~clguiMenuBar();

};

CLGUI_NAMESPACE_END