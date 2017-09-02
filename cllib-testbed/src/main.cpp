#include <iostream>
#include "clHierarchicalStructure.h"
#include "cllib.h"
#include "clTypeUtil.h"
#include "clRegexpUtil.h"
#include "clPrinter.h"
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
}




void TestPrinter(){
#if 0
  cl::Info("This is debugger info testing.");
  cl::Warning("This is debugger warning testing.");
  cl::Error("This is debugger error testing.");
  cl::Text("This is a random text..bubububububububububububbu.",ConsoleForeground::DARKCYAN);
#endif

#if 1
  vector<cluint> pos;
  pos.push_back(8);
  pos.push_back(1);
  pos.push_back(31);
  pos.push_back(10);
  cl::HighLightText("This is a printer,It's name is Jerry Chaos",ConsoleForeground::WHITE,pos,ConsoleForeground::RED);
#endif
}



void TestClType(){
#if(0)
  clI2 int2_1,int2_2;
  int2_1.Set(30);
  clTypeUtil::Set<clI2,clint>(int2_1,2,3);
  clTypeUtil::CopyAtoB(int2_2,int2_1);
  //clTypeUtil::SetToaa<clI2,clint>(int2_1,2,3);
  std::cout<<int2_2.x<<" "<<int2_2.y<<std::endl;

  clF3 f1,f2,f3;
  clTypeUtil::Set<clF3,clfloat>(f1,2.1f,3.0f,4.0f);
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

#if 0
  char str[]="- This, a sample string.";
  vector<string> vec;
  printf("Splitting string \"%s\" into tokens:\n",str);
  clTypeUtil::SplitString(str,&vec," .,-");
  for each(string s in vec){
    cl::Text(s);
  }
#endif

#if 0
  vector<string> a{"I","am","a","litte","dog","."};
  string s;
  clTypeUtil::CombineStrings(a,&s," ");
  Info(s);
#endif

#if 1
  Unimportant("String is:||   sfsfggg\n he   ||");
  NewLine();
  Info("||"+clTypeUtil::StringTrimLeft("   sfsfggg   ")+"||");
  NewLine();
  Info("||"+clTypeUtil::StringTrimRight("   sfsfggg\n he   ")+"||");
  NewLine();
  Info("||"+clTypeUtil::StringTrim("   ")+"||");
#endif
}


void TestFolderAndFile(){
  string rootPath="z:\\temp/folder";
  rootPath=FolderAndFile::FixPathOrURL(rootPath);
  FolderAndFile ff;
#if(0)
    if(!ff.CreateFolder("z:/tesf/sge/sfsf")){//fail;
    //if(!ff.CreateFolder("temp3/aa/")){
    //if(!ff.CreateFolder("z:/temp2/sss/aaa/")){
      cl::Error("Creating folder failed, mybe it's already exist!");
    }
    return;
#endif
  clint n;
  //cl::cFFInfo* info=ff.Traverse("z:/pbrt-v2",FolderAndFile::V_ALL,&n);
  //cl::cFFInfo* info=ff.Traverse("z:/pbrt-v2/",FolderAndFile::V_FOLDER,&n);
  //cl::cFFInfo* info=ff.Traverse("z:/pbrt-v2/",FolderAndFile::V_FILE,&n);
  //cl::cFFInfo* info=ff.Traverse("z:/temp/",FolderAndFile::V_ALL,&n);
  cl::cFFInfo* info=ff.Traverse(rootPath,FolderAndFile::V_ALL|FolderAndFile::V_NO_DOT_FOLDER,&n);


  string targetPath="z:/temp2\\folder";
  targetPath=FolderAndFile::FixPathOrURL(targetPath);
  FolderAndFile::CreateFolder(targetPath);


  while(info){
#if(1)
    if(info->isFolder){
      if(!FolderAndFile::IsFolderExist(targetPath+info->nameN))
        FolderAndFile::CreateFolder(targetPath+info->nameN);
    } else{
      if(!FolderAndFile::IsFileExist(targetPath+info->nameE)){
        if(!FolderAndFile::CopyFileTo(info,targetPath)){
          cl::Error("File: "+info->URL+" coping failed!");
        }
      }
    }
#endif

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



    info=info->next;
  }
  cl::Text("TOTAL::"+clTypeUtil::NumberToString(n));

}


