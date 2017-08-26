#include "clguiEvent.h"

using namespace cl;
namespace clgui {
	clguiEvent::clguiEvent(clguiEventType type):m_type(type) {
	}
	clguiEvent::~clguiEvent() {}
	/*
	const clUniformVariable* clguiEvent::GetOldValue() {
		return &m_oldValue;
	}
	const clUniformVariable* clguiEvent::GetNewValue() {
		return &m_newValue;
	}
*/
	void clguiEvent::StopPropagation() {
		m_bStopPropagation=true;
	}
	clguiEventType clguiEvent::GetType()const {
		return m_type;
	};
}
