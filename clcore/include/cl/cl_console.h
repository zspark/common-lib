#pragma once

#include <windows.h>
#include <vector>
#include "cl_types.h"

CL_NAMESPACE_START

namespace clConForeColor {
	enum color {
		BLACK = 0,
		DARKBLUE = FOREGROUND_BLUE,
		DARKGREEN = FOREGROUND_GREEN,
		DARKCYAN = FOREGROUND_GREEN | FOREGROUND_BLUE,
		DARKRED = FOREGROUND_RED,
		DARKMAGENTA = FOREGROUND_RED | FOREGROUND_BLUE,
		DARKYELLOW = FOREGROUND_RED | FOREGROUND_GREEN,
		DARKGRAY = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE,
		GRAY = FOREGROUND_INTENSITY,
		BLUE = FOREGROUND_INTENSITY | FOREGROUND_BLUE,
		GREEN = FOREGROUND_INTENSITY | FOREGROUND_GREEN,
		CYAN = FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_BLUE,
		RED = FOREGROUND_INTENSITY | FOREGROUND_RED,
		MAGENTA = FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE,
		YELLOW = FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN,
		WHITE = FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE,
	};
}

namespace clConBackColor {
	enum color {
		BLACK = 0,
		DARKBLUE = BACKGROUND_BLUE,
		DARKGREEN = BACKGROUND_GREEN,
		DARKCYAN = BACKGROUND_GREEN | BACKGROUND_BLUE,
		DARKRED = BACKGROUND_RED,
		DARKMAGENTA = BACKGROUND_RED | BACKGROUND_BLUE,
		DARKYELLOW = BACKGROUND_RED | BACKGROUND_GREEN,
		DARKGRAY = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE,
		GRAY = BACKGROUND_INTENSITY,
		BLUE = BACKGROUND_INTENSITY | BACKGROUND_BLUE,
		GREEN = BACKGROUND_INTENSITY | BACKGROUND_GREEN,
		CYAN = BACKGROUND_INTENSITY | BACKGROUND_GREEN | BACKGROUND_BLUE,
		RED = BACKGROUND_INTENSITY | BACKGROUND_RED,
		MAGENTA = BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_BLUE,
		YELLOW = BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN,
		WHITE = BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE,
	};
}


namespace clCon {

	typedef void(*fn_print)(DWORD currentC, clbool newline, const clstr& s, clstr mark);

	class CL_API clConsole {

	public:
		static clConsole* GetSingalton();
		static void Release();

	public:
		void Info(const clstr& s, clbool newLine = true);
		void Warning(const clstr& s, clbool newLine = true);
		void Error(const clstr& s, clbool newLine = true);

		void Text(const clstr& s, clbool newLine = true);
		void HighLightText(const clstr& s, std::vector<cluint>& pos, clint posColor
			, clbool newLine = true);
		void NewLine();

		/**
		 *  用c填充当前行剩余的位置，然后另起一行；
		 */
		void FillRestWith(clchar c);
		void UpdateLastNChars(const clstr& s, cluint n);
		void Input(clchar* c);

		void SetWorkingFlag(clbool b);
		void SetMark(clstr c) { m_mark = c; }
		void SetDefaultColor(clConForeColor::color defaultColor, clConBackColor::color backgroundColor);
		void SetInfoColor(clConForeColor::color defaultColor, clConBackColor::color backgroundColor);
		void SetWarningColor(clConForeColor::color defaultColor, clConBackColor::color backgroundColor);
		void SetErrorColor(clConForeColor::color defaultColor, clConBackColor::color backgroundColor);
		void SetInputColor(clConForeColor::color defaultColor, clConBackColor::color backgroundColor);

		void SetTitle(clstr title);

	private:
		clConsole();
		clConsole(const clConsole&) = delete;
		clConsole& operator=(const clConsole&) = delete;
		~clConsole();

	private:
		DWORD m_conDefaultColor;
		DWORD m_conInfoColor;
		DWORD m_conWarningColor;
		DWORD m_conErrorColor;
		DWORD m_conInputColor;
		DWORD m_originColor;
		cluint m_uFlag = 0u;

		clstr m_mark = "";

		fn_print m_tracer = nullptr;

	};

}

CL_NAMESPACE_END
