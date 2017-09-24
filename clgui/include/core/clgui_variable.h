#pragma once
#include <functional>
#include "cl_types.h"
#include "clgui_macro.h"

using namespace cl;

CLGUI_NAMESPACE_START

class clguiEvent;

template<typename T>
class ComponentVariable_T{
public:
  //ComponentVariable_T(const ComponentVariable_T&)=delete;
  //ComponentVariable_T(const ComponentVariable_T*)=delete;
  //const ComponentVariable_T& operator=(const ComponentVariable_T& another) = delete;

public:
  // reset old and new to same value;
  void ResetTo(T value){
    m_oldValue=m_newValue=value;
  }

  T GetOldValue()const{ return m_oldValue; };
  T GetNewValue()const{ return m_newValue; };
  T& GetNewValueRef(){ return m_newValue; };
  T* GetNewValuePointer(){ return &m_newValue; };

  //only set new to value;
  void SetNewValue(T value){ m_newValue=value; }

  // update old to new;
  void Update(){ m_oldValue=m_newValue; };

  // if old and new are different return true;
  // others return false;
  bool CheckChange()const{ return m_oldValue!=m_newValue; };

private:
  T m_oldValue;
  T m_newValue;
};
typedef ComponentVariable_T<clint> cvInt;
typedef ComponentVariable_T<cluint> cvUint;
typedef ComponentVariable_T<clfloat> cvFloat;
typedef ComponentVariable_T<cldouble> cvDouble;
typedef ComponentVariable_T<clbool> cvBool;

typedef ComponentVariable_T<clI3> cvInt3;
typedef ComponentVariable_T<clUi3> cvUint3;
typedef ComponentVariable_T<clF3> cvFloat3;
typedef ComponentVariable_T<clD3> cvDouble3;

enum UniformComponentVariableType{
  UCV_INT=0,
  UCV_UINT,
  UCV_FLOAT,
  UCV_DOUBLE,
  UCV_BOOL,

  UCV_INT3,
  UCV_UINT3,
  UCV_FLOAT3,
  UCV_DOUBLE3,
};

CLGUI_NAMESPACE_END
