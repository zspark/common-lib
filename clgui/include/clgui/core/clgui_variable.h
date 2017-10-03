#pragma once
#include <functional>
#include "cl/cl_types.h"
#include "clgui_macro.h"

using namespace cl;

CLGUI_NAMESPACE_START

class clguiEvent;

template<typename T,cluint D=1>
class ComponentVariable_T{
public:
  ComponentVariable_T(T newValue,T oldValue){
    for(cluint i=0;i<D;i++){
      m_newValue[i]=newValue;
      m_oldValue[i]=oldValue;
    }
  };
  ComponentVariable_T(T value){
    for(cluint i=0;i<D;i++){
      m_newValue[i]=value;
      m_oldValue[i]=value;
    }
  }
  //ComponentVariable_T(const ComponentVariable_T&)=delete;
  //ComponentVariable_T(const ComponentVariable_T*)=delete;
  //const ComponentVariable_T& operator=(const ComponentVariable_T& another) = delete;

public:

  T operator[](cluint index)const{
    return m_newValue[index];
  }

  T* operator[](cluint index){
    return &m_newValue[index];
  }

  // reset old and new to same value;
  void ResetTo(T value){
    for(cluint i=0;i<D;i++){
      m_newValue[i]=value;
      m_oldValue[i]=value;
    }
  }

  //only set new to value;
  void SetNewValue(T value){
    for(cluint i=0;i<D;i++){
      m_newValue[i]=value;
    }
  }

  // update old to new;
  void Update(){
    ::memcpy(m_oldValue,m_newValue,sizeof(T)*D);
  }

  // if old and new are different return true;
  // others return false;
  bool CheckChange()const{
    for(cluint i=0;i<D;i++){
      if(m_newValue[i]!=m_oldValue[i])return true;
    }
    return false;
  }

private:
  T m_oldValue[D];
  T m_newValue[D];
};

typedef ComponentVariable_T<clint,1> cvInt;
typedef ComponentVariable_T<clfloat,1> cvFloat;
typedef ComponentVariable_T<clbool,1> cvBool;

CLGUI_NAMESPACE_END
