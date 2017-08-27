#pragma once

#include <string>

namespace cl{
namespace clRegexp{
clB Contain(std::string str,std::string format);
std::string Replace(std::string str,std::string from,std::string to);
}
}

#define ReplaceBackSlashToSlash(str) cl::clRegexp::Replace(str,"\\","/")
