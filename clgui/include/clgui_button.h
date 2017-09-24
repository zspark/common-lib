#pragma once

#include "imgui.h"
#include "clgui_macro.h"
#include "clguiComponentVariable.h";
#include "clguiObject.h"

CLGUI_NAMESPACE_START

class clguiComponent;

CLGUI_API class clguiButton:public clguiComponent{
public:
  clguiButton();
  clguiButton(const clguiButton& btn);
  ~clguiButton();

public:
  void SetCaption(clstr caption);
  void SetSize(cluint width,cluint height);

protected:
  void Render()override;
  void PostRender()override;

private:
  cvBool m_cv;
  clstr m_caption="BUTTON";
  ImVec2 m_size;
};

CLGUI_NAMESPACE_END