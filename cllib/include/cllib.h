#pragma once

#include "clTypes.h"
#include "clTypeUtil.h"

namespace cl{

#define __CLLIB_INTERNAL_DEBUG__ 1

#if __CLLIB_INTERNAL_DEBUG__
#define F_DBG_ASSERT(s) if(!(s))throw "assertion failure";
#else
#define F_DBG_ASSERT(s)
#endif

cluint GetUniqueUint();

}
