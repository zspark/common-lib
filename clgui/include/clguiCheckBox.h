#pragma once
#include "clguiComponent.h"
#include "clguiComponentVariable.h";

namespace clgui {

  class clguiCheckBox :public clguiComponent {
  public:
	 clguiCheckBox();
	 ~clguiCheckBox();

  public:
	 void Render();
	 void PostRender();

	public:
		void SetSelection(bool v);

  private:
	 cvBool m_cv;
  };

}