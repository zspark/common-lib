#include <regex>
#include "cllib.h"
#include "clRegexpUtil.h"

namespace cl{
namespace clRegexp{
using namespace std;

clString GetFirstMatch(clString str,T_REGEXP_STRING format,vector<clString>& out,clB caseSensitive){
  regex e;
  if(caseSensitive)e.assign(format);
  else e.assign(format,regex::icase);
  smatch sm;
  if(regex_search(str,sm,e)){
    for(auto x:sm){
      out.push_back(x);
    }
    return sm.suffix().str();
  }
  return "";
}

clB Contain(clString str,T_REGEXP_STRING format,clB caseSensitive){
  regex e;
  if(caseSensitive)e.assign(format);
  else e.assign(format,regex::icase);
  return regex_search(str,e);
}

clB Match(clString str,T_REGEXP_STRING format,clB caseSensitive){
  regex e;
  if(caseSensitive)e.assign(format);
  else e.assign(format,regex::icase);
  return regex_match(str,e);
}

clString Replace(clString str,clString from,clString to){
  const clUi len=from.length();
  clString::size_type pos(0);
  while(true){
    if((pos=str.find(from,pos))!=clString::npos){
      str.replace(pos,len,to);
      pos+=len;
    } else break;
  }
  return str;
}

void ExecuteRegex(clString str,T_REGEXP_STRING format,vector<clString>& out){
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

clB IsEndedWith(clString str,clString sufix,clB caseSensitive){
  T_REGEXP_STRING tmp;
  tmp=sufix+"$";
  regex e;
  if(caseSensitive)e.assign(tmp);
  else e.assign(tmp,regex::icase);
  return regex_search(str,e);
}
clB IsStartedWith(clString str,clString prefix,clB caseSensitive){
  T_REGEXP_STRING tmp;
  tmp="^"+prefix;
  regex e;
  if(caseSensitive)e.assign(tmp);
  else e.assign(tmp,regex::icase);
  return regex_search(str,e);
}

clUi CountNumber(clString str,T_REGEXP_STRING format){
  regex e(format);
  smatch m;
  int i=0;
  clUi n=0;
  while(regex_search(str,m,e)){
    n++;
    str=m.suffix().str();
  }
  return n;
}



}
}