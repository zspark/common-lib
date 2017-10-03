#pragma once

#include <string>
#include "cl_types.h"

using namespace std;

CL_NAMESPACE_START

namespace clFF{

#define R_OK 4 /* Test for read permission. */
#define W_OK 2 /* Test for write permission. */
#define X_OK 1 /* Test for execute permission. */
#define F_OK 0 /* Test for existence. */

#define M_FF_FOLDER 1<<1
#define M_FF_FILE 1<<2
#define M_FF_ALL V_FILE|V_FOLDER
#define M_FF_NO_DOT_FOLDER 1<<3

#define FFFlag cluint

struct FFInfo{
  clbool isFolder;
  clstr nameN;
  clstr nameE;
  clstr URL;
  clstr parentPath;
  clstr extension;
  const FFInfo* next=nullptr;
};

/**
* 移除文件，也可以移除空目录；
* true if success;
*/
CL_API clbool Remove(const FFInfo*);

/**
* copy file
* if info refers to a folder, then returns false;
* if desFolderPath is not exist, then returns false;
* returns true if success
*/
CL_API clbool CopyFileTo(const FFInfo* info,clstr desFolderPath);
CL_API clbool CopyFileTo(clstr fromURL,clstr toURL);
CL_API clbool CreateFolder(clstr folderPath);
CL_API clbool IsFolderExist(clstr folderPath);
CL_API clbool IsFileExist(clstr fileURL);
CL_API clstr FixPathOrURL(clstr str);

/**
* cout表示有多少个文件，可不传值；
*/
CL_API const FFInfo* Traverse(clstr rootPath,FFFlag flag,clint* count=nullptr);

CL_API void Release(const FFInfo* info);


}
CL_NAMESPACE_END