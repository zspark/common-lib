#pragma once
#include <GL\glew.h>
#include "GLFW\glfw3.h"
#include "cl_types.h"

namespace clgui{

class clGUI{
public:
  static clGUI* GetIns();
public:
  void SetGLClearColor(int r,int g,int b);
  void Init(GLFWwindow* wnd);
  void Exec();
  void Exit();

private:
  clGUI(){};
  clGUI(const clGUI&)=delete;
  ~clGUI();

private:
  static clGUI* sIns;
  GLFWwindow* m_glfwWnd;
  cl::clF4 m_clearColor;

};

}
