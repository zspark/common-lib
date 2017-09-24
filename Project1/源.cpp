#include <iostream>
#include <vector>
#include <map>
using namespace std;

class CA{
public:
  explicit CA(int aa):a(aa){};
  int a=10;
};

class CB{
public:
  explicit CB(int aa):a(aa){};
  int a=10;
};

int main(int argc,char* argv[]){
  cout<<"Hello World"<<endl;

#if 0
  vector<CA*> vecCA;
  for(int i=0;i<3;i++){
    vecCA.push_back(new CA(i));
  }
  delete vecCA[1];
  CA* ca=vecCA[2];
#endif

#if 1
  map<CA*,CB*> mp;
  for(int i=0;i<3;i++){
    mp[new CA(i)]=new CB(i+10);
  }
#endif
  CA ca(1000);
  CB* cb=mp[&ca];// 这样查找的话，如果不存在确实会返回NULL，但同时给mp增加了新的条目ca，对应NULL；
  map<CA*,CB*>::iterator it=mp.find(&ca);

  system("pause");
  return EXIT_SUCCESS;
}