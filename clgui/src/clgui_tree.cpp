#include "clgui/component/clgui_tree.h"
#include "imgui\imgui.h"

CLGUI_NAMESPACE_START

clguiTree::clguiTree()
  :clguiComponent(CLGUI_OBJECT_TYPE_COMPONENT)
  ,m_cv(false){
  m_size.Set(60,30);
}

nodeID clguiTree::CreateNode(clchar * name,nodeID parentNodeID){
  nd* node=m_hs.CreateNode();
  node->customObject.name=name;
  node->customObject.flags=ImGuiTreeNodeFlags_OpenOnArrow
    |ImGuiTreeNodeFlags_OpenOnDoubleClick;
  if(parentNodeID<0){
    m_hs.InsertNode(nullptr,node,hsr::R_FIRST_CHILD);
  } else{
    nd* pNode=m_hs.GetNodeById(parentNodeID);
    m_hs.InsertNode(pNode,node,hsr::R_LAST_CHILD);
  }
  return node->GetId();
}

clguiTree::~clguiTree(){}

void clguiTree::Render(){
  m_isCtrlKeyDown=ImGui::GetIO().KeyCtrl;
  RenderSubNodes_(m_hs.GetFirstChildNode());
}

void clguiTree::PostRender(){
  if(m_cv.CheckChange()){
    //clguiEventButtonClick evt(this,clguiEventType::EVT_BUTTON_CLICK);
    //DispatchEvent_(&evt);
    m_cv.SetNewValue(false);
  }
}

void clguiTree::RenderSubNodes_(nd * node){
  bool isOpen;
  while(node){
    if(node->GetFirstChildNode()){
      node->customObject.flags&=~ImGuiTreeNodeFlags_Leaf;
    } else{
      node->customObject.flags|=ImGuiTreeNodeFlags_Leaf;
    }
    isOpen=ImGui::TreeNodeEx(node->customObject.name.c_str(),node->customObject.flags);
    if(ImGui::IsItemClicked()){
      if(m_isCtrlKeyDown)
        node->customObject.flags^=ImGuiTreeNodeFlags_Selected;
      else{
        node->customObject.flags|=ImGuiTreeNodeFlags_Selected;
      }
    } else{
      if(!m_isCtrlKeyDown)
        node->customObject.flags&=~ImGuiTreeNodeFlags_Selected;
    }
    if(isOpen){
      RenderSubNodes_(node->GetFirstChildNode());
      ImGui::TreePop();
    }
    node=node->GetNextSiblingNode();
  }
}



CLGUI_NAMESPACE_END
