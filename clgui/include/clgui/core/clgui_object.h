#pragma once

#include <map>
#include <vector>
#include "cl/cl_types.h"
#include "cl/cl_hierarchical_structure.h"
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


class clguiObjectManager;

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




class clguiContainer;

class CLGUI_API clguiComponent:public clguiInteractive{
public:
  clguiComponent(cluint type);

  inline void Visible(clbool b){ m_visible=b; }
  inline clbool Visible()const{ return m_visible; }
  clguiContainer* GetParent();

  virtual void SetSize(clint width,clint height);
  void GetSize(cluint* width,cluint* height)const;
  void ScaleSizeBy(clfloat f);
  virtual void SetPosition(clint x,clint y);
  void GetPosition(clint* x,clint* y)const;
  virtual void SetCaption(clstr caption);
  clstr GetCaption()const;

protected:
  virtual ~clguiComponent(){};
  clbool m_visible=true;
  clf2 m_pos;
  clf2 m_size;
  clstr m_caption;

};



class CLGUI_API clguiContainer:public clguiComponent{
public:
  clguiContainer(cluint type);

  virtual void AddChild(clguiComponent*);
  virtual void AddChildAt(clguiComponent*,clint index);
  virtual void RemoveChild(clguiComponent*);
  virtual void NoticeWindowSize(clint width,clint height){};
  virtual clguiComponent* GetDirectChildByCaption(clstr caption);

protected:
  virtual ~clguiContainer();

  //virtual bool BuildLayoutComponentsByJson(Json::Value);
};



class CLGUI_API clguiStage final:public clguiContainer{
public:
  clguiStage();

private:
  void Render()override{};
  void NoticeWindowSize(clint width,clint height)override;
  ~clguiStage(){};


};

CLGUI_NAMESPACE_END
