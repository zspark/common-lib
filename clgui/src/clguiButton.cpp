#include "clguiButton.h"
#include "imgui.h"
#include "clguiObjectType.h"

namespace clgui {

	clguiButton::clguiButton()
		:clguiComponent(clguiObjectType::OBJECT_TYPE_BUTTON) {
		SetCaption("Button");
	}

	clguiButton::~clguiButton() {
	}
	void clguiButton::Render() {
		if(ImGui::Button(m_imguiRenderID.c_str())) {
			m_cv.SetNewValue(true);
		}
	}
	void clguiButton::PostRender() {
		if(m_cv.CheckChange()) {
			clguiEvent evt(clguiEventType::clgui_EVT_BUTTON_CLICK);
			evt.newValue.type=clUniformVariableType::CLBOOL;
			evt.newValue.boolValue=m_cv.GetNewValue();
			evt.oldValue.type=clUniformVariableType::CLBOOL;
			evt.oldValue.boolValue=m_cv.GetOldValue();
			DispatchEvent_(&evt);
			m_cv.SetNewValue(false);
		}
	}
}
