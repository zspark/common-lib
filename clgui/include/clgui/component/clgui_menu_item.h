#pragma once

#include "clgui/core/clgui_macro.h"
#include "clgui/core\clgui_variable.h"
#include "clgui/core/clgui_object.h"

CLGUI_NAMESPACE_START

class CLGUI_API clguiMenuItem:public clguiComponent{
public:
  clguiMenuItem();

  void SetSelection(clbool b);
  clbool GetSelection()const;
  void Enable(clbool b);
  clbool Enable()const;
  void SetShortKey(clstr key){ m_shortKey=key; }
  clstr GetShortKey()const{ return m_shortKey; }

protected:
  void Render()override;
  void PostRender()override;

private:
  ~clguiMenuItem();

  cvBool m_clVarBool;
  clstr m_shortKey;
  clbool m_bEnable=true;
};

CLGUI_NAMESPACE_END