#include "clWindowTree.h"

namespace clgui {

	void clWindowTree::RenderSpecific() {
		if(ImGui::TreeNode("Trees")) {
			if(ImGui::TreeNode("Basic trees")) {
				for(int i=0; i<5; i++)
				if(ImGui::TreeNode((void*)(intptr_t)i,"Child %d",i)) {
					ImGui::Text("blah blah");
					ImGui::TreePop();
				}
				ImGui::TreePop();
			}

			if(ImGui::TreeNode("Advanced, with Selectable nodes")) {
				static bool align_label_with_current_x_position=false;
				ImGui::Checkbox("Align label with current X position)",&align_label_with_current_x_position);
				ImGui::Text("Hello!");
				if(align_label_with_current_x_position)
					ImGui::Unindent(ImGui::GetTreeNodeToLabelSpacing());

				static int selection_mask=(1<<2); // Dumb representation of what may be user-side selection state. You may carry selection state inside or outside your objects in whatever format you see fit.
				int node_clicked=-1;                // Temporary storage of what node we have clicked to process selection at the end of the loop. May be a pointer to your own node type, etc.
				ImGui::PushStyleVar(ImGuiStyleVar_IndentSpacing,ImGui::GetFontSize()*3); // Increase spacing to differentiate leaves from expanded contents.
				for(int i=0; i<6; i++) {
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
				if(align_label_with_current_x_position)
					ImGui::Indent(ImGui::GetTreeNodeToLabelSpacing());
				ImGui::TreePop();
			}
			ImGui::TreePop();
		}
	}

}