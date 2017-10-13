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

class clHS;

class CL_API clHSNode final{
public:
  inline cluint GetId()const{ return m_ID; }
  clHSNode* GetParentNode()const{ return m_pParentNode; }
  clHSNode* GetPreSiblingNode()const{ return m_pPreSiblingNode; }
  clHSNode* GetNextSiblingNode()const{ return m_pNextSiblingNode; }
  clHSNode* GetFirstChildNode()const{ return m_pFirstChildNode; }

  //One cant change id of a exist node;void SetId(cluint id) { m_ID=id; }

  void* custom=nullptr;

private:
  clHSNode(cluint ID,cluint HSID):m_ID(ID),m_HSID(HSID){};
  ~clHSNode(){
    m_pParentNode=nullptr;
    m_pPreSiblingNode=nullptr;
    m_pNextSiblingNode=nullptr;
    m_pFirstChildNode=nullptr;
    custom=nullptr;
  };

private:
  friend class clHS;
  const cluint m_ID;//unique;
  const cluint m_HSID;
  clHSNode* m_pParentNode=nullptr;
  clHSNode* m_pPreSiblingNode=nullptr;
  clHSNode* m_pNextSiblingNode=nullptr;
  clHSNode* m_pFirstChildNode=nullptr;
};

class CL_API clHS final{
public:
  clHS();
  ~clHS();

  /**
  * just create a new node ,then return ,nothing else .
  * but you cant create one using "new",
  * because all nodes have their unique id which is controled by scene graph.
  */
  clHSNode* CreateNode();

  //return the node which has the given id, if not return nullptr;
  clHSNode* GetNodeById(cluint id);

  // returns node's sibling node by offset
  // node should NOT be nullptr;
  // if offset gets out of range, then returns it's parent's first or last node
  // offset 0 means node itself;
  clHSNode* GetSiblingNodeByOffset(clHSNode* node,clint offset);

  /**
  * return the last child node of the given node;
  * if node has no children then return nullptr;
  * and if node is nullptr, return invisibleRootNode's last child;
  */
  clHSNode* GetLastChildNode(clHSNode* node=nullptr);

  /**
  * return node first child node;
  * if node has no children nodes then return nullptr;
  * and if node is nullptr return invisibleRootNode's first child;
  */
  clHSNode* GetFirstChildNode(clHSNode* node=nullptr);

  /**
  * if node exist,then remove it from graph and delete it,and return it's first child node;
  * if not return nullptr;
  * alongWithCustom means delete node's custom data as well;
  */
  clHSNode* DeleteNode(cluint id,clbool alongWithCustom=false);

  /**
  * if node exist,then remove it from graph and delete it,and return it's first child node;
  * if not return nullptr;
  * alongWithCustom means delete node's custom data as well;
  */
  clHSNode* DeleteNode(clHSNode* node,clbool alongWithCustom=false);

  /**
   *this will delete all nodes which have the same parent id.
   * alongWithCustom means delete node's custom data as well;
   */
  clbool DeleteDecendantNodes(cluint id,clbool alongWithCustom=false);
  clbool DeleteDecendantNodes(clHSNode* node,clbool alongWithCustom=false);

  //just return the node which has given id;if not return nullptr;
  // removeNode method will remove all relations of returning node except it's link to firstchildnode;
  // you can delete returned node by DeleteNode method;
  // or adding it back to graph.
  // and hs will be reconstructed;
  clHSNode* RemoveNode(cluint id);

  // removeNode method will remove all relations of given node except it's link to firstchildnode;
  // and hs will be reconstructed;
  void RemoveNode(clHSNode* node);

  //insert srcNode which has relation with targetNode to targetNode.
  //if targetNode is nullptr,means invisibleRootNode. in this case,all relation is ignord. 
  //we will add srcNode as root's child.
  // targetNode(if not null) and srcNode MUST be created by this HS;
  // srcNode should NOT be in HS;
  clHSInsertResult InsertNode(clHSNode* targetNode,clHSNode* srcNode,clHSNodeRelation relation);

  //return all children number of given node except it's decendant ;
  // if node==nullptr, means how many root nodes;
  cluint GetNumChildren(const clHSNode* node=nullptr)const;

  /**
   * returns true if the given node is already in hs;
   * else returns false;
   */
  clbool IsNodeInHS(clHSNode* node)const;

  /**
   * traserse all decendant nodes without root;
   */
  clHSNode* Traverse(const clHSNode* root=nullptr,clbool begin=false);

  /**
   * gets given node's all decendant nodes;
   * return total number of them, and store them in out parameter;
   */
  cluint GetDecendantNodes(const clHSNode* pNode,std::vector<clHSNode*>& out);

  /**
   * gets given node's all decendant nodes;
   * return total number of them, and store them in out parameter;
   */
  template<typename T>
  cluint GetDecendantCustom(const clHSNode* pNode,std::vector<T*>& out){
    clHSNode* tmp=Traverse(pNode,true);
    cluint n=0;
    while(tmp){
      n++;
      out.push_back((T*)(tmp->custom));
      tmp=Traverse(pNode);
    }
    return n;
  }

  /**
  *except root node,remember rootnode cant be destroyed!
  *unless this structure instance was destroyed
  */
  void DeleteAllNodes(clbool alongWithCustom=false);

  //print graph info;
  void Print()const;

private:
  void ReconstructRelationWithout_(clHSNode* node);

#if __CL_INTERNAL_DEBUG__
  //except root node ,all root node's children are at depth of 0;
  cluint GetDepth_(clHSNode* node)const;
#endif

  /**
   * set the given node's all children nodes parentNode to NULL;
   */
  void ClearAllChildrenParentNode_(clHSNode* parentNode);

private:
  clHSNode m_pInvisibleUniqueRootNode;
  clHSNode* m_trNode=nullptr;
  const cluint m_ID;
  clbool m_bDestroied=false;

};

}

CL_NAMESPACE_END
