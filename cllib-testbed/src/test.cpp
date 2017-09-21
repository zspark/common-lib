#include <Windows.h>
#include "cl_types.h"
#include "cl_console.h"

using namespace std;
using namespace cl;

#define T(s) clConsole::GetSingalton()->Text(s);

int main(){
  T("Hello World!");

  //cl::Info(cl::IS_PNG_FILE("sfsf.png")?"Is":"Is not");
  

  system("pause");
  return 0;
}