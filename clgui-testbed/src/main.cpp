#include <cstdlib>
#include <cstdio>
#include "clgui.h"
#include "Testclgui.h"

using namespace clgui;
using namespace std;
static void errorCallback(int error, const char* description) {
  //fprintf(stderr, "Error %d: %s\n", error, description);
}


int main(int argc, char* argv[]) {
  glfwSetErrorCallback(errorCallback);
  if (!glfwInit()) exit(EXIT_FAILURE);
  //glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
  //glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,2);
  //glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);

  int size[2] = { 600,800 };
	char* title="Hello clgui!";
  GLFWwindow* wnd = glfwCreateWindow(size[0], size[1], title, NULL, NULL);
  glfwMakeContextCurrent(wnd);
  glfwSwapInterval(1);
  glfwSetWindowPos(wnd, 400, 200);

  GLenum err = glewInit();
  if (err != GLEW_OK) exit(EXIT_FAILURE);

	clGUI* gui=clgui::GetCLGUI();
	gui->Init();
	gui->SetGLClearColor(30,30,30);
	gui->SetGLFWWindow(wnd);
	TestclguiMenuBar tm;
	while (!glfwWindowShouldClose(wnd)) {
	  glfwPollEvents();
	  gui->Exec();
	}
	clgui::DestroyCLGUI();
	glfwTerminate();

  return EXIT_SUCCESS;
}