#pragma once

#include "cl\cl_hierarchical_structure.h"

CL_NAMESPACE_START
namespace hs{


clHS::clHS()
  :m_pInvisibleUniqueRootNode(GetUniqueUint(),m_ID)
  ,m_ID(GetUniqueUint()){};

clHS::~clHS(){
  if(!m_bDestroied)throw "You need call DestroyAllNodes() before deleting HS";
};

clHSNode* clHS::CreateNode(){
  clHSNode* node=new clHSNode(GetUniqueUint(),m_ID);
  return node;
}

//return the node which has the given id, if not return nullptr;
clHSNode* clHS::GetNodeById(cluint id){
  if(m_pInvisibleUniqueRootNode.m_pFirstChildNode==nullptr)return nullptr;
  std::vector<clHSNode*> vec;
  vec.push_back(m_pInvisibleUniqueRootNode.m_pFirstChildNode);
  clHSNode* tmpNode=nullptr;
  while(vec.size()!=0){
    tmpNode=vec.back();
    vec.pop_back();
    if(tmpNode->m_ID==id)break;
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

clHSNode* clHS::GetSiblingNodeByOffset(clHSNode* node,clint offset){
  if(offset==0)return node;
  while(node){
    if(offset>0){
      if(node->m_pNextSiblingNode){
        node=node->m_pNextSiblingNode;
        offset--;
      } else return node;
    } else{
      if(node->m_pPreSiblingNode){
        node=node->m_pPreSiblingNode;
        offset++;
      } else return node;
    }
    if(offset==0)return node;
  }
  return nullptr;
}

clHSNode* clHS::GetLastChildNode(clHSNode* node){
  if(!node)node=&m_pInvisibleUniqueRootNode;
  clHSNode* tmpNode=node->m_pFirstChildNode;
  if(!tmpNode)return nullptr;
  while(tmpNode->m_pNextSiblingNode){
    tmpNode=tmpNode->m_pNextSiblingNode;
  }
  return tmpNode;
}

clHSNode* clHS::GetFirstChildNode(clHSNode* node){
  if(node)return node->m_pFirstChildNode;
  return m_pInvisibleUniqueRootNode.m_pFirstChildNode;
}

clHSNode* clHS::DeleteNode(cluint id,clbool alongWithCustom){
  clHSNode* tmpNode=GetNodeById(id);
  if(tmpNode){
    return DeleteNode(tmpNode,alongWithCustom);
  } else return nullptr;
}

clHSNode* clHS::DeleteNode(clHSNode* node,clbool alongWithCustom){
  if(IsNodeInHS(node)) ReconstructRelationWithout_(node);
  ClearAllChildrenParentNode_(node);
  clHSNode* firstNode=node->m_pFirstChildNode;
  if(alongWithCustom&&node->custom)delete node->custom;
  delete node;
  return firstNode;
}

clbool clHS::DeleteDecendantNodes(cluint id,clbool alongWithCustom){
  clHSNode* tmpNode=GetNodeById(id);
  if(tmpNode) return DeleteDecendantNodes(tmpNode,alongWithCustom);
  return false;
}

clbool clHS::DeleteDecendantNodes(clHSNode* node,clbool alongWithCustom){
  if(node->m_pFirstChildNode==nullptr)return false;
  std::vector<clHSNode*> vec;
  vec.push_back(node->m_pFirstChildNode);
  clHSNode* tmpNode=nullptr;
  while(vec.size()!=0){
    tmpNode=vec.back();
    vec.pop_back();
    if(tmpNode->m_pNextSiblingNode!=nullptr)
      vec.push_back(tmpNode->m_pNextSiblingNode);
    if(tmpNode->m_pFirstChildNode!=nullptr)
      vec.push_back(tmpNode->m_pFirstChildNode);
    if(alongWithCustom&&node->custom)delete node->custom;
    delete tmpNode;
  }
  node->m_pFirstChildNode=nullptr;
  return true;
}

clHSNode* clHS::RemoveNode(cluint id){
  clHSNode* tmpNode=GetNodeById(id);
  if(tmpNode){
    RemoveNode(tmpNode);
    return tmpNode;
  } else return nullptr;
}

void clHS::RemoveNode(clHSNode* node){
  ReconstructRelationWithout_(node);
  node->m_pNextSiblingNode=nullptr;
  node->m_pParentNode=nullptr;
  node->m_pPreSiblingNode=nullptr;
}

clHSInsertResult clHS::InsertNode(clHSNode* targetNode,clHSNode* srcNode,clHSNodeRelation relation){
  if(srcNode->m_HSID!=m_ID)return clHSInsertResult::HS_INSERT_RESULT_DIFFERENT_KIND_OF_NODE;
  if(targetNode && targetNode->m_HSID!=m_ID)return clHSInsertResult::HS_INSERT_RESULT_DIFFERENT_KIND_OF_NODE;
  if(targetNode==srcNode)return clHSInsertResult::HS_INSERT_RESULT_SAME_NODE;
  if(IsNodeInHS(srcNode))return clHSInsertResult::HS_INSERT_RESULT_SOURCE_NODE_ALREADY_IN_HS;

  if(targetNode==nullptr){
    clHSNode* lastChild=GetLastChildNode();
    if(lastChild){
      return InsertNode(lastChild,srcNode,clHSNodeRelation::R_NEXT_SIBLING);
    } else{
      m_pInvisibleUniqueRootNode.m_pFirstChildNode=srcNode;
      ////////////////////////////////////////////////////////////////////////////////////////////////////
      // invisible node CAN NOT been seen;
      // so to comment next line with second line;
      //srcNode->m_pParentNode=m_pInvisibleUniqueRootNode;
      srcNode->m_pParentNode=nullptr;
      ////////////////////////////////////////////////////////////////////////////////////////////////////
      return clHSInsertResult::HS_INSERT_RESULT_SUCCESS;
    }
  }
  switch(relation){
  case clHSNodeRelation::R_NEXT_SIBLING:
  {
    clHSNode* nextNode=targetNode->m_pNextSiblingNode;
    srcNode->m_pNextSiblingNode=nextNode;
    if(nextNode) nextNode->m_pPreSiblingNode=srcNode;
    targetNode->m_pNextSiblingNode=srcNode;
    srcNode->m_pPreSiblingNode=targetNode;
    srcNode->m_pParentNode=targetNode->m_pParentNode;
  }
  break;
  case clHSNodeRelation::R_PRE_SIBLING:
  {
    clHSNode* preNode=targetNode->m_pPreSiblingNode;
    srcNode->m_pPreSiblingNode=preNode;
    if(preNode) preNode->m_pNextSiblingNode=srcNode;
    else targetNode->m_pParentNode->m_pFirstChildNode=srcNode;
    targetNode->m_pPreSiblingNode=srcNode;
    srcNode->m_pNextSiblingNode=targetNode;
    srcNode->m_pParentNode=targetNode->m_pParentNode;
  }
  break;
  case clHSNodeRelation::R_FIRST_CHILD:
  {
    clHSNode* firstChildNode=targetNode->m_pFirstChildNode;
    if(firstChildNode){
      firstChildNode->m_pPreSiblingNode=srcNode;
      srcNode->m_pNextSiblingNode=firstChildNode;
    }
    targetNode->m_pFirstChildNode=srcNode;
    srcNode->m_pParentNode=targetNode;
  }
  break;
  case clHSNodeRelation::R_LAST_CHILD:
  {
    clHSNode* lastChildNode=GetLastChildNode(targetNode);
    if(lastChildNode){
      srcNode->m_pParentNode=targetNode;
      lastChildNode->m_pNextSiblingNode=srcNode;
      srcNode->m_pPreSiblingNode=lastChildNode;
    } else{
      return InsertNode(targetNode,srcNode,clHSNodeRelation::R_FIRST_CHILD);
    }

  }
  break;
  case clHSNodeRelation::R_NULL:
  default:
    return clHSInsertResult::HS_INSERT_RESULT_NO_OPERATION;
    break;
  }
  return clHSInsertResult::HS_INSERT_RESULT_SUCCESS;
}

cluint clHS::GetNumChildren(const clHSNode* node)const{
  if(!node)node=&m_pInvisibleUniqueRootNode;
  cluint sum=0;
  clHSNode* tmpNode=node->m_pFirstChildNode;
  while(tmpNode){
    sum++;
    tmpNode=tmpNode->m_pNextSiblingNode;
  }
  return sum;
}

clbool clHS::IsNodeInHS(clHSNode* node)const{
  if(!node)return false;
  while(node->m_pParentNode){
    node=node->m_pParentNode;
  }
  clHSNode* nd=m_pInvisibleUniqueRootNode.m_pFirstChildNode;
  while(nd){
    if(nd==node)return true;
    nd=nd->m_pNextSiblingNode;
  }
  return false;
}

clHSNode* clHS::Traverse(const clHSNode* root,clbool begin){
  if(begin){
    m_trNode=root?root->m_pFirstChildNode:m_pInvisibleUniqueRootNode.m_pFirstChildNode;
    return m_trNode;
  } else{
    if(m_trNode){
      if(m_trNode->m_pFirstChildNode){
        m_trNode=m_trNode->m_pFirstChildNode;
        return m_trNode;
      } else if(m_trNode->m_pNextSiblingNode){
        m_trNode=m_trNode->m_pNextSiblingNode;
        return m_trNode;
      } else{
        m_trNode=m_trNode->m_pParentNode;
        if(m_trNode==root)return nullptr;
        while(m_trNode){
          if(m_trNode->m_pNextSiblingNode){
            m_trNode=m_trNode->m_pNextSiblingNode;
            return m_trNode;
          } else{
            m_trNode=m_trNode->m_pParentNode;
            if(m_trNode==root)return nullptr;
          }
        };
        return nullptr;
      }
    } else return nullptr;
  }
}

cluint clHS::GetDecendantNodes(const clHSNode* pNode,std::vector<clHSNode*>& out){
  clHSNode* tmp=Traverse(pNode,true);
  cluint n=0;
  while(tmp){
    n++;
    out.push_back(tmp);
    tmp=Traverse(pNode);
  }
  return n;
}

void clHS::DeleteAllNodes(clbool alongWithCustom){
  DeleteDecendantNodes(&m_pInvisibleUniqueRootNode,alongWithCustom);
  m_bDestroied=true;
}

//print graph info;
void clHS::Print()const{
#if __CL_INTERNAL_DEBUG__
  using namespace std;
  const cluint perDepthWidth(3);
  //std::cout<<setiosflags(ios::left)<<setw(10)<<"Root:id=0"<<std::endl;

  if(m_pInvisibleUniqueRootNode.m_pFirstChildNode==nullptr)return;
  std::vector<clHSNode*> vec;
  vec.push_back(m_pInvisibleUniqueRootNode.m_pFirstChildNode);
  clHSNode* tmpNode=nullptr;
  while(vec.size()!=0){
    tmpNode=vec.back();
    vec.pop_back();
    if(tmpNode->m_pNextSiblingNode!=nullptr)
      vec.push_back(tmpNode->m_pNextSiblingNode);
    if(tmpNode->m_pFirstChildNode!=nullptr)
      vec.push_back(tmpNode->m_pFirstChildNode);

    cluint w=(GetDepth_(tmpNode))*perDepthWidth;
    std::cout<<setiosflags(ios::left)<<setw(w)<<""<<"id="<<tmpNode->m_ID<<std::endl;
  }
  return;
#endif
}

void clHS::ReconstructRelationWithout_(clHSNode* node){
  clHSNode* const preNode=node->m_pPreSiblingNode;
  clHSNode* const nextNode=node->m_pNextSiblingNode;
  clHSNode* const parentNode=node->m_pParentNode;

  if(parentNode->m_pFirstChildNode==node){
    parentNode->m_pFirstChildNode=nextNode;
    if(nextNode) nextNode->m_pPreSiblingNode=nullptr;
  } else{
    preNode->m_pNextSiblingNode=nextNode;
    if(nextNode) nextNode->m_pPreSiblingNode=preNode;
  }
}

#if __CL_INTERNAL_DEBUG__
//except root node ,all root node's children are at depth of 0;
cluint clHS::GetDepth_(clHSNode* node)const{
  cluint depth(0);
  clHSNode* tmpNode=node->m_pParentNode;
  while(tmpNode){
    depth++;
    tmpNode=tmpNode->m_pParentNode;
  }
  return depth;
}
#endif

void clHS::ClearAllChildrenParentNode_(clHSNode* parentNode){
  clHSNode* firstChild=parentNode->m_pFirstChildNode;
  while(firstChild){
    firstChild->m_pParentNode=nullptr;
    firstChild=firstChild->m_pNextSiblingNode;
  }
}

}

CL_NAMESPACE_END
