#pragma once
#include <map>
#include "clgui_macro.h"
#include "cl_types.h"
#include "cl_hierarchical_structure.h"

CLGUI_NAMESPACE_START

class clguiObject;
class clguiRenderable;
class clguiComponent;
class clguiContainer;
class clguiStage;


class clguiObjectManager final{
  static clguiObjectManager* sIns;
public:
  static clguiObjectManager* GetIns();
  static void DeleteIns();

private:
  typedef cl::hs::clHSNode_T<clguiObject*> node;

public:
  cluint GetObjectCount()const{ return m_objCount; }

  template<typename T>
  T Triverse(cluint type,clbool begin=false){
    node* nd=nullptr;
    if(begin) nd=m_hs.Traverse(true);
    else nd=m_hs.Traverse(false);

    while(nd){
      clguiObject* obj=nd->customObject;
      if((obj->GetType()&type)==type){
        return static_cast<T>(obj);
      } 
      nd=m_hs.Traverse(false);
    }
    return nullptr;
  };

  clguiStage* GetStage();
  clguiObject* GetNextSibling(clguiObject* obj)const noexcept;
  clguiObject* GetFirstChild(clguiObject* obj)const noexcept;
  clguiObject* GetParent(clguiObject* child)const noexcept;

  clguiContainer* ToclguiContainer(clguiObject* obj)const noexcept;
  clguiComponent* ToclguiComponent(clguiObject* obj)const noexcept;
  clguiRenderable* ToclguiRenderable(clguiObject* obj)const noexcept;


  void AddChildAt(clguiComponent* child,clguiContainer* parent,clint index=-1);
  void RemoveChild(clguiComponent* child);


private:
  clguiObjectManager();
  ~clguiObjectManager();
  clguiObjectManager(const clguiObjectManager&)=delete;
  void Init();
  void AddObject(clguiObject* obj);
  void RemoveObject(clguiObject* obj);

  node* GetNodeByclguiObject_(clguiObject* obj)const noexcept;

private:
  friend clguiObject;

  cl::hs::clHS_T<clguiObject*> m_hs;
  cluint m_objCount=0;

  std::map<clguiObject*,node*> m_map_clguiObject_node;

};

CLGUI_NAMESPACE_END
