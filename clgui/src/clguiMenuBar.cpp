#include "clguiMenuBar.h"
#include "imgui.h"
#include "clgui.h"
#include "clguiMenu.h"
#include "clguiObjectType.h"

namespace clgui {
  clguiMenuBar::clguiMenuBar()
	 :clguiComponentContainer(clguiObjectType::OBJECT_TYPE_MENUBAR) {
	 clgui::GetCLGUI()->AddChild(this);
  };
  clguiMenuBar::~clguiMenuBar() { }

  clguiMenu* clguiMenuBar::AddChild(ccharstar menuName) {
	 clguiMenu* m = new clguiMenu();
	 m->SetCaption(menuName);
	 AddChild(m);
	 return m;
  }
	clguiMenu* clguiMenuBar::GetMenu(uint index) {
		return static_cast<clguiMenu*>(clgui::GetCLGUI()->GetChildOf(this,index));
	}

  void clguiMenuBar::Render() {
	 if (ImGui::BeginMainMenuBar()) {
		clgui::GetCLGUI()->RenderChildrenOf(this);
		ImGui::EndMainMenuBar();
	 }
  }
	bool clguiMenuBar::BuildLayoutComponentsByJson(Json::Value json) {
		Json::Value mb=json["menubar"];
		std::string s=mb.toStyledString();
		const uint n{mb.size()};
		for(uint i=0;i<n;i++) {
			Json::Value comp=mb[i];
			if(comp["type"].asString()=="menuitem") {

			}
		}
		auto mem=mb.getMemberNames();
		for(auto it=mem.begin(); it!=mem.end(); it++) {
			std::string s=json[*it].toStyledString();
		}
		return true;
	}
}