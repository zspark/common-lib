#pragma once

#include <string>
#include "cllib.h"

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
    clB isFolder;
    string nameN;
    string nameE;
    string URL;
    string parentPath;
    string extension;
    const FFInfo* next=nullptr;
  };

  /**
  * 移除文件，也可以移除空目录；
  * true if success;
  */
  static bool Remove(const FFInfo*);

  /**
  * copy file
  * if info refers to a folder, then returns false;
  * if desFolderPath is not exist, then returns false;
  * returns true if success
  */
  static bool CopyFileTo(const FFInfo* info,string desFolderPath);
  static bool CreateFolder(string folderPath);
  static bool IsFolderExist(string folderPath);
  static bool IsFileExist(string fileURL);
  static string FixPathOrURL(string str);

public:
  FolderAndFile();
  ~FolderAndFile();

  /**
  * cout表示有多少个文件，可不传值；
  */
  const FFInfo* Traverse(string rootPath,clUi flag,clI* count=nullptr);

private:
  const FFInfo* m_root;

};

typedef const FolderAndFile::FFInfo cFFInfo;

}