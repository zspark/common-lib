#include "clguiMenuItem.h"
#include "imgui.h"
#include "clguiObjectType.h"

namespace clgui {
	clguiMenuItem::clguiMenuItem()
		:clguiComponent(clguiObjectType::OBJECT_TYPE_MENUITEM) {
	  SetCaption("Default menu item.");
		m_clVarBool.ResetTo(false);
	}
	clguiMenuItem::~clguiMenuItem() {
	}
	void clguiMenuItem::Render() {
		ImGui::MenuItem(m_imguiRenderID.c_str(),"CTRL+L",m_clVarBool.GetNewValueRef());
	}
	void clguiMenuItem::SetSelection(bool status) {
		m_clVarBool.ResetTo(status);
	}

	void clguiMenuItem::PostRender() {
		if(m_clVarBool.CheckChange()) {
			clguiEvent evt(clguiEventType::clgui_EVT_MENUITEM_STATUS_CHANGE);
			evt.newValue.type=clUniformVariableType::CLBOOL;
			evt.newValue.boolValue=m_clVarBool.GetNewValue();
			evt.oldValue.type=clUniformVariableType::CLBOOL;
			evt.oldValue.boolValue=m_clVarBool.GetOldValue();
			DispatchEvent_(&evt);
			m_clVarBool.Update();
		}
	}
}
