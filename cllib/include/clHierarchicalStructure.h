#pragma once
#include <vector>
#include "clTypes.h"

namespace cl{
enum clHierarchicalStructureNodeType{
  SN_ROOT=0,
  SN_GROUP,
  SN_GEO,
  SN_LIGHT,
  SN_CAMERA,
};
enum clHierarchicalStructureNodeRelation{
  R_NULL=0,
  R_NEXT_SIBLING,
  R_PRE_SIBLING,
  R_FIRST_CHILD,
  R_LAST_CHILD,
};

template<typename T>
class clHierarchicalStructureNode_T{
public:
  clHierarchicalStructureNode_T(clUi id):m_id(id){};
  ~clHierarchicalStructureNode_T(){
    m_pParentdNode=nullptr;
    m_pPreSiblingNode=nullptr;
    m_pNextSiblingNode=nullptr;
    m_pFirstChildNode=nullptr;
  };
  clHierarchicalStructureNodeType GetType()const{ return m_type; }
  void SetType(clHierarchicalStructureNodeType type){ m_type=type; }
  clUi GetId()const{ return m_id; }
  clHierarchicalStructureNode_T* GetParentNode()const{ return m_pParentdNode; }
  clHierarchicalStructureNode_T* GetPreSiblingNode()const{ return m_pPreSiblingNode; }
  clHierarchicalStructureNode_T* GetNextSiblingNode()const{ return m_pNextSiblingNode; }
  clHierarchicalStructureNode_T* GetFirstChildNode()const{ return m_pFirstChildNode; }

  //One cant change id of a exist node;void SetId(clUi id) { m_id=id; }

  T mCustomObject;
private:
  template<typename> friend class clHierarchicalStructure_T;
  //friend class clHierarchicalStructure;
  clUi m_id;//unique;
  clHierarchicalStructureNodeType m_type;
  clHierarchicalStructureNode_T* m_pParentdNode=nullptr;
  clHierarchicalStructureNode_T* m_pPreSiblingNode=nullptr;
  clHierarchicalStructureNode_T* m_pNextSiblingNode=nullptr;
  clHierarchicalStructureNode_T* m_pFirstChildNode=nullptr;
};


template<typename NODE>
class clHierarchicalStructure_T{
public:
  clHierarchicalStructure_T():m_pRootNode(new NODE(0)){};
  ~clHierarchicalStructure_T(){};

public:
  //just create a new node ,then return ,nothing else .
  //but you cant create one using "new",
  //because all nodes have their unique id which is controled by scene graph.
  NODE* CreateNode();

  //return the node which has the given id, if not return nullptr;
  NODE* GetNode(clUi id);

  //return the last child node of the given node;if given node has no children then return nullptr;
  NODE* GetLastChildNode(NODE* node);

  //if node exist,then remove it from graph and delete it,and return it's first child node;
  //if not return nullptr;
  NODE* DeleteNode(clUi id);

  //this will delete all nodes which have the same parent id of id.
  bool DeleteDecendantNodes(clUi id);

  //just return the node which has given id;if not return nullptr;
  // removeNode method will remove all relations of returning node except it's link to firstchildnode;
  // you can delete returned node yourself;
  // or adding it back to graph.
  NODE* RemoveNode(clUi id);

  //insert srcNode which has relation with targetNode to targetNode.
  //if targetNode is nullptr,means rootnode. in this case,all relation is ignord. we will 
  //add srcNode as root's child.
  bool InsertNode(NODE* targetNode,NODE* srcNode,clHierarchicalStructureNodeRelation relation);

  //return all children number of given node except it's decendant ;
  clUi GetNumChildren(NODE* node)const;

  //return all children number of root node except it's decendant.
  clUi GetNumChildren()const;

  //except root node,remember rootnode cant be destroyed!
  void DeleteAllNodes();

  // traserse begin;
  NODE* GetFirstNode();

  // traserse continue;
  // if return value is nullptr ,means over;
  NODE* GetNextNode();

  //print graph info;
  void Print();
private:
  void RemoveRelation(NODE* node);

  //except root node ,all root node's children are at depth of 0;
  clUi GetDepth(NODE* node);

  //return parent node if node is it's first child;
  //else return nullptr;
  NODE* IsNodeFirstChild(NODE* node);
  clUi GetNextAvaliableNodeId();

  //delete node;
  bool DeleteDecendantNodes(NODE* node);

private:
  clUi m_uNextAvaliableId=1;
  NODE* const m_pRootNode;
  std::vector<NODE*> m_vecTraverse;
};
}
#include "clHierarchicalStructure.inl"
