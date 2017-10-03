#include <iostream>
#define CLGUI_API_IMPORTS
#include "clgui/clgui.h"
#include "clgui/clgui_gui_sets.h"

using namespace std;
using namespace clgui;

static void errorCallback(int error,const char* description){
  //fprintf(stderr, "Error %d: %s\n", error, description);
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
}

static void CheckboxSelectionHander(clguiEvent* evt){
  cout<<"checkbox value changed!"<<endl;
  clguiEventCheckboxStatusChange* changeEvt=static_cast<clguiEventCheckboxStatusChange*>(evt);
  clguiCheckBox* cb=changeEvt->GetSender();
  cout<<cb->GetCaption()<<endl;
}

static void MenuItemStatusChangeHander(clguiEvent* evt){
  clguiEventMenuItemStatusChange* changeEvt=static_cast<clguiEventMenuItemStatusChange*>(evt);
  clguiMenuItem* mi=changeEvt->GetSender();
  cout<<mi->GetCaption()<<" "<<mi->GetSelection()<<" "<<mi->GetShortKey()<<" "<<mi->GetType()<<endl;

}

static void OnSliderValueChangeHandler(clguiEvent* evt){
  clguiEventSliderValueChangeFloat* changeEvt=static_cast<clguiEventSliderValueChangeFloat*>(evt);
  clguiSliderFloat* sl=changeEvt->GetSender();
  cout<<sl->GetValue(0)<<" "<<sl->GetValue(1)<<" "<<sl->GetValue(2)<<endl;
}

clguiSliderFloat* sl=nullptr;
static void OnChangeSliderDimensionHandler(clguiEvent* evt){
  clguiEventButtonClick* changeEvt=static_cast<clguiEventButtonClick*>(evt);
  clguiButton* btn=changeEvt->GetSender();
  cout<<"Change button clicked!"<<endl;
  sl->SetDimension(2);

  clguiSliderInt* sli=new clguiSliderInt();
  sli->SetDimension(3);
  sli->SetCaption("color:");
  sli->SetRange(0,255);
  clint value[3]={000,111,222};
  sli->SetValue(value);
  clguiAddToStage(sli);
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
  //ctn->AttachToBorder(attach_side::RIGHT,300.f);
  clguiMenu* m=clguiConverToMenu(mb->GetDirectChildByCaption("File"));
  if(m){
    clguiComponent* com=m->GetDirectChildByCaption("Hello4");
    clguiMenuItem* mi=clguiConverToMenuItem(com);
    int a=10;
    if(mi){
      mi->SetSelection(false);
    }
  }
}


