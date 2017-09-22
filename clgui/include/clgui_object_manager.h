#pragma once
#include <vector>
#include "cl_types.h"
#include "cl_hierarchical_structure.h"

namespace clgui{

class clguiObject;

class clguiObjectManager final{
  static clguiObjectManager* sIns;
public:
  static clguiObjectManager* GetIns();

public:
  cluint GetObjectCount()const{ return m_objCount; }

  template<typename T>
  T* Triverse(cluint type,clbool begin=false){
    static clint s_index=-1;
    if(begin)s_index=0;
    else s_index++;

    while(1){
      if(s_index>=m_vecObjs.size())return nullptr;
      else{
        clguiObject* obj=m_vecObjs[s_index];
        if((obj->GetType()&type)==type){
          return static_cast<T*>(obj);
        } else s_index++;
      }
    }
  }

private:
  clguiObjectManager();
  ~clguiObjectManager();
  clguiObjectManager(const clguiObjectManager&)=delete;
  void AddObject(clguiObject* obj);
  void RemoveObject(clguiObject* obj);

private:
  friend clguiObject;

  typedef cl::hs::clHSNode_T<clguiObject*> node;
  cl::hs::clHS_T<clguiObject*> m_hs;
  cluint m_objCount=0;
  std::vector<clguiObject*> m_vecObjs;

};
}
