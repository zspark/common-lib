#include "cl/cl_folder_file.h"
#include <stdio.h>
#include <regex>
#include <corecrt_io.h>
#include "dirent.h"
#include "cl/cl_misc.h"
#include "cl/cl_regexp_util.h"

CL_NAMESPACE_START

namespace clFF{

CL_API const FFInfo * Traverse(clstr rootPath,FFFlag flag,clint * count){
  DIR *pDIR;
  if(pDIR=::opendir(const_cast<clchar*>(rootPath.c_str()))){
    const clbool folderFlag=flag&M_FF_FOLDER;
    const clbool fileFlag=flag&M_FF_FILE;
    const clbool nodotFlag=flag&M_FF_NO_DOT_FOLDER;
    clint n{0};
    FFInfo* root=nullptr;
    FFInfo* pre=nullptr;
    FFInfo* current=nullptr;
    struct dirent *entry;
    while(entry=::readdir(pDIR)){
      switch(entry->d_type){
      case DT_REG:
        if(fileFlag){
          current=new FFInfo();
          n++;
          clstr nameE=clstr(entry->d_name);
          current->isFolder=false;
          current->nameE=nameE;
          current->URL=rootPath+nameE;
          current->parentPath=rootPath;
          clint index=nameE.find_last_of('.');
          current->nameN=index>0?nameE.substr(0,index):nameE;
          current->extension=index>0?nameE.substr(index+1):"";

          if(root){
            pre->next=current;
          } else root=current;
          pre=current;
        }
        break;
      case DT_DIR:
        if(folderFlag){
          if(nodotFlag){
            if(strcmp(entry->d_name,".")==0||strcmp(entry->d_name,"..")==0)
              continue;
          }
          current=new FFInfo();
          n++;
          clstr nameE=clstr(entry->d_name);
          current->isFolder=true;
          current->nameE=nameE;
          current->URL=rootPath+nameE;
          current->parentPath=rootPath;
          current->nameN=nameE;
          current->extension="";

          if(root){
            pre->next=current;
          } else root=current;
          pre=current;
        }
        break;
      default:
        break;
      }
    }
    ::closedir(pDIR);
    if(count)*count=n;
    return root;
  } else return nullptr;
}

void Release(const FFInfo* info){
  const FFInfo* next;
  while(info){
    next=info->next;
    delete info;
    info=next;
  }
}

clbool Remove(const FFInfo* info){
  if(info->isFolder){
    return ::RemoveDirectory(info->URL.c_str());
  } else return ::remove(info->URL.c_str())==0?true:false;
}

clbool CopyFileTo(const FFInfo* info,clstr desFolderPath){
  if(info->isFolder)return false;
  if(IsFolderExist(desFolderPath)){
    return CopyFile(info->URL.c_str(),(desFolderPath+info->nameE).c_str(),true);
  } else return false;
}

clbool CopyFileTo(clstr fromURL,clstr toURL){
  return CopyFile(fromURL.c_str(),toURL.c_str(),false);
}

clbool CreateFolder(clstr folderPath){
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

clbool IsFolderExist(clstr folderPath){
  return !_access(folderPath.c_str(),F_OK);
}

clbool IsFileExist(clstr fileURL){
  return !_access(fileURL.c_str(),R_OK);
}

clstr FixPathOrURL(clstr str){
  clstr result=clRegexp::Replace(str,"\\","/");
  if(!clRegexp::IsEndedWith(str,R"(/)")){
    result+='/';
  }

  if(!clRegexp::Contain(str,"^[a~zA~Z]:")){
    if(!clRegexp::IsStartedWith(str,R"(\.)")){
      result="./"+result;
    }
  }
  return result;
}

}
CL_NAMESPACE_END
