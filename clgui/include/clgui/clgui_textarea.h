#pragma once

#include "core/clgui_macro.h"
#include "core\clgui_variable.h"
#include "core/clgui_object.h"

CLGUI_NAMESPACE_START

class CLGUI_API clguiTextArea:public clguiComponent{
public:
  clguiTextArea();

public:

  void SetCaption(clstr caption)override;
  void SetColor(clfloat r,clfloat g,clfloat b,clfloat a=1.f);
  void SetValue(clstr value);
  clstr GetValue()const;

protected:
  ~clguiTextArea();
  void Render();

private:
  clstr m_value="<NO-VALUE>";
  clf4 m_color;
};

CLGUI_NAMESPACE_END