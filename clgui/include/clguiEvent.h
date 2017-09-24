#pragma once
#include "core\clgui_variable.h"

CLGUI_NAMESPACE_START

class clguiInteractive;
class clguiEvent;
typedef void CallBackEventFn(const clguiEvent*);

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
  clguiEvent(const clguiEvent&)=delete;
  clguiEvent(clguiEventType type,const clguiInteractive* sender)
    :m_type(type),m_eventSender(sender){};
  virtual ~clguiEvent(){};
  clguiEventType GetType()const{ return m_type; };
  const clguiInteractive* GetSender()const{ return m_eventSender; }

private:
  const clguiEventType m_type;
  const clguiInteractive* m_eventSender;

};



class clguiEventMouseClick final:public clguiEvent{
public:
  clguiEventMouseClick(const clguiInteractive* sender);
  ~clguiEventMouseClick();
};

CLGUI_NAMESPACE_END