#pragma once
#include "clgui/core/clgui_macro.h"
#include "clgui/core/clgui_variable.h"
#include "clgui/core/clgui_object.h"

CLGUI_NAMESPACE_START

enum class clguiAttachSide{
  TOP=0,
  BOTTON,
  LEFT,
  RIGHT,
  FREE,
};

enum class clguiPositionMode{
  POSITION_TOP_LEFT=0,
  POSITION_TOP_RIGHT,
  POSITION_BOTTOM_LEFT,
  POSITION_BOTTOM_RIGHT,
  POSITION_CENTER,
  POSITION_FREE,
};

class CLGUI_API clguiWindow:public clguiContainer{

public:
  clguiWindow();

public:
  void NoticeSystemWndNewSize(clint width,clint height)override;
  void SetSize(clint width,clint height)override;
  void SetPosition(clint x,clint y)override;
  /**
   * this method must be called after SetSize();
   */
  void SetPosition(clguiPositionMode mode);
  void StatusResize(clbool b);
  void StatusMove(clbool b);
  void StatusScrollbar(clbool b);
  void AttachToBorder(clguiAttachSide,cluint size);
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
  clguiAttachSide m_side=clguiAttachSide::FREE;
  clint m_attachSize;
  clguiPositionMode m_posMode=clguiPositionMode::POSITION_FREE;

};

CLGUI_NAMESPACE_END
