#include <regex>
#include "cllib.h"
#include "clRegexpUtil.h"

namespace cl{
namespace clRegexp{
using namespace std;

clB Contain(string str,T_REGEXP_STRING format,clB caseSensitive){
  regex e;
  if(caseSensitive)e.assign(format);
  else e.assign(format,regex::icase);
  return regex_search(str,e);
}

clB Match(string str,T_REGEXP_STRING format,clB caseSensitive){
  regex e;
  if(caseSensitive)e.assign(format);
  else e.assign(format,regex::icase);
  return regex_match(str,e);
}

string Replace(string str,string from,string to){
  const clUi len=from.length();
  string::size_type pos(0);
  while(true){
    if((pos=str.find(from,pos))!=string::npos){
      str.replace(pos,len,to);
      pos+=len;
    } else break;
  }
  return str;
}

void ExecuteRegex(string str,T_REGEXP_STRING format,vector<string>& out){
  regex e(format);
  smatch m;
  int i=0;
  while(regex_search(str,m,e)){
    for(auto x:m){
      out.push_back(x);
    }
    str=m.suffix().str();
  }
}

clB IsEndedWith(string str,string sufix){
  T_REGEXP_STRING tmp;
  tmp=sufix+"$";
  regex e(tmp,regex::icase);
  return regex_search(str,e);
}
clB IsStartedWith(string str,string prefix){
  T_REGEXP_STRING tmp;
  tmp="^"+prefix;
  regex e(tmp,regex::icase);
  return regex_search(str,e);
}
}
}