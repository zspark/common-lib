//#include <stdio.h>
#include <regex>
#include "clTypeUtil.h"

namespace cl{
using namespace std;

void clTypeUtil::SplitString(string s,vector<string>* vec,clCcs delimiters){
  clCs next_token;
  clCs pch=::strtok_s(const_cast<clCs>(s.c_str()),delimiters,&next_token);
  while(pch!=NULL){
    vec->push_back(pch);
    pch=::strtok_s(NULL,delimiters,&next_token);
  }
}

}