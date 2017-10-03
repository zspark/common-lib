#pragma once

#include <map>
#include <vector>
#include "cl_types.h"
#include "cl_hierarchical_structure.h"
#include "clgui_macro.h"
#include "clgui_variable.h"
#include "clgui_event.h"

using namespace cl;
class clguiRenderer;

CLGUI_NAMESPACE_START

#define CLGUI_CAPTION_DEFAULT_COLOR 1.f

#define CLGUI_OBJECT_TYPE_OBJECT 1
#define CLGUI_OBJECT_TYPE_RENDERABLE ((1<<1)|CLGUI_OBJECT_TYPE_OBJECT)
#define CLGUI_OBJECT_TYPE_COMPONENT ((1<<2)|CLGUI_OBJECT_TYPE_RENDERABLE)
#define CLGUI_OBJECT_TYPE_MENU_ITEM ((1<<3)|CLGUI_OBJECT_TYPE_COMPONENT)

#define CLGUI_OBJECT_TYPE_CONTAINER ((1<<16)|CLGUI_OBJECT_TYPE_COMPONENT)
#define CLGUI_OBJECT_TYPE_STAGE (1<17|CLGUI_OBJECT_TYPE_CONTAINER)
#define CLGUI_OBJECT_TYPE_MENUBAR ((1<<18)|CLGUI_OBJECT_TYPE_CONTAINER)
#define CLGUI_OBJECT_TYPE_MENU ((1<<19)|CLGUI_OBJECT_TYPE_CONTAINER)
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

class CLGUI_API clguiObject{
public:
  clguiObject(cluint type);
  clguiObject()=delete;
  clguiObject(const clguiObject&)=delete;

public:
  inline cluint GetType()const{ return m_type; };
  inline cluint GetUniqueID()const{ return m_uUniqueID; };

protected:
  virtual ~clguiObject();

private:
  friend class clguiObjectManager;
  const cluint m_type;
  const cluint m_uUniqueID;
};





class CLGUI_API clguiRenderable:public clguiObject{
public:
  clguiRenderable(cluint type):clguiObject(type){};

protected:
  friend class clguiRenderer;
  virtual ~clguiRenderable(){};

  virtual clbool PreRender(){ return true; };
  virtual void Render()=0;
  virtual void PostRender(){};
};





class CLGUI_API clguiInteractive:public clguiRenderable{
public:
  clguiInteractive(cluint type):clguiRenderable(type){};

  //EvenListener;
  void AddEventListener(clguiEventType eventName,CallBackEventFn* cbFn);

protected:
  virtual ~clguiInteractive();
  void DispatchEvent_(clguiEvent*);

private:
  std::map<clguiEventType,std::vector<CallBackEventFn*>> m_mapListeners_name_listener;

};

class CLGUI_API clguiComponent:public clguiInteractive{
public:
  clguiComponent(cluint type):clguiInteractive(type){
    m_pos.x=0.f;m_pos.y=0.f;
    m_size.x=100;m_size.y=30;
  };

  inline void Visible(clbool b){ m_visible=b; }
  inline clbool Visible()const{ return m_visible; }
  clguiContainer* GetParent();

  void SetSize(cluint width,cluint height);
  void SetPosition(clint x,clint y);
  void SetCaption(clstr caption){ m_caption=caption; }
  clstr GetCaption()const{ return m_caption; }

protected:
  virtual ~clguiComponent(){};
  clbool m_visible=true;
  ImVec2 m_pos;
  ImVec2 m_size;
  clstr m_caption="<NO-CAPTION>";

};



class CLGUI_API clguiContainer:public clguiComponent{
public:
  clguiContainer(cluint type);

  virtual void AddChild(clguiComponent*);
  virtual void AddChildAt(clguiComponent*,clint index);
  virtual void RemoveChild(clguiComponent*);

protected:
  virtual ~clguiContainer();

  //virtual bool BuildLayoutComponentsByJson(Json::Value);
private:
};



class CLGUI_API clguiStage final:public clguiContainer{
public:
  clguiStage():clguiContainer(CLGUI_OBJECT_TYPE_STAGE){}

public:
  void SetColor(cluint r,cluint g,cluint b);
  void SetGLFWwindow(GLFWwindow* wnd);

private:
  void Render()override;
  ~clguiStage(){ m_glfwWnd=nullptr; }

private:
  clF4 m_clearColor;
  GLFWwindow* m_glfwWnd=nullptr;
};

CLGUI_NAMESPACE_END
