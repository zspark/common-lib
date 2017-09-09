#include <iostream>
#include "cllib.h"
#include "clTypeUtil.h"
#include "clRegexpUtil.h"
#include "clPrinter.h"
#include "clFolderAndFile.h"

using namespace cl;




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

}


void TestRegexp(){
  //string str="z:\\sfsfsf\\gggg\\efefef\\sxxx.zip";
  string str=R"(zsssfgeghg:\sfsfsf\gggg\efefe**f\sxxx.zip)";
#if 0
  str=R"(')";
  Info(str);
#endif
#if 0
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
  str=R"("E:/r/")";
  //clstr sufix=clRegexp::GetFirstMatch(str,R"(\w{1,1})",out,false);
  clstr sufix=clRegexp::GetFirstMatch(str,R"([^"]+)",out,true);
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

#if 1
  //const string e="z";
  str="aab3*";
  const string e=R"(^[^\\/\*:\?"<>\|]+$)";
  if(clRegexp::Match(str,e)){
    Info(str+" is matched");
  } else{
    Info(str+" is not matched");
  }
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
  //TestClass();
  //TestLog();
  //TestClType();
  //TestPrinter();
  TestFolderAndFile();
  //TestRegexp();
  std::cout<<"Hello World! testbed end."<<std::endl;
  system("PAUSE");
  return 0;
}