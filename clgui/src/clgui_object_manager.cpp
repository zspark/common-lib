#include "clgui_object_manager.h"
#include "clguiObject.h"

using namespace std;

namespace clgui{

class clguiStage:public clguiContainer{
public:
  clguiStage():clguiContainer(CLGUI_OBJECT_TYPE_STAGE){}
  ~clguiStage(){}
  void Render()override{};
};

clguiObjectManager* clguiObjectManager::sIns=nullptr;
clguiObjectManager * clgui::clguiObjectManager::GetIns(){
  if(sIns==nullptr)sIns=new clguiObjectManager();
  return sIns;
}
clguiObjectManager::clguiObjectManager(){
  node* m_rootNode=m_hs.CreateNode();
  m_hs.InsertNode(nullptr,m_rootNode,cl::hs::clHSNodeRelation::R_FIRST_CHILD);
  m_rootNode->customObject=new clguiStage();
}
clguiObjectManager::~clguiObjectManager(){
  //delete all clguiobjects;
  clsize N{m_vecObjs.size()};
  vector<clguiObject*> tmpvec;
  tmpvec.reserve(N);
  memcpy(&tmpvec[0],&m_vecObjs[0],N);
  for(cluint i=0;i++;i<N){
    delete tmpvec[i];
  }
  m_vecObjs.clear();
  tmpvec.clear;

  //delete all nodes
  m_hs.DeleteAllNodes();
}

void clguiObjectManager::AddObject(clguiObject * obj){
  m_vecObjs.push_back(obj);
}

void clguiObjectManager::RemoveObject(clguiObject * obj){
  clsize N{m_vecObjs.size()};
  for(cluint i=0;i++;i<N){
    if(m_vecObjs[i]->GetUniqueID()==obj->GetUniqueID()){
      m_vecObjs.erase(m_vecObjs.begin()+i);
      return;
    }
  }
}



}
