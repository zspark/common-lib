#include "clgui/component/clgui_menu_bar.h"
#include "core\clgui_object_manager.h"
#include "clgui/component/clgui_menu.h"
#include "clgui/component/clgui_menu_item.h"
#include "imgui/imgui.h"
#include "clgui/clgui.h"

CLGUI_NAMESPACE_START

void clguiMenuItem::Render(){
  ImGui::MenuItem(m_sRenderName.c_str(),m_shortKey.c_str(),m_clVarBool[0]);
}

clguiMenuItem::clguiMenuItem()
  :clguiComponent(CLGUI_OBJECT_TYPE_MENU_ITEM),m_clVarBool(false){
}

void clguiMenuItem::SetSelection(clbool b){
  m_clVarBool.ResetTo(b);
}

clbool clguiMenuItem::GetSelection() const{
  return m_clVarBool[0];
}

void clguiMenuItem::Enable(clbool b){
  m_bEnable=b;
}

clbool clguiMenuItem::Enable()const{
  return m_bEnable;
}

void clguiMenuItem::PostRender(){
  if(m_clVarBool.CheckChange()){
    clguiEventMenuItemStatusChange evt(this,clguiEventType::EVT_MENUITEM_STATUS_CHANGE);
    DispatchEvent_(&evt);
    m_clVarBool.Update();
  }
}

clguiMenuItem::~clguiMenuItem(){}





clguiMenu::clguiMenu()
  :clguiContainer(CLGUI_OBJECT_TYPE_MENU)
{};

clguiMenu::~clguiMenu(){}

clbool clguiMenu::PreRender(){
  return ImGui::BeginMenu(m_sRenderName.c_str());
}

void clguiMenu::Render(){
  ImGui::EndMenu();
}






clguiMenuBar::clguiMenuBar()
  :clguiContainer(CLGUI_OBJECT_TYPE_MENUBAR){
};

clguiMenuBar::~clguiMenuBar(){}

clbool clguiMenuBar::PreRender(){
  return ImGui::BeginMainMenuBar();
}

void clguiMenuBar::Render(){
  ImGui::EndMainMenuBar();
}

void clguiMenuBar::AddChild(clguiMenu * menu){
  clguiContainer::AddChild(menu);
}

void clguiMenuBar::RemoveChild(clguiMenu * menu){
  clguiContainer::RemoveChild(menu);
}

/*
bool clguiMenuBar::BuildLayoutComponentsByJson(Json::Value json){
  Json::Value mb=json["menubar"];
  std::string s=mb.toStyledString();
  const uint n{mb.size()};
  for(uint i=0;i<n;i++){
    Json::Value comp=mb[i];
    if(comp["type"].asString()=="menuitem"){

    }
  }
  auto mem=mb.getMemberNames();
  for(auto it=mem.begin(); it!=mem.end(); it++){
    std::string s=json[*it].toStyledString();
  }
  return true;
}
*/

CLGUI_NAMESPACE_END