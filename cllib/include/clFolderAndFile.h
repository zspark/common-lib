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
  FolderAndFile();
  ~FolderAndFile();

  /**
  * rootURL必须以'/'结尾，否则直接返回；
  * cout表示有多少个文件，可不传值；
  */
  const FFInfo* Traverse(clCcs rootURL,clUi flag,clI* count=nullptr);
  void Release();

  /**
  * 移除文件，也可以移除空目录；
  * true if success;
  */
  bool Remove(const FFInfo*)const;

  /**
  * copy file
  * if info refers to a folder, then returns false;
  * if desFolderPath is not exist, then returns false;
  * returns true if success
  */
  bool CopyFileTo(const FFInfo* info,string desFolderPath)const;
  bool CreateFolder(string folderPath)const;
  inline bool IsFolderExist(string folderPath)const;
  inline bool IsFileExist(string fileURL)const;

  string FixPathOrURL(string str)const;

private:
  const FFInfo* m_root;

};

typedef const FolderAndFile::FFInfo cFFInfo;

}