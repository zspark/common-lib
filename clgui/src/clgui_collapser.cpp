#include "clgui/component/clgui_collapser.h"
#include "imgui\imgui.h"

CLGUI_NAMESPACE_START

clguiCollapser::clguiCollapser()
  :clguiContainer(CLGUI_OBJECT_TYPE_CONTAINER)
  ,m_cv(false){
}

clguiCollapser::~clguiCollapser(){}

clbool clguiCollapser::PreRender(){
  clbool b= ImGui::CollapsingHeader(m_sName.c_str());
  m_cv.SetNewValue(b);
  return b;
}

void clguiCollapser::Render(){}

void clguiCollapser::PostRender(){
  if(m_bCollapsingEventEnabled){
    if(m_cv.CheckChange()){
      clguiEventCollapserStatusChange evt(this,clguiEventType::EVT_COLLAPSER_STATUS_CHANGE);
      DispatchEvent_(&evt);
      m_cv.Update();
    }
  }
}

void clguiCollapser::EnableCollapsingEvent(){
  m_bCollapsingEventEnabled=true;
}

CLGUI_NAMESPACE_END
