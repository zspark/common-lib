#include "clgui/component/clgui_button.h"
#include "imgui\imgui.h"

CLGUI_NAMESPACE_START

clguiButton::clguiButton()
  :clguiComponent(CLGUI_OBJECT_TYPE_COMPONENT)
  ,m_cv(false){
  m_size.Set(60,30);
}

clguiButton::~clguiButton(){}

void clguiButton::Render(){
  if(ImGui::Button(m_sRenderName.c_str(),m_size)){
    m_cv.SetNewValue(true);
  }
}

void clguiButton::PostRender(){
  if(m_cv.CheckChange()){
    clguiEventButtonClick evt(this,clguiEventType::EVT_BUTTON_CLICK);
    DispatchEvent_(&evt);
    m_cv.SetNewValue(false);
  }
}

CLGUI_NAMESPACE_END
