#include "clgui.h"
#include "imgui.h"
#include "imgui_impl_glfw_gl3.h"
#include "clgui_object_manager.h"
#include "clguiObject.h"

class clguiRenderer{
public:
static void RenderConponent(clgui::clguiObjectManager& mgr,clgui::clguiObject* obj){
  F_DBG_ASSERT(obj!=nullptr);
  clgui::clguiComponent* com=mgr.ToclguiComponent(obj);
  if(!com->Visible())return;
  F_DBG_ASSERT(com);
  com->PreRender();
  com->Render();
  com->PostRender();
};

static void RenderContainer(clgui::clguiObjectManager& mgr,clgui::clguiObject* obj){
  F_DBG_ASSERT(obj!=nullptr);
  clgui::clguiContainer* con=mgr.ToclguiContainer(obj); F_DBG_ASSERT(con);
  if(!con->Visible())return;
  con->PreRender();
  con->Render();
  obj=mgr.GetFirstChild(con);
  while(obj){
    if(mgr.ToclguiContainer(obj)){
      //container;
      RenderContainer(mgr,obj);
    } else{
      // none container;
      RenderConponent(mgr,obj);
    }
    obj=mgr.GetNextSibling(obj);
  }
  con->PostRender();
};
};


CLGUI_NAMESPACE_START

void clguiInit(GLFWwindow* wnd){
  clguiObjectManager* mgr=clguiObjectManager::GetIns();
  mgr->GetStage()->SetGLFWwindow(wnd);
  ImGui_ImplGlfwGL3_Init(wnd,true);
}

void clguiExec(){
  ImGui_ImplGlfwGL3_NewFrame();
  clguiObjectManager* mgr=clguiObjectManager::GetIns();
  clguiStage* stage=mgr->GetStage();
  F_DBG_ASSERT(stage);
  clguiRenderer::RenderContainer(*mgr,stage);
  ImGui::Render();
};

void clguiExit(){
  clguiObjectManager::DeleteIns();
}

void clguiAddToStage(clguiComponent * com){
  clguiObjectManager* mgr=clguiObjectManager::GetIns();
  mgr->GetStage()->AddChild(com);
}

CLGUI_API void clguiRemoveFromStage(clguiComponent * com){
  clguiObjectManager* mgr=clguiObjectManager::GetIns();
  mgr->GetStage()->RemoveChild(com);
}

CLGUI_API void clguiSetStageColor(cluint r,cluint g,cluint b){
  clguiObjectManager* mgr=clguiObjectManager::GetIns();
  mgr->GetStage()->SetColor(r,g,b);
}

CLGUI_NAMESPACE_END
