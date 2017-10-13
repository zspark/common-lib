#include <iostream>
#include "cl3dm\cl3dm_loader.h"

using namespace std;
using namespace cl;
using namespace cl3dm;

int main(){
  cout<<"Hello World!"<<endl;


  cl3dmLoader loader;
  loader.Loader("obuma.obj");
  loader.Loader("obuma.obj");







  system("pause");
  return 0;
}