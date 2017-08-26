#include "ImGui_Wnd.h"
#include "imgui.h"
#include "MEFacade.h"
#include "CommonGui.h"

#pragma region LightWnd
void CImGui_LightWnd::Destroy() {
	m_pSelectedLight=nullptr;
	m_lightsChainRoot=nullptr;
}
void CImGui_LightWnd::Init(){
	m_lightsChainRoot=MECFacade::GetSington()->GetLightManager()->GetLightsChainRoot();
}

void CImGui_LightWnd::Render(){

	ImGui::SetNextWindowSize(ImVec2(500,440),ImGuiSetCond_FirstUseEver);
	if(ImGui::Begin("Lighting",&m_bIsWndOpen,ImGuiWindowFlags_MenuBar)) {

		// left
		ImGui::BeginChild("left pane",ImVec2(150,0),true);

		// m_lightsChainRoot is Root light,no shading ,invisible.
		CVirtualLight* tmpl=m_lightsChainRoot->Next();

		while(tmpl!=nullptr) {
			char label[10];
			int i=tmpl->GetId();
			sprintf(label,"Light %d",i);
			if(ImGui::Selectable(label,m_iSelectedLightIdex==i)) {
				m_iSelectedLightIdex=i;
				//fetch specific light structure data;
				m_pSelectedLight=tmpl;
				m_SelectedLightType=tmpl->GetType();
			}

			tmpl=tmpl->Next();
		}
		if(ImGui::Button("add",ImVec2(100,0))) {
			MECFacade::GetSington()->GetLightManager()->AddLight(e_lightType::LIGHT_TP_POINT,m_LightNumber++);
		}
		if(ImGui::Button("remove",ImVec2(100,0))) {
			MECFacade::GetSington()->GetLightManager()->RemoveLight(m_pSelectedLight);
			m_pSelectedLight=nullptr;
		}
		if(ImGui::Button("SendToOptix",ImVec2(100,0))) {
			MECFacade::GetSington()->GetLightManager()->SendDataToOptix(nullptr);
		}
		ImGui::EndChild();
		ImGui::SameLine();


		// right
#pragma region right
		ImGui::BeginGroup();
		if(m_pSelectedLight!=nullptr) {
			ImGui::BeginChild("item view",ImVec2(0,-ImGui::GetItemsLineHeightWithSpacing())); // Leave room for 1 line below us
			ImGui::Text("Light: %d",m_iSelectedLightIdex);
			ImGui::Combo("Light Type",&m_SelectedLightType,
						 " PointLight\0"
						 " DirectionalLight\0"
						 " SpotLight\0"
						 " AreaLight\0\0"
						 );
			if(m_pSelectedLight->GetType()!=e_lightType(m_SelectedLightType)) {
				m_pSelectedLight=MECFacade::GetSington()->GetLightManager()->ChangeLightTo(m_pSelectedLight,e_lightType(m_SelectedLightType));
				m_SelectedLightType=m_pSelectedLight->GetType();
			}
			m_pSelectedLight->PreRender();
			m_pSelectedLight->Render();
			ImGui::EndChild();
		} else {
			ImGui::TextDisabled("Please select a specific light at the left panel.");
		}

		ImGui::EndGroup();
#pragma endregion//right

	}
	ImGui::End();
}
#pragma endregion//lightWnd
#pragma region PanelWnd

void CImGui_MainPanelWnd::Init() {
	m_data=MECFacade::GetSington()->GetData();
	m_pcp=MECFacade::GetSington()->GetCase();
}

void CImGui_MainPanelWnd::RenderCommon() {
	static bool UseToolTip=false;

	ImGui::Text(m_pcp->GetCaseName().c_str());
	ImGui::SameLine();
	ImGui2::ShowHelpMarker(m_pcp->GetCaseDes().c_str());
	ImGui::Separator();
	ImGui::Text("%.3f ms/frame (%.1f FPS)",1000.0f/ImGui::GetIO().Framerate,ImGui::GetIO().Framerate);
	ImGuiIO& io=ImGui::GetIO();
	ImGui::Text("MousePos: (%g, %g)",io.MousePos.x,io.MousePos.y);
	ImGui::SliderFloat("GammaCorrection",&m_data->GammaCorrection,0.0f,10.0f);
	if(UseToolTip) if(ImGui::IsItemHovered())ImGui::SetTooltip("Global gamma correction.");
	ImGui::Separator();

	ImGui::ColorEdit3("ambient_light_color",(float*)&m_data->ambient_light_color);
	ImGui::ColorEdit3("bg_color",(float*)&m_data->bg_color);
	ImGui::ColorEdit3("bad_color",(float*)&m_data->bad_color);
	if(ImGui::Button("SaveMaterial")) {
		//TODO;;
		MECFacade::GetSington()->GetWndManager()->OpenWnd(e_wndName::WND_MATERIAL_SAVE);
	}
}
void CImGui_MainPanelWnd::RenderCase() {
	m_pcp->RenderGui();
}
void CImGui_MainPanelWnd::Render() {
	ImGui::SetNextWindowSize(ImVec2(500,440),ImGuiSetCond_FirstUseEver);
	if(ImGui::Begin("Panel",&m_bIsWndOpen,ImGuiWindowFlags_MenuBar)) {
		RenderCommon();
		RenderCase();
		ImGui::End();
	}
}
void CImGui_MainPanelWnd::Destroy() {
	m_data=nullptr;
	m_pcp=nullptr;
}
#pragma endregion
#pragma region wndManager
CWndManager::CWndManager() {}
CWndManager::~CWndManager() {
	closeWnd_();
	for(auto iter:m_wndMap) {
		if(iter.second!=nullptr) {
			iter.second->Destroy();
			delete iter.second;
		}
	}
	m_wndMap.clear();
}

