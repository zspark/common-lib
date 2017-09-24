#pragma once
#include "clguiObject.h"
#include "GLFW\glfw3.h"
#include "clguiEvent.h"
#include "clgui_object_manager.h"

using namespace std;
using namespace cl;

CLGUI_NAMESPACE_START

clguiObject::clguiObject(cluint type)
  :m_uUniqueID(GetUniqueUint())
  ,m_type(type){
  clguiObjectManager::GetIns()->AddObject(this);
};

clguiObject::~clguiObject(){ 
  clguiObjectManager::GetIns()->RemoveObject(this);
};







clguiInteractive::~clguiInteractive(){
  m_mapListeners_name_listener.clear();
};

void clguiInteractive::AddEventListener(clguiEventType type,CallBackEventFn* cbFn){
  vector<CallBackEventFn*>& tmpVec=m_mapListeners_name_listener[type];
  tmpVec.push_back(cbFn);
}

void clguiInteractive::DispatchEvent_(const clguiEvent* evt){
  vector<CallBackEventFn*>& tmpVec=m_mapListeners_name_listener[evt->GetType()];
  for(auto it:tmpVec){
    it(evt);
  }
}






clguiContainer::clguiContainer(cluint type)
  :clguiComponent(type){};

clguiContainer::~clguiContainer(){
};

void clguiContainer::AddChild(clguiComponent* child){
  clguiObjectManager::GetIns()->AddChildAt(child,this);
}
void clguiContainer::AddChildAt(clguiComponent* child,clint index){
  clguiObjectManager::GetIns()->AddChildAt(child,this,index);
}
void clguiContainer::RemoveChild(clguiComponent* child){
  clguiObjectManager::GetIns()->RemoveChild(child);
}




clguiContainer * clguiComponent::GetParent() {
  clguiObject* obj=clguiObjectManager::GetIns()->GetParent(this);
  return TryConvertTo<clguiContainer*>(obj,CLGUI_OBJECT_TYPE_CONTAINER);
}


void clguiStage::SetColor(cluint r,cluint g,cluint b){
  m_clearColor.x=r*M_1_255;
  m_clearColor.y=g*M_1_255;
  m_clearColor.z=b*M_1_255;
  m_clearColor.w=1.0f;
  glClearColor(m_clearColor.x,m_clearColor.y,m_clearColor.z,m_clearColor.w);
}

void clguiStage::SetGLFWwindow(GLFWwindow * wnd){ m_glfwWnd=wnd; }

void clguiStage::Render(){
  clint display_w,display_h;
  glfwGetFramebufferSize(m_glfwWnd,&display_w,&display_h);
  glViewport(0,0,display_w,display_h);
  glClear(GL_COLOR_BUFFER_BIT);
}




/*
bool clguiContainer::BuildLayoutComponentsByJson(Json::Value json){
  auto mem=json.getMemberNames();
  for(auto it=mem.begin(); it!=mem.end(); it++){
    std::string s=json[*it].toStyledString();
    int a={10};
    int b=10+a;
  }
  return true;
}
*/

CLGUI_NAMESPACE_END
