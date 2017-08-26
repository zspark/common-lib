#include "clguiLabel.h"
#include "clguiObjectType.h"
#include "imgui.h"

namespace clgui {
  clguiLabel::clguiLabel()
	 :clguiComponent(clguiObjectType::OBJECT_TYPE_LABEL)
  {
	 SetCaption("Label");
  }

  clguiLabel::~clguiLabel() {
  }
  void clguiLabel::Render() {
	 ImVec4 iv4(m_color.x, m_color.y, m_color.z, 1);
	 ImGui::TextColored(iv4, m_imguiRenderID.c_str());
	 if (!m_value.empty()) {
		ImGui::SameLine();
		ImGui::TextColored(iv4, m_value.c_str());
	 }
  }
  void clguiLabel::SetColor(clFloat3 c) {
	 m_color = c;
  }

  void clguiLabel::SetValue(int value) {
	 char tmpc[10];
	 sprintf_s(tmpc, "%d", value);
	 m_value = std::string(tmpc);
  }
  void clguiLabel::SetValue(float value) {
	 char tmpc[10];
	 sprintf_s(tmpc, "%f", value);
	 m_value = std::string(tmpc);
  }
  void clguiLabel::SetValue(double value) {
	 char tmpc[10];
	 sprintf_s(tmpc, "%f", value);
	 m_value = std::string(tmpc);
  }
  void clguiLabel::SetValue(ccharstar value) {
	 m_value = std::string(value);
  }
}
