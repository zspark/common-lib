#pragma once

#include "clguiComponentVariable.h"
#include "clguiComponentContainer.h"
#include "clguiComponent.h"

namespace clgui {
  class clguiWindow :public clguiComponentContainer {

  public:
	 clguiWindow();
	 virtual ~clguiWindow();

  public:
	 void Render()override;
	 void PostRender()override;
	 void AddEventListener(clguiEventType eventName,EventCallBackFn cbFn);
	 void SetWindowSize(uint width, uint height);
	 void SetWindowPos(int x, int y);

	 void SetCaption(ccharstar name);
	 bool BuildLayoutComponentsByJson(Json::Value json)override;

  protected:
	 clUint2 m_size;
	 clInt2 m_pos;

  private:
	 cvBool m_clVarBool;
	 bool m_bCloseEventListened=false;
  };
}
