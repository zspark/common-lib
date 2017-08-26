#pragma once

#include "clTypes.h"
#include <sstream>

namespace cl{
//void copyAtoB(clUniformVariable& a,clUniformVariable& b);

template <typename T>
std::string NumberToString(T Number){
  std::ostringstream ss;
  ss<<Number;
  return ss.str();
}

}