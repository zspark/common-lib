#pragma once

#include <cstdlib>
#include <vector>
#include "clTypes.h"

namespace cl{
namespace clTypeUtil{

void SplitString(std::string s,std::vector<std::string>* vec,clCcs delimiters);
void CombineStrings(const std::vector<std::string>& vec,std::string* result,clCcs delimiters);
clUi GetDecimalLength(clUi);
std::string StringTrim(std::string s);

template<typename T,typename T2>
T Make(T2 a,T2 b){
  T result;
  SetTo<T,T2>(result,a,b);
  return result;
}
template<typename T,typename T2>
T Make(T2 a,T2 b,T2 c){
  T result;
  SetTo<T,T2>(result,a,b,c);
  return result;
}
template<typename T,typename T2>
T Make(T2 a,T2 b,T2 c,T2 d){
  T result;
  SetTo<T,T2>(result,a,b,c,d);
  return result;
}

template<typename T,typename T2>
void Set(T& value,T2 a,T2 b){
  value.x=a;
  value.y=b;
};

template<typename T,typename T2>
void Set(T& value,T2 a,T2 b,T2 c){
  value.x=a;
  value.y=b;
  value.z=c;
};

template<typename T,typename T2>
void Set(T& value,T2 a,T2 b,T2 c,T2 d){
  value.x=a;
  value.y=b;
  value.z=c;
  value.w=d;
};

template<typename T>
void CopyAtoB(T& b,const T& a){
  memcpy(&b,&a,sizeof(a));
}
};
}
