#pragma once

#include <map>
#include "LightManager.h"
#include "data\data-debug.h"
#include "cases\meCase.h"


class CImGui_Wnd {

public:
	CImGui_Wnd() {};
	virtual ~CImGui_Wnd() {};
	virtual void Init() {};
	virtual void Destroy() {};
	virtual void PreRender() {};
	virtual void Render()=0;
protected:
	bool m_bIsWndOpen=true;
private:
	e_wndName m_name;
	friend class CWndManager;

};

class CImGui_DialogWnd:public CImGui_Wnd {
public:
	CImGui_DialogWnd() {}
	virtual ~CImGui_DialogWnd() {};
	void Render();
protected:
	void SetTitle(std::string);
	virtual void RenderSpecific()=0;
private:
	std::string m_sTitle="";
};

class CImGui_HelpDialog:public CImGui_DialogWnd {
public:
	CImGui_HelpDialog() {};
	virtual ~CImGui_HelpDialog() {};
	void RenderSpecific();
};
class CImGui_MaterialSaveDialog:public CImGui_DialogWnd {
public:
	CImGui_MaterialSaveDialog() {};
	virtual ~CImGui_MaterialSaveDialog() {};

	void Init();
	void Destroy();
	void PreRender();
protected:
	void RenderSpecific();
private:
	int m_currentSelected=0;
	char m_materialNameBuf[64];
	SDataDbg* m_data=nullptr;
};

class CImGui_LightWnd:public CImGui_Wnd {
public:
	CImGui_LightWnd() {}
	virtual ~CImGui_LightWnd() {};
	void Destroy();
	void Init();
	void Render();
private:
	CVirtualLight* m_pSelectedLight=nullptr;
	int m_SelectedLightType;
	int m_iSelectedLightIdex;
	CVirtualLight* m_lightsChainRoot=nullptr;
	int m_LightNumber=0;
};

class CImGui_MainPanelWnd:public CImGui_Wnd {
public:
	CImGui_MainPanelWnd() {};
	virtual ~CImGui_MainPanelWnd() {};
	void Destroy();
	void Init();
	void Render();

private:
	void RenderCommon();
	void RenderCase();
private:
	SDataDbg* m_data=nullptr;
	const MECCase* m_pcp=nullptr;
};

class CWndManager {
public:
	CWndManager();
	~CWndManager();
	void Init();
	bool CloseWnd(e_wndName name);
	CImGui_Wnd* OpenWnd(e_wndName name);
	bool IsWndExist(e_wndName name);
	void Render();
private:
	CImGui_Wnd* GetWndDirectlyFromMap(e_wndName name);
	void closeWnd_();
private:
	std::map<e_wndName,CImGui_Wnd*> m_wndMap;
	std::vector<CImGui_Wnd*> m_wndVec_waitingForClose;
	bool m_bCloseWndFlag=false;
};