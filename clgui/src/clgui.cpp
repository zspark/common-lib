#include "clgui.h"
#include "imgui.h"
#include "imgui_impl_glfw_gl3.h"
#include "clgui_object_manager.h"
#include "clguiObject.h"

namespace clgui{
clGUI* clGUI::sIns=nullptr;
clGUI * clGUI::GetIns(){
  if(!sIns)sIns=new clGUI();
  return sIns;
}
clGUI::~clGUI(){ };
void clGUI::Init(GLFWwindow* wnd){
  m_glfwWnd=wnd;
  ImGui_ImplGlfwGL3_Init(wnd,true);
}

void clGUI::SetGLClearColor(int r,int g,int b){
  const float F=1.0f/255.0f;
  m_clearColor.x=r*F;
  m_clearColor.y=r*F;
  m_clearColor.z=r*F;
  m_clearColor.w=1.0f;
}

void clGUI::Exec(){
  ImGui_ImplGlfwGL3_NewFrame();

  clguiObjectManager* mgr=clguiObjectManager::GetIns();
  clguiRenderable* robj=mgr->Triverse<clguiRenderable>(CLGUI_OBJECT_TYPE_RENDERABLE,true);
  while(robj){

    robj->PreRender();
    robj->Render();
    robj->PostRender();

    robj=mgr->Triverse<clguiRenderable>(CLGUI_OBJECT_TYPE_RENDERABLE);
  }

  int display_w,display_h;
  glfwGetFramebufferSize(m_glfwWnd,&display_w,&display_h);
  glViewport(0,0,display_w,display_h);
  glClearColor(m_clearColor.x,m_clearColor.y,m_clearColor.z,m_clearColor.w);
  glClear(GL_COLOR_BUFFER_BIT);
  ImGui::Render();
  glfwSwapBuffers(m_glfwWnd);

};

void clGUI::Exit(){
  m_glfwWnd=nullptr;
};

}
