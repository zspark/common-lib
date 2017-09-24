#pragma once

#include "imgui.h"
#include "clgui_macro.h"
#include "clguiComponentVariable.h";
#include "clguiObject.h"

CLGUI_NAMESPACE_START

class clguiComponent;

CLGUI_API
class clguiButton:public clguiComponent{
public:
  clguiButton();
  clguiButton(const clguiButton& btn);
  ~clguiButton();

public:
  void SetCaption(clstr caption);

protected:
  void Render()override;
  void PostRender()override;

private:
  cvBool m_cv;
  clstr m_caption="BUTTON";
};

CLGUI_NAMESPACE_END