#pragma once

#include "clTypes.h"
#include "clRegexpUtil.h"

#define __CLLIB_INTERNAL_DEBUG__ 1


namespace cl{

//------------------------------------------------------------------------------------------
#define F_IS_PNG_FILE(fileName) clRegexp::Match(fileName,".+\.png$",false)
#define F_IS_JPG_FILE(fileName) clRegexp::Match(fileName,".+\.jpe?g$",false)
#define F_IS_BMP_FILE(fileName) clRegexp::Match(fileName,".+\.bmp$",false)

#define F_IS_STRING_ALL_DECIMAL(str) clRegexp::Match(str,"[0-9]+")
#define F_REPLACE_BACKSLASH_TO_SLASH(str) clRegexp::Replace(str,"\\","/")

//------------------------------------------------------------------------------------------

#if __CLLIB_INTERNAL_DEBUG__
#define F_DBG_ASSERT(s) if(!(s))throw "Assertion failure";
#else
#define F_DBG_ASSERT(s)
#endif

}
