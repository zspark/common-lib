#include "clgui/core/clgui_object.h"
#include "GLFW\glfw3.h"
#include "imgui/imgui.h"
#include "cl/cl_regexp_util.h"
#include "clgui_object_manager.h"
#include "clgui/core/clgui_event.h"

using namespace std;
using namespace cl;

CLGUI_NAMESPACE_START


clguiObject::clguiObject(cluint type)
  :m_uUniqueID(GetUniqueUint())
  ,m_type(type){
  clguiObjectManager::GetIns()->AddObject(this);
};

clguiObject::~clguiObject(){ };







clguiInteractive::~clguiInteractive(){
  m_mapListeners_name_listener.clear();
};

void clguiInteractive::AddEventListener(clguiEventType type,CallBackEventFn* cbFn){
  vector<CallBackEventFn*>& tmpVec=m_mapListeners_name_listener[type];
  tmpVec.push_back(cbFn);
}

void clguiInteractive::DispatchEvent_(clguiEvent* evt){
  vector<CallBackEventFn*>& tmpVec=m_mapListeners_name_listener[evt->GetType()];
  for(auto it:tmpVec){
    it(evt);
  }
}



clguiComponent::clguiComponent(cluint type)
  :clguiInteractive(type){
  SetName("<NO-NAME>");
};

clguiContainer * clguiComponent::GetParent() {
  return clguiObjectManager::GetIns()->GetParent(this);
}

void clguiComponent::SetName(clstr name){
  m_sName=name;
  m_sRenderName=name+"##"+std::to_string(m_uUniqueID); 
}

clstr clguiComponent::GetName()const{
  return m_sName;
}

void clguiComponent::SetSize(clint width,clint height){
  if(width>=0) m_size.x=width;
  if(height>=0)m_size.y=height;
}

void clguiComponent::GetSize(clint* width,clint* height)const{
  *width=m_size.x;
  *height=m_size.y;
}

void clguiComponent::ScaleSizeBy(clfloat f){
  m_size.x*=f;
  m_size.y*=f;
}

void clguiComponent::SetSameline(clbool sameline,clfloat posx,clfloat spacing){
  m_isSameline=sameline;
  m_posx=posx;
  m_spacing=spacing;
}








clguiContainer::clguiContainer(cluint type)
  :clguiComponent(type)
  ,m_pos(0.f,0.f){}

clguiContainer::~clguiContainer(){ };

void clguiContainer::AddChild(clguiComponent* child){
  clguiObjectManager::GetIns()->AddChildAt(child,this,-1);
}

void clguiContainer::AddChildAt(clguiComponent* child,clint index){
  clguiObjectManager::GetIns()->AddChildAt(child,this,index);
}

void clguiContainer::RemoveChild(clguiComponent* child){
  clguiObjectManager::GetIns()->RemoveChild(child);
}

clguiComponent * clguiContainer::GetChildByName(clstr name){
  clguiObjectManager* mgr=clguiObjectManager::GetIns();
  clguiComponent* m=mgr->GetFirstChild(this);
  while(m){
    if(std::strcmp(m_sName.c_str(),name.c_str())==0){
      return m;
    }
    m=mgr->GetNextSibling(m);
  }
  return nullptr;
}

clguiComponent * clguiContainer::GetChildByUniqueID(cluint ID){
  clguiObjectManager* mgr=clguiObjectManager::GetIns();
  clguiComponent* m=mgr->GetFirstChild(this);
  while(m){
    if(m->GetUniqueID()==ID) return m;
    m=mgr->GetNextSibling(m);
  }
  return nullptr;
}

void clguiContainer::SetPosition(clint x,clint y){
  m_pos.x=x;
  m_pos.y=y;
}

void clguiContainer::GetPosition(clint* x,clint* y)const{
  *x=m_pos.x;
  *y=m_pos.y;
}









clguiStage::clguiStage()
  :clguiContainer(CLGUI_OBJECT_TYPE_STAGE){}

void clguiStage::NoticeSystemWndNewSize(clint width,clint height){
  clguiContainer::SetSize(width,height);
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
