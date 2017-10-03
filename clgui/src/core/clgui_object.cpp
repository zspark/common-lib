#include "clgui/core/clgui_object.h"
#include "GLFW\glfw3.h"
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
  :clguiInteractive(type)
  ,m_pos(0.f,0.f),m_size(100.f,30.f){
  SetCaption("<NO-CAPTION>");
};


clguiContainer * clguiComponent::GetParent() {
  clguiObject* obj=clguiObjectManager::GetIns()->GetParent(this);
  return clguiObjectManager::ToContainer(obj);
}

void clguiComponent::SetSize(clint width,clint height){
  if(width>=0) m_size.x=width;
  if(height>=0)m_size.y=height;
}

void clguiComponent::GetSize(cluint* width,cluint* height)const{
  *width=m_size.x;
  *height=m_size.y;
}

void clguiComponent::ScaleSizeBy(clfloat f){
  m_size.x*=f;
  m_size.y*=f;
}

void clguiComponent::SetPosition(clint x,clint y){
  m_pos.x=x;
  m_pos.y=y;
}

void clguiComponent::GetPosition(clint* x,clint* y)const{
  *x=m_pos.x;
  *y=m_pos.y;
}

void clguiComponent::SetCaption(clstr caption){
  m_caption=caption+"##"+std::to_string(GetUniqueID()); 
}

clstr clguiComponent::GetCaption()const{
  clstr c;
  clint index=m_caption.find_first_of('#',0);
  c=m_caption.substr(0,index);
  return c; 
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

clguiComponent * clguiContainer::GetDirectChildByCaption(clstr caption){
  clguiObjectManager* mgr=clguiObjectManager::GetIns();
  clguiComponent* m=clguiObjectManager::ToComponent(mgr->GetFirstChild(this));
  while(m){
    if(std::strcmp(m->GetCaption().c_str(),caption.c_str())==0){
      return m;
    }
    m=clguiObjectManager::ToComponent(mgr->GetNextSibling(m));
  }
  return nullptr;
}






clguiStage::clguiStage()
  :clguiContainer(CLGUI_OBJECT_TYPE_STAGE){}

void clguiStage::NoticeWindowSize(clint width,clint height){
  clguiComponent::SetSize(width,height);
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
