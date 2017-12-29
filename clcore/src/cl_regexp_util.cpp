#include <regex>
#include "cl/cl_regexp_util.h"

using namespace std;

CL_NAMESPACE_START
namespace clRegexp{

clstr GetFirstMatch(clstr str,T_REGEXP_STRING format,vector<clstr>& out,clbool caseSensitive){
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

clbool Contain(clstr str,T_REGEXP_STRING format,clbool caseSensitive){
  regex e;
  if(caseSensitive)e.assign(format);
  else e.assign(format,regex::icase);
  return regex_search(str,e);
}

clbool Match(clstr str,T_REGEXP_STRING format,clbool caseSensitive){
  regex e;
  if(caseSensitive)e.assign(format);
  else e.assign(format,regex::icase);
  return regex_match(str,e);
}

clstr Replace(clstr str,clstr from,clstr to){
  const cluint len=from.length();
  clstr::size_type pos(0);
  while(true){
    if((pos=str.find(from,pos))!=clstr::npos){
      str.replace(pos,len,to);
      pos+=len;
    } else break;
  }
  return str;
}

void ExecuteRegex(clstr str,T_REGEXP_STRING format,vector<clstr>& out){
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

clbool IsEndedWith(clstr str,clstr subs,clbool caseSensitive){
  const cluint subsLen=subs.size();
  const cluint strLen=str.size();
  if(subsLen>strLen)return false;
  else{
    if(subsLen<=0)return false;
    clint j=strLen-1;
    clint i=subsLen-1;
    for(;i>=0;){
      if(str[j]!=subs[i])return false;
      j--;i--;
    }
  }
  return true;
}

clbool IsStartedWith(clstr str,clstr subs,clbool caseSensitive){
#if 0
  if(subs.size()>str.size())return false;
  auto index=str.find_first_of(subs);
  return index==0;
#else
  const cluint subsLen=subs.size();
  if(subsLen>str.size())return false;
  else{
    if(subsLen<=0)return false;
    for(cluint i=0;i<subsLen;i++){
      if(str[i]!=subs[i])return false;
    }
  }
  return true;
#endif
}

cluint CountNumber(clstr str,T_REGEXP_STRING format){
  regex e(format);
  smatch m;
  int i=0;
  cluint n=0;
  while(regex_search(str,m,e)){
    n++;
    str=m.suffix().str();
  }
  return n;
}

clbool GetIndices(clstr str,T_REGEXP_STRING format,vector<cluint>& out){
  regex e(format);
  smatch m;
  int i=0;
  cluint sum=0;
  cluint n=0;
  while(regex_search(str,m,e)){
    n++;
    sum+=m.prefix().length();
    out.push_back(sum);
    sum++;
    str=m.suffix().str();
  }
  return n>0;
}



}
CL_NAMESPACE_END