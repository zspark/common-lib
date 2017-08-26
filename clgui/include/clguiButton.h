#pragma once
#include "clguiComponent.h"
#include "clguiComponentVariable.h";

namespace clgui {

  class clguiButton :public clguiComponent {
  public:
	 clguiButton();
	 ~clguiButton();

  public:
	 void Render();
	 void PostRender();

  private:
	 cvBool m_cv;
  };

}