#pragma once
#include <iostream>
#include <fstream>
#include "json.h"
#include "clTypeUtil.h"
#include "clguiMenuBar.h"
#include "clguiWindow.h"
#include "clguiButton.h"
#include "clguiLabel.h"
#include "clguiButton.h"
#include "clguiSlider.h"
#include "clguiCheckBox.h"

using namespace clgui;
static float lastValue=1.0f;
class TestclguiMenuBar {
public:
  TestclguiMenuBar() {
	 EventCallBackFn b = std::bind(&TestclguiMenuBar::cb, this, std::placeholders::_1);

	 mb = new clguiMenuBar();
	 /*
	 Json::Value json;
	 Json::Reader r;
	 std::ifstream file("clgui.json");
	 if(r.parse(file,json)) {
		 mb->BuildLayoutComponentsByJson(json);
	 } else {
		 std::cout<<"There was an error here!"<<std::endl;
	 }
*/
	 clguiMenu* m = new clguiMenu();
	 mb->AddChild(m);
	 m->SetCaption("File");
	 m->AddChild("Open..")->AddEventListener(clguiEventType::clgui_EVT_MENUITEM_STATUS_CHANGE,b);
	 m->AddChild("Open.2.");
	 m->AddChild("Open.3.");

	 m = new clguiMenu();
	 mb->AddChild(m);
	 m->SetCaption("View");
	 m->AddChild("View.3.");

	 m = new clguiMenu();
	 mb->AddChild(m);
	 m->SetCaption("Help");
	 m->AddChild("Help.3.");

	 m=mb->AddChild("aaa");
	 m->AddChild("Hello");
	 m->AddChild("World");

	 mb->AddChild("bbbbb")->AddChild("Helloaaa");

	 clguiButton* btn = new clguiButton();
	 btn->SetCaption("I'am a Button!");
	 //btn->AddEventListener(b);
	 m->AddChild(btn);

  }
  ~TestclguiMenuBar() {}

  void cb(clguiEvent* evt) {
		if(evt->newValue.boolValue) {
			OpenWindow();
		} else {
			delete m_wnd;
		}
  }

	void OpenWindow(){
	 EventCallBackFn b = std::bind(&TestclguiMenuBar::OnWindowCloseHandler, this, std::placeholders::_1);

	 ////////////////////////////////////////////////////////////////////////////////////////////////////
	 // window
	 m_wnd = new clguiWindow();
	 m_wnd->AddEventListener(clguiEventType::clgui_EVT_WINDOW_CLOSE,b);

	 /*
	 Json::Value json;
	 Json::Reader r;
	 std::ifstream file("clgui.json");
	 if(r.parse(file,json)) {
		 m_wnd->BuildLayoutComponentsByJson(json);
	 } else {
		 std::cout<<"There was an error here!"<<std::endl;
	 }
	 return;
*/
	 m_wnd->SetCaption("sfsfsfsf");
	 ////////////////////////////////////////////////////////////////////////////////////////////////////
	 //Label
	 m_wnd->AddChild(new clguiLabel());

	 m_lb = new clguiLabel();
	 m_lb->SetCaption("Im a Lable!");
	 m_lb->SetColor(clTypeUtil::Make<clFloat3,float>(1.f,0.f,0.f));
	 m_lb->SetValue(10);
	 m_wnd->AddChild(m_lb);

	 //Remove(m_lb);
	 //delete m_lb;

	 ////////////////////////////////////////////////////////////////////////////////////////////////////
	 //Button
	 clguiButton* btn = new clguiButton();
	 EventCallBackFn buttonClicked = std::bind(&TestclguiMenuBar::OnButtonClicked, this, std::placeholders::_1);
	 btn->SetCaption("aaaaaaaaaa");
	 btn->AddEventListener(clgui_EVT_BUTTON_CLICK,buttonClicked);
	 m_wnd->AddChild(btn);
	 m_wnd->AddChild(new clguiButton());

	 ////////////////////////////////////////////////////////////////////////////////////////////////////
	 //Slider
	 clguiSlider* sl = new clguiSlider();
	 sl->SetCaption("sliderrrrr");
	 //sl->ResetTo({ .3f,.2f,.1f },{ 0.0f },{ 2.0f });
	 sl->ResetTo(.8f, -1.f, 20.f);
	 EventCallBackFn sliderVChange = std::bind(&TestclguiMenuBar::OnSliderValueChange, this, std::placeholders::_1);
	 sl->AddEventListener(clguiEventType::clgui_EVT_SLIDER_VALUE_CHANGE,sliderVChange);
	 m_wnd->AddChild(sl);
	 sl->UpdateTo(lastValue);
	 //sl->SetRange(0.0f, 4.f);

	 ////////////////////////////////////////////////////////////////////////////////////////////////////
	 //checkbox
	 m_ckbox=new clguiCheckBox();
	 m_ckbox->SetCaption("selected");
	 EventCallBackFn selectionChange = std::bind(&TestclguiMenuBar::OnCheckBoxSelectionChange, this, std::placeholders::_1);
	 m_ckbox->AddEventListener(clguiEventType::clgui_EVT_CHECKBOX_SELECTION_CHANGE,selectionChange);
	 m_wnd->AddChild(m_ckbox);
  }

	void OnButtonClicked(clguiEvent* evt) {
		std::cout<<"button new value: "<<evt->newValue.boolValue<<std::endl;
	}
	void OnCheckBoxSelectionChange(clguiEvent* evt) {
		std::cout<<"checkbox new value: "<<evt->newValue.boolValue<<std::endl;
	}
	void OnSliderValueChange(clguiEvent* evt) {
		std::cout<<"slider new value: "<<evt->newValue.floatValue<<std::endl;
		std::cout<<"slider old value: "<<evt->oldValue.floatValue<<std::endl;
		lastValue=evt->newValue.floatValue;
	}

	void OnWindowCloseHandler(clguiEvent* evt) {
		static_cast<clguiMenuItem*>(mb->GetMenu(0)->GetMenuItem(0))->SetSelection(false);
		delete m_wnd;
	}

private:
	clguiMenuBar* mb;
  clguiLabel* m_lb = nullptr;
  clguiWindow* m_wnd = nullptr;
  clguiButton* m_btn = nullptr;
	clguiCheckBox* m_ckbox=nullptr;

};