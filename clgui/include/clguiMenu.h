#pragma once
#include "clguiComponentContainer.h"
#include "clguiComponentVariable.h"
#include "clguiMenuItem.h"

namespace clgui {
  class clguiMenu :public clguiComponentContainer {
  public:
	 clguiMenu();
	 ~clguiMenu();
  public:
	 void Render();

	 using clguiComponentContainer::AddChild;
	 // This call will create a default menu item;
	 // and returns it's pointer;
	 //clguiMenuItem* AddChild(ccharstar menuItemName, CallBackBoolFn cbFn);
	 clguiMenuItem* AddChild(ccharstar menuItemName);
	 clguiObject* clguiMenu::GetMenuItem(uint index);

  };
}