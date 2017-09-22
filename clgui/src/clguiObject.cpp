#pragma once
#include "clguiObject.h"
#include "clguiEvent.h"
#include "clgui_object_manager.h"

namespace clgui{
using namespace std;
using namespace cl;

clguiObject::clguiObject(cluint type)
  :m_uUniqueID(GetUniqueUint())
  ,m_type(type){
  clguiObjectManager::GetIns()->AddObject(this);
  m_node=clguiObjectManager::GetIns()->m_hs.CreateNode();
};

clguiObject::~clguiObject(){ 
  clguiObjectManager::GetIns()->RemoveObject(this);
  clguiObjectManager::GetIns()->m_hs.RemoveNode(m_node->GetId());
  m_node=nullptr;
};

clguiInteractive::~clguiInteractive(){
  m_mapListeners_name_listener.clear();
};

void clguiInteractive::AddEventListener(clguiEventType type,CallBackEventFn* cbFn){
  vector<CallBackEventFn*>& tmpVec=m_mapListeners_name_listener[type];
  tmpVec.push_back(cbFn);
}

void clguiInteractive::DispatchEvent_(clguiEventType type,clguiEvent evt){
  vector<CallBackEventFn*>& tmpVec=m_mapListeners_name_listener[type];
  for(auto it:tmpVec){
    it(evt);
  }
}

clguiContainer::clguiContainer(cluint type)
  :clguiInteractive(type){};

clguiContainer::~clguiContainer(){
};

void clguiContainer::AddChild(clguiRenderable* child){
}
void clguiContainer::RemoveChild(clguiRenderable* child){
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
}
