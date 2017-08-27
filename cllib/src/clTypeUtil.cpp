//#include <stdio.h>
#include "clTypeUtil.h"

namespace cl{
using namespace std;

void clTypeUtil::SplitString(clCs s,vector<string>* vec,clCcs delimiters){
  rsize_t strmax=sizeof(s);
  clCs next_token;
  clCs pch=::strtok_s(s,delimiters,&next_token);
  while(pch!=NULL){
    vec->push_back(pch);
    pch=::strtok_s(NULL,delimiters,&next_token);
  }
}

}