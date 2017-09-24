#include "clguiEvent.h"

CLGUI_NAMESPACE_START

clguiEventMouseClick::clguiEventMouseClick(const clguiInteractive* sender)
  :clguiEvent(CLGUI_EVT_BUTTON_CLICK,sender){}

clguiEventMouseClick::~clguiEventMouseClick(){}

CLGUI_NAMESPACE_END