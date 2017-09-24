#pragma once
#include "core/clgui_macro.h"
#include "core/clgui_variable.h"
#include "core/clguiObject.h"

CLGUI_NAMESPACE_START

CLGUI_API
class clguiWindow:public clguiContainer{

public:
  clguiWindow();
  virtual ~clguiWindow();

public:
  void SetCaption(clstr caption);
  //bool BuildLayoutComponentsByJson(Json::Value json)override;

protected:
  void Render()override;
  void PostRender()override;

private:
  cvBool m_clVarBool;
  clstr m_caption="WINDOW";
};

CLGUI_NAMESPACE_END
