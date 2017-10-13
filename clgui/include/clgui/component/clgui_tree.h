#pragma once

#include "clgui/core/clgui_macro.h"
#include "clgui/core\clgui_variable.h"
#include "clgui/core/clgui_object.h"
#include "cl\cl_hierarchical_structure.h"


CLGUI_NAMESPACE_START

/*
enum class clguiTreeNodeType{
  TYPE_CAMERA=0,
  TYPE_MODEL,
  TYPE_MESH,
  TYPE_LIGHT,
};
*/

struct clguiTreeNodeInfo{
  //clguiTreeNodeType type;
  clstr name;
  clint flags;
};

typedef cl::hs::clHS_T<clguiTreeNodeInfo> hs;
typedef cl::hs::clHSNode_T<clguiTreeNodeInfo> nd;
typedef cl::hs::clHSNodeRelation hsr;
typedef clint nodeID;

class CLGUI_API clguiTree:public clguiComponent{
public:
clguiTree();
nodeID CreateNode(clchar* name,nodeID parentNodeID=-1);


protected:
  ~clguiTree();
  void Render()override;
  void PostRender()override;
  void RenderSubNodes_(nd* node);

private:
  cvBool m_cv;
  hs m_hs;
  clbool m_isCtrlKeyDown=false;

};

CLGUI_NAMESPACE_END