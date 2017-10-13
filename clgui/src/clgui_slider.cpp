#include "clgui/component/clgui_slider.h"
#include "imgui/imgui.h"
#include "clgui/clgui.h"

CLGUI_NAMESPACE_START

clguiSliderFloat::clguiSliderFloat()
  :clguiSlider<clfloat>(){
  m_min=0.f;
  m_max=1.f;
  m_value.SetNewValue(.4f);
  SetDimension(1);
}

clguiSliderFloat::~clguiSliderFloat(){ m_RenderFn=nullptr; }

void clguiSliderFloat::SetDimension(cluint d){
  F_DBG_ASSERT(d<4);
  F_DBG_ASSERT(d>0);
  m_uDimension=d;
  switch(d){
  case 1:
    m_RenderFn=ImGui::SliderFloat;
    break;
  case 2:
    m_RenderFn=ImGui::SliderFloat2;
    break;
  case 3:
    m_RenderFn=ImGui::SliderFloat3;
    break;
  default:
    break;
  }
}

void clguiSliderFloat::Render(){
  m_RenderFn(m_sRenderName.c_str(),m_value[0],m_min,m_max,m_sFormat.c_str(),m_power);
}

void clguiSliderFloat::PostRender(){
  if(m_value.CheckChange()){
    clguiEventSliderValueChangeFloat evt(this,clguiEventType::EVT_SLIDER_VALUE_CHANGE);
    DispatchEvent_(&evt);
    m_value.Update();
  }
}








clguiSliderInt::clguiSliderInt()
  :clguiSlider<clint>(){
  m_min=0;
  m_max=100;
  m_value.SetNewValue(40);
  SetDimension(1);
}

clguiSliderInt::~clguiSliderInt(){ m_RenderFn=nullptr; }

void clguiSliderInt::SetDimension(cluint d){
  F_DBG_ASSERT(d<4);
  F_DBG_ASSERT(d>0);
  m_uDimension=d;
  switch(d){
  case 1:
    m_RenderFn=ImGui::SliderInt;
    break;
  case 2:
    m_RenderFn=ImGui::SliderInt2;
    break;
  case 3:
    m_RenderFn=ImGui::SliderInt3;
    break;
  default:
    break;
  }
}

void clguiSliderInt::Render(){
  m_RenderFn(m_sRenderName.c_str(),m_value[0],m_min,m_max,m_sFormat.c_str());
}

void clguiSliderInt::PostRender(){
  if(m_value.CheckChange()){
    clguiEventSliderValueChangeInt evt(this,clguiEventType::EVT_SLIDER_VALUE_CHANGE);
    DispatchEvent_(&evt);
    m_value.Update();
  }
}
CLGUI_NAMESPACE_END
