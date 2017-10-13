#include "clgui/component/clgui_checkbox.h"
#include "imgui/imgui.h"

CLGUI_NAMESPACE_START

clguiCheckBox::clguiCheckBox(clbool selected)
  :clguiComponent(CLGUI_OBJECT_TYPE_COMPONENT),m_cv(selected){
  m_size.x=50;
  m_size.y=25;
}

clguiCheckBox::~clguiCheckBox(){}

void clguiCheckBox::Render(){
  ImGui::Checkbox(m_sName.c_str(),m_cv[0]);
}

void clguiCheckBox::PostRender(){
  if(m_cv.CheckChange()){
    clguiEventCheckboxStatusChange evt(this,clguiEventType::EVT_CHECKBOX_STATUS_CHANGE);
    DispatchEvent_(&evt);
    m_cv.Update();
  }
}

clbool clguiCheckBox::GetSelection() const{
  return m_cv[0];
}

void clguiCheckBox::SetSelection(clbool v){
  m_cv.ResetTo(v);
}

CLGUI_NAMESPACE_END
