#pragma once

#include "core\cl_lib_compile.h"
#if __CLLIB_INTERNAL_DEBUG__
#include <iostream>
#include <iomanip>
#endif
#include <vector>

namespace cl{
namespace hs{

enum clHSNodeRelation{
  R_NULL=0,
  R_NEXT_SIBLING,
  R_PRE_SIBLING,
  R_FIRST_CHILD,
  R_LAST_CHILD,
};

template<typename T>
class clHSNode_T{
private:
  clHSNode_T(cluint id):m_id(id){};

  ~clHSNode_T(){
    m_pParentNode=nullptr;
    m_pPreSiblingNode=nullptr;
    m_pNextSiblingNode=nullptr;
    m_pFirstChildNode=nullptr;
  };

public:
  inline cluint GetId()const{ return m_id; }
  clHSNode_T* GetParentNode()const{ return m_pParentNode; }
  clHSNode_T* GetPreSiblingNode()const{ return m_pPreSiblingNode; }
  clHSNode_T* GetNextSiblingNode()const{ return m_pNextSiblingNode; }
  clHSNode_T* GetFirstChildNode()const{ return m_pFirstChildNode; }

  //One cant change id of a exist node;void SetId(cluint id) { m_id=id; }
  T* customObject=nullptr;

private:
  template<typename,template<typename>class>friend class clHS_T;
  //template<T,template<typename>class> friend class clHS_T;

  cluint m_id;//unique;
  clHSNode_T* m_pParentNode=nullptr;
  clHSNode_T* m_pPreSiblingNode=nullptr;
  clHSNode_T* m_pNextSiblingNode=nullptr;
  clHSNode_T* m_pFirstChildNode=nullptr;
};

template<typename T,template<typename> class NODE=clHSNode_T>
class clHS_T{
private:
  NODE<T>* const m_pInvisibleUniqueRootNode;
  std::vector<NODE<T>*> m_vecTraserseUseOnly;

public:
  clHS_T():m_pInvisibleUniqueRootNode(new NODE<T>(0)){};
  ~clHS_T(){
    DeleteDecendantNodes_(m_pInvisibleUniqueRootNode);
    delete m_pInvisibleUniqueRootNode;
  };

  /**
  * just create a new node ,then return ,nothing else .
  * but you cant create one using "new",
  * because all nodes have their unique id which is controled by scene graph.
  */
  NODE<T>* CreateNode(){
    NODE<T>* node=new NODE<T>(GetUniqueUint());
    node->
    NODE<clint> node2=new NODE<clint>(1);
    node2->
    return node;
  }

