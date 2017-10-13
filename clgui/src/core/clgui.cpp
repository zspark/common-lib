#include "clgui/clgui.h"
#include <vector>
#include "imgui/imgui_impl_glfw_gl3.h"
#include "clgui_object_manager.h"
#include "clgui/core/clgui_object.h"

using namespace std;

static class clguiRenderer{
public:
static void RenderConponent(clgui::clguiObjectManager& mgr,clgui::clguiComponent* com){
  F_DBG_ASSERT(com!=nullptr);
  if(!com->m_visible)return;
  if(com->m_isSameline)ImGui::SameLine(com->m_posx,com->m_spacing);
  if(com->PreRender()){
    com->Render();
  }
  com->PostRender();
};

static void RenderContainer(clgui::clguiObjectManager& mgr,clgui::clguiComponent* com){
  F_DBG_ASSERT(com!=nullptr);
  clgui::clguiContainer* con=mgr.ToContainer(com); F_DBG_ASSERT(con);
  if(!con->m_visible)return;
  if(con->PreRender()){
    com=mgr.GetFirstChild(con);
    while(com){
      if(mgr.ToContainer(com)){
        //container;
        RenderContainer(mgr,com);
      } else{
        // none container;
        RenderConponent(mgr,com);
      }
      com=mgr.GetNextSibling(com);
    }
    con->Render();
  }
  con->PostRender();
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
    con->NoticeSystemWndNewSize(w,h);
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

CLGUI_API void clguiDeleteObject(cluint objID,clbool withChildren){

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
  if(obj)return clguiObjectManager::ToMenubar(obj);
  else return nullptr;
}

CLGUI_API clguiMenu * clguiConverToMenu(clguiObject * obj){
  if(obj) return clguiObjectManager::ToMenu(obj);
  else return nullptr;
}

CLGUI_API clguiMenuItem * clguiConverToMenuItem(clguiObject * obj){
  if(obj) return clguiObjectManager::ToMenuItem(obj);
  else return nullptr;
}


CLGUI_NAMESPACE_END
