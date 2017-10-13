#pragma once

#include "clgui/core/clgui_macro.h"
#include "clgui/core\clgui_variable.h"
#include "clgui/core/clgui_object.h"

CLGUI_NAMESPACE_START

class CLGUI_API clguiLabel:public clguiComponent{
public:
  clguiLabel(cluint maxCharCount);

public:

  void SetValue(clstr fmt,...);
  clstr GetValue()const;

protected:
  ~clguiLabel();
  void Render();

private:
  clchar* m_value=nullptr;
  cluint m_maxCharCount;
};

CLGUI_NAMESPACE_END