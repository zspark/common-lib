#include <stdio.h>
#include <iostream>
#include "clPrinter.h"

namespace cl{

using namespace std;
HANDLE static h=GetStdHandle(STD_OUTPUT_HANDLE);

void Unimportant(const clString& s){
  SetConsoleTextAttribute(h,ConsoleForeground::GRAY);
  cout<<"[Unimportant] "+s<<endl;
  //SetConsoleTextAttribute(h,ConsoleForeground::GRAY);
}

void Info(const clString& s){
  SetConsoleTextAttribute(h,ConsoleForeground::GREEN);
  cout<<"[Info] "+s<<endl;
  SetConsoleTextAttribute(h,ConsoleForeground::GRAY);
}

void Error(const clString& s){
  SetConsoleTextAttribute(h,ConsoleForeground::RED);
  cout<<"[Error] "+s<<endl;
  SetConsoleTextAttribute(h,ConsoleForeground::GRAY);
}
void Warning(const clString& s){
  SetConsoleTextAttribute(h,ConsoleForeground::YELLOW);
  cout<<"[Warning] "+s<<endl;
  SetConsoleTextAttribute(h,ConsoleForeground::GRAY);
}

void Text(const clString& s,int color){
  SetConsoleTextAttribute(h,color);
  cout<<s<<endl;
  SetConsoleTextAttribute(h,ConsoleForeground::GRAY);
}

void HighLightText(const clString& s,clI color,vector<clUi>& pos,clI posColor){
  clI index=0;
  const clI n=pos.size();
  for(clI i=0;i<n;i+=2){
    clI posAti=pos[i];
    clI len=pos[i+1];
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

  cout<<endl;
  SetConsoleTextAttribute(h,ConsoleForeground::GRAY);
}

}
