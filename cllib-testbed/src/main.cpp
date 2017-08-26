#include <iostream>
#include "clHierarchicalStructure.h"
#include "Log.h"
#include "clTypeUtil.h"
#include "clDebugger.h"
#include "clFolderAndFile.h"

using namespace cl;
void TestHS(){
  typedef clHierarchicalStructureNode_T<int> NodeInt;
  typedef clHierarchicalStructure_T<NodeInt> SHInt;

  SHInt sh;
  NodeInt* node=sh.CreateNode();
  node->mCustomObject=10.0f;
  sh.InsertNode(nullptr,node,clHierarchicalStructureNodeRelation::R_FIRST_CHILD);

  NodeInt* node2=sh.CreateNode();
  node2->mCustomObject=1010;
  sh.InsertNode(node,node2,clHierarchicalStructureNodeRelation::R_FIRST_CHILD);


  sh.Print();

}


class A{
public:
  A(){}
  ~A(){}

  void Method(){
    std::cout<<"Method in A."<<std::endl;
  };

};

class B:public A{
public:
  B(){}
  ~B(){}

  void Method(){
    std::cout<<"Method in B."<<std::endl;
  };

};


void TestClass(){
  A* b=new B();
  //static_cast<A>(b).Method();
  b->Method();
}


void TestLog(){
  _LOGSYNCON
    _LOGWITHSYNC("Hello World!")
    Log(Log::LL_ERROR,"lalala");
}




void TestDebugger(){
  cl::Info("This is debugger info testing.");
  cl::Warning("This is debugger warning testing.");
  cl::Error("This is debugger error testing.");
  cl::Text("This is a random text..bubububububububububububbu.",ConsoleForeground::DARKCYAN);
}



void TestClType(){
  clI2 int2_1,int2_2;
  int2_1.Set(30);
  clTypeUtil::Set<clI2,clI>(int2_1,2,3);
  clTypeUtil::CopyAtoB(int2_2,int2_1);
  //clTypeUtil::SetToaa<clI2,clI>(int2_1,2,3);
  std::cout<<int2_2.x<<" "<<int2_2.y<<std::endl;

  clF3 f1,f2,f3;
  clTypeUtil::Set<clF3,clF>(f1,2.1f,3.0f,4.0f);
  clTypeUtil::CopyAtoB(f3,f1);
  std::cout<<f3.x<<" "<<f3.y<<" "<<f3.z<<std::endl;
  std::cout<<f1.x<<" "<<f1.y<<" "<<f1.z<<std::endl;

  /*
  clI2 int2;
  clF2 float2;
  float2.Set(1.0f,2.4f);
  int2.Copy(float2);
*/
}


void TestFolderAndFile(){
  cl::FolderAndFile ff;
  clI n;
  cl::cFFInfo* info=ff.Traverse("z:/pbrt-v2/",FolderAndFile::V_FILE,&n);
  
  while(info){
    cl::Info(info->nameN+"."+info->extension);
    info=info->next;
  }
  cout<<n<<endl;

  ff.Release();
}









int main(){
  std::cout<<"Hello World! testbed begin."<<std::endl;
  //TestHS();
  //TestClass();
  //TestLog();
  //TestClType();
  //TestDebugger();
  TestFolderAndFile();
  std::cout<<"Hello World! testbed end."<<std::endl;
  system("PAUSE");
  return 0;
}