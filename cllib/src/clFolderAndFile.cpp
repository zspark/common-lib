#include <stdio.h>
#include <regex>
#include <corecrt_io.h>
#include "core\dirent.h"
#include "clFolderAndFile.h"
#include "clTypeUtil.h"
#include "clPrinter.h"
#include "clRegexpUtil.h"
#include "clUtil.h"

namespace cl{



inline FolderAndFile::FFInfo* CreateNewFFInfo_(FolderAndFile::FFInfo* old,clI& n){
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
          current=CreateNewFFInfo_(current,n);
          string nameE=string(entry->d_name);
          current->isFolder=false;
          current->nameE=nameE;
          current->URL=rtURL+nameE;
          current->parentPath=rtURL;
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
          current=CreateNewFFInfo_(current,n);
          string nameE=string(entry->d_name);
          current->isFolder=true;
          current->nameE=nameE;
          current->URL=rtURL+nameE;
          current->parentPath=rtURL;
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
    return ::RemoveDirectory(info->URL.c_str());
  } else return ::remove(info->URL.c_str())==0?true:false;
}

bool FolderAndFile::CopyFileTo(const FFInfo* info,string desFolderPath)const{
  if(info->isFolder)return false;
  if(IsFolderExist(desFolderPath)){
    return CopyFile(info->URL.c_str(),(desFolderPath+info->nameE).c_str(),true);
  } else return false;
}

bool FolderAndFile::CreateFolder(string folderPath)const{
  vector<string> vec;
  clTypeUtil::SplitString(folderPath.c_str(),&vec,"/");
#if(0)
  //debug;
  for(auto& iter:vec){
    cl::Unimportant(iter);
  }
#endif
  string str=vec[0];
  const clUi n=vec.size();
  for(clI i=1;i<n;i++){
    str+="/"+vec[i];
    if(!IsFolderExist(str)){
      CreateDirectory(str.c_str(),NULL);
    }
  }
  return true;
}

inline bool FolderAndFile::IsFolderExist(string folderPath)const{
  return !_access(folderPath.c_str(),F_OK);
}

inline bool FolderAndFile::IsFileExist(string fileURL)const{
  return !_access(fileURL.c_str(),R_OK);
}

string FolderAndFile::FixPathOrURL(string str)const{
  str=ReplaceBackSlashToSlash(str);
  string result=str;
  if(!IsEndedWithSlash(str)){
#ifdef __CLLIB_INTERNAL_DEBUG__
    Warning("path \""+str+"\" is not ended with '/'");
#endif
    result+='/';
  } 

  if(!clRegexp::Contain(str,"^[a~zA~Z]:")){
    if(!IsBeginnedWithDot(str)){
#ifdef __CLLIB_INTERNAL_DEBUG__
      Warning("path \""+str+"\" is not beginned with '.'");
#endif
      result="./"+result;
    }
  }
  return result;
}

}
