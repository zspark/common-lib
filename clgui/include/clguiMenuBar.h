#pragma once
#include "clguiComponentContainer.h"
#include "clguiMenu.h"

namespace clgui {
  class clguiMenuBar :public clguiComponentContainer {
  public:
	 clguiMenuBar();
	 ~clguiMenuBar();
  public:
	 void Render();
	 clguiMenu* GetMenu(uint index);

	 // create a new menu and then returns it;
	 clguiMenu* AddChild(ccharstar menuName);
	 using clguiComponentContainer::AddChild;
	 bool BuildLayoutComponentsByJson(Json::Value json)override;
  };
}