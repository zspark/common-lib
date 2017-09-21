#pragma once

#include <vector>
#include "cl_types.h"

namespace cl{
namespace clRegexp{

typedef clstr T_REGEXP_STRING;

/**
* ����str���״�ƥ��T_REGEXP_STRING���ַ�������ƥ�������д���������
* ���ҷ���ƥ������֮����ַ�����
*/
clstr GetFirstMatch(clstr,T_REGEXP_STRING,std::vector<clstr>&,clbool caseSensitive=true);
clbool Contain(clstr str,T_REGEXP_STRING format,clbool caseSensitive=true);
clbool Match(clstr str,T_REGEXP_STRING format,clbool caseSensitive=true);
clstr Replace(clstr str,clstr from,clstr to);
void ExecuteRegex(clstr str,T_REGEXP_STRING format,std::vector<clstr>& out);
clbool IsEndedWith(clstr str,clstr subs,clbool caseSensitive=true);
clbool IsStartedWith(clstr str,clstr subs,clbool caseSensitive=true);
cluint CountNumber(clstr str,T_REGEXP_STRING format);

/**
* �������з���target���ִ���str�е�λ�á�
* ���û�з���false��
*/
clbool GetIndices(clstr str,T_REGEXP_STRING format,std::vector<cluint>& out);
}

#define F_IS_PNG_FILE(fileName) Match(fileName,".+\.png$",false)
#define F_IS_JPG_FILE(fileName) Match(fileName,".+\.jpe?g$",false)
#define F_IS_BMP_FILE(fileName) Match(fileName,".+\.bmp$",false)

#define F_IS_STRING_ALL_DECIMAL(str) Match(str,"[0-9]+")
#define F_REPLACE_BACKSLASH_TO_SLASH(str) Replace(str,"\\","/")

}

