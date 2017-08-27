#include <regex>
#include "cllib.h"
#include "clRegexpUtil.h"

namespace cl{
namespace clRegexp{
using namespace std;

clB Contain(string str,string format){
  regex e(format);
  return regex_search(str,e);
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

}
}