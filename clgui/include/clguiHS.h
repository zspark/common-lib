#pragma once
#include "clguiComponent.h"
#include "clguiComponentVariable.h";
#include "clHierarchicalStructure.h"

namespace clgui {

  class clguiHS :public clguiComponent {
  public:
		typedef clHierarchicalStructureNode_T<clUint> hsNodeUint;
		typedef clHierarchicalStructure_T<hsNodeUint> hsUint;
	 clguiHS();
	 ~clguiHS();

  public:
	 void Render();
	 void PostRender();

	public:
		void SetData(hsUint data);

  private:
		hsUint m_data;
		clUint m_uCurrentSelectedIndex;
  };

}