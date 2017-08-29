#include <Windows.h>
#include "cllib.h"
#include "clPrinter.h"

using namespace std;

int main(){
  cl::Info("Hello World!");

  cl::Info(cl::IS_PNG_FILE("sfsf.png")?"Is":"Is not");
  

  system("pause");
  return 0;
}