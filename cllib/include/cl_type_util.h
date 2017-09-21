#pragma once

#include <sstream>
#include <cstdlib>
#include <vector>
#include "cl_types.h"

namespace cl{
namespace clTypeUtil{

void SplitString(clstr s,std::vector<clstr>& vec,const clchar* delimiters);
void CombineStrings(const std::vector<clstr>& vec,clstr* result,const clchar* delimiters);
cluint GetDecimalLength(cluint);
clstr StringTrim(clstr s);
clstr StringTrimLeft(clstr s);
clstr StringTrimRight(clstr s);

template <typename T>
clstr NumberToString(T Number){
  ostringstream ss;
  ss<<Number;
  return ss.str();
}

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
