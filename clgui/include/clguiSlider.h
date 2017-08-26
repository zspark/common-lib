#pragma once
#include "clguiComponent.h"
#include "clguiComponentVariable.h"

namespace clgui {

  class clguiSlider :public clguiComponent {
  public:
	 clguiSlider();
	 ~clguiSlider();

  public:
	 void Render()override;
	 void PostRender()override;

	 // Reset rendering type ,you can change it's value type here;
	 // this will not dispatch event.
	 void ResetTo(float value, float min, float max);
	 void ResetTo(clFloat3 value, clFloat3 min, clFloat3 max);

	 // only update it's current value.
	 // keep it's min and max as it is.
	 // this will not dispatch event.
	 // WARNING:
	 // this call will not change value type, so if it's a float currently but you
	 // wanna change to int, this call will do nothing;
	 // only if value type are the same will there be changing it's current value;
	 //void UpdateTo(int value);
	 //void UpdateTo(uint value);
	 void UpdateTo(float value);
	 void UpdateTo(clFloat3 value);
	 //void UpdateTo(double value);

	 // reset min and max range;
	 // if current value is not in the range of new one, nothing change.
	 // this will not dispatch event;
	 void SetRange(float min, float max);
	 void SetRange(clFloat3 min, clFloat3 max);

  private:
	 UniformComponentVariable m_value;
	 UniformComponentVariable m_max;
	 UniformComponentVariable m_min;

	 typedef void(*RenderFn)(ccharstar,UniformComponentVariable&,const UniformComponentVariable&,const UniformComponentVariable&);
	 RenderFn m_RenderFn=nullptr;

  };

}