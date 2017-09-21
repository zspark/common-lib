#include <Windows.h>
#include "cl_console.h"

using namespace std;
using namespace cl;

int main(){

  clConsole* pcons=clConsole::GetSingalton();
  pcons->SetTitle("Hello Console!");
  pcons->Text("Hello World!");


#if 0
  //pcons->ResetColor(clcon::ConForeColor::RED,clcon::ConBackColor::YELLOW);
  pcons->UpdateLastNChars("Hello",3);
  pcons->NewLine();
  pcons->Info("this is a info!");
  pcons->Info("|",false);
  pcons->FillRestWith('=');
  pcons->Info("|");
  pcons->Info("|");
  pcons->Info("|",false);
  pcons->FillRestWith('=');
  //pcons->SetWorkingFlag(true);
  pcons->Warning("this is a warning!");
  pcons->Error("this is a error!");

#endif

#if 0
  int n=0;
  int m=1;
  while(1){
    if(n>9)m=2;
    if(n>99)m=3;
    if(n>999)m=4;

    pcons->UpdateLastNChars(clTypeUtil::NumberToString(n++),m);
    Sleep(50);
  }
#endif

#if 0
  clchar c[256];
  pcons->Input(c);
  clstr s(c);
  /*
  clchar c2[255];
  pcons->Input(c2);
  clstr s2(c2);
  */
#endif

#if 1
  for(clint i=0;i<10000;i++){
    pcons->Text("aa");
    Sleep(50);
  }
#endif

  clConsole::Release();
  return 0;
}