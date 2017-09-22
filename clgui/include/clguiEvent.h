#pragma once
#include "clguiComponentVariable.h"

namespace clgui{

enum clguiEventType{
  CLGUI_EVT_BUTTON_CLICK=0,
  CLGUI_EVT_MENUITEM_STATUS_CHANGE,
  CLGUI_EVT_SLIDER_VALUE_CHANGE,
  CLGUI_EVT_CHECKBOX_SELECTION_CHANGE,
  CLGUI_EVT_WINDOW_CLOSE,
};


class clguiEvent{
public:
  clguiEvent()=delete;
  clguiEvent(clguiEventType type):m_type(type){};
  virtual ~clguiEvent(){};
  clguiEventType GetType()const{ return m_type; };
  UniformComponentVariable oldValue;
  UniformComponentVariable newValue;

private:
  const clguiEventType m_type;
  clbool m_bStopPropagation=false;
};
}