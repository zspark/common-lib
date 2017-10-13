#include <iostream>
#define CLGUI_API_IMPORTS
#include "clgui/clgui.h"
#include "clgui/clgui_gui_sets.h"
#include "test_clgui.h"

using namespace std;
using namespace clgui;

static void errorCallback(int error,const char* description){
  //fprintf(stderr, "Error %d: %s\n", error, description);
}

clguiWindow* aboutWnd=nullptr;
static void OnComboboxStatusChangeHandler(clguiEvent* evt){
  clguiEventComboBoxStatusChange* cbevt=static_cast<clguiEventComboBoxStatusChange*>(evt);
  cout<<cbevt->GetSender()->GetSelectedIndex()<<endl;
  cout<<cbevt->GetSender()->GetSelectedLabel()<<endl;
}


static void OnCollapserStatusChange(clguiEvent* evt){
  clguiEventCollapserStatusChange* cbevt=static_cast<clguiEventCollapserStatusChange*>(evt);
  cout<<cbevt->GetSender()->GetName()<<endl;

}

static void cf(clguiEvent* evt){
  clguiButton* btn=new clguiButton();
  clguiAddToStage(btn);
  //gui->RemoveFromStage(evt->GetSenderAs<clguiComponent*>(CLGUI_OBJECT_TYPE_COMPONENT));
}

static void wndCloseHandler(clguiEvent* evt){
  cout<<"window close event!"<<endl;

  clguiEventWindowClose* closeEvt=static_cast<clguiEventWindowClose*>(evt);
  //clguiRemoveFromStage(static_cast<clguiComponent*>(closeEvt->GetSender()));
  clguiDeleteObject(closeEvt->GetSender(),true);
  //closeEvt->GetSender()->Visible(false);
  aboutWnd=nullptr;
}

static void CheckboxSelectionHander(clguiEvent* evt){
  cout<<"checkbox value changed!"<<endl;
  clguiEventCheckboxStatusChange* changeEvt=static_cast<clguiEventCheckboxStatusChange*>(evt);
  clguiCheckBox* cb=changeEvt->GetSender();
  cout<<cb->GetName()<<endl;
}

static void MenuItemStatusChangeHander(clguiEvent* evt){
  clguiEventMenuItemStatusChange* changeEvt=static_cast<clguiEventMenuItemStatusChange*>(evt);
  clguiMenuItem* mi=changeEvt->GetSender();
  cout<<mi->GetName()<<" "<<mi->GetSelection()<<" "<<mi->GetShortKey()<<" "<<mi->GetType()<<endl;

}

static void OnSliderValueChangeHandler(clguiEvent* evt){
  clguiEventSliderValueChangeFloat* changeEvt=static_cast<clguiEventSliderValueChangeFloat*>(evt);
  clguiSliderFloat* sl=changeEvt->GetSender();
  cout<<sl->GetValue(0)<<" "<<sl->GetValue(1)<<" "<<sl->GetValue(2)<<endl;
}

static void OnTwoEventsBtnClicked_evt_one(clguiEvent* evt){
  cout<<"event one triggered!"<<endl;
}

static void OnTwoEventsBtnClicked_evt_two(clguiEvent* evt){
  cout<<"event two triggered!"<<endl;
}

clguiSliderFloat* sl=nullptr;
static void OnChangeSliderDimensionHandler(clguiEvent* evt){
  clguiEventButtonClick* changeEvt=static_cast<clguiEventButtonClick*>(evt);
  clguiButton* btn=changeEvt->GetSender();
  cout<<"Change button clicked!"<<endl;
  cluint d=sl->GetDimension();
  if(d==1)sl->SetDimension(2);
  if(d==2)sl->SetDimension(3);
  if(d==3)sl->SetDimension(1);

}

clguiMenuBar* mb=nullptr;
static void OnResetSizeHandler(clguiEvent* evt){
  clguiEventButtonClick* changeEvt=static_cast<clguiEventButtonClick*>(evt);
  clguiButton* btn=changeEvt->GetSender();
  //clguiWindow* ctn=TryConvertTo<clguiWindow*>(btn->GetParent());
  //clguiContainer* ctn=btn->GetParent();
  //ctn->ScaleSizeBy(1.1f);
  //ctn->SetSize(100,100);
  //ctn->SetPosition(200,200);
  //ctn->StatusMove(false);
  //ctn->StatusResize(false);
  //ctn->StatusScrollbar(false);
  //ctn->AttachToBorder(clguiAttachSide::RIGHT,300.f);
  clguiMenu* m=clguiConverToMenu(mb->GetChildByName("File"));
  if(m){
    clguiComponent* com=m->GetChildByName("Hello4");
    clguiMenuItem* mi=clguiConverToMenuItem(com);
    int a=10;
    if(mi){
      mi->SetSelection(false);
    }
  }
}


static clguiMenuBar* mainMenubar=nullptr;
static clguiWindow* mainPanel=nullptr;
static clguiWindow* about=nullptr;


