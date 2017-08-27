#pragma once

#include <sstream>
#include "clTypes.h"
#include "clRegexpUtil.h"

namespace cl{
//void copyAtoB(clUniformVariable& a,clUniformVariable& b);

template <typename T>
std::string NumberToString(T Number){
  std::ostringstream ss;
  ss<<Number;
  return ss.str();
}

inline clB IsBeginnedWithDot(std::string s){
  return s.find_first_of('.')==0;
}

inline clB IsEndedWithSlash(std::string s){
  return s.find_last_of('/')==s.length()-1;
}

/**
* Windows OS only
*/
inline clB IsAbsolutePathOrURL(std::string s){
  return clRegexp::Contain(s,"[a~zA~Z]:");
}

}