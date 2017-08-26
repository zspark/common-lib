#pragma once
#include "clguiComponent.h"
#include "clguiComponentVariable.h"

namespace clgui {
  class clguiMenuItem :public clguiComponent {
  public:
	 clguiMenuItem();
	 ~clguiMenuItem();

	 void Render()override;
	 void PostRender()override;
	 void SetSelection(bool status);

  private:
	 cvBool m_clVarBool;
  };
}