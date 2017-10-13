#include "clgui/component/clgui_window.h"
#include "imgui/imgui.h"
#include "cl/cl_types.h"
#include "core/clgui_object_manager.h"

CLGUI_NAMESPACE_START

clguiWindow::clguiWindow()
  :clguiContainer(CLGUI_OBJECT_TYPE_CONTAINER)
  ,m_clVarBool(true)
  ,m_condition(ImGuiSetCond_Once)
  ,m_flag(0){}

void clguiWindow::NoticeSystemWndNewSize(clint width,clint height){
  clguiAttachSide tmpSide=m_side;
  m_side=clguiAttachSide::FREE;
  AttachToBorder(tmpSide,m_attachSize);
}

void clguiWindow::SetSize(clint width,clint height){
  clguiComponent::SetSize(width,height);
  m_condition=ImGuiSetCond_Always;
}

void clguiWindow::SetPosition(clint x,clint y){
  clguiContainer::SetPosition(x,y);
  m_condition=ImGuiSetCond_Always;
}

void clguiWindow::SetPosition(clguiPositionMode mode){
  m_posMode=mode;
  ImGuiIO& io=ImGui::GetIO();
  ImVec2 dsize=io.DisplaySize;
  clint w=(clint)dsize.x;
  clint h=(clint)dsize.y;
  switch(mode){
  case clgui::clguiPositionMode::POSITION_TOP_LEFT:
    m_pos.x=0.f;
    m_pos.y=0.f;
    break;
  case clgui::clguiPositionMode::POSITION_TOP_RIGHT:
    m_pos.x=w-m_size.x;
    m_pos.y=0.f;
    break;
  case clgui::clguiPositionMode::POSITION_BOTTOM_LEFT:
    m_pos.x=0.f;
    m_pos.y=h-m_size.y;
    break;
  case clgui::clguiPositionMode::POSITION_BOTTOM_RIGHT:
    m_pos.x=w-m_size.x;
    m_pos.y=h-m_size.y;
    break;
  case clgui::clguiPositionMode::POSITION_CENTER:
    m_pos.x=(w-m_size.x)*.5f;
    m_pos.y=(h-m_size.y)*.5f;
    break;
  case clgui::clguiPositionMode::POSITION_FREE:
  default:
    break;
  }
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

void clguiWindow::AttachToBorder(clguiAttachSide side,cluint size){
  if(side==m_side)return;
  if(side==clguiAttachSide::FREE)return;
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
  case clguiAttachSide::BOTTON:
    clguiComponent::SetSize(w,size);
    clguiContainer::SetPosition(0,h-size);
    break;
  case clguiAttachSide::LEFT:
    clguiComponent::SetSize(size,h-mbh);
    clguiContainer::SetPosition(0,mbh);
    break;
  case clguiAttachSide::RIGHT:
    clguiComponent::SetSize(size,h-mbh);
    clguiContainer::SetPosition(w-size,mbh);
    break;
  case clguiAttachSide::TOP:
    clguiComponent::SetSize(w,size);
    clguiContainer::SetPosition(0,mbh);
    break;
  case clguiAttachSide::FREE:
  default:
    break;
  }
  m_condition=ImGuiSetCond_Always;
}

void clguiWindow::DetachFromBorder(){
  if(m_side!=clguiAttachSide::FREE){
    m_side=clguiAttachSide::FREE;
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
  clbool r=ImGui::Begin(m_sRenderName.c_str(),m_clVarBool[0],m_flag);

  m_condition=ImGuiSetCond_Once;
  m_pos=ImGui::GetWindowPos();
  return r;
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