#pragma once

#include "core/clgui_macro.h"
#include "core\clgui_variable.h"
#include "core/clgui_object.h"


CLGUI_NAMESPACE_START

class CLGUI_API clguiCheckBox:public clguiComponent{
public:
  clguiCheckBox(clbool selected=false);

protected:
  void Render()override;
  void PostRender()override;

public:
  void SetSelection(clbool v);
  clbool GetSelection()const;

protected:
  ~clguiCheckBox();

private:
  cvBool m_cv;
};

CLGUI_NAMESPACE_END