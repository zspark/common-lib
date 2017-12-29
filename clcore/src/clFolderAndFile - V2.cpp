#include "core\dirent.h"
#include "cllib.h"
#include "clFolderAndFile.h"
#include "clUtil.h"
#include "clPrinter.h"

namespace cl{

inline FolderAndFile::FFInfo* CreateNewFFInfo(FolderAndFile::FFInfo* old,clI& n){
  FolderAndFile::FFInfo* info=new FolderAndFile::FFInfo();
  old->next=info;
  n++;
  return info;
}

static FolderAndFile::FFInfo* CreateAndConfigFFInfo(const dirent* entry,string rtURL,clB fileFlag,clB folderFlag){
  FolderAndFile::FFInfo* info=new FolderAndFile::FFInfo();
  switch(entry->d_type){
  case DT_REG:
    if(fileFlag){
      string nameE=string(entry->d_name);
      info->isFolder=false;
      info->fullURL=rtURL+nameE;
      clI index=nameE.find_last_of('.');
      info->nameN=index>0?nameE.substr(0,index):nameE;
      info->extension=index>0?nameE.substr(index+1):"";
    }
    break;
  case DT_DIR:
    if(folderFlag){
      string nameE=string(entry->d_name);
      info->isFolder=true;
      info->fullURL=rtURL+nameE;
      info->nameN=nameE;
      info->extension="";
    }
    break;
  default:
    break;
  }
  return info;
}

void Traveral_no_subfolder(clCcs rootURL,FolderAndFile::FFInfo* parentInfo,FolderAndFile::FFFlag flag,clI* count){
#define Info FolderAndFile::FFInfo
  DIR *pDIR;
  struct dirent *entry;
  if(pDIR=::opendir(rootURL)){
    const clB folderFlag=flag&FolderAndFile::V_FOLDER;
    const clB fileFlag=flag&FolderAndFile::V_FILE;
    Info* current=parentInfo;
    while(entry=::readdir(pDIR)){
      Info* tmp=CreateAndConfigFFInfo(entry,rootURL,fileFlag,folderFlag);
      current->next=tmp;
      current=tmp;
      (*count)++;
    }
  }
  ::closedir(pDIR);
#undef Info
}

FolderAndFile::FolderAndFile(){
  m_root=new FFInfo();
}
FolderAndFile::~FolderAndFile(){
  Release();
}

cFFInfo* FolderAndFile::Traverse(clCcs rootURL,FolderAndFile::FFFlag flag,clI* count){
  string rtURL{rootURL};
  if(!IsEndedWithSlash(rootURL)){
#ifdef __CLLIB_INTERNAL_DEBUG__
    Warning("path \""+rtURL+"\" is not ended with '/'");
#endif
    rtURL+='/';
  }
  DIR *pDIR;
  if(pDIR=::opendir(rootURL)){
    const clB folderFlag=flag&V_FOLDER;
    const clB fileFlag=flag&V_FILE;
    clI n{0};
    FFInfo* current=root;

    ::closedir(pDIR);
    if(count)*count=n;
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

}
