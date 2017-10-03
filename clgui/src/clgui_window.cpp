#include "clgui/clgui_window.h"
#include "imgui/imgui.h"
#include "cl/cl_types.h"
#include "core/clgui_object_manager.h"

inline static void ImVec2ToclF2(ImVec2& vec2,clf2& f2){
  vec2.x=f2.x;
  vec2.y=f2.y;
}

inline static void clF2ToImVec2(clf2& f2,ImVec2& vec2){
  f2.x=vec2.x;
  f2.y=vec2.y;
}

CLGUI_NAMESPACE_START

clguiWindow::clguiWindow()
  :clguiContainer(CLGUI_OBJECT_TYPE_CONTAINER)
  ,m_clVarBool(true)
  ,m_condition(ImGuiSetCond_Once)
  ,m_flag(0){}

void clguiWindow::NoticeWindowSize(clint width,clint height){
  attach_side tmpSide=m_side;
  m_side=attach_side::FREE;
  AttachToBorder(tmpSide,m_attachSize);
}

void clguiWindow::SetSize(clint width,clint height){
  clguiComponent::SetSize(width,height);
  m_condition=ImGuiSetCond_Always;
}

void clguiWindow::SetPosition(clint x,clint y){
  clguiComponent::SetPosition(x,y);
  m_condition=ImGuiSetCond_Always;
}

void clguiWindow::StatusResize(clbool b){
  if(b)m_flag&=~ImGuiWindowFlags_NoResize;
  else m_flag|=ImGuiWindowFlags_NoResize;
}

void clguiWindow::StatusMove(clbool b){
  if(b)m_flag&=~ImGuiWindowFlags_NoMove;
  else m_flag|=ImGuiWindowFlags_NoMove;
}

void clguiWindow::StatusScrollbar(clbool b){
  if(b)m_flag&=~ImGuiWindowFlags_NoScrollbar;
  else m_flag|=ImGuiWindowFlags_NoScrollbar;
}

void clguiWindow::AttachToBorder(attach_side side,cluint size){
  if(side==m_side)return;
  if(side==attach_side::FREE)return;
  m_side=side;
  m_attachSize=size;
  ImGuiIO& io=ImGui::GetIO();
  ImVec2 dsize=io.DisplaySize;
  clint w=(clint)dsize.x;
  clint h=(clint)dsize.y;

  //TODO: fix this magic number 
  clint mbh=19;//(clint)ImGui::GetFontSize;

  m_flag|=ImGuiWindowFlags_NoMove;
  m_flag|=ImGuiWindowFlags_NoResize;
  m_flag|=ImGuiWindowFlags_NoTitleBar;
  switch(side){
  case attach_side::BOTTON:
    clguiComponent::SetSize(w,size);
    clguiComponent::SetPosition(0,h-size);
    break;
  case attach_side::LEFT:
    clguiComponent::SetSize(size,h-mbh);
    clguiComponent::SetPosition(0,mbh);
    break;
  case attach_side::RIGHT:
    clguiComponent::SetSize(size,h-mbh);
    clguiComponent::SetPosition(w-size,mbh);
    break;
  case attach_side::TOP:
    clguiComponent::SetSize(w,size);
    clguiComponent::SetPosition(0,mbh);
    break;
  case attach_side::FREE:
  default:
    break;
  }
  m_condition=ImGuiSetCond_Always;
}

void clguiWindow::DetachFromBorder(){
  if(m_side!=attach_side::FREE){
    m_side=attach_side::FREE;
    m_flag&=~ImGuiWindowFlags_NoMove;
    m_flag&=~ImGuiWindowFlags_NoResize;
    m_flag&=~ImGuiWindowFlags_NoTitleBar;
  }
  m_condition=ImGuiSetCond_Always;
}

clguiWindow::~clguiWindow(){}

clbool clguiWindow::PreRender(){
  ImGui::SetNextWindowSize(m_size,m_condition);
  ImGui::SetNextWindowPos(m_pos,m_condition);
  ImGui::Begin(m_caption.c_str(),m_clVarBool[0],m_flag);

  m_condition=ImGuiSetCond_Once;
  m_pos=ImGui::GetWindowPos();
  return true;
}

void clguiWindow::Render(){
  ImGui::Text("Application average %.3f ms/frame (%.1f FPS)",1000.0f/ImGui::GetIO().Framerate,ImGui::GetIO().Framerate);
}

void clguiWindow::PostRender(){
  ImGui::End();
  if(m_clVarBool.CheckChange()){
    clguiEventWindowClose evt(this,clguiEventType::EVT_WINDOW_CLOSE);
    DispatchEvent_(&evt);
    m_clVarBool.SetNewValue(true);
  }
}

CLGUI_NAMESPACE_END