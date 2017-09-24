#include "clgui_object_manager.h"
#include "clguiObject.h"

using namespace std;

CLGUI_NAMESPACE_START

typedef cl::hs::clHSNode_T<clguiObject*> node;

clguiObjectManager* clguiObjectManager::sIns=nullptr;
clguiObjectManager* clguiObjectManager::GetIns(){
  if(!sIns){
    sIns=new clguiObjectManager();
    sIns->Init();
  }
  return sIns;
}
void clguiObjectManager::DeleteIns(){
  if(sIns)delete sIns;
}

clguiObjectManager::clguiObjectManager(){
}
clguiObjectManager::~clguiObjectManager(){
  //delete all clguiobjects;
}

void clguiObjectManager::Init(){
  clguiStage* stage=new clguiStage();
  m_hs.InsertNode(nullptr,m_map_clguiObject_node[stage],cl::hs::clHSNodeRelation::R_FIRST_CHILD);
}

clguiStage * clguiObjectManager::GetStage(){
  return TryConvertTo<clguiStage*>(m_hs.GetFirstChildNode()->customObject,CLGUI_OBJECT_TYPE_STAGE);
}

clguiObject * clguiObjectManager::GetNextSibling(clguiObject * obj) const noexcept{
  node* nd=GetNodeByclguiObject_(obj);
  if(nd){
    if(nd->GetNextSiblingNode())return nd->GetNextSiblingNode()->customObject;
  } 
  return nullptr;
}

clguiObject * clguiObjectManager::GetFirstChild(clguiObject * obj) const noexcept{
  node* nd=GetNodeByclguiObject_(obj);
  if(nd){
    if(nd->GetFirstChildNode())return nd->GetFirstChildNode()->customObject;
  } 
  return nullptr;
}

clguiObject * clguiObjectManager::GetParent(clguiObject * child) const noexcept{
  node* cNode=GetNodeByclguiObject_(child); F_DBG_ASSERT(cNode);
  return (cNode->GetParentNode())?cNode->GetParentNode()->customObject:nullptr;
}

clguiContainer * clguiObjectManager::ToclguiContainer(clguiObject * obj) const noexcept{
  return TryConvertTo<clguiContainer*>(obj,CLGUI_OBJECT_TYPE_CONTAINER);
}

clguiComponent * clguiObjectManager::ToclguiComponent(clguiObject * obj) const noexcept{
  return TryConvertTo<clguiComponent*>(obj,CLGUI_OBJECT_TYPE_COMPONENT);
}

clguiRenderable * clguiObjectManager::ToclguiRenderable(clguiObject * obj) const noexcept{
  return TryConvertTo<clguiRenderable*>(obj,CLGUI_OBJECT_TYPE_RENDERABLE);
}

void clguiObjectManager::AddChildAt(clguiComponent * child,clguiContainer * parent,clint index){
  node* cNode=GetNodeByclguiObject_(child); F_DBG_ASSERT(cNode);
  node* pNode=GetNodeByclguiObject_(parent); F_DBG_ASSERT(pNode);

  if(m_hs.IsNodeInHS(cNode)){
    m_hs.RemoveNode(cNode);
  }
  cl::hs::clHSNodeRelation r;
  if(index<0)r=cl::hs::clHSNodeRelation::R_LAST_CHILD;
  else if(index==0)r=cl::hs::clHSNodeRelation::R_FIRST_CHILD;
  else{
    if(pNode->GetFirstChildNode()){
      pNode=pNode->GetFirstChildNode();
      pNode=m_hs.GetSiblingNodeByOffset(pNode,index-1);
      r=cl::hs::clHSNodeRelation::R_NEXT_SIBLING;
    } else{
      r=cl::hs::clHSNodeRelation::R_FIRST_CHILD;
    }
  }
  m_hs.InsertNode(pNode,cNode,r);
}

void clguiObjectManager::RemoveChild(clguiComponent * child){
  node* cNode=GetNodeByclguiObject_(child); F_DBG_ASSERT(cNode);
  m_hs.RemoveNode(cNode);
}

void clguiObjectManager::AddObject(clguiObject * obj){
  node* nd=m_hs.CreateNode();
  m_map_clguiObject_node[obj]=nd;
  nd->customObject=obj;
}

void clguiObjectManager::RemoveObject(clguiObject * obj){
  map<clguiObject*,node*>::const_iterator it=m_map_clguiObject_node.find(obj);
  if(it!=m_map_clguiObject_node.end()){
    m_hs.DeleteNode(it->second);
    m_map_clguiObject_node.erase(it);
  }
}

inline node * clguiObjectManager::GetNodeByclguiObject_(clguiObject * obj) const noexcept{
  map<clguiObject*,node*>::const_iterator it=m_map_clguiObject_node.find(obj);
  return it==m_map_clguiObject_node.end()?nullptr:it->second;
}



CLGUI_NAMESPACE_END
