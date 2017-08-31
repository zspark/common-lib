#pragma once

#include "clTypes.h"
#include <vector>

namespace cl{
namespace clRegexp{

typedef clString T_REGEXP_STRING;

/**
* 查找str中首次匹配T_REGEXP_STRING的字符串，将匹配的内容写入参数三；
* 并且返回匹配内容之后的字符串；
*/
clString GetFirstMatch(clString,T_REGEXP_STRING,std::vector<clString>&,clB caseSensitive=true);
clB Contain(clString str,T_REGEXP_STRING format,clB caseSensitive=true);
clB Match(clString str,T_REGEXP_STRING format,clB caseSensitive=true);
clString Replace(clString str,clString from,clString to);
void ExecuteRegex(clString str,T_REGEXP_STRING format,std::vector<clString>& out);
clB IsEndedWith(clString str,clString sufix,clB caseSensitive=true);
clB IsStartedWith(clString str,clString prefix,clB caseSensitive=true);
clUi CountNumber(clString str,T_REGEXP_STRING target);
}
}

