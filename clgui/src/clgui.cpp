#include "clgui.h"
#include "imgui.h"
#include "imgui_impl_glfw_gl3.h"
#include "clguiObjectType.h"
#include "clHierarchicalStructure.h"

#include "clguiWindow.h"

class TempclguiObject:public clgui::clguiObject {
public:
	TempclguiObject():clguiObject(clguiObjectType::OBJECT_TYPE_NULL) {}
	~TempclguiObject() {}
	void Render() {};
};

typedef cl::clHierarchicalStructureNode_T<clgui::clguiObject*> NodeObjectStar;
typedef cl::clHierarchicalStructure_T<NodeObjectStar> HS;

static HS* s_hs=nullptr;
static std::vector<NodeObjectStar*>* s_vecNeedDeleting=nullptr;
static TempclguiObject* s_tempNullObject;
static bool s_bCleanFlag=false;

// no shading node , only one in application;
static NodeObjectStar* s_RootNode=nullptr;
static clgui::clGUI* s_self=nullptr;

namespace clgui {

	clGUI::~clGUI() {
		m_glfwWnd=nullptr;
	};
	void clGUI::Init() {
	}

	void clGUI::SetGLFWWindow(GLFWwindow* wnd) {
		m_glfwWnd=wnd;
		ImGui_ImplGlfwGL3_Init(wnd,true);
	}
	void clGUI::SetGLClearColor(int r,int g,int b) {
		const float F=1.0f/255.0f;
		m_clearColor.x=r*F;
		m_clearColor.y=r*F;
		m_clearColor.z=r*F;
		m_clearColor.w=1.0f;
	}

	void clGUI::Exec() {
		ImGui_ImplGlfwGL3_NewFrame();

		NodeObjectStar* node=s_RootNode->GetFirstChildNode();
		while(node) {

			/*
			clguiObject* obj = node->mCustomObject;
			obj->PreRender();
			obj->Render();
			obj->PostRender();
			*/

			node->mCustomObject->PreRender();
			node->mCustomObject->Render();
			node->mCustomObject->PostRender();

			node=node->GetNextSiblingNode();
		}

		//delete dirty flagged node;
		if(s_bCleanFlag) {
			for(auto it:*s_vecNeedDeleting) {
				s_hs->RemoveNode(it->GetId());
				delete it;
			}
			s_vecNeedDeleting->clear();
			s_bCleanFlag=false;
		}

		// Rendering
		int display_w,display_h;
		glfwGetFramebufferSize(m_glfwWnd,&display_w,&display_h);
		glViewport(0,0,display_w,display_h);
		glClearColor(m_clearColor.x,m_clearColor.y,m_clearColor.z,m_clearColor.w);
		glClear(GL_COLOR_BUFFER_BIT);
		ImGui::Render();
		glfwSwapBuffers(m_glfwWnd);
	};

	void clGUI::Exit() {};

	void clGUI::AddChild(clguiObject* child) {
		AddChild(child,s_RootNode->GetId());
	}
	void clGUI::AddChild(clguiObject* child,uint parentNodeIndex) {
		NodeObjectStar* node=s_hs->CreateNode();
		node->mCustomObject=child;
		child->SetNodeIndex(node->GetId());
		NodeObjectStar* parentNode=s_hs->GetNode(parentNodeIndex);
		s_hs->InsertNode(parentNode,node,clHierarchicalStructureNodeRelation::R_LAST_CHILD);
	}
	void clGUI::RemoveChild(clguiObject* child) {
		NodeObjectStar* node=s_hs->GetNode(child->GetNodeIndex());
		if(node) {
			node->mCustomObject=s_tempNullObject;
			child->SetNodeIndex(UINT_MAX);
			s_vecNeedDeleting->push_back(node);
			s_bCleanFlag=true;
		}
	}

	clguiObject* clGUI::GetChildOf(clguiComponentContainer* container,uint index)const {
		NodeObjectStar* parentNode=s_hs->GetNode(container->GetNodeIndex());
		NodeObjectStar* childNode=parentNode->GetFirstChildNode();
		int idx=index;
		while(idx-->0) {
			childNode=childNode->GetNextSiblingNode();
			if(childNode==nullptr)return nullptr;
		}
		return childNode->mCustomObject;
	}

	void clGUI::DeleteChildrenOf(clguiComponentContainer* container) {
		NodeObjectStar* parentNode=s_hs->GetNode(container->GetNodeIndex());
		NodeObjectStar* node=parentNode->GetFirstChildNode();
		while(node) {
			delete node->mCustomObject;
			node=node->GetNextSiblingNode();
		}
	}


	void clGUI::RenderChildrenOf(clguiComponentContainer* container) {
		NodeObjectStar* parentNode=s_hs->GetNode(container->GetNodeIndex());
		NodeObjectStar* node=parentNode->GetFirstChildNode();
		while(node) {
			node->mCustomObject->PreRender();
			node->mCustomObject->Render();
			node->mCustomObject->PostRender();

			node=node->GetNextSiblingNode();
		}
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////
	// static



	clGUI* GetCLGUI() {
		if(s_self==nullptr) {
			s_hs=new HS();
			s_RootNode=s_hs->CreateNode();
			s_hs->InsertNode(nullptr,s_RootNode,cl::clHierarchicalStructureNodeRelation::R_FIRST_CHILD);
			s_vecNeedDeleting=new std::vector<NodeObjectStar*>();
			s_self=new clGUI();
			s_tempNullObject=new TempclguiObject();
		}
		return s_self;
	}
	void DestroyCLGUI() {
		if(s_self) delete s_self;
		s_self=nullptr;
		if(s_hs) {
			s_hs->DeleteAllNodes();
			delete s_hs;
		}
		s_hs=nullptr;
		s_RootNode=nullptr;
		s_vecNeedDeleting->clear();
		delete s_vecNeedDeleting;
		s_vecNeedDeleting=nullptr;
		delete s_tempNullObject;
	}
}
