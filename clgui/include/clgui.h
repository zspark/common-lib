#pragma once
#include <GL\glew.h>
#include "GLFW\glfw3.h"
#include "clguiObject.h"
#include "clguiComponentContainer.h"

namespace clgui {

  class clGUI {
  public:
	 clGUI() {};
	 clGUI(const clGUI&)=delete;
	 clGUI(const clGUI*)=delete;
	 ~clGUI();
  public:
	 void SetGLFWWindow(GLFWwindow* wnd);
	 void SetGLClearColor(int r, int g, int b);
	 void Init();
	 void Exec();
	 void Exit();

	 void AddChild(clguiObject* child);
	 void AddChild(clguiObject* child,uint parentNodeIndex);

	 // This method will delete node ,but not custom data;
	 void RemoveChild(clguiObject* child);

	 // returns a child's custom object which has index of the given.
	 // if index is larger than max children counts,then returns nullptr;
	 clguiObject* GetChildOf(clguiComponentContainer* container,uint index)const;

	 // This method will delete node along with it's custom data;
	 void DeleteChildrenOf(clguiComponentContainer* container);

	 void RenderChildrenOf(clguiComponentContainer* container);

  private:
	 GLFWwindow* m_glfwWnd;
	 cl::clFloat4 m_clearColor;
	 bool m_bNeedDelete=false;

  };


  clGUI* GetCLGUI();
  void DestroyCLGUI();
}
