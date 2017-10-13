#pragma once
#include <map>
#include "clgui/core/clgui_macro.h"
#include "cl/cl_types.h"
#include "cl/cl_hierarchical_structure.h"

CLGUI_NAMESPACE_START

class clguiObject;
class clguiRenderable;
class clguiComponent;
class clguiContainer;
class clguiStage;
class clguiMenuBar;
class clguiMenu;
class clguiMenuItem;

typedef cl::hs::clHSNode node;

class clguiObjectManager final{
  static clguiObjectManager* sIns;
public:
  static clguiObjectManager* GetIns();
  static void DeleteIns();

  static clguiContainer* ToContainer(clguiObject* obj)noexcept;
  static clguiComponent* ToComponent(clguiObject* obj)noexcept;
  static clguiRenderable* ToRenderable(clguiObject* obj)noexcept;
  static clguiMenuBar* ToMenubar(clguiObject* obj)noexcept;
  static clguiMenu* ToMenu(clguiObject* obj)noexcept;
  static clguiMenuItem* ToMenuItem(clguiObject* obj)noexcept;

public:
  void Init();
  cluint GetObjectCount()const{ return m_objCount; }

  template<typename T>
  T* Traverse(cluint type,clbool begin=false){
    node* nd=nullptr;
    if(begin) nd=m_hs.Traverse(nullptr,true);
    else nd=m_hs.Traverse(nullptr,false);

    while(nd){
      clguiObject* obj=(clguiObject*)nd->custom;
      if((obj->GetType()&type)==type){
        return static_cast<T*>(obj);
      } 
      nd=m_hs.Traverse(nullptr,false);
    }
    return nullptr;
  };

  clguiStage* GetStage();
  clguiComponent* GetNextSibling(clguiComponent* obj)const noexcept;
  clguiComponent* GetFirstChild(clguiContainer* obj)const noexcept;
  clguiContainer* GetParent(clguiComponent* child)const noexcept;
  //cluint GetMenubarHeight() noexcept;
  void GetAllDecendant(clguiObject* parent,std::vector<clguiObject*>& out)noexcept;

  void AddChildAt(clguiComponent* child,clguiContainer* parent,clint index=-1);
  void RemoveChild(clguiComponent* child);


  void AddObject(clguiObject* obj);
  void DeleteObject(clguiObject* obj);

private:
  clguiObjectManager();
  ~clguiObjectManager();
  clguiObjectManager(const clguiObjectManager&)=delete;

  inline node* GetNodeByclguiObject_(clguiObject* obj)const noexcept;

private:
  cl::hs::clHS m_hs;
  cluint m_objCount=0;

  std::map<clguiObject*,node*> m_map_clguiObject_node;

};

CLGUI_NAMESPACE_END
