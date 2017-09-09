#include <stdio.h>
#include <regex>
#include <corecrt_io.h>
#include "core\dirent.h"
#include "clFolderAndFile.h"
#include "clTypeUtil.h"
#include "clPrinter.h"
#include "clRegexpUtil.h"

namespace cl{


void Release_(const FolderAndFile::FFInfo* rootInfo){
  const FolderAndFile::FFInfo* next;
  while(rootInfo){
    next=rootInfo->next;
    delete rootInfo;
    rootInfo=next;
  }
}


inline FolderAndFile::FFInfo* CreateNewFFInfo_(FolderAndFile::FFInfo* old,clint& n){
  FolderAndFile::FFInfo* info=new FolderAndFile::FFInfo();
  old->next=info;
  n++;
  return info;
}

FolderAndFile::FolderAndFile(){}
FolderAndFile::~FolderAndFile(){
  Release_(m_root);
}

cFFInfo* FolderAndFile::Traverse(clstr rootPath,cluint flag,clint* count){
  Release_(m_root);
  DIR *pDIR;
  struct dirent *entry;
  if(pDIR=::opendir(const_cast<clchar*>(rootPath.c_str()))){
    const clbool folderFlag=flag&V_FOLDER;
    const clbool fileFlag=flag&V_FILE;
    const clbool nodotFlag=flag&V_NO_DOT_FOLDER;
    clint n{0};
    FFInfo* root=new FFInfo();
    FFInfo* current=root;
    while(entry=::readdir(pDIR)){
      switch(entry->d_type){
      case DT_REG:
        if(fileFlag){
          current=CreateNewFFInfo_(current,n);
          clstr nameE=clstr(entry->d_name);
          current->isFolder=false;
          current->nameE=nameE;
          current->URL=rootPath+nameE;
          current->parentPath=rootPath;
          clint index=nameE.find_last_of('.');
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
          clstr nameE=clstr(entry->d_name);
          current->isFolder=true;
          current->nameE=nameE;
          current->URL=rootPath+nameE;
          current->parentPath=rootPath;
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

clbool FolderAndFile::Remove(const FFInfo* info){
  if(info->isFolder){
    return ::RemoveDirectory(info->URL.c_str());
  } else return ::remove(info->URL.c_str())==0?true:false;
}

clbool FolderAndFile::CopyFileTo(const FFInfo* info,clstr desFolderPath){
  if(info->isFolder)return false;
  if(IsFolderExist(desFolderPath)){
    return CopyFile(info->URL.c_str(),(desFolderPath+info->nameE).c_str(),true);
  } else return false;
}

clbool FolderAndFile::CopyFileTo(clstr fromURL,clstr toURL){
  return CopyFile(fromURL.c_str(),toURL.c_str(),false);
}

clbool FolderAndFile::CreateFolder(clstr folderPath){
  vector<clstr> vec;
  clTypeUtil::SplitString(folderPath.c_str(),vec,"/");
#if(0)
  //debug;
  for(auto& iter:vec){
    cl::Unimportant(iter);
  }
#endif
  clstr str=vec[0];
  const cluint n=vec.size();
  for(clint i=1;i<n;i++){
    str+="/"+vec[i];
    if(!IsFolderExist(str)){
      CreateDirectory(str.c_str(),NULL);
    }
  }
  return true;
}

clbool FolderAndFile::IsFolderExist(clstr folderPath){
  return !_access(folderPath.c_str(),F_OK);
}

clbool FolderAndFile::IsFileExist(clstr fileURL){
  return !_access(fileURL.c_str(),R_OK);
}

clstr FolderAndFile::FixPathOrURL(clstr str){
  clstr result=clRegexp::Replace(str,"\\","/");
  if(!clRegexp::IsEndedWith(str,R"(/)")){
#ifdef __CLLIB_INTERNAL_DEBUG__
    Warning("path \""+str+"\" is not ended with '/'");
#endif
    result+='/';
  } 

  if(!clRegexp::Contain(str,"^[a~zA~Z]:")){
    if(!clRegexp::IsStartedWith(str,R"(\.)")){
#ifdef __CLLIB_INTERNAL_DEBUG__
      Warning("path \""+str+"\" is not beginned with '.'");
#endif
      result="./"+result;
    }
  }
  return result;
}

}
