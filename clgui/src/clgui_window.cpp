#include "clgui_window.h"
#include "imgui.h"
#include "cl_types.h"

CLGUI_NAMESPACE_START

clguiWindow::clguiWindow()
  :clguiContainer(CLGUI_OBJECT_TYPE_CONTAINER){
  m_clVarBool.ResetTo(true);
}
clguiWindow::~clguiWindow(){};

void clguiWindow::Render(){
  ImGui::SetNextWindowSize(m_size,ImGuiSetCond_FirstUseEver);
  ImGui::SetNextWindowPos(m_pos,ImGuiSetCond_FirstUseEver);
  ImGui::Begin(m_caption.c_str(),m_clVarBool.GetNewValuePointer());
  ImGui::Text("Application average %.3f ms/frame (%.1f FPS)",1000.0f/ImGui::GetIO().Framerate,ImGui::GetIO().Framerate);

}
void clguiWindow::PostRender(){
  ImGui::End();
  if(!m_clVarBool.GetNewValue()){
    /*
    clguiEvent evt(clguiEventType::clgui_EVT_WINDOW_CLOSE);
    evt.newValue.type=clUniformVariableType::CLBOOL;
    evt.newValue.boolValue=m_clVarBool.GetNewValue();
    evt.oldValue.type=clUniformVariableType::CLBOOL;
    evt.oldValue.boolValue=m_clVarBool.GetOldValue();
    DispatchEvent_(&evt);
    */
    //m_clVarBool.SetNewValue(true);
    int a=10;
  }
}

void clguiWindow::SetCaption(clstr caption){
  m_caption=caption;
}

CLGUI_NAMESPACE_END