#pragma once

#include "clTypes.h"
#include <vector>

namespace cl{
namespace clRegexp{

typedef clString T_REGEXP_STRING;

/**
* ����str���״�ƥ��T_REGEXP_STRING���ַ�������ƥ�������д���������
* ���ҷ���ƥ������֮����ַ�����
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