void TestRegexp(){
  //string str="z:\\sfsfsf\\gggg\\efefef\\sxxx.zip";
  string str=R"(zsssfgeghg:\sfsfsf\gggg\efefe**f\sxxx.zip)";
#if 1
  if(clRegexp::IsStartedWith(str,"zsssfgeghg:\\sf"))Info("Yes");
  else Info("No");
  if(clRegexp::IsEndedWith(str,"sxxx.aip"))Info("Yes");
  else Info("No");
#endif
#if 0
  vector<cluint> out;
  clbool b=clRegexp::GetIndices(str,"\\*",out);
  if(b){
    for(clint i=0;i<out.size();i++){
      Info(NumberToString(out[i]));
    }
  } else Info("No one!");
#endif

#if 0
  cluint n=clRegexp::CountNumber(str,"\\*");
  Info(NumberToString(n));
#endif
#if 0
  vector<clstr> out;
  clstr sufix=clRegexp::GetFirstMatch(str,R"(\w{1,1})",out,false);
  if(sufix.length()>0){
    for(clstr s:out){
      Info(s);
    }
    Warning(sufix);
  } else{
    Error("No matched string");
  }
#endif
#if(0)
  cl::Info("string length:"+NumberToString(str.length()));
  string result;
  result=ReplaceBackSlashToSlash(str);
  cl::Info("\""+str+"\" repalced to"+" \""+result+"\"");
#endif

#if(0)
  //const string e="z";
  const string e="^[a-zA-Z]:";
  if(clRegexp::Contain(str,e)){
    Info(str+" is begin with "+e);
  } else{
    Info(str+" is not begin with "+e);
  }
#endif

#if 0
  std::string s("this subject has a submarine as a subsequence");
  std::vector<string> out;
  clRegexp::ExecuteRegex(s,"\\b(sub)([^ ]*)",out);

  for(clint i=0;i<out.size();i++){
    Info("index:"+NumberToString(i)+" value:"+out[i]);
  }

#endif
#if 0
  //string s="012525252000200";
  string s="10,125,252,520,002,000";
  if(F_IS_STRING_ALL_DECIMAL(s)){
    Info("It's all decimal numbers!");
  }
#endif
#if 0
  //string s="sfsf.ggg_x.gg_x";
  //string s="sfsf.ssex.ggg_x";
  //string s="sfsf.ssex.GGg_x";
  //string s=".GGg_x";
  string s=".GGg_xw";
  if(clRegexp::IsExtensionRight(s,"ggg_x")){
    Info("It's right!");
  }
#endif
#if 0
  //string fileName="sfsf.jpEg";
  //string fileName="sfsf.jpg";
  string fileName="sfsf/gef\\sfsf_sfg225/sg3__ssf22.jPeG";
  if(F_IS_JPG_FILE(fileName)){
    Info("It's jpg/jpeg file");
  }
#endif
#if 0
  string fileName="sfsf.PnG";
  //string fileName="sfsf.PNG";
  //string fileName="sfsf.png";
  //string fileName="sfsf/gef\\sfsf_sfg225/sg3__ssf22.png";
  if(F_IS_PNG_FILE(fileName)){
    Info("It's png file");
  }
#endif
}







int main(){
  std::cout<<"Hello World! testbed begin."<<std::endl;
  //TestHS();
  //TestClass();
  //TestLog();
  //TestClType();
  //TestPrinter();
  //TestFolderAndFile();
  TestRegexp();
  std::cout<<"Hello World! testbed end."<<std::endl;
  system("PAUSE");
  return 0;
}