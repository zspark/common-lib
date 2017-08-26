#include "CommonGui.h"
#include <map>

#include "CompileMacros.h"
#include "PinholeCamera.h"
#include "optixu\optixpp.h"
#include "OptixCommonLib.h"
#include "DeviceInfo.h"
#include "imgui.h"
#include "utils.h"
#include "meFacade.h"

#define IM_ARRAYSIZE(_ARR)  ((int)(sizeof(_ARR)/sizeof(*_ARR)))

char static s_c_materialNameBuf[64]="";
int static s_currentSelected=-1;
int static s_i_geoIDOld=-1;
int static s_i_caseIDOld=-1;
int static s_i_envMapIDOld=-1;
int static s_i_matNameIDOld=-1;
int static s_b_saveToConfig=false;
int static s_b_printDeviceInfo=false;
bool static s_b_deviceInfoWnd=false;
int static s_b_creatMatType=false;

namespace ImGui2 {
	void ShowHelpMarker(const char* desc) {
		ImGui::TextDisabled("(?)");
		if(ImGui::IsItemHovered()) {
			ImGui::BeginTooltip();
			ImGui::PushTextWrapPos(450.0f);
			ImGui::TextUnformatted(desc);
			ImGui::PopTextWrapPos();
			ImGui::EndTooltip();
		}
	}
	void  RenderImGuiWindowSize(int w,int h) {
		const int border=2;
		const int titleBarH=20;
		const int sizeW=350;
		ImGui::SetWindowSize(ImVec2(sizeW,h-titleBarH-2*border));
		ImGui::SetWindowPos(ImVec2(w-sizeW-border,titleBarH+border));
	}

