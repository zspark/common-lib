#pragma once
#include <map>
#include <vector>
#include "imgui.h"
#include "imgui_impl_glfw_gl3.h"
#include "cl_types.h"
#include "cl_hierarchical_structure.h"
#include "clgui_macro.h"
#include "clguiEvent.h"
#include "clguiComponentVariable.h"

using namespace cl;
class clguiRenderer;

CLGUI_NAMESPACE_START

#define CLGUI_OBJECT_TYPE_OBJECT 1
#define CLGUI_OBJECT_TYPE_RENDERABLE ((1<<1)|CLGUI_OBJECT_TYPE_OBJECT)
#define CLGUI_OBJECT_TYPE_COMPONENT ((1<<2)|CLGUI_OBJECT_TYPE_RENDERABLE)
#define CLGUI_OBJECT_TYPE_CONTAINER ((1<<3)|CLGUI_OBJECT_TYPE_COMPONENT)
#define CLGUI_OBJECT_TYPE_STAGE (1<7|CLGUI_OBJECT_TYPE_CONTAINER)
/*
#define CLGUI_OBJECT_TYPE_SLIDER
#define CLGUI_OBJECT_TYPE_LABEL
#define CLGUI_OBJECT_TYPE_CHECKBOX
#define CLGUI_OBJECT_TYPE_WINDOW
#define CLGUI_OBJECT_TYPE_MENUBAR
#define CLGUI_OBJECT_TYPE_MENU
#define CLGUI_OBJECT_TYPE_MENUITEM
#define CLGUI_OBJECT_TYPE_NULL
*/


class clguiObject;
class clguiContainer;
class clguiObjectManager;

template<typename T>
CLGUI_API inline T TryConvertTo(clguiObject* obj,cluint type)noexcept{
  return ((obj->GetType()&type)==type)?static_cast<T>(obj):nullptr;
}

CLGUI_API class clguiObject{
public:
  clguiObject(cluint type);
  virtual ~clguiObject();
  clguiObject()=delete;
  clguiObject(const clguiObject&)=delete;

public:
  inline cluint GetType()const{ return m_type; };
  inline cluint GetUniqueID()const{ return m_uUniqueID; };

private:
  const cluint m_type;
  const cluint m_uUniqueID;
};





CLGUI_API class clguiRenderable:public clguiObject{
public:
  clguiRenderable(cluint type):clguiObject(type){};
  virtual ~clguiRenderable(){};

protected:
  friend class clguiRenderer;

  virtual void PreRender(){};
  virtual void Render()=0;
  virtual void PostRender(){};
};





CLGUI_API class clguiInteractive:public clguiRenderable{
public:
  clguiInteractive(cluint type):clguiRenderable(type){};
  virtual ~clguiInteractive();

  //EvenListener;
  void AddEventListener(clguiEventType eventName,CallBackEventFn* cbFn);

protected:
  void DispatchEvent_(const clguiEvent*);

private:
  std::map<clguiEventType,std::vector<CallBackEventFn*>> m_mapListeners_name_listener;

};

CLGUI_API class clguiComponent:public clguiInteractive{
public:
  clguiComponent(cluint type):clguiInteractive(type){
    m_pos.x=0.f;m_pos.y=0.f;
    m_size.x=m_size.y=100;
  };
  virtual ~clguiComponent(){};

  inline void Visible(clbool b){ m_visible=b; }
  inline clbool Visible()const{ return m_visible; }
  clguiContainer* GetParent();
  void SetSize(cluint width,cluint height);
  void SetPosition(clint x,clint y);

protected:
  clbool m_visible=true;
  ImVec2 m_pos;
  ImVec2 m_size;

};



CLGUI_API class clguiContainer:public clguiComponent{
public:
  clguiContainer(cluint type);
  virtual ~clguiContainer();

  void AddChild(clguiComponent*);
  void AddChildAt(clguiComponent*,clint index);
  void RemoveChild(clguiComponent*);

  //virtual bool BuildLayoutComponentsByJson(Json::Value);
private:
};



CLGUI_API class clguiStage final:public clguiContainer{
public:
  clguiStage():clguiContainer(CLGUI_OBJECT_TYPE_STAGE){}
  ~clguiStage(){ m_glfwWnd=nullptr; }

public:
  void SetColor(cluint r,cluint g,cluint b);
  void SetGLFWwindow(GLFWwindow* wnd);

protected:
  void Render()override;

private:
  clF4 m_clearColor;
  GLFWwindow* m_glfwWnd=nullptr;
};

CLGUI_NAMESPACE_END
