#pragma once

#include "clgui/core/clgui_macro.h"
#include "clgui/core\clgui_variable.h"
#include "clgui/core/clgui_object.h"

CLGUI_NAMESPACE_START

template<typename T>
class clguiSlider:public clguiComponent{
public:
  clguiSlider()
    :clguiComponent(CLGUI_OBJECT_TYPE_COMPONENT)
    ,m_value(.4f){}

public:
  virtual void SetDimension(cluint d)=0;
  cluint GetDimension()const{ return m_uDimension; }
  void SetValue(T* value){ ::memcpy(m_value[0],value,sizeof(T)*m_uDimension); }
  void SetValue(T value){ m_value.SetNewValue(value); }
  T GetValue(cluint index)const{ return m_value[index]; }
  T GetValue()const{ return m_value[0]; }
  void SetRange(T min,T max){ m_min=min; m_max=max; }

protected:
  virtual ~clguiSlider(){};
  ComponentVariable_T<T,3> m_value;
  T m_min;
  T m_max;
  cluint m_uDimension=1u;
  clstr m_sFormat="%.3f";
  T m_power=1.0f;

};


class CLGUI_API clguiSliderFloat:public clguiSlider<clfloat>{
public:
  clguiSliderFloat();
  ~clguiSliderFloat();

  void SetDimension(cluint d)override;

protected:
  void Render()override;
  void PostRender()override;

private:
  typedef clbool(*RenderFn)(const clchar* caption,clfloat* value,clfloat min,clfloat max,const clchar* display_format,clfloat power);
  RenderFn m_RenderFn=nullptr;

};

class CLGUI_API clguiSliderInt:public clguiSlider<clint>{
public:
  clguiSliderInt();
  ~clguiSliderInt();

  void SetDimension(cluint d)override;

protected:
  void Render()override;
  void PostRender()override;

private:
  typedef clbool(*RenderFn)(const clchar* caption,clint* value,clint min,clint max,const clchar* display_format);
  RenderFn m_RenderFn=nullptr;

};
CLGUI_NAMESPACE_END