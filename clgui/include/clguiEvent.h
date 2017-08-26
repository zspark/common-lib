#pragma once
#include "clTypes.h"

namespace clgui {

	enum clguiEventType {
		clgui_EVT_BUTTON_CLICK=0,
		clgui_EVT_MENUITEM_STATUS_CHANGE,
		clgui_EVT_SLIDER_VALUE_CHANGE,
		clgui_EVT_CHECKBOX_SELECTION_CHANGE,
		clgui_EVT_WINDOW_CLOSE,
	};


	class clguiEvent {
	public:
		clguiEvent()=delete;
		clguiEvent(clguiEventType type);
		virtual ~clguiEvent();
		void StopPropagation();
		clguiEventType GetType()const;
		cl::clUniformVariable oldValue;
		cl::clUniformVariable newValue;

	private:
		friend class clguiObject;
		const clguiEventType m_type;
		bool m_bStopPropagation=false;
	};
}