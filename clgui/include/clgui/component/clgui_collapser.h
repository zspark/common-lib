#pragma once

#include "clgui/core/clgui_macro.h"
#include "clgui/core\clgui_variable.h"
#include "clgui/core/clgui_object.h"


CLGUI_NAMESPACE_START

class CLGUI_API clguiCollapser:public clguiContainer{
public:
clguiCollapser();
void EnableCollapsingEvent();
clbool DisableCollapsingEvent()const{ return m_bCollapsingEventEnabled; }

protected:
  ~clguiCollapser();
  clbool PreRender()override;
  void Render()override;
  void PostRender()override;

private:
  cvBool m_cv;
  clbool m_bCollapsingEventEnabled=false;
};

CLGUI_NAMESPACE_END