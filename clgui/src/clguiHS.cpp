#include "clguiHS.h"
#include "imgui.h"
#include "clguiObjectType.h"

namespace clgui {

	clguiHS::clguiHS()
		:clguiComponent(clguiObjectType::OBJECT_TYPE_CHECKBOX) {
		SetCaption("CheckBox");
	}

	clguiHS::~clguiHS() {
	}
	void clguiHS::Render() {
		if(ImGui::TreeNode(m_caption)) {

			static int selection_mask=(1<<2); // Dumb representation of what may be user-side selection state. You may carry selection state inside or outside your objects in whatever format you see fit.
			int node_clicked=-1;                // Temporary storage of what node we have clicked to process selection at the end of the loop. May be a pointer to your own node type, etc.
			ImGui::PushStyleVar(ImGuiStyleVar_IndentSpacing,ImGui::GetFontSize()*3); // Increase spacing to differentiate leaves from expanded contents.

			hsNodeUint* rootNode=m_data.
			for(int i=0; i<60; i++) {
				// Disable the default open on single-click behavior and pass in Selected flag according to our selection state.
				ImGuiTreeNodeFlags node_flags=ImGuiTreeNodeFlags_OpenOnArrow|ImGuiTreeNodeFlags_OpenOnDoubleClick|((selection_mask & (1<<i))?ImGuiTreeNodeFlags_Selected:0);
				if(i<3) {
					// Node
					bool node_open=ImGui::TreeNodeEx((void*)(intptr_t)i,node_flags,"Selectable Node %d",i);
					if(ImGui::IsItemClicked())
						node_clicked=i;
					if(node_open) {
						ImGui::Text("Blah blah\nBlah Blah");
						ImGui::TreePop();
					}
				} else {
					// Leaf: The only reason we have a TreeNode at all is to allow selection of the leaf. Otherwise we can use BulletText() or TreeAdvanceToLabelPos()+Text().
					ImGui::TreeNodeEx((void*)(intptr_t)i,node_flags|ImGuiTreeNodeFlags_Leaf|ImGuiTreeNodeFlags_NoTreePushOnOpen,"Selectable Leaf %d",i);
					if(ImGui::IsItemClicked())
						node_clicked=i;
				}
			}
			if(node_clicked!=-1) {
				// Update selection state. Process outside of tree loop to avoid visual inconsistencies during the clicking-frame.
				if(ImGui::GetIO().KeyCtrl)
					selection_mask^=(1<<node_clicked);          // CTRL+click to toggle
				else //if (!(selection_mask & (1 << node_clicked))) // Depending on selection behavior you want, this commented bit preserve selection when clicking on item that is part of the selection
					selection_mask=(1<<node_clicked);           // Click to single-select
			}
			ImGui::PopStyleVar();
			ImGui::TreePop();
		}
		ImGui::TreePop();
	}

	void clguiHS::PostRender() {
		/*
		if(m_cv.CheckChange()) {
			clguiEvent evt(clguiEventType::clgui_EVT_CHECKBOX_SELECTION_CHANGE);
			evt.newValue.type=clUniformVariableType::CLBOOL;
			evt.newValue.boolValue=m_cv.GetNewValue();
			evt.oldValue.type=clUniformVariableType::CLBOOL;
			evt.oldValue.boolValue=m_cv.GetOldValue();
			DispatchEvent_(&evt);

			m_cv.Update();
		}
*/
	}
	void clguiHS::SetData(hsUint data) {
		m_data=data;
	}
	//void clguiHS::SetSelection(bool v) {
	//}
}
