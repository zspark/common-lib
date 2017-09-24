#pragma once

#include "imgui/imgui.h"
#include "core/clgui_macro.h"
#include "core\clgui_variable.h"
#include "core/clguiObject.h"

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