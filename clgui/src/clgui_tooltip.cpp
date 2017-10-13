#include "clgui/component/clgui_tooltip.h"
#include "imgui\imgui.h"

CLGUI_NAMESPACE_START

clguiToolTip::clguiToolTip()
  :clguiComponent(CLGUI_OBJECT_TYPE_COMPONENT){
  m_size.Set(10,10);
}

void clguiToolTip::SetMark(clstr mark){ m_toolTipMark=mark; }

void clguiToolTip::SetDescription(clstr des){ m_toolTipDescription=des; }

clguiToolTip::~clguiToolTip(){}

void clguiToolTip::Render(){
  ImGui::SameLine();
  ImGui::TextDisabled(m_toolTipMark.c_str());
  if(ImGui::IsItemHovered()){
    ImGui::BeginTooltip();
    ImGui::PushTextWrapPos(450.0f);
    ImGui::TextUnformatted(m_toolTipDescription.c_str());
    ImGui::PopTextWrapPos();
    ImGui::EndTooltip();
  }
}


CLGUI_NAMESPACE_END
