#include "clguiComponentContainer.h"
#include "clgui.h"

namespace clgui {

  clguiComponentContainer::clguiComponentContainer(clguiObjectType objectType)
	 :clguiObject(objectType) {
  };

  clguiComponentContainer::~clguiComponentContainer() {
	 clgui::GetCLGUI()->DeleteChildrenOf(this);
  };

  void clguiComponentContainer::AddChild(clguiObject* child) {
	 clgui::GetCLGUI()->AddChild(child,m_nodeIndex);
  }
  void clguiComponentContainer::RemoveChild(clguiObject* child) {
	 clgui::GetCLGUI()->RemoveChild(child);
  }
	bool clguiComponentContainer::BuildLayoutComponentsByJson(Json::Value json) {
		auto mem=json.getMemberNames();
		for(auto it=mem.begin(); it!=mem.end(); it++) {
			std::string s=json[*it].toStyledString();
			int a={10};
			int b=10+a;
		}
		return true;
	}
}
