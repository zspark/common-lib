#pragma once

#include "clgui/core/clgui_macro.h"
#include "clgui/core\clgui_variable.h"
#include "clgui/core/clgui_object.h"


CLGUI_NAMESPACE_START

class CLGUI_API clguiToolTip:public clguiComponent{
public:
clguiToolTip();
void SetMark(clstr mark);
void SetDescription(clstr des);

protected:
  ~clguiToolTip();
  void Render()override;

private:
  clstr m_toolTipMark="(?)";
  clstr m_toolTipDescription="<NOT SETTED>";
};

CLGUI_NAMESPACE_END