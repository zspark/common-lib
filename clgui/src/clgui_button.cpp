#include "clgui_button.h"
#include "core/clguiObject.h"

CLGUI_NAMESPACE_START

clguiButton::clguiButton()
  :clguiComponent(CLGUI_OBJECT_TYPE_COMPONENT){
  m_size.x=100;
  m_size.y=50;
  m_cv.ResetTo(false);
}

clguiButton::clguiButton(const clguiButton & btn)
:clguiButton(){
  m_size.x=btn.m_size.x;
  m_size.y=btn.m_size.y;
}

clguiButton::~clguiButton(){}

void clguiButton::Render(){
  if(ImGui::Button(m_caption.c_str(),m_size)){
    m_cv.SetNewValue(true);
  }
}

void clguiButton::PostRender(){
  if(m_cv.CheckChange()){
    clguiEventMouseClick evt(this);
    DispatchEvent_(&evt);
    m_cv.SetNewValue(false);
  }
}

void clgui::clguiButton::SetCaption(clstr caption){
  m_caption=caption;
}

CLGUI_NAMESPACE_END
