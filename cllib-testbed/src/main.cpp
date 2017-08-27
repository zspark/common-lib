#include <iostream>
#include "clHierarchicalStructure.h"
#include "Log.h"
#include "clTypeUtil.h"
#include "clRegexpUtil.h"
#include "clPrinter.h"
#include "clFolderAndFile.h"
#include "clUtil.h"

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
#if(0)
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
#endif
  /*
  clI2 int2;
  clF2 float2;
  float2.Set(1.0f,2.4f);
  int2.Copy(float2);
*/

#if(1)
  char str[]="- This, a sample string.";
  vector<string> vec;
  printf("Splitting string \"%s\" into tokens:\n",str);
  clTypeUtil::SplitString(str,&vec," .,-");
  for each(string s in vec){
    cl::Text(s);
  }
#endif
}


void TestFolderAndFile(){
  cl::FolderAndFile ff;
#if(0)
    if(!ff.CreateFolder("z:/tesf/sge/sfsf")){//fail;
    //if(!ff.CreateFolder("temp3/aa/")){
    //if(!ff.CreateFolder("z:/temp2/sss/aaa/")){
      cl::Error("Creating folder failed, mybe it's already exist!");
    }
    return;
#endif
  clI n;
  //cl::cFFInfo* info=ff.Traverse("z:/pbrt-v2",FolderAndFile::V_ALL,&n);
  //cl::cFFInfo* info=ff.Traverse("z:/pbrt-v2/",FolderAndFile::V_FOLDER,&n);
  //cl::cFFInfo* info=ff.Traverse("z:/pbrt-v2/",FolderAndFile::V_FILE,&n);
  //cl::cFFInfo* info=ff.Traverse("z:/temp/",FolderAndFile::V_ALL,&n);
  cl::cFFInfo* info=ff.Traverse("z:/temp/",FolderAndFile::V_ALL|FolderAndFile::V_NO_DOT_FOLDER,&n);
  
  while(info){
#if(0)
    if(info->isFolder)cl::Text(info->nameN);
    else cl::Text(info->nameN+"."+info->extension);
#else
    if(info->isFolder)cl::Text(info->URL,ConsoleForeground::RED);
    else cl::Text(info->URL,ConsoleForeground::GREEN);
#endif
#if(0)
    if(!ff.Remove(info)){
      cl::Error("File: "+info->URL+" did not removed!");
    }
#endif
#if(1)
    if(!ff.CopyFileTo(info,"z:/temp2/aaa/bbb")){
      cl::Error("File: "+info->URL+" coping failed!");
    }
#endif



    info=info->next;
  }
  cl::Text("TOTAL::"+cl::NumberToString(n));

  ff.Release();
}


void TestRegexp(){
  //string str="z:\\sfsfsf\\gggg\\efefef\\sxxx.zip";
  string str=R"(z:\sfsfsf\gggg\efefef\sxxx.zip)";
#if(0)
  cl::Info("string length:"+NumberToString(str.length()));
  string result;
  result=ReplaceBackSlashToSlash(str);
  cl::Info("\""+str+"\" repalced to"+" \""+result+"\"");
#endif

#if(1)
  //const string e="z";
  const string e="^[a-zA-Z]:";
  if(clRegexp::Contain(str,e)){
    Info(str+" is begin with "+e);
  } else{
    Info(str+" is not begin with "+e);
  }

#endif
}







int main(){
  std::cout<<"Hello World! testbed begin."<<std::endl;
  //TestHS();
  //TestClass();
  //TestLog();
  //TestClType();
  //TestDebugger();
  TestFolderAndFile();
  //TestRegexp();
  std::cout<<"Hello World! testbed end."<<std::endl;
  system("PAUSE");
  return 0;
}