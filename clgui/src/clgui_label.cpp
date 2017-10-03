#include "clgui/clgui_label.h"
#include "imgui/imgui.h"

CLGUI_NAMESPACE_START

clguiLabel::clguiLabel()
  :clguiComponent(CLGUI_OBJECT_TYPE_COMPONENT){
  m_color.w=1.f;
  m_color.x=m_color.y=m_color.z=CLGUI_CAPTION_DEFAULT_COLOR;
}

clguiLabel::~clguiLabel(){}

void clguiLabel::Render(){
  ImGui::TextColored(m_color,m_caption.c_str());
  if(m_value.empty())return;
  ImGui::SameLine();
  ImGui::TextColored(m_color,m_value.c_str());
}

void clguiLabel::SetCaption(clstr caption){
  m_caption=caption;
}

void clguiLabel::SetColor(clfloat r,clfloat g,clfloat b,clfloat a){
  m_color.x=r;m_color.y=g;m_color.z=b;m_color.w=a;
}

void clguiLabel::SetValue(cluint value){
  m_value=std::to_string(value);
}

void clguiLabel::SetValue(clint value){
  m_value=std::to_string(value);
}

void clguiLabel::SetValue(clfloat value){
  m_value=std::to_string(value);
}

void clguiLabel::SetValue(cldouble value){
  m_value=std::to_string(value);
}

void clguiLabel::SetValue(clchar* value){
  m_value=clstr(value);
}

void clguiLabel::SetValue(clstr value){
  m_value=value;
}

clstr clguiLabel::GetValue() const{
  return m_value;
}

CLGUI_NAMESPACE_END