  //return the node which has the given id, if not return nullptr;
  NODE<T>* GetNodeById(cluint id){
    if(m_pInvisibleUniqueRootNode->m_pFirstChildNode==nullptr)return nullptr;
    std::vector<NODE<T>*> vec;
    vec.push_back(m_pInvisibleUniqueRootNode->m_pFirstChildNode);
    NODE<T>* tmpNode=nullptr;
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

  /**
  * return the last child node of the given node;
  * if node has no children then return nullptr;
  * and if node is nullptr, return invisibleRootNode's last child;
  */
  NODE<T>* GetLastChildNode(NODE<T>* node){
    if(!node)node=m_pInvisibleUniqueRootNode;
    NODE<T>* tmpNode=node->m_pFirstChildNode;
    if(!tmpNode)return nullptr;
    while(tmpNode->m_pNextSiblingNode){
      tmpNode=tmpNode->m_pNextSiblingNode;
    }
    return tmpNode;
  }

  /**
  * return node first child node;
  * if node has no children nodes then return nullptr;
  * and if node is nullptr return invisibleRootNode's first child;
  */
  NODE<T>* GetFirstChildNode(NODE<T>* node=nullptr){
    if(node)return node->m_pFirstChildNode;
    return m_pInvisibleUniqueRootNode->m_pFirstChildNode;
  }

  /**
  * if node exist,then remove it from graph and delete it,and return it's first child node;
  * if not return nullptr;
  */
  NODE<T>* DeleteNode(cluint id){
    NODE<T>* tmpNode=GetNode(id);
    if(tmpNode==nullptr)return nullptr;
    else{
      NODE<T>* firstNode=tmpNode->m_pFirstChildNode;
      ReconstructRelationWithout_(tmpNode);
      delete tmpNode;
      return firstNode;
    }
  }

  //this will delete all nodes which have the same parent id.
  clbool DeleteDecendantNodes(cluint id){
    NODE<T>* tmpNode=GetNode(id);
    if(tmpNode==nullptr)return false;
    return DeleteDecendantNodes_(tmpNode);
  }

  //just return the node which has given id;if not return nullptr;
  // removeNode method will remove all relations of returning node except it's link to firstchildnode;
  // you can delete returned node by DeleteNode method;
  // or adding it back to graph.
  NODE<T>* RemoveNode(cluint id){
    NODE<T>* tmpNode=GetNode(id);
    if(tmpNode==nullptr)return nullptr;
    else{
      ReconstructRelationWithout_(tmpNode);
      tmpNode->m_pNextSiblingNode=nullptr;
      tmpNode->m_pParentNode=nullptr;
      tmpNode->m_pPreSiblingNode=nullptr;
    }
    return tmpNode;
  }

  //insert srcNode which has relation with targetNode to targetNode.
  //if targetNode is nullptr,means rootnode. in this case,all relation is ignord. we will 
  //add srcNode as root's child.
  clbool InsertNode(NODE<T>* targetNode,NODE<T>* srcNode,clHSNodeRelation relation){
    if(targetNode==srcNode)return false;
    if(targetNode==nullptr){
      NODE<T>* firstNode=m_pInvisibleUniqueRootNode->m_pFirstChildNode;
      if(firstNode){
        return InsertNode(firstNode,srcNode,clHSNodeRelation::R_NEXT_SIBLING);
      } else{
        m_pInvisibleUniqueRootNode->m_pFirstChildNode=srcNode;
        // invisible node CAN NOT been seen;
        //srcNode->m_pParentNode=m_pInvisibleUniqueRootNode;
      }
      return true;
    }
    switch(relation){
    case R_NEXT_SIBLING:
    {
      NODE<T>* nextNode=targetNode->m_pNextSiblingNode;
      targetNode->m_pNextSiblingNode=srcNode;
      srcNode->m_pPreSiblingNode=targetNode;
      srcNode->m_pNextSiblingNode=nextNode;
      srcNode->m_pParentNode=targetNode->m_pParentNode;
      if(nextNode!=nullptr)
        nextNode->m_pPreSiblingNode=srcNode;
    }
    break;
    case R_PRE_SIBLING:
    {
      NODE<T>* preNode=targetNode->m_pPreSiblingNode;
      targetNode->m_pPreSiblingNode=srcNode;
      srcNode->m_pNextSiblingNode=targetNode;
      srcNode->m_pPreSiblingNode=preNode;
      srcNode->m_pParentNode=targetNode->m_pParentNode;
      if(preNode!=nullptr)
        preNode->m_pPreSiblingNode=srcNode;
      else targetNode->m_pParentNode->m_pFirstChildNode=srcNode;
    }
    break;
    case R_FIRST_CHILD:
    {
      NODE<T>* firstChildNode=targetNode->m_pFirstChildNode;
      targetNode->m_pFirstChildNode=srcNode;
      srcNode->m_pParentNode=targetNode;
      if(firstChildNode!=nullptr){
        firstChildNode->m_pPreSiblingNode=srcNode;
        srcNode->m_pNextSiblingNode=firstChildNode;
      }
    }
    break;
    case R_LAST_CHILD:
    {
      NODE<T>* lastChildNode=GetLastChildNode(targetNode);
      if(lastChildNode==nullptr){
        return InsertNode(targetNode,srcNode,clHSNodeRelation::R_FIRST_CHILD);
      } else{
        srcNode->m_pParentNode=targetNode;
        lastChildNode->m_pNextSiblingNode=srcNode;
        srcNode->m_pPreSiblingNode=lastChildNode;
      }

    }
    break;
    case R_NULL:
    default:
      return false;
      break;
    }
    return true;
  }

  //return all children number of given node except it's decendant ;
  cluint GetNumChildren(NODE<T>* node)const{
    cluint sum=0;
    NODE<T>* tmpNode=node->m_pFirstChildNode;
    while(tmpNode!=nullptr){
      sum++;
      tmpNode=tmpNode->m_pNextSiblingNode;
    }
    return sum;

  }
  //return all children number of root node except it's decendant.
  cluint GetNumChildren()const{
    return GetNumChildren(m_pInvisibleUniqueRootNode);
  }

  /**
  *except root node,remember rootnode cant be destroyed!
  *unless this structure instance was destroyed
  */
  void DeleteAllNodes(){
    DeleteDecendantNodes_(m_pInvisibleUniqueRootNode);
  }
  
  // traserse begin;
  NODE<T>* TraverseBegin(){
    if(m_pInvisibleUniqueRootNode->m_pFirstChildNode==nullptr)return nullptr;
    m_vecTraserseUseOnly.clear();
    NODE<T>* tmpNode=m_pInvisibleUniqueRootNode->m_pFirstChildNode;
    if(tmpNode->m_pNextSiblingNode!=nullptr)
      m_vecTraserseUseOnly.push_back(tmpNode->m_pNextSiblingNode);
    if(tmpNode->m_pFirstChildNode!=nullptr)
      m_vecTraserseUseOnly.push_back(tmpNode->m_pFirstChildNode);
    return tmpNode;
  }

  // traserse continue;
  // if return value is nullptr ,means over;
  NODE<T>* TraverContinue(){
    NODE<T>* tmpNode=nullptr;
    if(m_vecTraserseUseOnly.size()!=0){
      tmpNode=m_vecTraserseUseOnly.back();
      m_vecTraserseUseOnly.pop_back();
      if(tmpNode->m_pNextSiblingNode!=nullptr)
        m_vecTraserseUseOnly.push_back(tmpNode->m_pNextSiblingNode);
      if(tmpNode->m_pFirstChildNode!=nullptr)
        m_vecTraserseUseOnly.push_back(tmpNode->m_pFirstChildNode);
    }
    return tmpNode;
  }

  //print graph info;
  void Print()const{
#if __CLLIB_INTERNAL_DEBUG__
    using namespace std;
    const cluint perDepthWidth(3);
    //std::cout<<setiosflags(ios::left)<<setw(10)<<"Root:id=0"<<std::endl;

    if(m_pInvisibleUniqueRootNode->m_pFirstChildNode==nullptr)return;
    std::vector<NODE<T>*> vec;
    vec.push_back(m_pInvisibleUniqueRootNode->m_pFirstChildNode);
    NODE<T>* tmpNode=nullptr;
    while(vec.size()!=0){
      tmpNode=vec.back();
      vec.pop_back();
      if(tmpNode->m_pNextSiblingNode!=nullptr)
        vec.push_back(tmpNode->m_pNextSiblingNode);
      if(tmpNode->m_pFirstChildNode!=nullptr)
        vec.push_back(tmpNode->m_pFirstChildNode);

      cluint w=(GetDepth_(tmpNode))*perDepthWidth;
      std::cout<<setiosflags(ios::left)<<setw(w)<<""<<"id="<<tmpNode->m_id<<std::endl;
    }
    return;
#endif
  }


private:
  void ReconstructRelationWithout_(NODE<T>* node){
    NODE<T>* const preNode=node->m_pPreSiblingNode;
    NODE<T>* const nextNode=node->m_pNextSiblingNode;
    NODE<T>* const parentNode=node->m_pParentNode;

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

#if __CLLIB_INTERNAL_DEBUG__
  //except root node ,all root node's children are at depth of 0;
  cluint GetDepth_(NODE<T>* node)const{
    cluint depth(0);
    NODE<T>* tmpNode=node->m_pParentNode;
    while(tmpNode){
      depth++;
      tmpNode=tmpNode->m_pParentNode;
    }
    return depth;
  }
#endif

  //return parent node if node is it's first child;
  //else return nullptr;
  NODE<T>* IsNodeFirstChild_(NODE<T>* node){
    if(node==node->m_pParentNode->m_pFirstChildNode)
      return node->m_pParentNode==m_pInvisibleUniqueRootNode?nullptr:node->m_pParentNode;
    else return nullptr;
  }

  //delete node;
  clbool DeleteDecendantNodes_(NODE<T>* node){
    if(node->m_pFirstChildNode==nullptr)return false;
    std::vector<NODE<T>*> vec;
    vec.push_back(node->m_pFirstChildNode);
    NODE<T>* tmpNode=nullptr;
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
};

}
}
