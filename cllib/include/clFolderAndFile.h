#pragma once

#include <string>
#include "clTypes.h"

namespace cl{

using namespace std;

class FolderAndFile final{
public:
  enum FFFlag{
    V_FOLDER=0x0001,
    V_FILE=0x0002,
    V_ALL=V_FILE|V_FOLDER,
    V_SUBFOLDER=0x0100,
  };
  struct FFInfo{
    clB isFolder;
    string nameN;
    string fullURL;
    string extension;
    const FFInfo* next=nullptr;
  };
  FolderAndFile();
  ~FolderAndFile();

  /**
  * rootURL必须以'/'结尾，否则直接返回；
  * cout表示有多少个文件，可不传值；
  */
  const FFInfo* Traverse(clCcs rootURL,FFFlag flag,clI* count=nullptr);
  void Release();

private:
  const FFInfo* m_root;

};

typedef const FolderAndFile::FFInfo cFFInfo;

}