static void CreateGUI5(){
  clguiCheckBox* cb=new clguiCheckBox(false);
  cb->SetCaption("click to select");
  clguiAddToStage(cb);

  clguiLabel* lb=new clguiLabel();
  lb->SetCaption("strength:");
  lb->SetValue(1333);
  lb->SetColor(191.f/255,191.f/255,191.f/255);
  clguiAddToStage(lb);
}
static void CreateGUI2(){
  clguiButton* btn=new clguiButton();
  btn->AddEventListener(clguiEventType::EVT_BUTTON_CLICK,cf);
  clguiAddToStage(btn);
  btn->SetCaption("HH");
  btn->SetSize(100,50);

  const cluint N{10};
  for(cluint i=0;i<N;i++){
    clguiButton* btn2=new clguiButton(*btn);
    clguiAddToStage(btn2);
  }
}
static void CreateGUI4(){
  clguiWindow* wnd=new clguiWindow();
  wnd->SetCaption("Hello windows");
  wnd->SetPosition(100,100);
  wnd->SetSize(400,300);
  wnd->AddEventListener(clguiEventType::EVT_WINDOW_CLOSE,wndCloseHandler);
  clguiAddToStage(wnd);

  clguiWindow* wnd2=new clguiWindow();
  wnd2->SetCaption("Hello windows2");
  wnd2->SetPosition(100,100);
  wnd2->SetSize(400,300);
  wnd2->AddEventListener(clguiEventType::EVT_WINDOW_CLOSE,wndCloseHandler);
  clguiAddToStage(wnd2);


  clguiButton* btn=new clguiButton();
  btn->AddEventListener(clguiEventType::EVT_BUTTON_CLICK,cf);
  wnd->AddChild(btn);
  wnd2->AddChild(btn);

  //btn->clguiSetSize(50,20);
  //btn->Visible(false);
}
static void CreateGUI3(){
  clguiWindow* wnd=new clguiWindow();
  wnd->SetCaption("Hello windows");
  wnd->SetPosition(100,100);
  wnd->SetSize(400,300);
  wnd->AddEventListener(clguiEventType::EVT_WINDOW_CLOSE,wndCloseHandler);
  clguiAddToStage(wnd);

  clguiWindow* wnd2=new clguiWindow();
  wnd2->SetCaption("Hello windows2");
  wnd2->SetPosition(100,100);
  wnd2->SetSize(400,300);
  wnd2->AddEventListener(clguiEventType::EVT_WINDOW_CLOSE,wndCloseHandler);
  wnd->AddChild(wnd2);


  clguiButton* btn=new clguiButton();
  btn->SetCaption("Hello clgui");
  btn->AddEventListener(clguiEventType::EVT_BUTTON_CLICK,cf);
  wnd2->AddChild(btn);
  btn->SetSize(500,20);
  //btn->Visible(false);
}
static void CreateGUI1(){
  clguiButton* btn=new clguiButton();
  btn->AddEventListener(clguiEventType::EVT_BUTTON_CLICK,cf);
  clguiAddToStage(btn);
}
static void CreateGUI0(){
  clguiWindow* wnd=new clguiWindow();
  wnd->SetCaption("Hello windows");
  wnd->SetPosition(100,100);
  wnd->SetSize(400,300);
  wnd->AddEventListener(clguiEventType::EVT_WINDOW_CLOSE,wndCloseHandler);
  wnd->AttachToBorder(attach_side::RIGHT,300.f);
  clguiAddToStage(wnd);

  clguiButton* btn=new clguiButton();
  btn->AddEventListener(clguiEventType::EVT_BUTTON_CLICK,OnResetSizeHandler);
  wnd->AddChild(btn);


  clguiCheckBox* cb=new clguiCheckBox();
  cb->AddEventListener(clguiEventType::EVT_CHECKBOX_STATUS_CHANGE
    ,CheckboxSelectionHander);
  wnd->AddChild(cb);

  clguiLabel* lb=new clguiLabel();
  wnd->AddChild(lb);
  lb->SetColor(191.f/255.f,191.f/255.f,191.f/255.f,1.f);
  lb->SetCaption("name:");
  lb->SetValue(1);
  lb->SetValue("JerryChaos");


}
static void CreateGUI10(){

  mb=new clguiMenuBar();
  clguiAddToStage(mb);
  clguiMenu* m=new clguiMenu();
  m->SetCaption("File");
  mb->AddChild(m);

  int i=5;
  while(--i>=0){
    clguiMenuItem* mi=new clguiMenuItem();
    mi->SetCaption("Hello"+std::to_string(i));
    mi->SetShortKey("Ctrl+B");
    m->AddChild(mi);
    //mi->AddEventListener(clguiEventType::EVT_MENUITEM_STATUS_CHANGE,MenuItemStatusChangeHander);
    //m->AddChildAt(mi,i);
  }
  clguiMenuItem* mi=new clguiMenuItem();
  mi->SetCaption("panel");
  mi->SetShortKey("ctrl+p");
  m->AddChild(mi);
  mi->AddEventListener(clguiEventType::EVT_MENUITEM_STATUS_CHANGE,MenuItemStatusChangeHander);


  m=new clguiMenu();
  m->SetCaption("Edit");
  mb->AddChild(m);

  i=5;
  while(--i>=0){
    clguiButton* btn=new clguiButton();
    btn->SetCaption("Hello");
    m->AddChild(btn);
  }

  clguiCheckBox* cb=new clguiCheckBox();
  cb->AddEventListener(clguiEventType::EVT_VALUE_CHANGE
    ,CheckboxSelectionHander);
  m->AddChild(cb);
}
static void CreateSlider(){
  clguiButton* btn=new clguiButton();
  btn->SetCaption("Change Dimension");
  btn->AddEventListener(clguiEventType::EVT_BUTTON_CLICK,OnChangeSliderDimensionHandler);
  btn->SetSize(200,50);
  clguiAddToStage(btn);


  sl=new clguiSliderFloat();
  sl->SetDimension(1);
  sl->SetCaption("value:");
  sl->SetRange(1.f,100.f);
  sl->SetValue(11.f);
  sl->AddEventListener(clguiEventType::EVT_SLIDER_VALUE_CHANGE,OnSliderValueChangeHandler);
  clguiAddToStage(sl);

}

