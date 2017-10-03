#include "clgui_object_manager.h"
#include "clgui/core/clgui_object.h"
#include "clgui/clgui_menu_bar.h"
#include "clgui/clgui_menu.h"
#include "clgui/clgui_menu_item.h"

using namespace std;

CLGUI_NAMESPACE_START

template<typename T>
inline T TryConvertTo(clguiObject* obj,cluint type)noexcept{
  return ((obj->GetType()&type)==type)?static_cast<T>(obj):nullptr;
}


typedef cl::hs::clHSNode_T<clguiObject*> node;

clguiObjectManager* clguiObjectManager::sIns=nullptr;
clguiObjectManager* clguiObjectManager::GetIns(){
  if(!sIns){
    sIns=new clguiObjectManager();
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

/*
cluint clguiObjectManager::GetMenubarHeight() noexcept{
  clguiMenuBar* mb=nullptr;
  mb=Traverse<clguiMenuBar>(CLGUI_OBJECT_TYPE_MENUBAR,true);
  while(mb){
    return 20;
  }
  return 0;
}
*/

void clguiObjectManager::GetAllDecendant(clguiObject * parent,vector<clguiObject*>& out) noexcept{
  node* nd=GetNodeByclguiObject_(parent); F_DBG_ASSERT(nd);
  m_hs.GetDecendantCustom(nd,out);
}

clguiContainer * clguiObjectManager::ToContainer(clguiObject * obj) noexcept{
  return TryConvertTo<clguiContainer*>(obj,CLGUI_OBJECT_TYPE_CONTAINER);
}

clguiComponent * clguiObjectManager::ToComponent(clguiObject * obj) noexcept{
  return TryConvertTo<clguiComponent*>(obj,CLGUI_OBJECT_TYPE_COMPONENT);
}

clguiRenderable * clguiObjectManager::ToRenderable(clguiObject * obj) noexcept{
  return TryConvertTo<clguiRenderable*>(obj,CLGUI_OBJECT_TYPE_RENDERABLE);
}

clguiMenuBar * clguiObjectManager::ToMenubar(clguiObject * obj) noexcept{
  return TryConvertTo<clguiMenuBar*>(obj,CLGUI_OBJECT_TYPE_MENUBAR);
}

clguiMenu * clguiObjectManager::ToMenu(clguiObject * obj) noexcept{
  return TryConvertTo<clguiMenu*>(obj,CLGUI_OBJECT_TYPE_MENU);
}

clguiMenuItem * clguiObjectManager::ToMenuItem(clguiObject * obj) noexcept{
  return TryConvertTo<clguiMenuItem*>(obj,CLGUI_OBJECT_TYPE_MENU_ITEM);
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

void clguiObjectManager::DeleteObject(clguiObject * obj){
  map<clguiObject*,node*>::const_iterator it=m_map_clguiObject_node.find(obj);
  if(it!=m_map_clguiObject_node.end()){
    m_hs.DeleteNode(it->second);
    m_map_clguiObject_node.erase(it);
    delete obj;
  }
}

inline node * clguiObjectManager::GetNodeByclguiObject_(clguiObject * obj) const noexcept{
  map<clguiObject*,node*>::const_iterator it=m_map_clguiObject_node.find(obj);
  return it==m_map_clguiObject_node.end()?nullptr:it->second;
}



CLGUI_NAMESPACE_END
