//#include <stdio.h>
#include <vector>
#include "cllib.h"
#include "clTypeUtil.h"
#include "clRegexpUtil.h"
#ifdef __CLLIB_INTERNAL_DEBUG__
#include "clPrinter.h"
#endif

namespace cl{
namespace clTypeUtil{

using namespace std;

static clstr s_StringTrim(clstr s,clstr format){
  vector<clstr> vec;
  clRegexp::ExecuteRegex(s,format,vec);
  return vec.size()>1?vec[1]:"";
}

void SplitString(clstr s,vector<clstr>& vec,const clchar* delimiters){
  clchar* next_token;
  clchar* pch=::strtok_s(const_cast<clchar*>(s.c_str()),delimiters,&next_token);
  while(pch!=NULL){
    vec.push_back(pch);
    pch=::strtok_s(NULL,delimiters,&next_token);
  }
}

void CombineStrings(const vector<clstr>& vec,clstr* result,const clchar* delimiters){
  *result="";
  const clstr tmp{delimiters};
  const cluint n=vec.size();
  for(clint i=0;i<n;i++){
    *result=(*result)+tmp+vec[i];
  }
}

cluint GetDecimalLength(cluint dec){
  int flag=0;
  while(dec){
    dec/=10;
    flag++;
  }
  return flag;
}

clstr StringTrim(clstr s){
  return s_StringTrim(s,R"(\s*((.|\n)*\S)\s*)");
}

clstr StringTrimLeft(clstr s){
  return s_StringTrim(s,R"(\s*((.|\n)+))");
}

clstr StringTrimRight(clstr s){
  return s_StringTrim(s,R"(((.|\n)+\S)\s*)");
}

clstr fixToLength(cluint num,clint n){
  if(GetDecimalLength(num)>n){
#ifdef __CLLIB_INTERNAL_DEBUG__
    Warning("试图将一个更长的数字调整为长度较短的字符串，函数终止，并返回空字符串！");
#endif
    return "";
  }
  char f[10];
  sprintf_s(f,"%%0%dd",n);
  char c[10];
  sprintf_s(c,f,num);
  return c;
}



}
}