#pragma once

#include "clgui/core/clgui_macro.h"
#include "clgui/core\clgui_variable.h"
#include "clgui/core/clgui_object.h"


CLGUI_NAMESPACE_START

class CLGUI_API clguiButton:public clguiComponent{
public:
clguiButton();

protected:
  ~clguiButton();
  void Render()override;
  void PostRender()override;

private:
  cvBool m_cv;
};

CLGUI_NAMESPACE_END