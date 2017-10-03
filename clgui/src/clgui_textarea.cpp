#include "clgui/clgui_textarea.h"
#include <stdarg.h>
#include "imgui/imgui.h"

CLGUI_NAMESPACE_START

clguiTextArea::clguiTextArea()
  :clguiComponent(CLGUI_OBJECT_TYPE_COMPONENT){
  m_color.w=1.f;
  m_color.x=m_color.y=m_color.z=CLGUI_CAPTION_DEFAULT_COLOR;
}

clguiTextArea::~clguiTextArea(){}

void clguiTextArea::Render(){
  //ImGui::TextColored(m_color,m_caption.c_str());
  ImGui::Text(m_caption.c_str());
}

void clguiTextArea::SetCaption(clstr caption){
  m_caption=caption;
}

void clguiTextArea::SetColor(clfloat r,clfloat g,clfloat b,clfloat a){
  m_color.x=r;m_color.y=g;m_color.z=b;m_color.w=a;
}

void clguiTextArea::SetValue(clstr value){
  m_value=value;
}

clstr clguiTextArea::GetValue() const{
  return m_value;
}

CLGUI_NAMESPACE_END
