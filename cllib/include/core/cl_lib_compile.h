#pragma once

#define __CLLIB_INTERNAL_DEBUG__ 1

#if __CLLIB_INTERNAL_DEBUG__
#include "cl_console.h"
#define F_DBG_ASSERT(s) {if(!(s))throw "assertion failure";}
#define F_DBG_Info(s) {cl::clConsole::GetSingalton()->Info(s);}
#define F_DBG_Warning(s) {cl::clConsole::GetSingalton()->Warning(s);}
#define F_DBG_Error(s) {cl::clConsole::GetSingalton()->Error(s);}
#else
#define F_DBG_ASSERT(s)
#define F_DBG_Info(s)
#define F_DBG_Warning(s)
#define F_DBG_Error(s)
#endif
