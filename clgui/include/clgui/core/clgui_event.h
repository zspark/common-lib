#pragma once

#include "clgui_variable.h"

CLGUI_NAMESPACE_START

class clguiInteractive;
class clguiButton;
class clguiWindow;
class clguiCheckBox;
class clguiMenuItem;
class clguiSliderFloat;
class clguiSliderInt;
class clguiComboBox;
class clguiCollapser;

typedef void CallBackEventFn(clguiEvent*);

enum class clguiEventType{
  EVT_BUTTON_CLICK=0,
  EVT_WINDOW_CLOSE,
  EVT_CHECKBOX_STATUS_CHANGE,
  EVT_VALUE_CHANGE,
  EVT_MENUITEM_STATUS_CHANGE,
  EVT_SLIDER_VALUE_CHANGE,
  EVT_COMBOBOX_STATUS_CHANGE,
  EVT_COLLAPSER_STATUS_CHANGE,
};

class clguiEvent{
public:
  clguiEvent(clguiInteractive* sender,clguiEventType type)
    :m_type(type){
    m_eventSender=sender;
  };

  ~clguiEvent(){ m_eventSender=nullptr; };

  clguiEventType GetType()const{ return m_type; }

protected:
  const clguiEventType m_type;
  clguiInteractive* m_eventSender;

};

template<typename T>
class clguiEvent_T:public clguiEvent{
public:
  clguiEvent_T(T* sender,clguiEventType type)
    :clguiEvent(sender,type){};

  ~clguiEvent_T(){};

  T* GetSender()const{ return static_cast<T*>(m_eventSender); }
};

////////////////////////////////////////////////////////////////////////////////////////////////////

typedef clguiEvent_T<clguiButton> clguiEventButtonClick ;
typedef clguiEvent_T<clguiWindow> clguiEventWindowClose ;
typedef clguiEvent_T<clguiCheckBox> clguiEventCheckboxStatusChange ;
typedef clguiEvent_T<clguiMenuItem> clguiEventMenuItemStatusChange ;
typedef clguiEvent_T<clguiSliderFloat> clguiEventSliderValueChangeFloat ;
typedef clguiEvent_T<clguiSliderInt> clguiEventSliderValueChangeInt ;
typedef clguiEvent_T<clguiComboBox> clguiEventComboBoxStatusChange ;
typedef clguiEvent_T<clguiCollapser> clguiEventCollapserStatusChange ;


////////////////////////////////////////////////////////////////////////////////////////////////////
/*
template<typename T>
class clguiEventValueChange final:public clguiEvent{
public:
  clguiEventValueChange(clguiInteractive* sender,T newValue,T oldValue)
    :clguiEvent(clguiEventType::EVT_VALUE_CHANGE),m_eventSender(sender)
    ,m_value(newValue,oldValue){}

  ~clguiEventValueChange(){};
  clguiInteractive* GetSender()const{ return m_eventSender; }
  ComponentVariable_T<T> GetValue()const{ return m_value; }
  ComponentVariable_T<T>& GetValue_ref(){ return m_value; }


private:
  clguiInteractive* m_eventSender;
  ComponentVariable_T<T> m_value;
};

typedef clguiEventValueChange<clbool> clguiEvnetBoolChange;
*/

////////////////////////////////////////////////////////////////////////////////////////////////////

CLGUI_NAMESPACE_END