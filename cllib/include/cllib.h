#pragma once

#include "clTypes.h"
#include "clTypeUtil.h"

#define __CLLIB_INTERNAL_DEBUG__ 1


namespace cl{


//------------------------------------------------------------------------------------------

#if __CLLIB_INTERNAL_DEBUG__
#define F_DBG_ASSERT(s) if(!(s))throw "assertion failure";
#else
#define F_DBG_ASSERT(s)
#endif

}
