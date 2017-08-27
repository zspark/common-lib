#ifndef DEBUG_H_INCLUDED
#define DEBUG_H_INCLUDED

#include <windows.h>
#include <string>

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
void Unimportant(const std::string& s);
void Info(const std::string& s);
void Error(const std::string& s);
void Warning(const std::string& s);
void Text(const std::string& t,int color=ConsoleForeground::WHITE);
}

#endif // DEBUG_H_INCLUDED
