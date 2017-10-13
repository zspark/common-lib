#include "clgui/component/clgui_label.h"
#include <varargs.h>
#include "imgui/imgui.h"

CLGUI_NAMESPACE_START

clguiLabel::clguiLabel(cluint maxCharCount)
  :clguiComponent(CLGUI_OBJECT_TYPE_COMPONENT)
,m_maxCharCount(maxCharCount)
{
  m_value=new clchar[maxCharCount];
}

clguiLabel::~clguiLabel(){
  delete[] m_value;
  m_value=nullptr;
}

void clguiLabel::Render(){
  ImGui::LabelText(m_sRenderName.c_str(),m_value);
}

void clguiLabel::SetValue(clstr fmt,...){
  va_list args;
  va_start(args,fmt);
  vsnprintf_s(m_value,m_maxCharCount,m_maxCharCount,fmt.c_str(),args);
  va_end(args);
}

clstr clguiLabel::GetValue() const{
  return clstr(m_value);
}

CLGUI_NAMESPACE_END
