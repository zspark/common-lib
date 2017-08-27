#include <stdio.h>
#include <corecrt_io.h>
#include "core\dirent.h"
#include "cllib.h"
#include "clFolderAndFile.h"
#include "clUtil.h"
#include "clPrinter.h"

namespace cl{

inline string CheckPath(string path){
  if(!IsEndedWithSlash(path)){
#ifdef __CLLIB_INTERNAL_DEBUG__
    Warning("path \""+path+"\" is not ended with '/'");
#endif
    return path+'/';
  } else return path;
}

inline FolderAndFile::FFInfo* CreateNewFFInfo(FolderAndFile::FFInfo* old,clI& n){
  FolderAndFile::FFInfo* info=new FolderAndFile::FFInfo();
  old->next=info;
  n++;
  return info;
}

FolderAndFile::FolderAndFile(){}
FolderAndFile::~FolderAndFile(){
  Release();
}

cFFInfo* FolderAndFile::Traverse(clCcs rootURL,clUi flag,clI* count){
  string rtURL{rootURL};
  rtURL=CheckPath(rtURL);
  Release();
  DIR *pDIR;
  struct dirent *entry;
  if(pDIR=::opendir(rootURL)){
    const clB folderFlag=flag&V_FOLDER;
    const clB fileFlag=flag&V_FILE;
    const clB nodotFlag=flag&V_NO_DOT_FOLDER;
    clI n{0};
    FFInfo* root=new FFInfo();
    FFInfo* current=root;
    while(entry=::readdir(pDIR)){
      switch(entry->d_type){
      case DT_REG:
        if(fileFlag){
          current=CreateNewFFInfo(current,n);
          string nameE=string(entry->d_name);
          current->isFolder=false;
          current->nameE=nameE;
          current->fullURL=rtURL+nameE;
          current->fullPath=rtURL;
          clI index=nameE.find_last_of('.');
          current->nameN=index>0?nameE.substr(0,index):nameE;
          current->extension=index>0?nameE.substr(index+1):"";
        }
        break;
      case DT_DIR:
        if(folderFlag){
          if(nodotFlag){
            if(strcmp(entry->d_name,".")==0||strcmp(entry->d_name,"..")==0)
              continue;
          }
          current=CreateNewFFInfo(current,n);
          string nameE=string(entry->d_name);
          current->isFolder=true;
          current->nameE=nameE;
          current->fullURL=rtURL+nameE;
          current->fullPath=rtURL;
          current->nameN=nameE;
          current->extension="";
        }
        break;
      default:
        break;
      }
    }
    ::closedir(pDIR);
    if(count)*count=n;
    m_root=root;
    return m_root->next;
  } else return nullptr;
}
void FolderAndFile::Release(){
  cFFInfo* next;
  while(m_root){
    next=m_root->next;
    delete m_root;
    m_root=next;
  }
}
bool FolderAndFile::Remove(const FFInfo* info)const{
  if(info->isFolder){
    return ::RemoveDirectory(info->fullURL.c_str());
  } else return ::remove(info->fullURL.c_str())==0?true:false;
}
bool FolderAndFile::Copy(const FFInfo* info,string desFolderURL)const{
  desFolderURL=CheckPath(desFolderURL);
  if(info->isFolder){}
  else return CopyFile(info->fullURL.c_str(),(desFolderURL+info->nameE).c_str(),true);
}
bool FolderAndFile::CreateFolder(string folderPath)const{
  folderPath=CheckPath(folderPath);
  return CreateDirectory(folderPath.c_str(),NULL);
}
inline bool FolderAndFile::IsFolderExist(string folderPath)const{
  return !_access(folderPath.c_str(),F_OK);
}

inline bool FolderAndFile::IsFileExist(string fileURL)const{
  return !_access(fileURL.c_str(),R_OK);
}

}
