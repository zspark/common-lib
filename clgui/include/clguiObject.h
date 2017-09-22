#pragma once
#include <map>
#include <vector>
#include "cl_types.h"
#include "cl_hierarchical_structure.h"
#include "clguiEvent.h"
#include "clguiComponentVariable.h"

namespace clgui{
using namespace cl;
class clguiObject;
typedef cl::hs::clHSNode_T<clguiObject*> node;

#define CLGUI_OBJECT_TYPE_OBJECT 1
#define CLGUI_OBJECT_TYPE_RENDERABLE ((1<<1)|CLGUI_OBJECT_TYPE_OBJECT)
#define CLGUI_OBJECT_TYPE_INTERACTIVE ((1<<2)|CLGUI_OBJECT_TYPE_RENDERABLE)
#define CLGUI_OBJECT_TYPE_CONTAINER ((1<<3)|CLGUI_OBJECT_TYPE_INTERACTIVE)
#define CLGUI_OBJECT_TYPE_STAGE 0xFF000000
/*
#define CLGUI_OBJECT_TYPE_BUTTON
#define CLGUI_OBJECT_TYPE_SLIDER
#define CLGUI_OBJECT_TYPE_LABEL
#define CLGUI_OBJECT_TYPE_CHECKBOX
#define CLGUI_OBJECT_TYPE_WINDOW
#define CLGUI_OBJECT_TYPE_MENUBAR
#define CLGUI_OBJECT_TYPE_MENU
#define CLGUI_OBJECT_TYPE_MENUITEM
#define CLGUI_OBJECT_TYPE_NULL
*/

class clguiObject{
public:
  clguiObject(cluint type);
  virtual ~clguiObject();
  clguiObject()=delete;
  clguiObject(const clguiObject&)=delete;

public:
  inline cluint GetType()const{ return m_type; };
  inline cluint GetUniqueID()const{ return m_uUniqueID; };

protected:
  const cluint m_type;
  const cluint m_uUniqueID;
  node* m_node=nullptr;
};






class clguiRenderable:public clguiObject{
public:
  clguiRenderable(cluint type):clguiObject(type){};
  virtual ~clguiRenderable(){};

  virtual void Init(){};
  virtual void PreRender(){};
  virtual void Render()=0;
  virtual void PostRender(){};
  virtual void Destroy(){};
};

class clguiInteractive:public clguiRenderable{
public:
  clguiInteractive(cluint type):clguiRenderable(type){};
  virtual ~clguiInteractive();

  //EvenListener;
  void AddEventListener(clguiEventType eventName,CallBackEventFn* cbFn);

protected:
  void DispatchEvent_(clguiEventType type,clguiEvent);

private:
  std::map<clguiEventType,std::vector<CallBackEventFn*>> m_mapListeners_name_listener;

};

class clguiContainer:public clguiInteractive{
public:
  clguiContainer(cluint type);
  virtual ~clguiContainer();

  void AddChild(clguiRenderable*);
  void RemoveChild(clguiRenderable*);

  //virtual bool BuildLayoutComponentsByJson(Json::Value);
private:
};
}
