#pragma once
#include "clguiObject.h"

namespace clgui {
  class clguiComponent :public clguiObject {
  public:
	 clguiComponent(clguiObjectType objectType) :clguiObject(objectType) {};
	 ~clguiComponent() {}
  };
}