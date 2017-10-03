#include "clgui_event.h"
//#include "core\clgui_object.h"
#include "clgui_button.h"


CLGUI_NAMESPACE_START


////////////////////////////////////////////////////////////////////////////////////////////////////

clguiEventButtonClick::clguiEventButtonClick(clguiButton* sender)
  :clguiEvent_T<clguiButton>(sender,clguiEventType::CLGUI_EVT_BUTTON_CLICK){
}

clguiEventButtonClick::~clguiEventButtonClick(){}





////////////////////////////////////////////////////////////////////////////////////////////////////
clguiEventWindowClose::clguiEventWindowClose(clguiWindow * sender)
:clguiEvent(clguiEventType::CLGUI_EVT_WINDOW_CLOSE),m_eventSender(sender){}

clguiEventWindowClose::~clguiEventWindowClose(){}

clguiWindow* clguiEventWindowClose::GetSender()const{
  return GetSender_<clguiWindow>();
}
////////////////////////////////////////////////////////////////////////////////////////////////////


CLGUI_NAMESPACE_END

