#pragma once

#include <vector>
#include "cl_types.h"
#if __CL_INTERNAL_DEBUG__
#include <iostream>
#include <iomanip>
#endif

CL_NAMESPACE_START
namespace hs{

enum class clHSInsertResult{
  HS_INSERT_RESULT_SUCCESS=0,
  HS_INSERT_RESULT_SAME_NODE,
  HS_INSERT_RESULT_NO_OPERATION,
  HS_INSERT_RESULT_DIFFERENT_KIND_OF_NODE,
  HS_INSERT_RESULT_SOURCE_NODE_ALREADY_IN_HS,
};

enum class clHSNodeRelation{
  R_NULL=0,
  R_NEXT_SIBLING,
  R_PRE_SIBLING,
  R_FIRST_CHILD,
  R_LAST_CHILD,
};

template<typename T>
class clHSNode_T{
private:
  clHSNode_T(cluint ID,cluint HSID):m_ID(ID),m_HSID(HSID){};
  ~clHSNode_T(){
    m_pParentNode=nullptr;
    m_pPreSiblingNode=nullptr;
    m_pNextSiblingNode=nullptr;
    m_pFirstChildNode=nullptr;
  };

public:
  inline cluint GetId()const{ return m_ID; }
  clHSNode_T* GetParentNode()const{ return m_pParentNode; }
  clHSNode_T* GetPreSiblingNode()const{ return m_pPreSiblingNode; }
  clHSNode_T* GetNextSiblingNode()const{ return m_pNextSiblingNode; }
  clHSNode_T* GetFirstChildNode()const{ return m_pFirstChildNode; }

  //One cant change id of a exist node;void SetId(cluint id) { m_ID=id; }
  T customObject;

private:
  template<typename,template<typename>class>friend class clHS_T;
  //template<T,template<typename>class> friend class clHS_T;

  const cluint m_ID;//unique;
  const cluint m_HSID;
  clHSNode_T* m_pParentNode=nullptr;
  clHSNode_T* m_pPreSiblingNode=nullptr;
  clHSNode_T* m_pNextSiblingNode=nullptr;
  clHSNode_T* m_pFirstChildNode=nullptr;
};

enum clHSMode{
  HS_MODE_NODE=0,
  HS_MODE_CUSTOM,
};

template<typename T,template<typename> class NODE=clHSNode_T>
class clHS_T{
private:
  NODE<T>* const m_pInvisibleUniqueRootNode;
  NODE<T>* m_trNode;
  const cluint m_ID;

public:
  clHS_T():m_pInvisibleUniqueRootNode(new NODE<T>(GetUniqueUint(),m_ID))
    ,m_ID(GetUniqueUint()){
  };
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
    NODE<T>* node=new NODE<T>(GetUniqueUint(),m_ID);
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

