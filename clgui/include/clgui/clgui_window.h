#pragma once
#include "core/clgui_macro.h"
#include "core/clgui_variable.h"
#include "core/clgui_object.h"

CLGUI_NAMESPACE_START

enum class attach_side{
  TOP=0,
  BOTTON,
  LEFT,
  RIGHT,
  FREE,
};

class CLGUI_API clguiWindow:public clguiContainer{

public:
  clguiWindow();

public:
  void NoticeWindowSize(clint width,clint height)override;
  void SetSize(clint width,clint height)override;
  void SetPosition(clint x,clint y)override;
  void StatusResize(clbool b);
  void StatusMove(clbool b);
  void StatusScrollbar(clbool b);
  void AttachToBorder(attach_side,cluint size);
  void DetachFromBorder();

  //bool BuildLayoutComponentsByJson(Json::Value json)override;

protected:
  virtual ~clguiWindow();
  clbool PreRender()override;
  void Render()override;
  void PostRender()override;

private:
  cvBool m_clVarBool;
  clint m_condition;
  clint m_flag=0;
  attach_side m_side=attach_side::FREE;
  clint m_attachSize;

};

CLGUI_NAMESPACE_END