	void  RenderMainMenu(MECScene* scene,SDataDbg* data) {

		static std::map < int,const char* > s_envMapNames=MECFacade::GetSington()->GetEnvListMap();
		std::map < int,const char* >::iterator EnvIter;

		if(ImGui::BeginMainMenuBar()) {

			//common
			if(ImGui::BeginMenu("Common")) {
				ImGui::MenuItem("LockInteraction","ctrl+r",&data->bLockInteraction);
				ImGui::Separator();
				if(ImGui::Button("ResetCamera")) {
					data->bResetCamera=true;
				}
				if(ImGui::Button("TogglePanelWnd")){
					data->bTogglePanelWnd=true;
				}
				if(ImGui::Button("ToggleLightWnd")) {
					data->bToggleLightWnd=true;
				}
				std::string ButtonName=data->bShowAxes?"HideAxes":"ShowAxes";
				if(ImGui::Button(ButtonName.c_str())) { data->bShowAxes=!data->bShowAxes; }
				if(ImGui::Button("SaveEnvironment")) { s_b_saveToConfig=true; }
				if(ImGui::Button("PrintDeviceInfo")) { s_b_printDeviceInfo=true; }
				if(ImGui::Button("CreatMatType")) { s_b_creatMatType=true; }
				if(ImGui::Button("LoadModel")) { 
					MECFacade::GetSington()->LoadModel("");
				}
				ImGui::EndMenu();
			}

			//map
			if(ImGui::BeginMenu("EnvMap")) {
				std::map < int,const char* > envName=MECFacade::GetSington()->GetEnvListMap();
				for(EnvIter=envName.begin(); EnvIter!=envName.end(); EnvIter++) {
					const char* name=EnvIter->second;
					ImGui::RadioButton(name,&data->currentEnvMap,EnvIter->first);
				}
				ImGui::EndMenu();
			}

			//cases;
			/*
			if(ImGui::BeginMenu("Case")) {
				std::vector <MECCase> caseProxyVec=MECFacade::GetSington()->GetCase();

				auto iter=caseProxyVec.begin();
				for(;iter!=caseProxyVec.end();iter++) {
					ImGui::RadioButton(iter->name.c_str(),&data->currentCaseID,iter->index);
				}
				ImGui::EndMenu();
			}
*/

			//geometry
			if(ImGui::BeginMenu("Geometry")) {
				ImGui::RadioButton("sphere",&data->currentGeometryID,0);
				ImGui::RadioButton("plane",&data->currentGeometryID,1);
				ImGui::RadioButton("box",&data->currentGeometryID,2);
				ImGui::RadioButton("cylinder",&data->currentGeometryID,3);
				ImGui::RadioButton("mesh",&data->currentGeometryID,4);
				ImGui::RadioButton("simple-scene",&data->currentGeometryID,5);
				ImGui::RadioButton("simple-scene2",&data->currentGeometryID,6);
				ImGui::EndMenu();
			}

			//materials
			if(ImGui::BeginMenu("Material")) {
				/*
				std::map < int,const char* >::iterator iter;
				std::map < int,const char* > materials=MECFacade::GetSington()->GetMaterialNameMap();
				for(iter=materials.begin(); iter!=materials.end(); iter++) {
					const char* name=iter->second;
					ImGui::RadioButton(name,&data->currentMateral,iter->first);
				}
*/
				ImGui::EndMenu();
			}

			//global render settings;
			if(ImGui::BeginMenu("Global")) {
				ShowHelpMarker("These are Global render settings.");
				ImGui::MenuItem("UseEnvTS",NULL,&data->useEnvTS);
				ImGui::MenuItem("UseAO",NULL,&data->useAO);
				ImGui::Separator();

				ImGui::SliderFloat("distanceDecay",&data->distanceDecay,0.1f,1.0f);
				ImGui::SliderInt("rayTraceDepth",&data->max_depth,0,10);
				ImGui::DragFloat("importanceThreshold",&data->importanceThreshold,0.00001f,0.0f,0.0f,"%.06f");
				if(data->useAO) {
					ImGui::SliderFloat("occlusion_distance",&data->occlusion_distance,0.0f,100.f);
					ImGui::SliderFloat("occlusion_density",&data->occlusion_density,0.0f,1.f);
				}
				ImGui::DragFloat("scene_epsilon",&data->scene_epsilon,0.00001f,0.0f,0.0f,"%.06f");
				ImGui::SliderFloat("scene_max",&data->scene_max,0.0f,10000000.f);
				ImGui::EndMenu();
			}

			//help
			if(ImGui::BeginMenu("?")) {
				CWndManager* pWndMgr=MECFacade::GetSington()->GetWndManager();
				if(pWndMgr->IsWndExist(e_wndName::WND_HELPER)) {
					pWndMgr->CloseWnd(e_wndName::WND_HELPER);
				} else {
					pWndMgr->OpenWnd(e_wndName::WND_HELPER);
				}
				ImGui::EndMenu();
			}
			
			ImGui::EndMainMenuBar();
		}
		if(data->bToggleLightWnd) {
			data->bToggleLightWnd=false;
			CWndManager* pWndMgr=MECFacade::GetSington()->GetWndManager();
			if(pWndMgr->IsWndExist(e_wndName::WND_LIGHTING)) {
				pWndMgr->CloseWnd(e_wndName::WND_LIGHTING);
			} else {
				pWndMgr->OpenWnd(e_wndName::WND_LIGHTING);
			}
		}
		if(data->bTogglePanelWnd) {
			data->bTogglePanelWnd=false;
			CWndManager* pWndMgr=MECFacade::GetSington()->GetWndManager();
			if(pWndMgr->IsWndExist(e_wndName::WND_MAIN_PANEL)) {
				pWndMgr->CloseWnd(e_wndName::WND_MAIN_PANEL);
			} else {
				pWndMgr->OpenWnd(e_wndName::WND_MAIN_PANEL);
			}
		}
		if(data->bResetCamera) {
			data->bResetCamera=false;
			optix::float3 camEye={.0f,0.0f,5.0f};
			optix::float3 camLookAt={.0f,.0f,.0f};
			optix::float3 camUp={.0f,1.0f,.0f};
			float const fov=60;
			const PinholeCamera* camera=scene->GetCamera();
			int size[2];
			MECFacade::GetSington()->GetCase()->GetScene()->GetDefaultSize(size);
			float pi=M_PIf/180;
			float hfov=2.f*atan(tan(.5f*fov*pi)*size[0]/size[1])/pi;
			const_cast<PinholeCamera*> (camera)->setParameters(camEye,camLookAt,camUp,hfov,fov,PinholeCamera::KeepVertical);
		}

		/*
		if(s_i_matNameIDOld!=data->currentMateral) {
			s_i_matNameIDOld=data->currentMateral;
			std::map < int,const char* >::iterator iter;
			std::map < int,const char* > materials=MECFacade::GetSington()->GetMaterialNameMap();
			iter=materials.find(data->currentMateral);
			if(iter!=materials.end()) {
				const char* matName=iter->second;
				std::string texName(matName);
				MECFacade::GetSington()->MaterialReadConfigFile(texName);
			}
		}
		if(s_i_envMapIDOld!=data->currentEnvMap) {
			s_i_envMapIDOld=data->currentEnvMap;
			const char* name=s_envMapNames.find(data->currentEnvMap)->second;
			std::string  texName(name);
			MECFacade::GetSington()->ChangeEnvMap(texName);
		}
*/

		if(s_i_caseIDOld!=data->currentCaseID) {
			s_i_caseIDOld=data->currentCaseID;
			MECFacade::GetSington()->ChangeCase(data->currentCaseID);
		}
		/*
		if(s_i_geoIDOld!=data->currentGeometryID) {
			s_i_geoIDOld=data->currentGeometryID;
			MECFacade::GetSington()->ChangeGeometry(static_cast<CScene::GeoID>(data->currentGeometryID));
		}
		if(s_b_saveToConfig) {
			s_b_saveToConfig=false;
			MECFacade::GetSington()->SaveToConfigFile();
		}
		if(s_b_creatMatType) {
			s_b_creatMatType=false;
			MECFacade::GetSington()->CreateMatType();
		}

		static char DeviceInfo[512];
		static char DeviceMemoryInfo[100];
		if(s_b_printDeviceInfo) {
			s_b_printDeviceInfo=false;
			::GetDeviceInfo(MECFacade::GetSington()->GetScene()->GetContext(),DeviceInfo);
			s_b_deviceInfoWnd^=1;
		}
		if(s_b_deviceInfoWnd) {

			ImGui::SetNextWindowSize(ImVec2(400,500),ImGuiSetCond_FirstUseEver);
			ImGui::SetNextWindowPos(ImVec2(50,500),ImGuiSetCond_FirstUseEver);
			::GetDeviceCurrentMemoryInfo(MECFacade::GetSington()->GetScene()->GetContext(),DeviceMemoryInfo);
			ImGui::Begin("Device Info",&s_b_deviceInfoWnd);
			ImGui::Text(DeviceMemoryInfo);
			ImGui::InputTextMultiline("##source",DeviceInfo,IM_ARRAYSIZE(DeviceInfo),ImVec2(-1.0f,-1.0f),ImGuiInputTextFlags_AllowTabInput|(true?ImGuiInputTextFlags_ReadOnly:0));
			ImGui::End();
		}
*/
	}

