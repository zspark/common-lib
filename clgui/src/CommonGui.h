#pragma once
#include "cases\meCase.h"
#include "data\data-debug.h"
#include "meScene.h"

namespace ImGui2 {
	void ShowHelpMarker(const char* desc);
	void RenderImGuiWindowSize(int w,int h);
	void RenderMainMenu(MECScene* scene,SDataDbg* data);
	void SetCommonDataToOptix(MECScene* scene,SDataDbg* data);
};