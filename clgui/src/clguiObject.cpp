#pragma once
#include <vector>
#include "clguiObject.h"
#include "clguiUtil.h"
#include "clgui.h"

namespace clgui {
  using namespace cl;

  clguiObject::clguiObject(clguiObjectType objectType)
	 :m_objectID(GetUniqueId())
	 , m_objectType(objectType)
  {};

  clguiObject::~clguiObject() {
	 if (m_nodeIndex != UINT_MAX) {
		//means this object is still in hierarchical structure.
		clgui::GetCLGUI()->RemoveChild(this);
	 }
	 m_mapListeners_name_listener.clear();
  };
  void clguiObject::SetCaption(ccharstar name) {
	 m_caption = name;
	 m_imguiRenderID = std::string(m_caption) + "##" + NumberToString(m_objectID);
  }
  
  uint clguiObject::GetObjectType()const { return m_objectType; };
  uint clguiObject::GetObjectID()const { return m_objectID; };
  uint clguiObject::GetNodeIndex()const { return m_nodeIndex; }
  void clguiObject::SetNodeIndex(uint index) { m_nodeIndex = index; }

	void clguiObject::AddEventListener(clguiEventType eventName,EventCallBackFn cbFn) {
		m_mapListeners_name_listener[eventName]=cbFn;
	}
	void clguiObject::DispatchEvent_(clguiEvent* evt) {
		std::vector<clgui::EventCallBackFn> tmpVec;
		for(auto var:m_mapListeners_name_listener) {
			if(var.first==evt->m_type) {
				tmpVec.push_back(var.second);
			}
		}
		for(auto var:tmpVec) {
			var(evt);
		}
	}
}
