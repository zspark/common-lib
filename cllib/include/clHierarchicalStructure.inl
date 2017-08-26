#include "clHierarchicalStructure.h"
#include <vector>
#include <iostream>
#include <iomanip>

namespace cl{
template<typename NODE>
clUi clHierarchicalStructure_T<NODE>::GetNextAvaliableNodeId(){
  return m_uNextAvaliableId++;
}

template<typename NODE>
NODE* clHierarchicalStructure_T<NODE>::CreateNode(){
  NODE* node=new NODE(GetNextAvaliableNodeId());
  return node;
}

template<typename NODE>
NODE* clHierarchicalStructure_T<NODE>::GetNode(clUi id){
  if(m_pRootNode->m_pFirstChildNode==nullptr)return nullptr;
  std::vector<NODE*> vec;
  vec.push_back(m_pRootNode->m_pFirstChildNode);
  NODE* tmpNode=nullptr;
  while(vec.size()!=0){
    tmpNode=vec.back();
    vec.pop_back();
    if(tmpNode->m_id==id)break;
    else{
      if(tmpNode->m_pNextSiblingNode!=nullptr)
        vec.push_back(tmpNode->m_pNextSiblingNode);
      if(tmpNode->m_pFirstChildNode!=nullptr)
        vec.push_back(tmpNode->m_pFirstChildNode);
      tmpNode=nullptr;
    }
  }
  return tmpNode;
}

template<typename NODE>
NODE* clHierarchicalStructure_T<NODE>::GetLastChildNode(NODE* node){
  NODE* tmpNode=node->m_pFirstChildNode;
  if(tmpNode==nullptr)return nullptr;
  while(tmpNode->m_pNextSiblingNode!=nullptr){
    tmpNode=tmpNode->m_pNextSiblingNode;
  }
  return tmpNode;
}

template<typename NODE>
NODE* clHierarchicalStructure_T<NODE>::DeleteNode(clUi id){
  NODE* tmpNode=GetNode(id);
  if(tmpNode==nullptr)return nullptr;
  else{
    NODE* firstNode=tmpNode->m_pFirstChildNode;
    RemoveRelation(tmpNode);
    delete tmpNode;
    return firstNode;
  }
}

template<typename NODE>
bool clHierarchicalStructure_T<NODE>::DeleteDecendantNodes(NODE* node){
  if(node->m_pFirstChildNode==nullptr)return false;
  std::vector<NODE*> vec;
  vec.push_back(node->m_pFirstChildNode);
  NODE* tmpNode=nullptr;
  while(vec.size()!=0){
    tmpNode=vec.back();
    vec.pop_back();
    if(tmpNode->m_pNextSiblingNode!=nullptr)
      vec.push_back(tmpNode->m_pNextSiblingNode);
    if(tmpNode->m_pFirstChildNode!=nullptr)
      vec.push_back(tmpNode->m_pFirstChildNode);
    delete tmpNode;
  }
  node->m_pFirstChildNode=nullptr;
  return true;
}

template<typename NODE>
bool clHierarchicalStructure_T<NODE>::DeleteDecendantNodes(clUi id){
  NODE* tmpNode=GetNode(id);
  if(tmpNode==nullptr)return false;
  return DeleteDecendantNodes(tmpNode);
}

template<typename NODE>
void clHierarchicalStructure_T<NODE>::DeleteAllNodes(){
  DeleteDecendantNodes(m_pRootNode);
}

template<typename NODE>
NODE* clHierarchicalStructure_T<NODE>::GetFirstNode(){
  if(m_pRootNode->m_pFirstChildNode==nullptr)return nullptr;
  m_vecTraverse.clear();
  NODE* tmpNode=m_pRootNode->m_pFirstChildNode;
  if(tmpNode->m_pNextSiblingNode!=nullptr)
    m_vecTraverse.push_back(tmpNode->m_pNextSiblingNode);
  if(tmpNode->m_pFirstChildNode!=nullptr)
    m_vecTraverse.push_back(tmpNode->m_pFirstChildNode);
  return tmpNode;
}

template<typename NODE>
NODE* clHierarchicalStructure_T<NODE>::GetNextNode(){
  NODE* tmpNode=nullptr;
  if(m_vecTraverse.size()!=0){
    tmpNode=m_vecTraverse.back();
    m_vecTraverse.pop_back();
    if(tmpNode->m_pNextSiblingNode!=nullptr)
      m_vecTraverse.push_back(tmpNode->m_pNextSiblingNode);
    if(tmpNode->m_pFirstChildNode!=nullptr)
      m_vecTraverse.push_back(tmpNode->m_pFirstChildNode);

  }
  return tmpNode;
}

template<typename NODE>
void clHierarchicalStructure_T<NODE>::RemoveRelation(NODE* node){
  NODE* const preNode=node->m_pPreSiblingNode;
  NODE* const nextNode=node->m_pNextSiblingNode;
  NODE* const parentNode=node->m_pParentdNode;
  NODE* const firstChildNode=node->m_pFirstChildNode;

  if(parentNode->m_pFirstChildNode==node){
    parentNode->m_pFirstChildNode=nextNode;
    if(nextNode!=nullptr)
      nextNode->m_pPreSiblingNode=nullptr;
  } else{
    preNode->m_pNextSiblingNode=nextNode;
    if(nextNode!=nullptr)
      nextNode->m_pPreSiblingNode=preNode;
  }
}

template<typename NODE>
NODE* clHierarchicalStructure_T<NODE>::RemoveNode(clUi id){
  NODE* tmpNode=GetNode(id);
  if(tmpNode==nullptr)return nullptr;
  else{
    RemoveRelation(tmpNode);
    tmpNode->m_pNextSiblingNode=nullptr;
    tmpNode->m_pParentdNode=nullptr;
    tmpNode->m_pPreSiblingNode=nullptr;
  }
  return tmpNode;
}

template<typename NODE>
NODE* clHierarchicalStructure_T<NODE>::IsNodeFirstChild(NODE* node){
  if(node->m_pParentdNode==node->m_pParentdNode->m_pFirstChildNode)
    return node->m_pParentdNode;
  else return nullptr;
}

template<typename NODE>
bool clHierarchicalStructure_T<NODE>::InsertNode(NODE* targetNode,NODE* srcNode,clHierarchicalStructureNodeRelation relation){
  if(targetNode==srcNode)return false;
  if(targetNode==nullptr){
    NODE* firstNode=m_pRootNode->m_pFirstChildNode;
    if(firstNode!=nullptr){
      return InsertNode(firstNode,srcNode,clHierarchicalStructureNodeRelation::R_NEXT_SIBLING);
    } else{
      m_pRootNode->m_pFirstChildNode=srcNode;
      srcNode->m_pParentdNode=m_pRootNode;
    }
    return true;
  }
  switch(relation){
  case R_NEXT_SIBLING:
  {
    NODE* nextNode=targetNode->m_pNextSiblingNode;
    targetNode->m_pNextSiblingNode=srcNode;
    srcNode->m_pPreSiblingNode=targetNode;
    srcNode->m_pNextSiblingNode=nextNode;
    srcNode->m_pParentdNode=targetNode->m_pParentdNode;
    if(nextNode!=nullptr)
      nextNode->m_pPreSiblingNode=srcNode;
  }
  break;
  case R_PRE_SIBLING:
  {
    NODE* preNode=targetNode->m_pPreSiblingNode;
    targetNode->m_pPreSiblingNode=srcNode;
    srcNode->m_pNextSiblingNode=targetNode;
    srcNode->m_pPreSiblingNode=preNode;
    srcNode->m_pParentdNode=targetNode->m_pParentdNode;
    if(preNode!=nullptr)
      preNode->m_pPreSiblingNode=srcNode;
    else targetNode->m_pParentdNode->m_pFirstChildNode=srcNode;
  }
  break;
  case R_FIRST_CHILD:
  {
    NODE* firstChildNode=targetNode->m_pFirstChildNode;
    targetNode->m_pFirstChildNode=srcNode;
    srcNode->m_pParentdNode=targetNode;
    if(firstChildNode!=nullptr){
      firstChildNode->m_pPreSiblingNode=srcNode;
      srcNode->m_pNextSiblingNode=firstChildNode;
    }
  }
  break;
  case R_LAST_CHILD:
  {
    NODE* lastChildNode=GetLastChildNode(targetNode);
    if(lastChildNode==nullptr){
      return InsertNode(targetNode,srcNode,clHierarchicalStructureNodeRelation::R_FIRST_CHILD);
    } else{
      srcNode->m_pParentdNode=targetNode;
      lastChildNode->m_pNextSiblingNode=srcNode;
      srcNode->m_pPreSiblingNode=lastChildNode;
    }

  }
  break;
  case R_NULL:
  default:
    break;
  }
  return true;
}

template<typename NODE>
clUi clHierarchicalStructure_T<NODE>::GetNumChildren(NODE* node)const{
  clUi sum=0;
  NODE* tmpNode=node->m_pFirstChildNode;
  while(tmpNode!=nullptr){
    sum++;
    tmpNode=tmpNode->m_pNextSiblingNode;
  }
  return sum;
}

template<typename NODE>
clUi clHierarchicalStructure_T<NODE>::GetNumChildren()const{
  return GetNumChildren(m_pRootNode);
}

template<typename NODE>
clUi clHierarchicalStructure_T<NODE>::GetDepth(NODE* node){
  clUi depth(0);
  NODE* tmpNode=node->m_pParentdNode;
  while(tmpNode!=m_pRootNode){
    depth++;
    tmpNode=tmpNode->m_pParentdNode;
  }
  return depth;
}

template<typename NODE>
void clHierarchicalStructure_T<NODE>::Print(){
  using namespace std;
  const clUi perDepthWidth(5);
  cout<<setiosflags(ios::left)<<setw(10)<<"Root:id=0"<<std::endl;

  if(m_pRootNode->m_pFirstChildNode==nullptr)return;
  std::vector<NODE*> vec;
  vec.push_back(m_pRootNode->m_pFirstChildNode);
  NODE* tmpNode=nullptr;
  while(vec.size()!=0){
    tmpNode=vec.back();
    vec.pop_back();
    if(tmpNode->m_pNextSiblingNode!=nullptr)
      vec.push_back(tmpNode->m_pNextSiblingNode);
    if(tmpNode->m_pFirstChildNode!=nullptr)
      vec.push_back(tmpNode->m_pFirstChildNode);

    clUi w=(2+GetDepth(tmpNode))*perDepthWidth;
    cout<<setiosflags(ios::left)<<setw(w)<<""<<"id="<<tmpNode->m_id<<std::endl;
  }
  return;
}
}