#ifndef DEBUG_H_INCLUDED
#define DEBUG_H_INCLUDED

#include <windows.h>
#include <string>
#include <vector>
#include "clTypes.h"

namespace ConsoleForeground{
enum{
  BLACK=0,
  DARKBLUE=FOREGROUND_BLUE,
  DARKGREEN=FOREGROUND_GREEN,
  DARKCYAN=FOREGROUND_GREEN|FOREGROUND_BLUE,
  DARKRED=FOREGROUND_RED,
  DARKMAGENTA=FOREGROUND_RED|FOREGROUND_BLUE,
  DARKYELLOW=FOREGROUND_RED|FOREGROUND_GREEN,
  DARKGRAY=FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE,
  GRAY=FOREGROUND_INTENSITY,
  BLUE=FOREGROUND_INTENSITY|FOREGROUND_BLUE,
  GREEN=FOREGROUND_INTENSITY|FOREGROUND_GREEN,
  CYAN=FOREGROUND_INTENSITY|FOREGROUND_GREEN|FOREGROUND_BLUE,
  RED=FOREGROUND_INTENSITY|FOREGROUND_RED,
  MAGENTA=FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_BLUE,
  YELLOW=FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_GREEN,
  WHITE=FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE,
};
}

namespace cl{

void Text(const clstr& s,clint color=ConsoleForeground::WHITE,clbool newLine=true);

void HighLightText(
  const clstr& s,clint color
  ,std::vector<cluint>& pos,clint posColor
  ,clbool newLine=true);

void Unimportant(const clstr& s,clbool newLine=true,clbool mark=true);
void Info(const clstr& s,clbool newLine=true,clbool mark=true);
void Warning(const clstr& s,clbool newLine=true,clbool mark=true);
void Error(const clstr& s,clbool newLine=true,clbool mark=true);
void NewLine();

}

#endif // DEBUG_H_INCLUDED
