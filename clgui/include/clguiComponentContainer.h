#pragma once
#include "clguiObject.h"
#include <list>
#include "json.h"

namespace clgui {

  class clguiComponentContainer :public clguiObject{
  public:
	 clguiComponentContainer(clguiObjectType objectType);
	 virtual ~clguiComponentContainer();
	 clguiComponentContainer(const clguiComponentContainer&) = delete;
	 clguiComponentContainer(const clguiComponentContainer*) = delete;

	 void AddChild(clguiObject*);
	 void RemoveChild(clguiObject*);

	 virtual bool BuildLayoutComponentsByJson(Json::Value);
  };
}
