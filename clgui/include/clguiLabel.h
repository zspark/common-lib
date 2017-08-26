#pragma once
#include "clguiComponent.h"
#include <string>

namespace clgui {

  class clguiLabel :public clguiComponent {
  public:
	 clguiLabel();
	 ~clguiLabel();

  public:
	 void Render();

	 void SetColor(clFloat3);

	 void SetValue(int value);
	 void SetValue(float value);
	 void SetValue(double value);
	 void SetValue(ccharstar value);

  private:
	 std::string m_value="";
	 clFloat3 m_color;
  };

}