static void OnRenderAtMaxSpeed(clguiEvent* evt){
  clguiEventMenuItemStatusChange* changeEvt=static_cast<clguiEventMenuItemStatusChange*>(evt);
  clguiMenuItem* mi=changeEvt->GetSender();
  glfwSwapInterval(mi->GetSelection()?0:1);
}

static void OnMainPanelStatusChangeHandler(clguiEvent* evt){
  clguiEventMenuItemStatusChange* changeEvt=static_cast<clguiEventMenuItemStatusChange*>(evt);
  clguiMenuItem* mi=changeEvt->GetSender();
  //mainPanel->Visible(mi->GetSelection());
  clgui::clguiDeleteChildren(mainPanel);
}

static void OnAboutItemStatusChanged(clguiEvent* evt){
  clguiEventMenuItemStatusChange* changeEvt=static_cast<clguiEventMenuItemStatusChange*>(evt);
  clguiMenuItem* mi=changeEvt->GetSender();
  if(mi->GetSelection()){
    aboutWnd=new clguiWindow();
    aboutWnd->SetName("About clgui");
    aboutWnd->SetSize(400,100);
    aboutWnd->SetPosition(clguiPositionMode::POSITION_CENTER);
    //aboutWnd->SetPosition(clguiPositionMode::POSITION_BOTTOM_LEFT);
    aboutWnd->AddEventListener(clguiEventType::EVT_WINDOW_CLOSE,wndCloseHandler);
    clguiAddToStage(aboutWnd);
    clguiText* text=new clguiText(102400);
    text->SetText("clgui is a C++ wrapper lib of ImGui C lib, It's created for my computer graphics gui part.");
    text->SetTextMode(clguiTextMode::AUTO_WRAP);
    aboutWnd->AddChild(text);
  } else{
    if(aboutWnd){
      clguiDeleteObject(aboutWnd,true);
      aboutWnd=nullptr;
    }
  }

}


static void CreateMainGUI(){
  mainMenubar=new clguiMenuBar();
  mb=mainMenubar;
  clguiAddToStage(mb);

  ///////////////////file
  clguiMenu* m=new clguiMenu();
  m->SetName("File");
  mb->AddChild(m);

  clguiMenuItem* mi=new clguiMenuItem();
  mi->SetName("Open");
  mi->SetShortKey("ctrl+o");
  m->AddChild(mi);

  mi=new clguiMenuItem();
  mi->SetName("Save");
  mi->SetShortKey("ctrl+s");
  m->AddChild(mi);

  mi=new clguiMenuItem();
  mi->SetName("Exit");
  m->AddChild(mi);


  ///////////////////Edit
  m=new clguiMenu();
  m->SetName("Edit");
  mb->AddChild(m);

  mi=new clguiMenuItem();
  mi->SetName("Options..");
  m->AddChild(mi);

  ///////////////////View
  m=new clguiMenu();
  m->SetName("View");
  mb->AddChild(m);

  mi=new clguiMenuItem();
  mi->SetName("MainPanel..");
  mi->SetShortKey("ctrl+p");
  mi->SetSelection(true);
  mi->AddEventListener(clguiEventType::EVT_MENUITEM_STATUS_CHANGE,OnMainPanelStatusChangeHandler);
  m->AddChild(mi);

  mi=new clguiMenuItem();
  mi->SetName("LightPanel..");
  mi->SetShortKey("ctrl+l");
  m->AddChild(mi);

  mi=new clguiMenuItem();
  mi->SetName("ModelPanel..");
  mi->SetShortKey("ctrl+m");
  m->AddChild(mi);

  mi=new clguiMenuItem();
  mi->SetName("RenderAtMaxSpeed");
  mi->SetShortKey("ctrl+n");
  mi->AddEventListener(clguiEventType::EVT_MENUITEM_STATUS_CHANGE,OnRenderAtMaxSpeed);
  m->AddChild(mi);


  ///////////////////Help
  m=new clguiMenu();
  m->SetName("Help");
  mb->AddChild(m);

  mi=new clguiMenuItem();
  mi->SetName("About clgui");
  mi->AddEventListener(clguiEventType::EVT_MENUITEM_STATUS_CHANGE,OnAboutItemStatusChanged);
  m->AddChild(mi);

  mi=new clguiMenuItem();
  mi->SetName("Version");
  m->AddChild(mi);



  clguiWindow* wnd=new clguiWindow();
  mainPanel=wnd;
  wnd->SetPosition(100,100);
  wnd->SetSize(400,300);
  //wnd->AttachToBorder(clguiAttachSide::RIGHT,350);
  clguiAddToStage(wnd);
  clguiButton* btn=new clguiButton();
  btn->AddEventListener(clguiEventType::EVT_BUTTON_CLICK,OnResetSizeHandler);
  wnd->AddChild(btn);


  clguiCheckBox* cb=new clguiCheckBox();
  cb->AddEventListener(clguiEventType::EVT_CHECKBOX_STATUS_CHANGE
    ,CheckboxSelectionHander);
  wnd->AddChild(cb);

  clguiText* t=new clguiText(2560);
  //t->SetName("ss");
  t->SetTextMode(clguiTextMode::AUTO_WRAP);
  t->SetText("1.  [obn] connected with drawings and design,especially in the production of books,magazines,etc.  2.   clear and full of details,especially about sth unpleasant " );
  //t->SetText("number:%d%s",11,"sss");
  wnd->AddChild(t);
  cout<<t->GetText()<<endl;

  btn=new clguiButton();
  btn->SetSize(400,20);
  clint w,h;
  btn->GetSize(&w,&h);
  wnd->AddChild(btn);

  clguiLabel* lb=new clguiLabel(30);
  wnd->AddChild(lb);
  lb->SetName("name");
  lb->SetValue("JerryChaos");


  clguiComboBox* cbb=new clguiComboBox();
  cbb->SetSize(100,30);
  cbb->GetSize(&w,&h);
  cbb->SetName("");
  cbb->AppendLabel("label1");
  cbb->AppendLabel("label2");
  cbb->AppendLabel("label3");
  cbb->AppendLabel("label4");
  wnd->AddChild(cbb);
  cbb=new clguiComboBox();
  cbb->SetSize(200,30);
  cbb->SetSameline(true);
  //cbb->SetSameline(false);
  std::vector<clstr> vec;
  for(clint i=0;i<100;i++){
    vec.push_back("label"+std::to_string(i));
  }
  cbb->AppendLabel(vec);
  wnd->AddChild(cbb);
  cbb->AddEventListener(clguiEventType::EVT_COMBOBOX_STATUS_CHANGE,OnComboboxStatusChangeHandler);


  clguiCollapser* clpser=new clguiCollapser();
  clpser->SetName("Collapser");
  clpser->EnableCollapsingEvent();
  clpser->AddEventListener(clguiEventType::EVT_COLLAPSER_STATUS_CHANGE,OnCollapserStatusChange);
  wnd->AddChild(clpser);


  btn=new clguiButton();
  btn->SetName("Change Dimension");
  btn->AddEventListener(clguiEventType::EVT_BUTTON_CLICK,OnChangeSliderDimensionHandler);
  btn->SetSize(200,20);
  clpser->AddChild(btn);

  sl=new clguiSliderFloat();
  sl->SetDimension(1);
  sl->SetName("Color");
  sl->SetRange(1.f,100.f);
  sl->SetValue(11.f);
  sl->AddEventListener(clguiEventType::EVT_SLIDER_VALUE_CHANGE,OnSliderValueChangeHandler);
  clpser->AddChild(sl);

  clguiToolTip* tip=new clguiToolTip();
  tip->SetDescription("This is a tool tip, Color of a surface");
  clpser->AddChild(tip);

  btn=new clguiButton();
  btn->SetName("This trigges two events");
  btn->AddEventListener(clguiEventType::EVT_BUTTON_CLICK,OnTwoEventsBtnClicked_evt_one);
  btn->AddEventListener(clguiEventType::EVT_BUTTON_CLICK,OnTwoEventsBtnClicked_evt_two);
  btn->SetSize(300,20);
  btn->SetSameline(false);
  clpser->AddChild(btn);


}

