#pragma once

#include <vector>
#include "cl/cl_types.h"

CL_NAMESPACE_START
namespace clRegexp{

typedef clstr T_REGEXP_STRING;

/**
* 查找str中首次匹配T_REGEXP_STRING的字符串，将匹配的内容写入参数三；
* 并且返回匹配内容之后的字符串；
*/
CL_API clstr GetFirstMatch(clstr,T_REGEXP_STRING,std::vector<clstr>&,clbool caseSensitive=true);
CL_API clbool Contain(clstr str,T_REGEXP_STRING format,clbool caseSensitive=true);
CL_API clbool Match(clstr str,T_REGEXP_STRING format,clbool caseSensitive=true);
CL_API clstr Replace(clstr str,clstr from,clstr to);
CL_API void ExecuteRegex(clstr str,T_REGEXP_STRING format,std::vector<clstr>& out);
CL_API clbool IsEndedWith(clstr str,clstr subs,clbool caseSensitive=true);
CL_API clbool IsStartedWith(clstr str,clstr subs,clbool caseSensitive=true);
CL_API cluint CountNumber(clstr str,T_REGEXP_STRING format);

/**
* 返回所有符合target的字串在str中的位置。
* 如果没有返回false：
*/
CL_API clbool GetIndices(clstr str,T_REGEXP_STRING format,std::vector<cluint>& out);
}

#define F_IS_PNG_FILE(fileName) Match(fileName,".+\.png$",false)
#define F_IS_JPG_FILE(fileName) Match(fileName,".+\.jpe?g$",false)
#define F_IS_BMP_FILE(fileName) Match(fileName,".+\.bmp$",false)

#define F_IS_STRING_ALL_DECIMAL(str) Match(str,"[0-9]+")
#define F_REPLACE_BACKSLASH_TO_SLASH(str) Replace(str,"\\","/")

CL_NAMESPACE_END