  // returns node's sibling node by offset
  // node should NOT be nullptr;
  // if offset gets out of range, then returns it's parent's first or last node
  // offset 0 means node itself;
  NODE<T>* GetSiblingNodeByOffset(NODE<T>* node,clint offset){
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

  /**
  * return the last child node of the given node;
  * if node has no children then return nullptr;
  * and if node is nullptr, return invisibleRootNode's last child;
  */
  NODE<T>* GetLastChildNode(NODE<T>* node=nullptr){
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
    NODE<T>* tmpNode=GetNodeById(id);
    if(tmpNode){
      return DeleteNode(tmpNode);
    } else return nullptr;
  }

  /**
  * if node exist,then remove it from graph and delete it,and return it's first child node;
  * if not return nullptr;
  */
  NODE<T>* DeleteNode(NODE<T>* node){
    if(IsNodeInHS(node)) ReconstructRelationWithout_(node);
    ClearAllChildrenParentNode_(node);
    NODE<T>* firstNode=node->m_pFirstChildNode;
    delete node;
    return firstNode;
  }

  //this will delete all nodes which have the same parent id.
  clbool DeleteDecendantNodes(cluint id){
    NODE<T>* tmpNode=GetNodeById(id);
    if(tmpNode) return DeleteDecendantNodes_(tmpNode);
    return false;
  }

  //just return the node which has given id;if not return nullptr;
  // removeNode method will remove all relations of returning node except it's link to firstchildnode;
  // you can delete returned node by DeleteNode method;
  // or adding it back to graph.
  // and hs will be reconstructed;
  NODE<T>* RemoveNode(cluint id){
    NODE<T>* tmpNode=GetNodeById(id);
    if(tmpNode){
      RemoveNode(tmpNode);
      return tmpNode;
    } else return nullptr;
  }

  // removeNode method will remove all relations of given node except it's link to firstchildnode;
  // and hs will be reconstructed;
  void RemoveNode(NODE<T>* node){
    ReconstructRelationWithout_(node);
    node->m_pNextSiblingNode=nullptr;
    node->m_pParentNode=nullptr;
    node->m_pPreSiblingNode=nullptr;
  }

  //insert srcNode which has relation with targetNode to targetNode.
  //if targetNode is nullptr,means invisibleRootNode. in this case,all relation is ignord. 
  //we will add srcNode as root's child.
  // targetNode(if not null) and srcNode MUST be created by this HS;
  // srcNode should NOT be in HS;
  clHSInsertResult InsertNode(NODE<T>* targetNode,NODE<T>* srcNode,clHSNodeRelation relation){
    if(srcNode->m_HSID!=m_ID)return clHSInsertResult::HS_INSERT_RESULT_DIFFERENT_KIND_OF_NODE;
    if(targetNode && targetNode->m_HSID!=m_ID)return clHSInsertResult::HS_INSERT_RESULT_DIFFERENT_KIND_OF_NODE;
    if(targetNode==srcNode)return clHSInsertResult::HS_INSERT_RESULT_SAME_NODE;
    if(IsNodeInHS(srcNode))return clHSInsertResult::HS_INSERT_RESULT_SOURCE_NODE_ALREADY_IN_HS;

    if(targetNode==nullptr){
      NODE<T>* lastChild=GetLastChildNode();
      if(lastChild){
        return InsertNode(lastChild,srcNode,clHSNodeRelation::R_NEXT_SIBLING);
      } else{
        m_pInvisibleUniqueRootNode->m_pFirstChildNode=srcNode;
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
      NODE<T>* nextNode=targetNode->m_pNextSiblingNode;
      srcNode->m_pNextSiblingNode=nextNode;
      if(nextNode) nextNode->m_pPreSiblingNode=srcNode;
      targetNode->m_pNextSiblingNode=srcNode;
      srcNode->m_pPreSiblingNode=targetNode;
      srcNode->m_pParentNode=targetNode->m_pParentNode;
    }
    break;
    case clHSNodeRelation::R_PRE_SIBLING:
    {
      NODE<T>* preNode=targetNode->m_pPreSiblingNode;
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
      NODE<T>* firstChildNode=targetNode->m_pFirstChildNode;
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
      NODE<T>* lastChildNode=GetLastChildNode(targetNode);
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

  //return all children number of given node except it's decendant ;
  // if node==nullptr, means how many root nodes;
  cluint GetNumChildren(NODE<T>* node=nullptr)const{
    if(!node)node=m_pInvisibleUniqueRootNode;
    cluint sum=0;
    NODE<T>* tmpNode=node->m_pFirstChildNode;
    while(tmpNode){
      sum++;
      tmpNode=tmpNode->m_pNextSiblingNode;
    }
    return sum;
  }

  clbool IsNodeInHS(NODE<T>* node)const{
    if(!node)return false;
    while(node->m_pParentNode){
      node=node->m_pParentNode;
    }
    NODE<T>* nd=m_pInvisibleUniqueRootNode->m_pFirstChildNode;
    while(nd){
      if(nd==node)return true;
      nd=nd->m_pNextSiblingNode;
    }
    return false;
  }

  /**
   * traserse all decendant nodes without root;
   */
  NODE<T>* Traverse(const NODE<T>* root=nullptr,clbool begin=false){
    if(begin){
      m_trNode=root?root->m_pFirstChildNode:m_pInvisibleUniqueRootNode->m_pFirstChildNode;
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

  /**
   * gets given node's all decendant nodes;
   * return total number of them, and store them in out parameter;
   */
  cluint GetDecendantNodes(const NODE<T>* pNode,std::vector<NODE<T>*>& out){
    NODE<T>* tmp=Traverse(pNode,true);
    cluint n=0;
    while(tmp){
      n++;
      out.push_back(tmp);
      tmp=Traverse(pNode);
    }
    return n;
  }

  /**
   * gets given node's all decendant nodes;
   * return total number of them, and store them in out parameter;
   */
  cluint GetDecendantCustom(const NODE<T>* pNode,std::vector<T>& out){
    NODE<T>* tmp=Traverse(pNode,true);
    cluint n=0;
    while(tmp){
      n++;
      out.push_back(tmp->customObject);
      tmp=Traverse(pNode);
    }
    return n;
  }

  /**
  *except root node,remember rootnode cant be destroyed!
  *unless this structure instance was destroyed
  */
  void DeleteAllNodes(){
    DeleteDecendantNodes_(m_pInvisibleUniqueRootNode);
  }
  
  //print graph info;
  void Print()const{
#if __CL_INTERNAL_DEBUG__
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
      std::cout<<setiosflags(ios::left)<<setw(w)<<""<<"id="<<tmpNode->m_ID<<std::endl;
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
      if(nextNode) nextNode->m_pPreSiblingNode=nullptr;
    } else{
      preNode->m_pNextSiblingNode=nextNode;
      if(nextNode) nextNode->m_pPreSiblingNode=preNode;
    }
  }

#if __CL_INTERNAL_DEBUG__
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
  NODE<T>* Im_trNodeFirstChild_(NODE<T>* node){
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

  /**
   * set the given node's all children nodes parentNode to NULL;
   */
  void ClearAllChildrenParentNode_(NODE<T>* parentNode){
    NODE<T>* firstChild=parentNode->m_pFirstChildNode;
    while(firstChild){
      firstChild->m_pParentNode=nullptr;
      firstChild=firstChild->m_pNextSiblingNode;
    }
  }
};

}

CL_NAMESPACE_END
