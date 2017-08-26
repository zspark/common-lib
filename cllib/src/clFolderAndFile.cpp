#include "core\dirent.h"
#include "clFolderAndFile.h"

namespace cl{

inline FolderAndFile::FFInfo* CreateNewFFInfo(FolderAndFile::FFInfo* old,clI& n){
  FolderAndFile::FFInfo* info=new FolderAndFile::FFInfo();
  old->next=info;
  n++;
  return info;
}

FolderAndFile::FolderAndFile(){}
FolderAndFile::~FolderAndFile(){}

cFFInfo* FolderAndFile::Traverse(clCcs rootURL,FolderAndFile::FFFlag flag,clI* count){
  DIR *pDIR;
  struct dirent *entry;
  if(pDIR=::opendir(rootURL)){
    const clB folderFlag=flag&V_FOLDER;
    const clB fileFlag=flag&V_FILE;
    clI n{0};
    FFInfo* root=new FFInfo();
    FFInfo* current=root;
    while(entry=::readdir(pDIR)){
      switch(entry->d_type){
      case DT_REG:
      {
        if(fileFlag){
          current=CreateNewFFInfo(current,n);
          string nameE=string(entry->d_name);
          current->isFolder=false;
          current->fullURL=(string)rootURL+"/"+nameE;
          clI index=nameE.find_last_of('.');
          current->nameN=index>0?nameE.substr(0,index):nameE;
          current->extension=index>0?nameE.substr(index+1):"";
        }
      }
      break;
      case DT_DIR:
        if(folderFlag){
          current=CreateNewFFInfo(current,n);
          string nameE=string(entry->d_name);
          current->isFolder=true;
          current->fullURL=(string)rootURL+"/"+nameE;
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

}
