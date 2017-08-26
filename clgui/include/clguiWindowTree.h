#pragma once
#include "clWindowBase.h"

namespace clgui {
  class clWindowTree :public clWindowBase {
  public:
	 clWindowTree() :clWindowBase() {
		m_size.Set(100, 100);
	 }
	 ~clWindowTree() {};
  public:
	 void RenderSpecific()override;

  private:

  };
}