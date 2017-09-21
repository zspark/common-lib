#include "cl_console.h"
#include <iostream>

using namespace std;

#define WORKING 1<<2

HANDLE s_handler=NULL;

void static sConsPrint_none(DWORD currentC,clbool newline,const clstr& s,clstr mark){}

void static sConsPrint(DWORD currentC,clbool newline,const clstr& s,clstr mark){
  SetConsoleTextAttribute(s_handler,currentC);
  cout<<mark;
  cout<<s;
  if(newline)cout<<endl;
}

/**
 * only works at current line
 */
void sCursorBackNChars(cluint n){
  CONSOLE_SCREEN_BUFFER_INFO bufInfo;
  GetConsoleScreenBufferInfo(s_handler,&bufInfo);
  COORD coord=bufInfo.dwCursorPosition;
  int tmp=coord.X-n;
  if(tmp<0)tmp=0;
  coord.X=tmp;
  SetConsoleCursorPosition(s_handler,coord);
}

void sCleanCurrentLineBeheadCursor(){
  CONSOLE_SCREEN_BUFFER_INFO bufInfo;
  GetConsoleScreenBufferInfo(s_handler,&bufInfo);
  COORD coord=bufInfo.dwCursorPosition;
  cluint n=bufInfo.dwSize.X-coord.X;
  WriteConsole(s_handler,"",n,NULL,NULL);
  SetConsoleCursorPosition(s_handler,coord);
}



namespace cl{

static clConsole* s_ins=nullptr;

clConsole * clConsole::GetSingalton(){
  if(s_ins)return s_ins;
  else{
    s_ins=new clConsole();
    return s_ins;
  }
}

void clConsole::Release(){
  if(s_ins)delete s_ins;
  s_handler=NULL;
  system("pause");
}

void clConsole::Info(const clstr & s,clbool newLine){
  m_tracer(m_conInfoColor,newLine,s,m_mark);
}

void clConsole::Warning(const clstr & s,clbool newLine){
  m_tracer(m_conWarningColor,newLine,s,m_mark);
}

void clConsole::Error(const clstr & s,clbool newLine){
  m_tracer(m_conErrorColor,newLine,s,m_mark);
}

void clConsole::Text(const clstr& s,clbool newLine){
  m_tracer(m_conDefaultColor,newLine,s,m_mark);
}

void clConsole::Input(clchar* c){
  if(m_uFlag&WORKING)return;
  SetConsoleTextAttribute(s_handler,m_conInputColor);
  cin.get(c,256);
  rewind(stdin);
}

void clConsole::HighLightText(
  const clstr& s,vector<cluint>& pos,clint posColor,clbool newLine)
{
  if(m_uFlag&WORKING)return;
  SetConsoleTextAttribute(s_handler,m_conDefaultColor);
  clint index=0;
  const clint N=pos.size();
  for(clint i=0;i<N;i+=2){
    clint posAti=pos[i];
    clint len=pos[i+1];
    cout<<s.substr(index,posAti-index);
    SetConsoleTextAttribute(s_handler,posColor);
    cout<<s.substr(posAti,len);
    index=posAti+len;
  }
  if(index<s.length()){
    SetConsoleTextAttribute(s_handler,m_conDefaultColor);
    cout<<s.substr(index,s.length()-index);
  }
  if(newLine)cout<<endl;
}

void clConsole::NewLine(){ cout<<endl; }

void clConsole::FillRestWith(clchar c){
  CONSOLE_SCREEN_BUFFER_INFO bufInfo;
  GetConsoleScreenBufferInfo(s_handler,&bufInfo);
  size_t N=bufInfo.dwSize.X-bufInfo.dwCursorPosition.X;
  clstr s(N,c);
  m_tracer(-1,false,s,"");
}

void clConsole::UpdateLastNChars(const clstr & s,cluint n){
  sCursorBackNChars(n);
  WriteConsole(s_handler,s.c_str(),s.length(),NULL,NULL);
}

void clConsole::SetDefaultColor(ConForeColor::color defaultColor,ConBackColor::color backgroundColor){
  m_conDefaultColor=defaultColor|backgroundColor;
}

void clConsole::SetInfoColor(ConForeColor::color defaultColor,ConBackColor::color backgroundColor){
  m_conInfoColor=defaultColor|backgroundColor;
}

void clConsole::SetWarningColor(ConForeColor::color defaultColor,ConBackColor::color backgroundColor){
  m_conWarningColor=defaultColor|backgroundColor;
}

void clConsole::SetErrorColor(ConForeColor::color defaultColor,ConBackColor::color backgroundColor){
  m_conErrorColor=defaultColor|backgroundColor;
}

void clConsole::SetInputColor(ConForeColor::color defaultColor,ConBackColor::color backgroundColor){
  m_conInputColor=defaultColor|backgroundColor;
}

void clConsole::SetTitle(clstr title){
  ::SetConsoleTitle(title.c_str());
}

void clConsole::SetWorkingFlag(clbool b){
  if(b){
    m_uFlag|=WORKING;
    m_tracer=sConsPrint_none;
  } else{
    m_uFlag&=~WORKING;
    m_tracer=sConsPrint;
  }
}

clConsole::clConsole(){
  s_handler=GetStdHandle(STD_OUTPUT_HANDLE);
  CONSOLE_SCREEN_BUFFER_INFO bufInfo;
  GetConsoleScreenBufferInfo(s_handler,&bufInfo);
  m_originColor=bufInfo.wAttributes;
  
  DWORD backColor=m_originColor&0x00F0;
  m_conDefaultColor=ConForeColor::DARKGRAY|backColor;
  m_conInfoColor=ConForeColor::GREEN|backColor;
  m_conWarningColor=ConForeColor::YELLOW|backColor;
  m_conErrorColor=ConForeColor::RED|backColor;
  m_conInputColor=ConForeColor::BLUE|ConBackColor::WHITE;

/*
  COORD coord;coord.X=80; coord.Y=10;
  SetConsoleScreenBufferSize(s_handler,coord);
  coord.X=0; coord.Y=0;
  DWORD att=ConForeColor::WHITE|ConBackColor::DARKBLUE;
  const DWORD N=bufInfo.dwSize.X*bufInfo.dwSize.Y;
  DWORD n;
  FillConsoleOutputAttribute(s_handler,att,N,coord,&n);
  */

  m_tracer=sConsPrint;
}

clConsole::~clConsole(){
  m_tracer=nullptr;
  SetConsoleTextAttribute(s_handler,m_originColor);
}

}
