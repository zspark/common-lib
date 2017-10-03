#include "clgui/clgui.h"
#include <vector>
#include "imgui/imgui_impl_glfw_gl3.h"
#include "clgui_object_manager.h"
#include "clgui/core/clgui_object.h"

using namespace std;

class clguiRenderer{
public:
static void RenderConponent(clgui::clguiObjectManager& mgr,clgui::clguiObject* obj){
  F_DBG_ASSERT(obj!=nullptr);
  clgui::clguiComponent* com=mgr.ToComponent(obj);
  if(!com->Visible())return;
  F_DBG_ASSERT(com);
  if(com->PreRender()){
    com->Render();
    com->PostRender();
  }
};

static void RenderContainer(clgui::clguiObjectManager& mgr,clgui::clguiObject* obj){
  F_DBG_ASSERT(obj!=nullptr);
  clgui::clguiContainer* con=mgr.ToContainer(obj); F_DBG_ASSERT(con);
  if(!con->Visible())return;
  if(con->PreRender()){
    con->Render();
    obj=mgr.GetFirstChild(con);
    while(obj){
      if(mgr.ToContainer(obj)){
        //container;
        RenderContainer(mgr,obj);
      } else{
        // none container;
        RenderConponent(mgr,obj);
      }
      obj=mgr.GetNextSibling(obj);
    }
    con->PostRender();
  }
};
};

CLGUI_NAMESPACE_START
class clguiContainer;
CLGUI_NAMESPACE_END

static void WindowResizeCallback(GLFWwindow* wnd,clint w,clint h){
  ImGui_ImplGlfw_UpdateWindowSize();
  clgui::clguiObjectManager* mgr=clgui::clguiObjectManager::GetIns();
  clgui::clguiContainer* con=mgr->Traverse<clgui::clguiContainer>(CLGUI_OBJECT_TYPE_CONTAINER,true);
  while(con){
    con->NoticeWindowSize(w,h);
    con=mgr->Traverse<clgui::clguiContainer>(CLGUI_OBJECT_TYPE_CONTAINER,false);
  }
}


static vector<clgui::clguiObject*> s_vecTobeDeleting;


CLGUI_NAMESPACE_START

void clguiInit(GLFWwindow* wnd){
  clguiObjectManager* mgr=clguiObjectManager::GetIns();
  mgr->Init();
  glfwSetWindowSizeCallback(wnd,WindowResizeCallback);
  ImGui_ImplGlfw_Init(wnd,true);
  ImGui_ImplGlfw_UpdateWindowSize();
}

void clguiExec(){
  ImGui_ImplGlfw_NewFrame();
  clguiObjectManager* mgr=clguiObjectManager::GetIns();
  clguiStage* stage=mgr->GetStage();
  F_DBG_ASSERT(stage);
  clguiRenderer::RenderContainer(*mgr,stage);
  ImGui::Render();

  //delete objects;
  if(s_vecTobeDeleting.size()>0){
    for(auto& it:s_vecTobeDeleting){
      mgr->DeleteObject(it);
    }
    s_vecTobeDeleting.clear();
  }
};

void clguiExit(){
  clguiObjectManager::DeleteIns();
  s_vecTobeDeleting.clear();
}

void clguiAddToStage(clguiComponent * com){
  clguiObjectManager* mgr=clguiObjectManager::GetIns();
  mgr->GetStage()->AddChild(com);
}

void clguiRemoveFromStage(clguiComponent * com){
  clguiObjectManager* mgr=clguiObjectManager::GetIns();
  mgr->GetStage()->RemoveChild(com);
}

void clguiDeleteObject(clguiObject * obj,clbool withChildren){
  s_vecTobeDeleting.push_back(obj);
  if(withChildren){
    clguiObjectManager* mgr=clguiObjectManager::GetIns();
    mgr->GetAllDecendant(obj,s_vecTobeDeleting);
  }
}

CLGUI_API void clguiDeleteChildren(clguiObject * obj){
  clguiObjectManager* mgr=clguiObjectManager::GetIns();
  mgr->GetAllDecendant(obj,s_vecTobeDeleting);
}

clguiStage * clguiGetStage(){
  clguiObjectManager* mgr=clguiObjectManager::GetIns();
  return mgr->GetStage();
}

CLGUI_API clguiMenuBar * clguiConverToMenuBar(clguiObject * obj){
  return clguiObjectManager::ToMenubar(obj);
}

CLGUI_API clguiMenu * clguiConverToMenu(clguiObject * obj){
  return clguiObjectManager::ToMenu(obj);
}

CLGUI_API clguiMenuItem * clguiConverToMenuItem(clguiObject * obj){
  return clguiObjectManager::ToMenuItem(obj);
}


CLGUI_NAMESPACE_END
