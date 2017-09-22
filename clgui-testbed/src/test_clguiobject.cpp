#include <iostream>
#include "clgui_object_manager.h"
#include "clguiObject.h"

using namespace std;
using namespace clgui;

int main(int argc, char* argv[]) {

  cout<<"Test clguiObject"<<endl;
  clguiObjectManager* mgr=clguiObjectManager::GetIns();

  const cluint N{100};
  clguiObject* obj;
  for(clint i=0;i<N;i++){
    obj=new clguiObject(CLGUI_OBJECT_TYPE_INTERACTIVE);
  }
  new clguiObject(CLGUI_OBJECT_TYPE_RENDERABLE);

  cout<<"total objects:"<<mgr->GetObjectCount()<<endl;

  clguiRenderable* robj=mgr->Triverse<clguiRenderable>(CLGUI_OBJECT_TYPE_RENDERABLE,true);
  while(robj){
    cout<<robj->GetUniqueID()<<endl;
    robj=mgr->Triverse<clguiRenderable>(CLGUI_OBJECT_TYPE_RENDERABLE);
  }

#if 0
  clguiObject a(clguiObjectType::OBJECT_TYPE_BUTTON);
  clguiObject b=a;
  clguiObject c(a);
  clguiObject d(clguiObjectType::OBJECT_TYPE_BUTTON);
  d=a;

  clguiRenderable aa(clguiObjectType::OBJECT_TYPE_BUTTON);
  clguiRenderable bb(aa);
#endif



    

  system("pause");
  return EXIT_SUCCESS;
}