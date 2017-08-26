#pragma once
#include <map>
#include <limits>
#include "clTypes.h"
#include "clUtil.h"
#include "clguiObjectType.h"
#include "clguiEvent.h"
#include "clguiComponentVariable.h"

namespace clgui {
  using namespace cl;

  class clguiObject {
  public:
	 clguiObject(clguiObjectType objectType);
	 virtual ~clguiObject();
	 clguiObject() = delete;
	 clguiObject(const clguiObject&) = delete;
	 clguiObject(const clguiObject*) = delete;

  public:
	 uint GetObjectType()const;
	 uint GetObjectID()const;
	 uint GetNodeIndex()const;
	 void SetNodeIndex(uint index);

	 virtual void Init() {};
	 virtual void PreRender() {};
	 virtual void Render() = 0;
	 virtual void PostRender() {};
	 virtual void Destroy() {};

	 //EvenListener;
	 virtual void AddEventListener(clguiEventType eventName, EventCallBackFn cbFn);
	 void SetCaption(ccharstar name);

  protected:
	 void DispatchEvent_(clguiEvent*);

  protected:
	 ccharstar m_caption = "NULL";
	 std::string m_imguiRenderID = "NULL";
	 clguiObjectType m_objectType;
	 const uint m_objectID;
	 int m_nodeIndex = UINT_MAX;

	private:
		std::map<clguiEventType,EventCallBackFn> m_mapListeners_name_listener;
  };
}