static clguiMenuBar* mainMenubar=nullptr;
static clguiWindow* mainPanel=nullptr;
static clguiWindow* about=nullptr;


static void OnMainPanelStatusChangeHandler(clguiEvent* evt){
  clguiEventMenuItemStatusChange* changeEvt=static_cast<clguiEventMenuItemStatusChange*>(evt);
  clguiMenuItem* mi=changeEvt->GetSender();
  //mainPanel->Visible(mi->GetSelection());
  clgui::clguiDeleteChildren(mainPanel);
}


static void CreateMainGUI(){
  mainMenubar=new clguiMenuBar();
  clguiMenuBar* mb=mainMenubar;
  clguiAddToStage(mb);

  ///////////////////file
  clguiMenu* m=new clguiMenu();
  m->SetCaption("File");
  mb->AddChild(m);

  clguiMenuItem* mi=new clguiMenuItem();
  mi->SetCaption("Open");
  mi->SetShortKey("ctrl+o");
  m->AddChild(mi);

  mi=new clguiMenuItem();
  mi->SetCaption("Save");
  mi->SetShortKey("ctrl+s");
  m->AddChild(mi);

  mi=new clguiMenuItem();
  mi->SetCaption("Exit");
  m->AddChild(mi);


  ///////////////////Edit
  m=new clguiMenu();
  m->SetCaption("Edit");
  mb->AddChild(m);

  mi=new clguiMenuItem();
  mi->SetCaption("Options..");
  m->AddChild(mi);

  ///////////////////View
  m=new clguiMenu();
  m->SetCaption("View");
  mb->AddChild(m);

  mi=new clguiMenuItem();
  mi->SetCaption("MainPanel..");
  mi->SetShortKey("ctrl+p");
  mi->SetSelection(true);
  mi->AddEventListener(clguiEventType::EVT_MENUITEM_STATUS_CHANGE,OnMainPanelStatusChangeHandler);
  m->AddChild(mi);

  mi=new clguiMenuItem();
  mi->SetCaption("LightPanel..");
  mi->SetShortKey("ctrl+l");
  m->AddChild(mi);

  mi=new clguiMenuItem();
  mi->SetCaption("ModelPanel..");
  mi->SetShortKey("ctrl+m");
  m->AddChild(mi);


  ///////////////////Help
  m=new clguiMenu();
  m->SetCaption("Help");
  mb->AddChild(m);

  mi=new clguiMenuItem();
  mi->SetCaption("About openGL-review");
  m->AddChild(mi);

  mi=new clguiMenuItem();
  mi->SetCaption("Version");
  m->AddChild(mi);



  clguiWindow* wnd=new clguiWindow();
  mainPanel=wnd;
  wnd->SetPosition(100,100);
  wnd->SetSize(400,300);
  wnd->AttachToBorder(attach_side::RIGHT,300);
  clguiAddToStage(wnd);
  clguiButton* btn=new clguiButton();
  btn->AddEventListener(clguiEventType::EVT_BUTTON_CLICK,OnResetSizeHandler);
  wnd->AddChild(btn);


  clguiCheckBox* cb=new clguiCheckBox();
  cb->AddEventListener(clguiEventType::EVT_CHECKBOX_STATUS_CHANGE
    ,CheckboxSelectionHander);
  wnd->AddChild(cb);

  clguiLabel* lb=new clguiLabel();
  wnd->AddChild(lb);
  lb->SetColor(191.f/255.f,191.f/255.f,191.f/255.f,1.f);
  lb->SetCaption("name:");
  lb->SetValue(1);
  lb->SetValue("JerryChaos");

  clguiTextArea* t=new clguiTextArea();
  t->SetCaption("1.  [obn] connected with drawings and design,\nespecially in the production of books,magazines,etc.  \n2.  £¬clear and full of details,especially \nabout sth unpleasant ");
  wnd->AddChild(t);
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
  //glfwSwapInterval(1);
  glfwSetWindowPos(wnd,400,200);
  //CreateGUI0();
  //CreateGUI10();
  CreateMainGUI();
  //CreateSlider();

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