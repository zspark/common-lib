#include "clgui.h"
#include "clgui_gui_sets.h"

using namespace std;

static void errorCallback(int error,const char* description){
  //fprintf(stderr, "Error %d: %s\n", error, description);
}

static void cf(const clgui::clguiEvent* evt){
  /*
  clguiButton* btn=new clguiButton();
  gui->AddToStage(btn);
  */
  //gui->RemoveFromStage(evt->GetSenderAs<clguiComponent*>(CLGUI_OBJECT_TYPE_COMPONENT));
}
static void CreateGUI(){
  clgui::clguiWindow* wnd=new clgui::clguiWindow();
  wnd->SetCaption("Hello windows");
  wnd->SetPosition(100,100);
  wnd->SetSize(400,300);
  clgui::clguiAddToStage(wnd);


  clgui::clguiButton* btn=new clgui::clguiButton();
  btn->AddEventListener(clgui::clguiEventType::CLGUI_EVT_BUTTON_CLICK,cf);
  wnd->AddChild(btn);
  //btn->clguiSetSize(50,20);
  //btn->Visible(false);
}


int main(int argc,char* argv[]){
  glfwSetErrorCallback(errorCallback);
  if(!glfwInit()) exit(EXIT_FAILURE);
  //glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
  //glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,2);
  //glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);

  int size[2]={600,400};
  char* title="Hello clgui!";
  GLFWwindow* wnd=glfwCreateWindow(size[0],size[1],title,NULL,NULL);
  glfwMakeContextCurrent(wnd);
  //glfwSwapInterval(1);
  glfwSetWindowPos(wnd,400,200);

  clgui::clguiInit(wnd);
  clgui::clguiSetStageColor(191,191,0);
  CreateGUI();

  while(!glfwWindowShouldClose(wnd)){
    glfwPollEvents();
    clgui::clguiExec();
    glfwSwapBuffers(wnd);
  }
  clgui::clguiExit();
  glfwTerminate();

  return EXIT_SUCCESS;
}