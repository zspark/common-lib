#include "clguiWindow.h"
#include "clTypes.h"
#include "imgui.h"
#include "clguiObjectType.h"
#include "clgui.h"

namespace clgui {

	clguiWindow::clguiWindow()
		:clguiComponentContainer(clguiObjectType::OBJECT_TYPE_WINDOW) {
		m_clVarBool.ResetTo(true);
		SetCaption("Window");
		clgui::GetCLGUI()->AddChild(this);
	}
	clguiWindow::~clguiWindow() {
	};

	void clguiWindow::Render() {
		ImGui::SetNextWindowSize(ImVec2(m_size.x,m_size.y),ImGuiSetCond_FirstUseEver);
		if(m_bCloseEventListened)
			ImGui::Begin(m_imguiRenderID.c_str(),m_clVarBool.GetNewValueRef());
		else
			ImGui::Begin(m_imguiRenderID.c_str());
		clgui::GetCLGUI()->RenderChildrenOf(this);
		ImGui::End();

	}
	void clguiWindow::PostRender(){
		if(!m_clVarBool.GetNewValue()) {
			clguiEvent evt(clguiEventType::clgui_EVT_WINDOW_CLOSE);
			evt.newValue.type=clUniformVariableType::CLBOOL;
			evt.newValue.boolValue=m_clVarBool.GetNewValue();
			evt.oldValue.type=clUniformVariableType::CLBOOL;
			evt.oldValue.boolValue=m_clVarBool.GetOldValue();
			DispatchEvent_(&evt);
			//m_clVarBool.SetNewValue(true);
		}
	}

	void clguiWindow::SetWindowSize(uint width,uint height) {
		m_size.Set(width,height);
	}
	void clguiWindow::SetWindowPos(int x,int y) {
		m_pos.Set(x,y);
	}
	void clguiWindow::SetCaption(ccharstar name) {
		m_caption=name;
		m_imguiRenderID=std::string(m_caption);
	}
	void clguiWindow::AddEventListener(clguiEventType eventName,EventCallBackFn cbFn) {
		m_bCloseEventListened=true;
		clguiObject::AddEventListener(eventName,cbFn);
	}
	bool clguiWindow::BuildLayoutComponentsByJson(Json::Value json) {
		auto mem=json.getMemberNames();
		for(auto it=mem.begin(); it!=mem.end(); it++) {
			std::string s=json[*it].toStyledString();
		}
		return true;
	}
}