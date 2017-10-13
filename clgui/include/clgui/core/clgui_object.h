#pragma once

#include <map>
#include <vector>
#include "cl/cl_types.h"
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
  const cluint m_type;
  const cluint m_uUniqueID;

private:
  friend class clguiObjectManager;
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

  void SetVisible(clbool b){ m_visible=b; }
  clbool GetVisible()const{ return m_visible; }
  clguiContainer* GetParent();
  void SetSameline(clbool sameline,clfloat posx=0.f,clfloat spacing=1.f);
  virtual void SetName(clstr name);
  clstr GetName()const;
  virtual void SetSize(clint width,clint height);
  void GetSize(clint* width,clint* height)const;
  clint GetWidth()const{ return m_size.x; };
  clint GetHeight()const{ return m_size.y; };
  void ScaleSizeBy(clfloat f);

protected:
  friend class clguiRenderer;

  virtual ~clguiComponent(){};
  clbool m_visible=true;
  clstr m_sName;
  clstr m_sRenderName;
  clf2 m_size;
  clfloat m_posx=0.f;
  clfloat m_spacing=1.f;
  clfloat m_isSameline=false;

};








class CLGUI_API clguiContainer:public clguiComponent{
public:
  clguiContainer(cluint type);

  virtual void AddChild(clguiComponent*);
  virtual void AddChildAt(clguiComponent*,clint index);
  virtual void RemoveChild(clguiComponent*);
  virtual void NoticeSystemWndNewSize(clint width,clint height){};
  clguiComponent* GetChildByName(clstr name);
  clguiComponent* GetChildByUniqueID(cluint ID);


protected:
  virtual ~clguiContainer();
  virtual void SetPosition(clint x,clint y);
  void GetPosition(clint* x,clint* y)const;

  clf2 m_pos;

  //virtual bool BuildLayoutComponentsByJson(Json::Value);
};



class CLGUI_API clguiStage final:public clguiContainer{
public:
  clguiStage();

private:
  void Render()override{};
  void NoticeSystemWndNewSize(clint width,clint height)override;
  ~clguiStage(){};


};

CLGUI_NAMESPACE_END
