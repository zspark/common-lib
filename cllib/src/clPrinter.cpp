#include <stdio.h>
#include <iostream>
#include "clPrinter.h"

namespace cl{

using namespace std;
HANDLE static h=GetStdHandle(STD_OUTPUT_HANDLE);

void Info(const string& s){
  SetConsoleTextAttribute(h,ConsoleForeground::GREEN);
  cout<<s<<endl;
  SetConsoleTextAttribute(h,ConsoleForeground::GRAY);
}

void Error(const string& s){
  SetConsoleTextAttribute(h,ConsoleForeground::RED);
  cout<<s<<endl;
  SetConsoleTextAttribute(h,ConsoleForeground::GRAY);
}
void Warning(const string& s){
  SetConsoleTextAttribute(h,ConsoleForeground::YELLOW);
  cout<<s<<endl;
  SetConsoleTextAttribute(h,ConsoleForeground::GRAY);
}

void Text(const string& s,int color){
  SetConsoleTextAttribute(h,color);
  cout<<s<<endl;
  SetConsoleTextAttribute(h,ConsoleForeground::GRAY);
}
}
