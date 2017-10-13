#include "clgui/component/clgui_text.h"
#include <stdarg.h>
#include "imgui/imgui.h"

CLGUI_NAMESPACE_START

clguiText::clguiText(cluint maxsize)
  :clguiComponent(CLGUI_OBJECT_TYPE_COMPONENT)
  ,m_maxSize(maxsize){
  m_text=new clchar[maxsize];
  SetTextMode(clguiTextMode::NORMAL);
}

clguiText::~clguiText(){
  RenderFn=nullptr;
  delete[] m_text;
}

void clguiText::Render(){
  RenderFn(m_text);
}

void clguiText::SetText(clstr fmt,...){
  m_fmt=fmt;
  va_list args;
  va_start(args,fmt);
  vsnprintf_s(m_text,m_maxSize,m_maxSize,fmt.c_str(),args);
  va_end(args);
}

clstr clguiText::GetText() const{
  clstr str(m_text);
  return str;
}

void clguiText::SetTextMode(clguiTextMode mod){
  m_mod=mod;
  RenderFn=mod==clguiTextMode::AUTO_WRAP?ImGui::TextWrapped:ImGui::Text;
}

clguiTextMode clguiText::GetTextMode() const{
  return m_mod;
}


CLGUI_NAMESPACE_END
