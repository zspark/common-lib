#include "clguiMenu.h"
#include "imgui.h"
#include "clgui.h"
#include "clguiObjectType.h"

namespace clgui {
  clguiMenu::clguiMenu() :clguiComponentContainer(clguiObjectType::OBJECT_TYPE_MENU) {
	 SetCaption("Menu");
  }
  clguiMenu::~clguiMenu() { }

  void clguiMenu::Render() {
	 if (ImGui::BeginMenu(m_imguiRenderID.c_str())) {
		clgui::GetCLGUI()->RenderChildrenOf(this);
		ImGui::EndMenu();
	 }
  }

  /*
*/
  clguiMenuItem* clguiMenu::AddChild(ccharstar menuItemName){
	 clguiMenuItem* mi = new clguiMenuItem();
	 mi->SetCaption(menuItemName);
	 AddChild(mi);
	 return mi;
  }
  /*
  clguiMenuItem* clguiMenu::AddChild(ccharstar menuItemName, CallBackBoolFn cbFn) {
	 clguiMenuItem* mi = new clguiMenuItem();
	 mi->SetCaption(menuItemName);
	 //mi->AddEventListener(cbFn);
	 AddChild(mi);
  }
*/
	clguiObject* clguiMenu::GetMenuItem(uint index) {
		return static_cast<clguiObject*>(clgui::GetCLGUI()->GetChildOf(this,index));
	}
}