	void  SetCommonDataToOptix(MECScene* scene,SDataDbg* data) {

		static unsigned int frame_number=0;
		optix::Context context;//=scene->GetContext();
		context["frame_number"]->setUint(++frame_number);
		if(data->bLockInteraction) return;

		//Render mode ,we shall not let camera change;
		const PinholeCamera* camera=scene->GetCamera();
		optix::float3 cameraPos,cameraU,cameraV,cameraW;
		camera->getEyeUVW(cameraPos,cameraU,cameraV,cameraW);
		static optix::float3 oldcameraPos,oldcameraU,oldcameraV,oldcameraW;
		if(oldcameraPos.x!=cameraPos.x||oldcameraPos.y!=cameraPos.y||oldcameraPos.z!=cameraPos.z
			 ||oldcameraU.x!=cameraU.x||oldcameraU.y!=cameraU.y||oldcameraU.z!=cameraU.z
			 ||oldcameraV.x!=cameraV.x||oldcameraV.y!=cameraV.y||oldcameraV.z!=cameraV.z
			 ||oldcameraW.x!=cameraW.x||oldcameraW.y!=cameraW.y||oldcameraW.z!=cameraW.z
			 ) {
			frame_number=0;
			oldcameraPos=cameraPos;
			oldcameraU=cameraU;
			oldcameraV=cameraV;
			oldcameraW=cameraW;
		}

		oml::common::UpdateCamera(context,cameraPos,cameraU,cameraV,cameraW);
		context["gammaCorrection"]->setFloat(data->GammaCorrection);
		context["bg_color"]->setFloat(data->bg_color.x,data->bg_color.y,data->bg_color.z,data->bg_color.w);
		context["ambient_light_color"]->setFloat(data->ambient_light_color.x,data->ambient_light_color.y,data->ambient_light_color.z,data->ambient_light_color.w);
		context["bad_color"]->setFloat(data->bad_color.x,data->bad_color.y,data->bad_color.z,data->bad_color.w);

		context["DistanceDecay"]->setFloat(data->distanceDecay);
		context["occlusion_distance"]->setFloat(data->occlusion_distance);
		context["occlusion_density"]->setFloat(data->occlusion_density);
		context["max_depth"]->setInt(data->max_depth);
		context["useEnvTS"]->setInt(data->useEnvTS);
		context["useAO"]->setInt(data->useAO);
		context["useLights"]->setInt(data->useLights);
		context["useHeadLight"]->setInt(data->useHeadLight);
		context["headLightColour"]->setFloat(data->headLightColour.x,data->headLightColour.y,data->headLightColour.z,data->headLightColour.w);

		context["scene_epsilon"]->setFloat(data->scene_epsilon);
		context["scene_max"]->setFloat(data->scene_max);
		context["importanceThreshold"]->setFloat(data->importanceThreshold);

#ifdef MATERIAL_DEBUG
		if(data->bResetDebugPos) {
			data->bResetDebugPos=false;
			static int size[2];
			scene->GetDefaultSize(size);
			ImGuiIO& io=ImGui::GetIO();
			context["mousePos"]->setInt(io.MousePos.x,size[1]-io.MousePos.y);
		}
#endif
	}
}
