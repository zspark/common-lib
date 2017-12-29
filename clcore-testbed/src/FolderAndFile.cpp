#include <Windows.h>
#include "cllib.h"
#include "clPrinter.h"
#include "clFolderAndFile.h"

using namespace std;
using namespace cl;

int main(){
  cl::Info("Hello World!");


  string rootPath="z:\\temp/folder";
  rootPath=FolderAndFile::FixPathOrURL(rootPath);
  FolderAndFile ff;
#if(0)
  if(!ff.CreateFolder("z:/tesf/sge/sfsf")){//fail;
  //if(!ff.CreateFolder("temp3/aa/")){
  //if(!ff.CreateFolder("z:/temp2/sss/aaa/")){
    cl::Error("Creating folder failed, mybe it's already exist!");
  }
  return;
#endif
  clint n;
  //cl::cFFInfo* info=ff.Traverse("z:/pbrt-v2",FolderAndFile::V_ALL,&n);
  //cl::cFFInfo* info=ff.Traverse("z:/pbrt-v2/",FolderAndFile::V_FOLDER,&n);
  //cl::cFFInfo* info=ff.Traverse("z:/pbrt-v2/",FolderAndFile::V_FILE,&n);
  //cl::cFFInfo* info=ff.Traverse("z:/temp/",FolderAndFile::V_ALL,&n);
  cl::cFFInfo* info=ff.Traverse(rootPath,FolderAndFile::V_ALL|FolderAndFile::V_NO_DOT_FOLDER,&n);


  string targetPath="z:/temp2\\folder";
  targetPath=FolderAndFile::FixPathOrURL(targetPath);
  FolderAndFile::CreateFolder(targetPath);


  while(info){
#if(1)
    if(info->isFolder){
      if(!FolderAndFile::IsFolderExist(targetPath+info->nameN))
        FolderAndFile::CreateFolder(targetPath+info->nameN);
    } else{
      if(!FolderAndFile::IsFileExist(targetPath+info->nameE)){
        if(!FolderAndFile::CopyFileTo(info,targetPath)){
          cl::Error("File: "+info->URL+" coping failed!");
        }
      }
    }
#endif

#if(0)
    if(info->isFolder)cl::Text(info->nameN);
    else cl::Text(info->nameN+"."+info->extension);
#else
    if(info->isFolder)cl::Text(info->URL,ConsoleForeground::RED);
    else cl::Text(info->URL,ConsoleForeground::GREEN);
#endif
#if(0)
    if(!ff.Remove(info)){
      cl::Error("File: "+info->URL+" did not removed!");
    }
#endif



    info=info->next;
  }
  cl::Text("TOTAL::"+clTypeUtil::NumberToString(n));

  system("pause");
  return 0;
}