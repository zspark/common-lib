#pragma once

#include <string>
#include "clTypes.h"

namespace cl{

#define R_OK 4 /* Test for read permission. */
#define W_OK 2 /* Test for write permission. */
#define X_OK 1 /* Test for execute permission. */
#define F_OK 0 /* Test for existence. */

using namespace std;

class FolderAndFile final{


public:
  enum FFFlag{
    V_FOLDER=0x0001,
    V_FILE=0x0002,
    V_ALL=V_FILE|V_FOLDER,
    V_NO_DOT_FOLDER=0x0100,
  };
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
  static clbool Remove(const FFInfo*);

  /**
  * copy file
  * if info refers to a folder, then returns false;
  * if desFolderPath is not exist, then returns false;
  * returns true if success
  */
  static clbool CopyFileTo(const FFInfo* info,clstr desFolderPath);
  static clbool CopyFileTo(clstr fromURL,clstr toURL);
  static clbool CreateFolder(clstr folderPath);
  static clbool IsFolderExist(clstr folderPath);
  static clbool IsFileExist(clstr fileURL);
  static clstr FixPathOrURL(clstr str);

public:
  FolderAndFile();
  ~FolderAndFile();

  /**
  * cout表示有多少个文件，可不传值；
  */
  const FFInfo* Traverse(clstr rootPath,cluint flag,clint* count=nullptr);

private:
  const FFInfo* m_root;

};

typedef const FolderAndFile::FFInfo cFFInfo;

}