void CWndManager::Init() {}

bool CWndManager::CloseWnd(e_wndName name) {
	if(IsWndExist(name)) {
		CImGui_Wnd* wnd=GetWndDirectlyFromMap(name);
		m_wndVec_waitingForClose.push_back(wnd);
		m_bCloseWndFlag=true;
		return true;
	}
	return false;
}

CImGui_Wnd* CWndManager::OpenWnd(e_wndName name) {
	if(IsWndExist(name))return GetWndDirectlyFromMap(name);
	CImGui_Wnd* wnd=nullptr;
	switch(name) {
		case WND_LIGHTING:
			wnd=new CImGui_LightWnd();
			break;
		case WND_MAIN_PANEL:
			wnd=new CImGui_MainPanelWnd();
			break;
		case WND_MATERIAL_SAVE:
			wnd=new CImGui_MaterialSaveDialog();
			break;
		case WND_HELPER:
			wnd=new CImGui_HelpDialog();
			break;
		default:
			return nullptr;
			break;
	}
	wnd->Init();
	wnd->m_name=name;
	m_wndMap[name]=wnd;
	return wnd;
}

void CWndManager::Render() {
	if(m_bCloseWndFlag) closeWnd_();
	for(auto iter:m_wndMap) {
		CImGui_Wnd* wnd=iter.second;
		if(!wnd->m_bIsWndOpen) {
			CloseWnd(wnd->m_name);
		}
		wnd->PreRender();
		wnd->Render();
	}
}

void CWndManager::closeWnd_() {
	m_bCloseWndFlag=false;
	for(auto iter:m_wndVec_waitingForClose) {
		m_wndMap.erase(iter->m_name);
		iter->Destroy();
		delete iter;
	}
	m_wndVec_waitingForClose.clear();
}

CImGui_Wnd* CWndManager::GetWndDirectlyFromMap(e_wndName name) {
	return m_wndMap[name];
}

bool CWndManager::IsWndExist(e_wndName name) {
	return m_wndMap[name]!=nullptr;
}

#pragma endregion


#pragma region dialogWnd
void CImGui_DialogWnd::SetTitle(std::string title) {
	m_sTitle=title;
}
void CImGui_DialogWnd::Render() {
	ImGui::OpenPopup(m_sTitle.c_str());
	if(ImGui::BeginPopupModal(m_sTitle.c_str(),&m_bIsWndOpen,ImGuiWindowFlags_AlwaysAutoResize)) {
		RenderSpecific();
		ImGui::EndPopup();
	}
}
#pragma endregion

#pragma region materialSaveDialog
void CImGui_MaterialSaveDialog::Init() {
	SetTitle("MaterialSave");
	m_data=MECFacade::GetSington()->GetData();
	::memset(m_materialNameBuf,0,sizeof(m_materialNameBuf)/sizeof(char));
}

void CImGui_MaterialSaveDialog::Destroy() {
	m_data=nullptr;
	CImGui_DialogWnd::Destroy();
}

void CImGui_MaterialSaveDialog::PreRender() {
}
void CImGui_MaterialSaveDialog::RenderSpecific() {
	/*
	ImGui::Text("Choose an existing material\n");
	std::map < int,const char* >::iterator iter;
	std::map < int,const char* > materials=MECFacade::GetSington()->GetMaterialNameMap();
	for(iter=materials.begin(); iter!=materials.end(); iter++) {
		const char* name=iter->second;
		if(ImGui::RadioButton(name,m_currentSelected==iter->first)) {
			m_currentSelected=iter->first;

			std::string temp=std::string(name);
			int first=temp.find_first_of('_');
			int last=temp.find_last_of('.');

			memcpy(m_materialNameBuf,std::string(temp.substr(first+1,last-first-1)).c_str(),sizeof(m_materialNameBuf));
		}
	}
	ImGui::Separator();
	ImGui::Text("Or enter material name.(Prior)\n");
	ImGui::InputText("",m_materialNameBuf,64,ImGuiInputTextFlags_CharsNoBlank);
	ImGui::Separator();
	if(ImGui::Button("Save",ImVec2(100,0))) {
		if(m_materialNameBuf[0]!='\0') {
			m_bSaveToFile=true;
			m_bIsWndOpen=false;
		}
	}
	ImGui::SameLine();
	if(ImGui::Button("Cancel",ImVec2(100,0))) {
		m_bIsWndOpen=false;
	}
*/
}

#pragma endregion

void CImGui_HelpDialog::RenderSpecific() {
	ImGui::Text("%-8s%s","Ctrl+p","-> toggle material property panel.");
	ImGui::Text("%-8s%s","Ctrl+l","-> toggle light edit panel.");
	ImGui::Text("%-8s%s","Ctrl+r","-> lock screen.");
	ImGui::Text("%-8s%s","p","-> locat debug pos( a red pixel ).");
	ImGui::Text("%-8s%s","r","-> reset camera.");
}
