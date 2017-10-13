#pragma once

#include "clgui/core/clgui_macro.h"
#include "clgui/core\clgui_variable.h"
#include "clgui/core/clgui_object.h"

CLGUI_NAMESPACE_START

enum class clguiTextMode{
  AUTO_WRAP=0,
  NORMAL,
};

class CLGUI_API clguiText:public clguiComponent{
public:
  clguiText(cluint maxsize);

public:

  void SetText(clstr fmt,...);
  clstr GetText()const;
  void SetTextMode(clguiTextMode mod);
  clguiTextMode GetTextMode()const;

protected:
  ~clguiText();
  void Render();

private:

  typedef void(*RenderFn_)(const clchar* fmt,...);
  RenderFn_ RenderFn=nullptr;
  clstr m_fmt="";
  clguiTextMode m_mod=clguiTextMode::NORMAL;
  cluint m_maxSize;
  clchar* m_text=nullptr;
};

CLGUI_NAMESPACE_END