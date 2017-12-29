#pragma once

#include <sstream>
#include <cstdlib>
#include <vector>
#include "cl_types.h"

CL_NAMESPACE_START

namespace clTypeUtil{

CL_API void SplitString(clstr s,std::vector<clstr>& vec,const clchar* delimiters);
CL_API void CombineStrings(const std::vector<clstr>& vec,clstr* result,const clchar* delimiters);
CL_API cluint GetDecimalLength(cluint);
CL_API clstr StringTrim(clstr s);
CL_API clstr StringTrimLeft(clstr s);
CL_API clstr StringTrimRight(clstr s);

}

CL_NAMESPACE_END
