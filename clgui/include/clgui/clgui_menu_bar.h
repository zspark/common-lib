#pragma once

#include "core/clgui_macro.h"
#include "core\clgui_variable.h"
#include "core/clgui_object.h"

CLGUI_NAMESPACE_START

class CLGUI_API clguiMenuBar:public clguiContainer{
public:
  clguiMenuBar();

public:
  void AddChild(clguiComponent* menu)override;
  void RemoveChild(clguiComponent* menu)override;
  void SetSize(clint width,clint height)override{ throw "Menubar can't set custom size at the moment!"; };
  //bool BuildLayoutComponentsByJson(Json::Value json)override;


protected:
  clbool PreRender()override;
  void Render()override;
  void PostRender()override;

private:
  ~clguiMenuBar();

};

CLGUI_NAMESPACE_END