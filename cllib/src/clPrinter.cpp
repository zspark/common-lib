#include <stdio.h>
#include <iostream>
#include "clPrinter.h"

namespace cl{

using namespace std;
HANDLE static h=GetStdHandle(STD_OUTPUT_HANDLE);

void Info(const string& s){
  SetConsoleTextAttribute(h,ConsoleForeground::GREEN);
  cout<<"[Info]"+s<<endl;
  SetConsoleTextAttribute(h,ConsoleForeground::GRAY);
}

void Error(const string& s){
  SetConsoleTextAttribute(h,ConsoleForeground::RED);
  cout<<"[Error]"+s<<endl;
  SetConsoleTextAttribute(h,ConsoleForeground::GRAY);
}
void Warning(const string& s){
  SetConsoleTextAttribute(h,ConsoleForeground::YELLOW);
  cout<<"[Warning]"+s<<endl;
  SetConsoleTextAttribute(h,ConsoleForeground::GRAY);
}

void Text(const string& s,int color){
  SetConsoleTextAttribute(h,color);
  cout<<s<<endl;
  SetConsoleTextAttribute(h,ConsoleForeground::GRAY);
}
}
