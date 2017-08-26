#include "clguiSlider.h"
#include "imgui.h"
#include "clguiObjectType.h"
#include "clguiComponentVariable.h"

using namespace clgui;

static void RenderFloat3(
  ccharstar caption,
  UniformComponentVariable& value,
  const UniformComponentVariable& min,
  const UniformComponentVariable& max)
{
  ImGui::SliderFloat3(caption, &(value.float3Value.GetNewValueRef()->x), min.float3Value.GetNewValue().x, max.float3Value.GetNewValue().x);
}

static void RenderFloat(ccharstar caption, UniformComponentVariable& value, const UniformComponentVariable& min, const UniformComponentVariable& max) {
  ImGui::SliderFloat(caption, value.floatValue.GetNewValueRef(), min.floatValue.GetNewValue(), max.floatValue.GetNewValue());
}


namespace clgui {
  clguiSlider::clguiSlider()
	 :clguiComponent(clguiObjectType::OBJECT_TYPE_SLIDER) {
	 m_value.type = UniformComponentVariableType::UCV_FLOAT;
	 m_value.floatValue.SetNewValue(.5f);
	 m_min.type = UniformComponentVariableType::UCV_FLOAT;
	 m_min.floatValue.SetNewValue(0.f);
	 m_max.type = UniformComponentVariableType::UCV_FLOAT;
	 m_max.floatValue.SetNewValue(1.f);
	 m_RenderFn = RenderFloat;
	 SetCaption("Slider");
  }

  clguiSlider::~clguiSlider() {
	 m_RenderFn = nullptr;
  }
  void clguiSlider::Render() {
	 m_RenderFn(m_imguiRenderID.c_str(), m_value, m_min, m_max);
  }

  void clguiSlider::PostRender(){
	 if (m_value.CheckChange()) {
		 clguiEvent evt(clguiEventType::clgui_EVT_SLIDER_VALUE_CHANGE);
		 evt.newValue.type=clUniformVariableType::CLFLOAT;
		 evt.newValue.floatValue=m_value.floatValue.GetNewValue();
		 evt.oldValue.type=clUniformVariableType::CLFLOAT;
		 evt.oldValue.floatValue=m_value.floatValue.GetOldValue();
		 DispatchEvent_(&evt);
		 m_value.Update();
	 }
	}

  void clguiSlider::ResetTo(float value, float min, float max) {
	 m_value.type = UniformComponentVariableType::UCV_FLOAT;
	 m_value.floatValue.ResetTo(value);
	 m_min.type = UniformComponentVariableType::UCV_FLOAT;
	 m_min.floatValue.ResetTo(min);
	 m_max.type = UniformComponentVariableType::UCV_FLOAT;
	 m_max.floatValue.ResetTo(max);
	 m_RenderFn = RenderFloat;

  }
  void clguiSlider::ResetTo(clFloat3 value, clFloat3 min, clFloat3 max) {
	 m_value.type = UniformComponentVariableType::UCV_FLOAT3;
	 m_value.float3Value.ResetTo(value);
	 m_min.type = UniformComponentVariableType::UCV_FLOAT3;
	 m_min.float3Value.ResetTo(min);
	 m_max.type = UniformComponentVariableType::UCV_FLOAT3;
	 m_max.float3Value.ResetTo(max);
	 m_RenderFn = RenderFloat3;
  }

  void clguiSlider::UpdateTo(clFloat3 value) {
	 if (m_value.type == UniformComponentVariableType::UCV_FLOAT3) {
		m_value.float3Value.ResetTo(value);
	 }
  }
  void clguiSlider::UpdateTo(float value) {
	 if (m_value.type == UniformComponentVariableType::UCV_FLOAT) {
		m_value.floatValue.ResetTo(value);
	 }
  }

  void clguiSlider::SetRange(float min, float max) {
	 if (m_value.type == UniformComponentVariableType::UCV_FLOAT) {
		m_min.floatValue.ResetTo(min);
		m_max.floatValue.ResetTo(max);
	 }
  }
  void clguiSlider::SetRange(clFloat3 min, clFloat3 max) {
	 if (m_value.type == UniformComponentVariableType::UCV_FLOAT3) {
		m_min.float3Value.ResetTo(min);
		m_max.float3Value.ResetTo(max);
	 }
  }
}
