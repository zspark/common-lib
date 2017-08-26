#include "clguiCheckBox.h"
#include "imgui.h"
#include "clguiObjectType.h"

namespace clgui {

	clguiCheckBox::clguiCheckBox()
		:clguiComponent(clguiObjectType::OBJECT_TYPE_CHECKBOX) {
		SetCaption("CheckBox");
		m_cv.ResetTo(false);
	}

	clguiCheckBox::~clguiCheckBox() {
	}
	void clguiCheckBox::Render() {
		ImGui::Checkbox(m_imguiRenderID.c_str(),m_cv.GetNewValueRef());
	}
	void clguiCheckBox::PostRender() {
		if(m_cv.CheckChange()) {
			clguiEvent evt(clguiEventType::clgui_EVT_CHECKBOX_SELECTION_CHANGE);
			evt.newValue.type=clUniformVariableType::CLBOOL;
			evt.newValue.boolValue=m_cv.GetNewValue();
			evt.oldValue.type=clUniformVariableType::CLBOOL;
			evt.oldValue.boolValue=m_cv.GetOldValue();
			DispatchEvent_(&evt);

			m_cv.Update();
		}
	}
	void clguiCheckBox::SetSelection(bool v) {
		m_cv.ResetTo(v);
	}
}