static void CreateTreeGUI(){
  clguiWindow* wnd=new clguiWindow();
  wnd->SetName("Tree");
  wnd->SetPosition(clguiPositionMode::POSITION_TOP_LEFT);
  wnd->SetSize(400,300);
  clguiAddToStage(wnd);

  clguiTree* tree=new clguiTree();
  tree->CreateNode("Camera");
  nodeID id=tree->CreateNode("Lights");
  tree->CreateNode("pointLight",id);
  tree->CreateNode("spot light",id);
  tree->CreateNode("areaLight",id);
  id=tree->CreateNode("Model");
  tree->CreateNode("head",id);
  tree->CreateNode("body",id);
  nodeID id2=tree->CreateNode("legs",id);
  tree->CreateNode("left leg",id2);
  tree->CreateNode("right leg",id2);
  id=tree->CreateNode("arms",id);
  tree->CreateNode("left arm",id);
  tree->CreateNode("right arm",id);
  /*
  */
  wnd->AddChild(tree);
}

int main(int argc,char* argv[]){


  glfwSetErrorCallback(errorCallback);
  if(!glfwInit()) exit(EXIT_FAILURE);
  //glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
  //glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,2);
  //glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);

  int size[2]={600,400};
  char* title="Hello clgui!";
  GLFWwindow* wnd=glfwCreateWindow(size[0],size[1],title,NULL,NULL);
  glfwMakeContextCurrent(wnd);
  clguiInit(wnd);
  glfwSwapInterval(1);
  glfwSetWindowPos(wnd,400,200);

  CreateMainGUI();
  CreateTreeGUI();

  glClearColor(191.f/255.f,191.f/255.f,191.f/255.f,1.f);
  while(!glfwWindowShouldClose(wnd)){
    glViewport(0,0,size[0],size[1]);
    glClear(GL_COLOR_BUFFER_BIT);

    glfwPollEvents();
    clguiExec();
    glfwSwapBuffers(wnd);
  }
  clguiExit();
  glfwTerminate();

  return EXIT_SUCCESS;
}