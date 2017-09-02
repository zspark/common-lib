#include <stdio.h>
#include <iostream>
#include "clPrinter.h"

namespace cl{

using namespace std;

HANDLE static h=GetStdHandle(STD_OUTPUT_HANDLE);

void Unimportant(const clstr& s,clbool newLine,clbool mark){
  SetConsoleTextAttribute(h,ConsoleForeground::GRAY);
  if(mark)cout<<"[Unimportant] ";
  cout<<s;
  if(newLine)cout<<endl;
  //SetConsoleTextAttribute(h,ConsoleForeground::GRAY);
}

void Info(const clstr& s,clbool newLine,clbool mark){
  SetConsoleTextAttribute(h,ConsoleForeground::GREEN);
  if(mark)cout<<"[Info] ";
  cout<<s;
  if(newLine)cout<<endl;
  SetConsoleTextAttribute(h,ConsoleForeground::GRAY);
}

void Error(const clstr& s,clbool newLine,clbool mark){
  SetConsoleTextAttribute(h,ConsoleForeground::RED);
  if(mark)cout<<"[Error] ";
  cout<<s;
  if(newLine)cout<<endl;
  SetConsoleTextAttribute(h,ConsoleForeground::GRAY);
}
void Warning(const clstr& s,clbool newLine,clbool mark){
  SetConsoleTextAttribute(h,ConsoleForeground::YELLOW);
  if(mark)cout<<"[Warning] ";
  cout<<s;
  if(newLine)cout<<endl;
  SetConsoleTextAttribute(h,ConsoleForeground::GRAY);
}

void Text(const clstr& s,clint color,clbool newLine){
  SetConsoleTextAttribute(h,color);
  cout<<s;
  if(newLine)cout<<endl;
  SetConsoleTextAttribute(h,ConsoleForeground::GRAY);
}

void HighLightText(
  const clstr& s,clint color
  ,vector<cluint>& pos,clint posColor,clbool newLine){
  clint index=0;
  const clint n=pos.size();
  for(clint i=0;i<n;i+=2){
    clint posAti=pos[i];
    clint len=pos[i+1];
    SetConsoleTextAttribute(h,color);
    cout<<s.substr(index,posAti-index);
    SetConsoleTextAttribute(h,posColor);
    cout<<s.substr(posAti,len);
    index=posAti+len;
  }
  if(index<s.length()){
    SetConsoleTextAttribute(h,color);
    cout<<s.substr(index,s.length()-index);
  }

  if(newLine)cout<<endl;
  SetConsoleTextAttribute(h,ConsoleForeground::GRAY);
}

void NewLine(){ cout<<endl; }

}
