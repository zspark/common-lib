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

void SplitString(string s,vector<string>* vec,clCcs delimiters){
  clCs next_token;
  clCs pch=::strtok_s(const_cast<clCs>(s.c_str()),delimiters,&next_token);
  while(pch!=NULL){
    vec->push_back(pch);
    pch=::strtok_s(NULL,delimiters,&next_token);
  }
}

void CombineStrings(const std::vector<std::string>& vec,std::string* result,clCcs delimiters){
  *result="";
  const string tmp{delimiters};
  const clUi n=vec.size();
  for(clI i=0;i<n;i++){
    *result=(*result)+tmp+vec[i];
  }
}

clUi GetDecimalLength(clUi dec){
  int flag=0;
  while(dec){
    dec/=10;
    flag++;
  }
  return flag;
}

string StringTrim(string s){
  vector<string> vec;
  clRegexp::ExecuteRegex(s,R"(\s*((.|\n)+\S)\s*)",vec);
  return vec.size()>1?vec[1]:"";
}

string fixToLength(clUi num,int n){
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