#pragma once

#include <string>
#include <vector>

namespace cl{
namespace clRegexp{
using namespace std;

#define T_REGEXP_STRING std::string

clB Contain(string str,T_REGEXP_STRING format,clB caseSensitive=true);
clB Match(string str,T_REGEXP_STRING format,clB caseSensitive=true);
string Replace(string str,string from,string to);
void ExecuteRegex(string str,T_REGEXP_STRING format,vector<string>& out);
clB IsEndedWith(string str,string sufix);
clB IsStartedWith(string str,string prefix);
}
}

