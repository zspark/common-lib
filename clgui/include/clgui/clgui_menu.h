#pragma once

#include "core/clgui_macro.h"
#include "core\clgui_variable.h"
#include "core/clgui_object.h"

CLGUI_NAMESPACE_START

class CLGUI_API clguiMenu:public clguiContainer{
public:
  clguiMenu();
  clguiMenu(const clguiMenu&)=delete;
  clguiMenu& operator=(const clguiMenu&)=delete;

public:
  //clguiObject* clguiMenu::GetMenuItem(uint index);

protected:
  clbool PreRender()override;
  void Render()override;
  void PostRender()override;

private:
  ~clguiMenu();


};


CLGUI_NAMESPACE_END